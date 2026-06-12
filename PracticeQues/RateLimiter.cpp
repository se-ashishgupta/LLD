#include <iostream>
#include <unordered_map>
#include <queue>
#include <memory>
#include <chrono>
#include <mutex>

using namespace std;

//======================================================
// USER TIERS
//======================================================

enum class Tier
{
    FREE,
    PREMIUM
};

class UserTier
{
public:
    virtual int getLimit() const = 0;
    virtual ~UserTier() = default;
};

class FreeTier : public UserTier
{
public:
    int getLimit() const override
    {
        return 5;
    }
};

class PremiumTier : public UserTier
{
public:
    int getLimit() const override
    {
        return 100;
    }
};

//======================================================
// USER
//======================================================

class User
{
private:
    string userId;
    unique_ptr<UserTier> tier;

public:
    User(string id, unique_ptr<UserTier> t)
        : userId(id), tier(move(t)) {}

    string getUserId() const
    {
        return userId;
    }

    int getLimit() const
    {
        return tier->getLimit();
    }
};

//======================================================
// STRATEGY
//======================================================

class IRateLimiter
{
public:
    virtual bool allowRequest(const User &user) = 0;
    virtual ~IRateLimiter() = default;
};

//======================================================
// FIXED WINDOW
//======================================================

class FixedWindowLimiter : public IRateLimiter
{

private:
    struct RequestInfo
    {
        int count = 0;
        chrono::steady_clock::time_point startTime;
    };

    unordered_map<string, RequestInfo> requests;
    mutex mtx;

    int windowSizeSeconds;

public:
    FixedWindowLimiter(int window = 60)
        : windowSizeSeconds(window) {}

    bool allowRequest(const User &user) override
    {

        lock_guard<mutex> lock(mtx);

        auto now = chrono::steady_clock::now();

        auto &data = requests[user.getUserId()];

        if (data.count == 0)
        {
            data.startTime = now;
        }

        auto elapsed =
            chrono::duration_cast<chrono::seconds>(
                now - data.startTime)
                .count();

        if (elapsed >= windowSizeSeconds)
        {
            data.count = 0;
            data.startTime = now;
        }

        if (data.count < user.getLimit())
        {
            data.count++;
            return true;
        }

        return false;
    }
};

//======================================================
// SLIDING WINDOW
//======================================================

class SlidingWindowLimiter : public IRateLimiter
{

private:
    unordered_map<
        string,
        queue<chrono::steady_clock::time_point>>
        requests;

    mutex mtx;

    int windowSizeSeconds;

public:
    SlidingWindowLimiter(int window = 60)
        : windowSizeSeconds(window) {}

    bool allowRequest(const User &user) override
    {

        lock_guard<mutex> lock(mtx);

        auto now = chrono::steady_clock::now();

        auto &q = requests[user.getUserId()];

        while (!q.empty())
        {

            auto age =
                chrono::duration_cast<chrono::seconds>(
                    now - q.front())
                    .count();

            if (age >= windowSizeSeconds)
                q.pop();
            else
                break;
        }

        if ((int)q.size() < user.getLimit())
        {
            q.push(now);
            return true;
        }

        return false;
    }
};

//======================================================
// TOKEN BUCKET
//======================================================

class TokenBucketLimiter : public IRateLimiter
{

private:
    struct Bucket
    {

        double tokens;
        chrono::steady_clock::time_point lastRefill;

        Bucket(double capacity)
            : tokens(capacity),
              lastRefill(chrono::steady_clock::now()) {}
    };

    unordered_map<string, Bucket> buckets;

    mutex mtx;

public:
    bool allowRequest(const User &user) override
    {

        lock_guard<mutex> lock(mtx);

        auto now = chrono::steady_clock::now();

        int capacity = user.getLimit();

        if (buckets.find(user.getUserId()) == buckets.end())
        {

            buckets.emplace(
                user.getUserId(),
                Bucket(capacity));
        }

        auto &bucket = buckets[user.getUserId()];

        auto elapsed =
            chrono::duration_cast<chrono::seconds>(
                now - bucket.lastRefill)
                .count();

        double refillRate =
            (double)capacity / 60.0;

        bucket.tokens =
            min(
                (double)capacity,
                bucket.tokens +
                    elapsed * refillRate);

        bucket.lastRefill = now;

        if (bucket.tokens >= 1)
        {
            bucket.tokens -= 1;
            return true;
        }

        return false;
    }
};

//======================================================
// FACTORY
//======================================================

enum class LimiterType
{
    FIXED_WINDOW,
    SLIDING_WINDOW,
    TOKEN_BUCKET
};

class LimiterFactory
{

public:
    static unique_ptr<IRateLimiter>
    createLimiter(LimiterType type)
    {

        switch (type)
        {

        case LimiterType::FIXED_WINDOW:
            return make_unique<FixedWindowLimiter>();

        case LimiterType::SLIDING_WINDOW:
            return make_unique<SlidingWindowLimiter>();

        case LimiterType::TOKEN_BUCKET:
            return make_unique<TokenBucketLimiter>();

        default:
            throw invalid_argument("Invalid type");
        }
    }
};

//======================================================
// CONTEXT
//======================================================

class RateLimiter
{

private:
    unique_ptr<IRateLimiter> strategy;

public:
    RateLimiter(
        unique_ptr<IRateLimiter> limiter)
        : strategy(move(limiter)) {}

    bool allow(const User &user)
    {
        return strategy->allowRequest(user);
    }
};

//======================================================
// CLIENT
//======================================================

int main()
{

    User freeUser(
        "user1",
        make_unique<FreeTier>());

    User premiumUser(
        "user2",
        make_unique<PremiumTier>());

    auto limiter =
        LimiterFactory::createLimiter(
            LimiterType::TOKEN_BUCKET);

    RateLimiter rateLimiter(
        move(limiter));

    cout << "Free User\n";

    for (int i = 1; i <= 7; i++)
    {

        cout
            << "Request "
            << i
            << " : "
            << (rateLimiter.allow(freeUser)
                    ? "Allowed"
                    : "Blocked")
            << endl;
    }

    cout << "\nPremium User\n";

    for (int i = 1; i <= 7; i++)
    {

        cout
            << "Request "
            << i
            << " : "
            << (rateLimiter.allow(premiumUser)
                    ? "Allowed"
                    : "Blocked")
            << endl;
    }

    return 0;
}
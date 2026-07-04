#include <iostream>
#include <vector>
#include <map>

using namespace std;

// enums

enum class PlyerType
{
    BATSMAN,
    BOWLER,
    ALLROUNDER,
    WICKETKEEPER,
    CAPTAIN
};

enum class WicketType
{
    BOWLED,
    CAUGHT,
    LBW,
    RUNOUT,
    STUMPED
};

enum class BallType
{
    NORMAL,
    WIDEBALL,
    NOBALL
};

enum class RunType
{
    DOTBALL,
    SINGLE,
    DOUBLE,
    TRIPLE,
    FOUR,
    SIX
};

class MatchType
{
public:
    virtual int noOfOvers() = 0;
    virtual int maxOverCountBowlers() = 0;
    virtual ~MatchType() = default;
};

class OneDayMatch : public MatchType
{
public:
    int noOfOvers() override
    {
        return 50;
    }

    int maxOverCountBowlers() override
    {
        return 10;
    }
};

class T20Match : public MatchType
{
public:
    int noOfOvers() override
    {
        return 20;
    }

    int maxOverCountBowlers() override
    {
        return 4;
    }
};

// Ball Details
class BallDetails
{
    int ballNumber;
    BallType ballType;
    RunType runType;
    PlayerDetails playedBy;
    PlayerDetails bowledBy;
    Wicket wicket;
};

// Over Details
class OverDetails
{
    int overNumber;
};

// Player class
class Person
{
public:
    string name;
    int age;
    string address;
};

class Wicket
{
    WicketType wicketType;
    PlayerDetails takenBy;
    OverDetails overDetails;
    BallDetails ballDetails;
};

class BattingScoreCard
{
    int totalRuns;
    int totalBallsPlayed;
    int totalFours;
    int totalSixes;
    double strikeRate;
    Wicket wicketDetails;
};

class PlayerDetails
{
    Person person;
    PlyerType playerType;
    BattingScoreCard battingScoreCard;
};

int main()
{
    return 0;
}
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class IColleague
{
public:
    virtual void placeBid(double bidAmount) = 0;
    virtual void receiveBidNotification(double bidAmount) = 0;
    virtual string getName() = 0;
    virtual ~IColleague() = default;
};

class AuctionMediator
{
public:
    virtual void registerBidder(class IColleague *colleague) = 0;
    virtual void placeBid(IColleague *bidder, double bidAmount) = 0;
    virtual void closeAuction() = 0;

    virtual ~AuctionMediator() = default;
};

class AutionHouse : public AuctionMediator
{
private:
    vector<IColleague *> bidders;
    string itemName;
    double highestBid;
    IColleague *highestBidder;

public:
    AutionHouse(string itemName)
    {
        this->itemName = itemName;
        this->highestBid = 0.0;
        this->highestBidder = nullptr;
        cout << "Auction House created for item: " << itemName << endl;
    }

    void registerBidder(IColleague *colleague) override
    {
        bidders.push_back(colleague);
        cout << "Bidder registered: " << colleague->getName() << endl;
    }

    void placeBid(IColleague *bidder, double bidAmount) override
    {
        if (bidAmount > highestBid)
        {
            highestBid = bidAmount;
            highestBidder = bidder;
            cout << "New highest bid: " << bidAmount << " by " << bidder->getName() << endl;

            // Notify all bidders about the new highest bid
            for (IColleague *b : bidders)
            {
                if (b != bidder)
                {
                    b->receiveBidNotification(bidAmount);
                }
            }
        }
        else
        {
            cout << "Bid of " << bidAmount << " by " << bidder->getName() << " is lower than the current highest bid of " << highestBid << endl;
        }
    }
    void closeAuction() override
    {
        cout << "Auction closed for item: " << itemName << endl;
        if (highestBidder)
        {
            cout << "Winner: " << highestBidder->getName() << " with a bid of " << highestBid << endl;
        }
        else
        {
            cout << "No bids were placed." << endl;
        }
    }
};

class Bidder : public IColleague
{
private:
    string name;
    AuctionMediator *mediator;

public:
    Bidder(string bidderName, AuctionMediator *auctionMediator)
    {
        this->name = bidderName;
        this->mediator = auctionMediator;
    }

    void placeBid(double bidAmount) override
    {
        mediator->placeBid(this, bidAmount);
    }

    void receiveBidNotification(double bidAmount) override
    {
        cout << "Bidder " << name << " received notification: New highest bid is " << bidAmount << endl;
    }

    string getName() override
    {
        return name;
    }
};

int main()
{
    cout << "###### Mediator Design Pattern Demo ######\n";

    AutionHouse *auctionHouse = new AutionHouse("Antique Vase");

    Bidder *bidder1 = new Bidder("Alice", auctionHouse);
    Bidder *bidder2 = new Bidder("Bob", auctionHouse);
    Bidder *bidder3 = new Bidder("Charlie", auctionHouse);
    Bidder *bidder4 = new Bidder("Amit", auctionHouse);

    auctionHouse->registerBidder(bidder1);
    auctionHouse->registerBidder(bidder2);
    auctionHouse->registerBidder(bidder3);
    auctionHouse->registerBidder(bidder4);

    bidder1->placeBid(100);
    bidder2->placeBid(400);
    bidder3->placeBid(500);
    bidder4->placeBid(900);

    auctionHouse->closeAuction();

    return 0;
}
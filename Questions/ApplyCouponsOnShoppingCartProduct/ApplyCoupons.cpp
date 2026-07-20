#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>

using namespace std;

enum class ProductType
{
    FURNITURE,
    ELECTRONICS,
    GROCERY,
    CLOTHING,
    PHARMACY
};

class Product
{
protected:
    string name;
    double originalPrice;
    ProductType type;

public:
    Product(string name, double price, ProductType type)
    {
        this->name = name;
        this->originalPrice = price;
        this->type = type;
    }

    virtual double getPrice() = 0;

    ProductType getType()
    {
        return type;
    }

    string getName()
    {
        return name;
    }

    double getOriginalPrice() const
    {
        return originalPrice;
    }

    virtual ~Product() = default;
};

class Item1 : public Product
{
public:
    Item1(string name, double price, ProductType type) : Product(name, price, type)
    {
    }

    double getPrice() override
    {
        return originalPrice;
    }
};

class Item2 : public Product
{
public:
    Item2(string name, double price, ProductType type) : Product(name, price, type)
    {
    }

    double getPrice() override
    {
        return originalPrice;
    }
};

class CouponDecorator : public Product
{
protected:
    Product *product;
    int discountPercentage;

public:
    CouponDecorator(Product *product, int discountPercentage) : Product(product->getName(), product->getOriginalPrice(), product->getType())
    {
        this->product = product;
        this->discountPercentage = discountPercentage;
    }
};

class PercentageCouponDecorator : public CouponDecorator
{

public:
    PercentageCouponDecorator(Product *product, int percentage) : CouponDecorator(product, percentage) {}

    double getPrice() override
    {
        double price = this->product->getPrice();
        double priceAfterDiscount = price - (price * discountPercentage) / 100;
        cout << "Applying percentage coupon of " << discountPercentage << "% on " << product->getName() << ", original price : " << price << ", price after discount : " << priceAfterDiscount << endl;
        return priceAfterDiscount;
    }
};

class TypeCouponDecorator : public CouponDecorator
{
protected:
    static vector<ProductType> eligibleTypes;

public:
    TypeCouponDecorator(Product *product, int percentage) : CouponDecorator(product, percentage)
    {
    }

    double getPrice() override
    {
        double price = this->product->getPrice();

        if (find(eligibleTypes.begin(), eligibleTypes.end(),
                 product->getType()) != eligibleTypes.end())
        {

            double discountedPrice =
                price - (price * discountPercentage) / 100.0;

            cout << "Applying specific product type coupon of "
                 << discountPercentage << "% on "
                 << product->getName()
                 << ", original price : " << price
                 << ", price after discount : " << discountedPrice
                 << endl;

            return discountedPrice;
        }

        return price;
    }
};

// Static member initialization
vector<ProductType> TypeCouponDecorator::eligibleTypes = {
    ProductType::FURNITURE,
    ProductType::ELECTRONICS};

class ShoppingCart
{
protected:
    vector<Product *> productList;

public:
    ShoppingCart()
    {
    }

    void addToCart(Product *product)
    {
        Product *productWithEligibleDiscount = new TypeCouponDecorator(new PercentageCouponDecorator(product, 20), 10);
        productList.push_back(productWithEligibleDiscount);
    }

    double getTotalPrice()
    {
        double totalPrice = 0;

        for (Product *product : productList)
        {
            totalPrice += product->getPrice();
        }

        return totalPrice;
    }
};

int main()
{
    cout << "\n###### LLD - Coupon Application System Demo ######\n"
         << endl;

    // Create Products
    Product *item1 = new Item1("Fan", 1500, ProductType::ELECTRONICS);
    Product *item2 = new Item2("Office Chair", 6000, ProductType::FURNITURE);
    Product *item3 = new Item2("Omega3-Tabs", 600, ProductType::PHARMACY);
    Product *item4 = new Item1("Shirt", 1200, ProductType::CLOTHING);

    // Shopping Cart
    ShoppingCart cart;
    cart.addToCart(item1);
    cart.addToCart(item2);
    cart.addToCart(item3);
    cart.addToCart(item4);

    // Calculate Total Price
    cout << "\n===>>> Total Price after discount: " << endl
         << cart.getTotalPrice() << endl;

    // Cleanup
    delete item1;
    delete item2;
    delete item3;
    delete item4;

    return 0;
}
#include <iostream>
#include <vector>
using namespace std;

// Open-Closed Principle: Software entities (classes, modules, functions, etc.) should be open for extension but closed for modification.

class Product
{
public:
    string name;
    int price;

    Product(string name, int price)
    {
        this->name = name;
        this->price = price;
    }
};

class ShoppingCart
{
private:
    vector<Product *> product;

public:
    void addToCart(Product *p)
    {
        this->product.push_back(p);
    }

    const vector<Product *> &getProducts() const
    {
        return product;
    }

    double calculateTotalPrice()
    {
        double total = 0;
        for (auto p : this->getProducts())
        {
            total += p->price;
        }
        return total;
    }
};

class InvoiceGenerator
{
private:
    ShoppingCart *cart;

public:
    InvoiceGenerator(ShoppingCart *cart)
    {
        this->cart = cart;
    }

    void generateInvoice()
    {
        cout << "Invoice:" << endl;
        for (auto p : cart->getProducts())
        {
            cout << p->name << ": $" << p->price << endl;
        }
        cout << "Total: $" << cart->calculateTotalPrice() << endl;
    }
};

class Persistence
{
private:
    ShoppingCart *cart;

public:
    virtual void save(ShoppingCart *cart) = 0; // pure virtual function
};

class SQLPersistence : public Persistence
{
public:
    void save(ShoppingCart *cart) override
    {
        cout << "Saving shopping cart to SQL DB.." << endl;
    }
};

class MongoPersistence : public Persistence
{
public:
    void save(ShoppingCart *cart) override
    {
        cout << "Saving shopping cart to Mongo DB.." << endl;
    }
};

class FilePersistence : public Persistence
{
public:
    void save(ShoppingCart *cart) override
    {
        cout << "Saving shopping cart to File.." << endl;
    }
};

int main()
{

    Product *p1 = new Product("Macbook", 900000);
    Product *p2 = new Product("Keyboard", 20000);

    ShoppingCart *cart = new ShoppingCart();
    cart->addToCart(p1);
    cart->addToCart(p2);

    InvoiceGenerator *invoice = new InvoiceGenerator(cart);
    invoice->generateInvoice();

    Persistence *sql = new SQLPersistence();
    Persistence *mongo = new MongoPersistence();
    Persistence *file = new FilePersistence();

    sql->save(cart);
    mongo->save(cart);
    file->save(cart);

    return 0;
}
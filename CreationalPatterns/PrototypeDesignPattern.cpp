#include <iostream>
using namespace std;

// Abstract base class representing a prototype for products
class ProductPrototype
{
public:
    virtual ProductPrototype *clone() = 0;
    virtual void display() = 0;
    virtual void setName(const string &s) = 0;
    virtual ~ProductPrototype() {} // this is used to properly destroy derived class objects using base class pointers
};

// Concrete prototype class representing a product
class Product : public ProductPrototype
{
private:
    string name;
    double price;

public:
    Product(const string &name, double price)
        : name(name), price(price) {}

    ProductPrototype *clone() override // returning pointer to base class instead of current class
    {
        return new Product(*this); // Copy constructor used for cloning , this will do a deep copy in C++
    }

    void display() override
    {
        cout << "Product: " << name << endl;
        cout << "Price: $" << price << endl;
    }

    void setName(const string &nm) override
    {
        name = nm;
    }
};

int main()
{
    // Create prototype instances of products
    ProductPrototype *product1 = new Product("Laptop", 999.99);
    ProductPrototype *product2 = new Product("Smartphone", 499.99);

    // Clone the prototypes to create new product instances
    ProductPrototype *newProduct1 = product1->clone();
    ProductPrototype *newProduct2 = product2->clone();

    newProduct1->setName("Cloned Laptop");
    newProduct2->setName("Cloned Smartphone");

    // Display product details
    cout << "Original Products:\n";
    product1->display();
    product2->display();

    cout << "\nCloned Products:\n";
    newProduct1->display();
    newProduct2->display();

    // Clean up
    delete product1;
    delete product2;
    delete newProduct1;
    delete newProduct2;

    return 0;
}
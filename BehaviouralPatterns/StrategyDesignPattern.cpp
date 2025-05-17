#include<bits/stdc++.h>
using namespace std;

// ================================
// Step 1: Define the Strategy Interface
// ================================

// 1. Virtual Destructor
//  Declaring the destructor as virtual ensures that if you delete an object of a 
//  derived class through a pointer to the base class, the correct destructor for the derived class gets called.

//  This prevents undefined behavior and memory leaks .
//  PaymentStrategy* strategy = new CreditCardStrategy();
//  delete strategy; // Calls ~CreditCardStrategy() correctly if base has virtual destructor
/*
 = default
This tells the compiler to generate the default implementation for the destructor. 
So even though we're declaring it explicitly, we're not writing any custom logic — 
just using what the compiler would have generated automatically, but with the added benefit of being virtual .
 */


class PaymentStrategy {
public:
    virtual void processPayment(double amount) = 0;
    virtual ~PaymentStrategy() = default;
};

// ================================
// Step 2: Implement Concrete Strategies
// ================================

class CreditCardStrategy : public PaymentStrategy {
public:
    void processPayment(double amount) override {
        std::cout << "Paid $" << amount << " via Credit Card." << std::endl;
    }
};

class PayPalStrategy : public PaymentStrategy {
public:
    void processPayment(double amount) override {
        std::cout << "Paid $" << amount << " via PayPal." << std::endl;
    }
};

class BitcoinStrategy : public PaymentStrategy {
public:
    void processPayment(double amount) override {
        std::cout << "Paid $" << amount << " via Bitcoin." << std::endl;
    }
};

// ================================
// Step 3: Context using the Strategy
// ================================

class PaymentContext {
private:
    PaymentStrategy* strategy;

public:
    PaymentContext(PaymentStrategy* st){
        strategy = st;
    }

    void setStrategy(PaymentStrategy* newStrategy) {
        strategy = newStrategy;
    }

    void processPayment(double amount) {
        if (strategy) {
            strategy->processPayment(amount);
        } else {
            std::cerr << "No payment strategy set!" << std::endl;
        }
    }
};

// ================================
// Step 4: Main Program (Usage)
// ================================

int main() {
    // Create context with a default strategy
    PaymentContext context(new CreditCardStrategy());
    
    context.processPayment(100.0);  // Output: Paid $100 via Credit Card.

    // Change strategy at runtime
    context.setStrategy(new PayPalStrategy());
    context.processPayment(250.0);  // Output: Paid $250 via PayPal.

    context.setStrategy(new BitcoinStrategy());
    context.processPayment(500.0);  // Output: Paid $500 via Bitcoin.

    return 0;
} 
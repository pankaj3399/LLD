#include <bits/stdc++.h>
using namespace std;

// You will be given a list of transactions. You need to write a generic search api to filter on a combination of specific fields and values
// Example :
// transactions = [
// {id: 1, time: 1, userId: 1, amount: 10},
// {id: 2, time: 2, userId: 3, amount: 10},
// {id: 3, time: 3, userId: 4, amount: 11},
// {id: 4, time: 4, userId: 2, amount: 12},
// ]
// Filters should support operations like "=", ">", "<" etc
// The question is open ended. You need to decide how the input should look like.

// Follow up :
// Explain pagination and why we need it?
// What are some of the techniques used for pagination?
// How do you choose a cursor id column when using cursor based pagination?
// Enhance your code to support cursor based pagination.

class Transaction
{
    int id;
    int time;
    int userId;
    int amount;

public:
    Transaction(int _id, int _time, int _userId, int _amt)
    {
        id = _id;
        time = _time;
        userId = _userId;
        amount = _amt;
    }

    void print()
    {
        cout << id << " " << time << " " << userId << " " << amount << endl;
    }

    int getUserId()
    {
        return userId;
    }

    int getAmount()
    {
        return amount;
    }
};

class Filter
{
public:
    virtual vector<Transaction *> apply(vector<Transaction *> t) = 0;
};

class UserFilter : public Filter
{
    int userId;

public:
    UserFilter(int u)
    {
        userId = u;
    }
    vector<Transaction *> apply(vector<Transaction *> t) override
    {
        vector<Transaction *> result;
        for (auto txn : t)
        {
            if (txn->getUserId() == userId)
            {
                result.push_back(txn);
            }
        }
        return result;
    };
};

class AmountFilter : public Filter
{
    int amount;

public:
    AmountFilter(int amt)
    {
        amount = amt;
    }
    vector<Transaction *> apply(vector<Transaction *> t) override
    {
        vector<Transaction *> result;
        for (auto txn : t)
        {
            if (txn->getAmount() < amount)
            {
                result.push_back(txn);
            }
        }
        return result;
    };
};

int main()
{
    Transaction *t1 = new Transaction(1, 1, 1, 10);
    Transaction *t2 = new Transaction(2, 2, 3, 10);
    Transaction *t3 = new Transaction(3, 3, 4, 11);
    Transaction *t4 = new Transaction(4, 4, 2, 12);

    vector<Transaction *> v = {t1, t2, t3, t4};
    UserFilter *u1 = new UserFilter(2);
    vector<Transaction *> filtered = u1->apply(v);
    for (auto txn : filtered)
    {
        txn->print();
    }

    AmountFilter *a1 = new AmountFilter(11);
    vector<Transaction *> filteredA = a1->apply(v);
    for (auto txn : filteredA)
    {
        txn->print();
    }

    delete t1;
    delete t2;
    delete t3;
    delete t4;
    delete u1;
    delete a1;

    return 0;
}
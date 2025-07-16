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
        cout << "ID: " << id << " Time: " << time
             << " User: " << userId << " Amount: " << amount << endl;
    }

    int getUserId()
    {
        return userId;
    }

    int getAmount()
    {
        return amount;
    }
    int getId() const { return id; }
    int getTime() const { return time; }
};

enum class Operator
{
    EQ,
    GT,
    LT
};

class Filter
{
public:
    virtual vector<Transaction *> apply(vector<Transaction *> t) = 0;
};

class GenericFieldFilter : public Filter
{
    string field;
    Operator op;
    int value;

public:
    GenericFieldFilter(string f, Operator o, int v) : field(f), op(o), value(v) {}

    bool compare(int a)
    {
        switch (op)
        {
        case Operator::EQ:
            return a == value;
        case Operator::GT:
            return a > value;
        case Operator::LT:
            return a < value;
        default:
            return false;
        }
    }

    vector<Transaction *> apply(vector<Transaction *> txns) override
    {
        vector<Transaction *> result;
        for (auto txn : txns)
        {
            int fieldValue = getFieldValue(txn);
            if (compare(fieldValue))
                result.push_back(txn);
        }
        return result;
    }

private:
    int getFieldValue(Transaction *txn)
    {
        if (field == "userId")
            return txn->getUserId();
        if (field == "amount")
            return txn->getAmount();
        // Add getId(), getTime() methods in Transaction if needed
        throw invalid_argument("Unsupported field: " + field);
    }
};

class AndFilter : public Filter
{
    vector<Filter *> filters;

public:
    AndFilter(vector<Filter *> f) : filters(f) {}

    vector<Transaction *> apply(vector<Transaction *> txns) override
    {
        for (auto filter : filters)
        {
            txns = filter->apply(txns); // Apply in sequence
        }
        return txns;
    }
};

// Cursor paginator
class CursorPaginator
{
    int pageSize;
    int afterId; // this is the cursor

public:
    CursorPaginator(int _afterId, int _pageSize)
        : afterId(_afterId), pageSize(_pageSize) {}

    vector<Transaction *> paginate(const vector<Transaction *> &transactions)
    {
        vector<Transaction *> result;
        // Assume transactions are already sorted by id
        for (auto txn : transactions)
        {
            if (txn->getId() > afterId)
            {
                result.push_back(txn);
                if (result.size() >= pageSize)
                    break;
            }
        }
        return result;
    }
};

int main()
{
    Transaction *t1 = new Transaction(1, 1, 1, 10);
    Transaction *t2 = new Transaction(2, 2, 3, 10);
    Transaction *t3 = new Transaction(3, 3, 4, 11);
    Transaction *t4 = new Transaction(4, 4, 2, 12);

    vector<Transaction *> transactions = {t1, t2, t3, t4};
    // Sort transactions by id ascending (you can switch to time)
    sort(transactions.begin(), transactions.end(), [](Transaction *a, Transaction *b)
         { return a->getId() < b->getId(); });
    // Simulate fetching next page after id 2, page size = 2
    CursorPaginator paginator(/*afterId=*/2, /*pageSize=*/2);
    auto page = paginator.paginate(transactions);

    cout << "Paginated Results (after id=2, limit=2):\n";
    for (auto txn : page)
        txn->print();
    vector<Filter *> filters;
    filters.push_back(new GenericFieldFilter("userId", Operator::EQ, 1));
    filters.push_back(new GenericFieldFilter("amount", Operator::LT, 11));

    AndFilter combined(filters);
    auto result = combined.apply(transactions);

    for (auto txn : result)
    {
        txn->print();
    }

    for (auto f : filters)
        delete f;
    for (auto t : transactions)
        delete t;

    return 0;
}
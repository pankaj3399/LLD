#include <bits/stdc++.h>
using namespace std;

class Transaction
{
public:
    string id;
    float amount;
    string status;
    string userId;
    Transaction(string _id, float _amount, string _status, string _userId)
    {
        id = _id;
        amount = _amount;
        status = _status;
        userId = _userId;
    }

    void print() const
    {
        cout << id << " | " << status << " | $" << amount << " | " << userId << endl;
    }
};

class Filter
{
public:
    virtual vector<Transaction *> apply(const vector<Transaction *> &items) const = 0;
    virtual ~Filter() = default;
};

class StatusFilter : public Filter
{
    string targetStatus;

public:
    StatusFilter(const string &st)
    {
        targetStatus = st;
    }
    vector<Transaction *> apply(const vector<Transaction *> &items) const override
    {
        vector<Transaction *> result;
        for (auto tx : items)
        {
            if (tx->status == targetStatus)
            {
                result.push_back(tx);
            }
        }
        return result;
    }
};

class UserFilter : public Filter
{
    string userId;

public:
    UserFilter(const string &uid)
    {
        userId = uid;
    }
    vector<Transaction *> apply(const vector<Transaction *> &items) const override
    {
        vector<Transaction *> result;
        for (auto tx : items)
        {
            if (tx->userId == userId)
            {
                result.push_back(tx);
            }
        }
        return result;
    }
};

// class AndFilter : public Filter
// {
//     Filter *f1;
//     Filter *f2;

// public:
//     AndFilter(Filter *filter1, Filter *filter2) : f1(filter1), f2(filter2) {}

//     ~AndFilter()
//     {
//         delete f1;
//         delete f2;
//     }
//     //  use this if you are passing status filter without new keyword as then it is in stack not in heap
//     // ~AndFilter()
//     // {

//     // }

//     vector<Transaction *> apply(const vector<Transaction *> &items) override
//     {
//         auto firstResult = f1->apply(items);
//         return f2->apply(firstResult);
//     }
// };

// good and filter
class AndFilter : public Filter
{
    unique_ptr<Filter> f1;
    unique_ptr<Filter> f2;

public:
    AndFilter(unique_ptr<Filter> filter1, unique_ptr<Filter> filter2)
    {
        f1 = move(filter1);
        f2 = move(filter2);
    }

    vector<Transaction *> apply(const vector<Transaction *> &items) const override
    {
        auto firstResult = f1->apply(items);
        return f2->apply(firstResult);
    }
};

bool compareById(Transaction *a, Transaction *b)
{
    return a->id < b->id;
}

// // Sorting function with optional comparator
// void sortTransactions(
//     vector<Transaction *> &list,
//     bool (*comparator)(Transaction *, Transaction *) = compareById)
// {
//     sort(list.begin(), list.end(), comparator);
// }

class Database
{
    vector<Transaction *> allTransactions;

public:
    Database(const vector<Transaction> &transactions)
    {
        for (const auto &tx : transactions)
        {
            allTransactions.push_back(new Transaction(tx));
        }
    }

    ~Database()
    {
        for (auto tx : allTransactions)
        {
            delete tx;
        }
    }

    vector<Transaction *> getPaginated(
        Filter *filter,
        int offset,
        int pageSize,
        bool (*comparator)(Transaction *, Transaction *) = compareById)
    {
        vector<Transaction *> filtered = filter->apply(allTransactions);

        if (comparator)
        {
            sort(filtered.begin(), filtered.end(), comparator);
        }

        int start = offset;
        int end = min(offset + pageSize, static_cast<int>(filtered.size()));

        if (start >= static_cast<int>(filtered.size()) || start < 0)
        {
            return {};
        }

        return vector<Transaction *>(filtered.begin() + start, filtered.begin() + end);
    }

    int getTotalCount(Filter *filter = nullptr)
    {
        if (!filter)
        {
            return allTransactions.size();
        }

        auto result = filter->apply(allTransactions);
        return result.size();
    }
};

int main()
{
    // Step 1: Define raw transaction data
    vector<Transaction> txData = {
        {"t1", 100.0f, "completed", "u1"},
        {"t2", 200.0f, "failed", "u1"},
        {"t3", 150.0f, "failed", "u2"},
        {"t4", 300.0f, "completed", "u2"},
        {"t5", 50.0f, "failed", "u1"},
        {"t6", 90.0f, "failed", "u1"}};

    // Step 2: Initialize Database
    Database db(txData);

    // Step 3: Create filters
    string status = "failed";
    string userId = "u1";

    // StatusFilter statusFilter(status);
    // UserFilter userFilter(userId);

    // // Step 4: Combine filters
    // AndFilter andFilter(&statusFilter, &userFilter);
    // Filter *f1 = new StatusFilter(status);
    // Filter *f2 = new UserFilter(userId);
    // AndFilter andFilter(f1, f2);

    auto f1 = make_unique<StatusFilter>("failed");
    auto f2 = make_unique<UserFilter>("u1");

    AndFilter andFilter(move(f1), move(f2));

    // Step 5: Get paginated results (page 1, page size = 2)
    int offset = 0;
    int pageSize = 2;

    vector<Transaction *> result = db.getPaginated(&andFilter, offset, pageSize);

    // Step 6: Print results
    cout << "Filtered & Paginated Transactions:" << endl;
    for (auto tx : result)
    {
        tx->print();
    }

    // Optional: Print total count
    cout << "Total matching records: " << db.getTotalCount(&andFilter) << endl;

    return 0;
}
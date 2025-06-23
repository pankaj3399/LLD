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
};

class TransactionUpdates
{
public:
    string tid;
    string newStatus;
    TransactionUpdates(string _id, string _status)
    {
        tid = _id;
        newStatus = _status;
    }
};

int main()
{
    Transaction *t1 = new Transaction("t1", 100, "pending", "u1");
    Transaction *t2 = new Transaction("t2", 50, "completed", "u1");
    Transaction *t3 = new Transaction("t3", 200, "pending", "u2");

    vector<Transaction *> txn = {t1, t2, t3};

    TransactionUpdates *update1 = new TransactionUpdates("t1", "failed");
    TransactionUpdates *update2 = new TransactionUpdates("t3", "completed");

    vector<TransactionUpdates *> updates = {update1, update2};

    unordered_map<string, int> mp; // tid -> index in vector
    for (int i = 0; i < txn.size(); i++)
    {
        Transaction *tx = txn[i];
        mp[tx->id] = i;
    }

    for (auto u : updates)
    {
        string tid = u->tid;
        int idx = mp[tid];
        txn[idx]->status = u->newStatus;
    }

    map<string, vector<Transaction *>> userTxn;
    for (auto tx : txn)
    {
        userTxn[tx->userId].push_back(tx);
    }

    map<string, vector<Transaction *>> failedTxn;

    for (auto it : userTxn)
    {
        vector<Transaction *> t = it.second;
        bool hasFailed = false;
        for (auto tx : t)
        {
            if (tx->status == "failed")
            {
                hasFailed = true;
                break;
            }
        }
        if (hasFailed)
        {
            failedTxn[it.first] = it.second;
        }
    }
    for (const auto &[userId, txns] : failedTxn)
    {
        cout << "User: " << userId << endl;
        for (const auto &tx : txns)
        {
            cout << "  " << tx->id << " | " << tx->status << " | $" << tx->amount << endl;
        }
    }

    return 0;
}
#include <bits/stdc++.h>
using namespace std;

class Iterator
{

public:
    virtual int next() = 0;
    virtual bool hasNext() = 0;
    virtual ~Iterator() = default;
};
class ZigzagIterator : public Iterator
{
    vector<vector<int>> vecs;
    vector<int> idx;
    int turn;

public:
    ZigzagIterator(vector<int> &v1, vector<int> &v2)
    {
        vecs = {v1, v2};
        idx = {0, 0}; // indices for v1 and v2
        turn = 0;
    }

    int next() override
    {
        int n = vecs.size();
        for (int i = 0; i < n; i++)
        {
            int curr = (turn + i) % n;
            if (idx[curr] < vecs[curr].size())
            {
                turn = (curr + 1) % n;
                return vecs[curr][idx[curr]++];
            }
        }
        throw std::out_of_range("No more elements");
    }

    bool hasNext() override
    {
        int n = vecs.size();
        for (int i = 0; i < n; i++)
        {
            if (idx[i] < vecs[i].size())
            {
                return true;
            }
        }
        return false;
    }
};

class RangeIterator : public Iterator
{
    int start;
    int end;
    int step;
    int curr;

public:
    RangeIterator(int s, int e, int st)
    {
        start = s;
        end = e;
        step = st;
        curr = start;
    }

    int next() override
    {
        int val = curr;
        curr += step;
        return val;
    }

    bool hasNext() override
    {
        if (step == 0)
            return false; // avoid infinite loop, good edge case I forgot
        if (step > 0)
            return curr <= end;
        return curr >= end;
    }
};

class InterleavingIterator : public Iterator
{
    vector<Iterator *> its;
    int turn;

public:
    InterleavingIterator(vector<Iterator *> i)
    {
        its = i;
        turn = 0;
    }

    bool hasNext() override
    {
        int n = its.size();
        for (int i = 0; i < n; i++)
        {
            if (its[i]->hasNext())
            {
                return true;
            }
        }
        return false;
    }

    int next() override
    {
        int n = its.size();
        for (int i = 0; i < n; i++)
        {
            int curr = (turn + i) % n;
            if (its[curr]->hasNext())
            {
                turn = (curr + 1) % n;
                return its[curr]->next();
            }
        }
        throw std::out_of_range("No more elements");
    }
};

class InterleavingIteratorWithFilter : public Iterator
{
    vector<Iterator *> its;
    int turn;
    bool (*filter)(int); // function pointer filter
    vector<queue<int>> cache;

public:
    InterleavingIteratorWithFilter(vector<Iterator *> i, bool (*f)(int) = nullptr)
    {
        its = i;
        turn = 0;
        filter = f;
        cache.resize(i.size());
    }

    bool hasNext() override
    {
        int n = its.size();
        for (int i = 0; i < n; ++i)
        {
            int curr = (turn + i) % n;

            // if already cached, we have next
            if (!cache[curr].empty())
                return true;

            // try fetching from iterator
            while (its[curr]->hasNext())
            {
                int val = its[curr]->next();
                if (!filter || filter(val))
                {
                    cache[curr].push(val);
                    return true;
                }
            }
        }
        return false;
    }

    int next() override
    {
        int n = its.size();
        for (int i = 0; i < n; ++i)
        {
            int curr = (turn + i) % n;

            // use cached value
            if (!cache[curr].empty())
            {
                int val = cache[curr].front();
                cache[curr].pop();
                turn = (curr + 1) % n;
                return val;
            }

            // pull from iterator
            while (its[curr]->hasNext())
            {
                int val = its[curr]->next();
                if (!filter || filter(val))
                {
                    turn = (curr + 1) % n;
                    return val;
                }
            }
        }
        throw std::out_of_range("No matching elements");
    }
};

bool isEven(int x)
{
    return x % 2 == 0;
}

int main()
{

    // vector<int> v1 = {1, 3, 5};
    // vector<int> v2 = {2, 4, 6, 8};

    // ZigzagIterator i(v1, v2);
    // while (i.hasNext())
    // {
    //     cout << i.next() << " ";
    // }
    // Output: 1 2 3 4 5 6 8

    // RangeIterator i(1, 10, 2);
    // while (i.hasNext())
    // {
    //     cout << i.next() << " ";
    // }

    // RangeIterator i(10, 0, -2);
    // while (i.hasNext())
    // {
    //     cout << i.next() << " ";
    // }

    // vector<int> v1 = {1, 3, 5};
    // vector<int> v2 = {2, 4, 6, 8};
    // ZigzagIterator *z = new ZigzagIterator(v1, v2);
    // RangeIterator *r = new RangeIterator(11, 20, 2);

    // vector<Iterator *> its = {z, r};
    // InterleavingIterator i(its);
    // while (i.hasNext())
    // {
    //     cout << i.next() << " ";
    // }

    // delete z;
    // delete r;

    vector<int> v1 = {1, 3, 5};
    vector<int> v2 = {2, 4, 6, 8};
    ZigzagIterator *z = new ZigzagIterator(v1, v2);
    RangeIterator *r = new RangeIterator(11, 20, 2);

    vector<Iterator *> its = {z, r};
    InterleavingIteratorWithFilter i(its, isEven); // <-- pass regular function here

    while (i.hasNext())
    {
        cout << i.next() << " ";
    }

    delete z;
    delete r;

    return 0;
}

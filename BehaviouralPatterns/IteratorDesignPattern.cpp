#include <bits/stdc++.h>
using namespace std;

class IteratorInterface
{
public:
    virtual string next() = 0;
    virtual bool hasNext() = 0;
    virtual ~IteratorInterface() {};
};

class PlaylistIterator : public IteratorInterface
{
    vector<string> &playlist;
    int idx;

public:
    PlaylistIterator(vector<string> &arr) : playlist(arr), idx(0) {}
    string next() override
    {
        if (idx < playlist.size())
        {
            return playlist[idx++];
        }
        return "Out of bounds";
    }

    bool hasNext() override
    {
        if (idx < playlist.size())
        {
            return true;
        }
        return false;
    }
};

int main()
{

    vector<string> playlist = {"Abc", "Def", "Ghi", "Jkl"};

    PlaylistIterator *iter = new PlaylistIterator(playlist);

    cout << iter->next() << endl;
    cout << iter->hasNext() << endl;

    delete iter;

    cout << "Hello" << endl;

    return 0;
}
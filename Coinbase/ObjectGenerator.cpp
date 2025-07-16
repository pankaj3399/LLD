#include <bits/stdc++.h>
using namespace std;

class ObjectGenerator
{
    vector<vector<string>> props;
    set<string> objects;

public:
    ObjectGenerator(vector<vector<string>> &properties)
    {
        props = properties;
    }

    string generateRandom()
    {
        // missed this condition
        int totalComb = 1;
        for (auto &p : props)
            totalComb *= p.size();

        if (objects.size() >= totalComb)
            return "All exhausted";
        bool generated = false;
        while (!generated)
        {
            int n = props.size();
            string ans = "";
            for (int i = 0; i < n; i++)
            {
                vector<string> prop = props[i];
                int m = prop.size();
                int randomNumInRange = rand() % m;
                ans += prop[randomNumInRange];
                ans += " ";
            }

            if (objects.find(ans) == objects.end())
            {
                generated = true;
                objects.insert(ans); // missed this
                return ans;
            }
        }
        return "";
    }
};

int main()
{
    srand(time(0));

    vector<string> len = {"short", "medium", "tall"};
    vector<string> leafColor = {"green", "yellow", "red"};

    vector<vector<string>> properties = {len, leafColor};

    ObjectGenerator *gen = new ObjectGenerator(properties);

    cout << gen->generateRandom() << endl;
    cout << gen->generateRandom() << endl;
    cout << gen->generateRandom() << endl;
    cout << gen->generateRandom() << endl;
    cout << gen->generateRandom() << endl;

    delete gen;

    return 0;
}
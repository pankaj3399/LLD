#include <bits/stdc++.h>
using namespace std;

struct PropertyValue
{
    string value;
    double weight; // Higher = more common
};

class ObjectGenerator
{
    vector<vector<PropertyValue>> props;
    set<string> objects;
    int totalComb;

    string pickWeighted(const vector<PropertyValue> &choices)
    {
        double sum = 0;
        for (auto &pv : choices)
            sum += pv.weight;

        double r = ((double)rand() / RAND_MAX) * sum;
        double cumulative = 0;

        for (auto &pv : choices)
        {
            cumulative += pv.weight;
            if (r <= cumulative)
                return pv.value;
        }

        // Fallback (shouldn't happen)
        return choices.back().value;
    }

public:
    ObjectGenerator(vector<vector<PropertyValue>> &properties)
    {
        props = properties;
        totalComb = INT_MAX; // Skip for now; combinatorial logic changes with weights
    }

    string generateRandom()
    {
        if (objects.size() >= totalComb)
            return "All exhausted";

        while (true)
        {
            string ans = "";
            for (auto &prop : props)
            {
                ans += pickWeighted(prop) + " ";
            }

            if (objects.find(ans) == objects.end())
            {
                objects.insert(ans);
                return ans;
            }
        }
    }
};

int main()
{
    srand(time(0));

    // Length: short (common), medium (common), tall (rare)
    vector<PropertyValue> len = {
        {"short", 0.5},
        {"medium", 0.4},
        {"tall", 0.1}};

    // Leaf color: all equally likely
    vector<PropertyValue> leafColor = {
        {"green", 0.33},
        {"yellow", 0.33},
        {"red", 0.34}};

    vector<vector<PropertyValue>> properties = {len, leafColor};

    ObjectGenerator gen(properties);

    for (int i = 0; i < 6; i++)
        cout << gen.generateRandom() << endl;

    return 0;
}

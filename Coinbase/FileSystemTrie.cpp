#include <bits/stdc++.h>
using namespace std;

class TrieNode
{
public:
    string name;
    bool isFile;
    string content;
    unordered_map<string, TrieNode *> children;

    TrieNode()
    {
        isFile = false;
        name = "";
    }

    ~TrieNode()
    {
        for (auto ch : children)
        {
            delete ch.second;
        }
    }

    TrieNode *insert(string path, bool fileStatus)
    {
        // important logic
        // how to deal with strings in c++
        TrieNode *node = this;
        vector<string> result;
        stringstream ss(path);
        string item;
        while (getline(ss, item, '/'))
        {
            if (!item.empty())
            {
                result.push_back(item);
            }
        }

        for (auto part : result)
        {
            if (node->children.find(part) == node->children.end())
            {
                node->children[part] = new TrieNode();
            }
            node = node->children[part];
        }
        node->isFile = fileStatus;
        node->name = result[result.size() - 1]; // last element
        return node;
    }

    TrieNode *search(string path)
    {
        TrieNode *node = this;
        vector<string> result;
        stringstream ss(path);
        string item;
        while (getline(ss, item, '/'))
        {
            if (!item.empty())
            {
                result.push_back(item);
            }
        }

        for (auto part : result)
        {
            if (node->children.find(part) == node->children.end())
            {
                return nullptr;
            }
            node = node->children[part];
        }

        return node;
    }
};

class FileSystem
{
private:
    TrieNode *root;

public:
    FileSystem()
    {
        root = new TrieNode();
    }
    ~FileSystem()
    {
        delete root;
    }

    void mkdir(string path)
    {
        root->insert(path, false);
    }

    // List the contents in a directory or return the file if it's just a single file.
    vector<string> ls(const string &path)
    {
        vector<string> result;
        TrieNode *node = root->search(path);
        // cout << node << endl;
        if (!node)
        {
            return result; // Empty vector if path not found
        }

        if (node->isFile)
        {
            // If it's a file, add the file name to the result list
            result.push_back(node->name);
        }
        else
        {
            // If it's a directory, add all the child names to the list
            for (auto &child : node->children)
            {
                result.push_back(child.first);
            }
        }
        sort(result.begin(), result.end()); // Sort the list lexicographically
        return result;
    }

    void addContentToFile(string filePath, string content)
    {
        TrieNode *node = root->insert(filePath, true);
        node->content += content; // Append the content to the file's content
    }

    string readContentFromFile(string filePath)
    {
        TrieNode *node = root->search(filePath);
        if (node && node->isFile)
        {
            return node->content; // Return file content as a String
        }
        return ""; // Return empty String if file does not exist or if it's a directory
    }
};

int main()
{

    FileSystem *fs = new FileSystem();
    fs->mkdir("/a/b/c");
    vector<string> ans = fs->ls("/a");
    for (auto ch : ans)
    {
        cout << ch << endl;
    }
    fs->addContentToFile("/a/b/c/d", "Hello");
    cout << fs->readContentFromFile("/a/b/c/d") << endl;

    return 0;
}
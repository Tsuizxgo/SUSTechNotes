#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

class Node
{
public:
    string name;
    bool isFolder;
    string content;
    vector<Node *> kids;

    Node(string name) : name(name) {};

    void addNode(Node *node)
    {
        this->isFolder = true;
        this->kids.push_back(node);
    }
    Node *findNode(string name)
    {
        for (Node *node : kids)
            if (node->name == name)
                return node;
        return nullptr;
    }
    void rm(Node *node)
    {
        for (int i = 0; i < kids.size(); i++)
        {
            if (kids[i]->name == node->name)
            {
                kids.erase(kids.begin() + i);
                return;
            }
        }
    }
};

class FileSystem
{
public:
    Node *root;
    FileSystem() : root(new Node("/"))
    {
        root->isFolder = true;
    }
    vector<string> handlePath(string path)
    {
        string file;
        vector<string> files;
        stringstream ss(path);
        while (getline(ss, file, '/'))
        {
            if (file.empty() || file == ".")
                continue;
            if (file == "..")
            {
                if (files.empty())
                    cout << "file is empty" << endl;
                else
                    files.pop_back();
                continue;
            }
            files.push_back(file);
        }
        return files;
    }
    Node *findParent(string path)
    {
        Node *cur = root;
        vector<string> files = handlePath(path);
        if (files.empty())
            return cur;
        for (int i = 0; i < files.size() - 1; i++)
        {
            string name = files[i];
            Node *next = cur->findNode(name);
            if (next)
                cur = next;
            else
                return nullptr;
        }
        return cur;
    }
    void mkdir(string path)
    {
        Node *parentNode = findParent(path);
        if (parentNode)
        {
            vector<string> files = handlePath(path);
            // 需要检查是否为空
            string name = files.back();
            Node *target = parentNode->findNode(name);
            if (!target)
            {
                Node *newNode = new Node(name);
                newNode->isFolder = true;
                parentNode->addNode(newNode);
            }
            else
                return;
        }
    }
    void echo(string content, string path)
    {
        Node *parent = findParent(path);
        if (parent)
        {
            vector<string> files = handlePath(path);
            string name = files.back();
            Node *target = parent->findNode(name);
            if (!target)
            {
                Node *newNode = new Node(name);
                newNode->isFolder = false;
                newNode->content = content;
                parent->addNode(newNode);
            }
            else
            {
                target->content = content;
                target->isFolder = false;
            }
        }
        else
            return;
    }
    void cat(string path)
    {
        Node *parentNode = findParent(path);
        if (parentNode)
        {
            vector<string> files = handlePath(path);
            string targetFileName = files.back();
            Node *target = parentNode->findNode(targetFileName);
            if (target)
                cout << target->content << endl;
            else
                return;
        }
    }
    void rm(string path)
    {
        Node *parent = findParent(path);
        if (parent)
        {
            vector<string> files = handlePath(path);
            string targetFileName = files.back();
            Node *target = parent->findNode(targetFileName);
            if (target)
                parent->rm(target);
            else
                return;
        }
    }
    void rmRf(string path)
    {
        Node *parent = findParent(path);
        vector<string> files = handlePath(path);
        if (!files.empty())
        {
            string name = files.back();
            Node *target = parent->findNode(name);
            if (target)
            {
                recursiveDelete(target);
                parent->rm(target);
            }
            else
                return;
        }
    }
    void recursiveDelete(Node *node)
    {
        for (auto it = node->kids.begin(); it != node->kids.end(); ++it)
        {
            recursiveDelete(*it);
        }
        node->kids.clear();
    }
    void mv(string sourcePath, string targetPath)
    {
        Node *sourceParent = findParent(sourcePath);
        Node *targetParent = findParent(targetPath);
        if (sourceParent && targetParent)
        {
            vector<string> sourceFiles = handlePath(sourcePath);
            vector<string> targetFiles = handlePath(targetPath);
            if (!sourceFiles.empty())
            {
                string sourceName = sourceFiles.back();
                Node *sourceNode = sourceParent->findNode(sourceName);
                if (sourceNode)
                {
                    if (!targetFiles.empty())
                    {
                        string targetName = targetFiles.back();
                        Node *targetNode = targetParent->findNode(targetName);
                        if (targetNode && targetNode->isFolder)
                        {
                            targetNode->addNode(sourceNode);
                            sourceParent->rm(sourceNode);
                        }
                        else
                        {
                            targetNode = new Node(targetName);
                            targetNode->addNode(sourceNode);
                            sourceParent->rm(sourceNode);
                        }
                    }
                }
            }
        }
    }
    void find(string arg1, string arg2, string arg3, string arg4, string arg5, int n)
    {
        Node *start;
        string path;
        if (arg1.empty())
        {
            start = root;
            path = ".";
        }
        else
        {
            path = arg1;
            vector<string> files = handlePath(path);
            Node *parent = findParent(arg1);
            if (files.empty())
                start = root;
            else
                start = parent->findNode(files.back());
        }
        vector<string> results;
        if (n == 0 || n == 1)
            dfs(start, "", "", results, path);
        else if (n == 2 || n == 3)
        {
            if (arg2 == "-type")
                dfs(start, arg3, "", results, path);
            else if (arg2 == "-name")
                dfs(start, "", arg3, results, path);
        }
        else if (n == 4 || n == 5)
        {
            if (arg2 == "-type")
                dfs(start, arg3, arg5, results, path);
            else if (arg2 == "-name")
                dfs(start, arg5, arg3, results, path);
        }
        cout << results.size() << endl;
        for (const string &result : results)
        {
            cout << (result.empty() ? "." : result) << endl; // 如果为空，输出 "."
        }
    }

    void dfs(Node *start, string type, string name, vector<string> &results, string currentPath)
    {
        if (!start)
            return;
        bool print = true;
        if (!type.empty() && type == "f" && start->isFolder == true)
            print = false;
        if (!type.empty() && type == "d" && start->isFolder == false)
            print = false;
        if (!name.empty() && start->name != name)
            print = false;

        if (print)
            results.push_back(currentPath);
        for (Node *child : start->kids)
        {
            if (currentPath.back() == '/')
                currentPath.pop_back();
            dfs(child, type, name, results, currentPath + (currentPath.empty() ? "" : "/") + child->name);
        }
    }
};
int main()
{
    int n, m;
    cin >> n >> m;
    cin.ignore();
    FileSystem *f = new FileSystem();
    int t = n + m;
    while (t--)
    {
        string commandLine;
        getline(cin, commandLine);
        stringstream ss(commandLine);
        string command;
        vector<string> commands;
        while (ss >> command)
            commands.push_back(command);
        if (commands[0] == "echo")
        {
            string name = commands[1];
            if (commands.size() == 4)
                f->echo(commands[1], commands[3]);
            else if (commands.size() == 3)
                f->echo("", commands[2]);
        }
        else if (commands[0] == "mkdir")
        {
            string path = commands[1];
            f->mkdir(path);
        }
        else if (commands[0] == "rm")
        {
            if (commands[1] != "-rf")
            {
                string path = commands[1];
                f->rm(path);
            }
            else if (commands[1] == "-rf")
            {
                string path = commands[2];
                f->rmRf(path);
            }
            else
                return 0;
        }
        else if (commands[0] == "mv")
        {
            string sourcePath = commands[1];
            string targetPath = commands[2];
            f->mv(sourcePath, targetPath);
        }
        else if (commands[0] == "cat")
        {
            f->cat(commands[1]);
        }
        else if (commands[0] == "find")
        {
            if (commands.size() == 1)
                f->find("", "", "", "", "", 0);
            else if (commands.size() == 2)
                f->find(commands[1], "", "", "", "", 1);
            else if (commands.size() == 3)
                f->find("", commands[1], commands[2], "", "", 2);
            else if (commands.size() == 4)
                f->find(commands[1], commands[2], commands[3], "", "", 3);
            else if (commands.size() == 5)
                f->find("", commands[1], commands[2], commands[3], commands[4], 4);
            else if (commands.size() == 6)
                f->find(commands[1], commands[2], commands[3], commands[4], commands[5], 5);
        }
    }
    return 0;
}
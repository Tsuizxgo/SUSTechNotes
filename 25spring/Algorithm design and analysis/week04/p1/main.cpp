#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

// echo 不会给出不合法的父亲文件或者子文件
// 问题：
//    根目录是否一定是 /
//    创建的path最后是否会以 / 结尾
//
class Folder;

class File
{
public:
    string name;
    string content;
    Folder *parent;
    File(string name, string content, Folder *parent) : name(name), content(content), parent(parent) {}
};
class Folder
{
public:
    string name;
    Folder *parent;
    vector<File> kidsFile;
    vector<Folder> kidsFolder;
    Folder(string name, Folder *parent) : name(name), parent(parent) {}

    Folder *findFolder(string name)
    {
        for (Folder &folder : kidsFolder)
        {
            if (folder.name == name)
            {
                return &folder;
            }
        }
        return nullptr;
    }
    File *findFile(string name)
    {
        for (File &file : kidsFile)
        {
            if (file.name == name)
            {
                return &file;
            }
        }
        return nullptr;
    }
};
class FileSystem
{
public:
    Folder *root;
    Folder *current;
    FileSystem() : root(new Folder("/", nullptr)), current(root) {}
    Folder *getRoot()
    {
        return root;
    }
    vector<string> handlePath(string path)
    {
        string copyPath = path;
        string file;
        vector<string> files;
        stringstream ss(copyPath);
        while (getline(ss, file, '/'))
        {
            files.push_back(file);
        }
        return files;
    }
    void mkdir(const string path)
    {
        Folder *cur = current;
        vector<string> files = handlePath(path);

        for (int i = 0; i < files.size(); i++)
        {
            string name = files[i];
            if (name.empty())
                continue;
            Folder *next = cur->findFolder(name);
            if (!next)
            {
                if (i != files.size() - 1)
                    return;
                else
                {
                    Folder *newFolder = new Folder(name, cur);
                    cur->kidsFolder.push_back(*newFolder);
                    return;
                }
            }
        }
    }
    void echo(string content, string any, string path)
    {
        Folder *cur = current;
        vector<string> files = handlePath(path);
        for (int i = 0; i < files.size(); i++)
        {
            string name = files[i];
            Folder *next = cur->findFolder(name);
            if (!next)
            {
                if (i != files.size() - 1)
                    return;
                else
                {
                    File *newFile = new File(name, content, cur);
                    cur->kidsFile.push_back(*newFile);
                    return;
                }
            }
        }
    }
    void cat(string path)
    {
        Folder *cur = current;
        vector<string> files = handlePath(path);
        for (int i = 0; i < files.size(); i++)
        {
            string name = files[i];
            if (i != files.size() - 1)
            {
                Folder *next = cur->findFolder(name);
                cur = next;
                if (!next)
                {
                    return;
                }
            }
            else
            {
                File *next = cur->findFile(name);
                cout << next->content;
                if (!next)
                {
                    return;
                }
            }
        }
    }
};
int main()
{
    int n, m;
    cin >> n >> m;
    FileSystem *fileSystem = new FileSystem();
    while (n + m)
    {
        string commandLine;
        getline(cin, commandLine);
        stringstream ss(commandLine);
        string commmand;
        vector<string> commmands;
        while (ss >> commmand)
            commmands.push_back(commmand);
        if (commmands[0] == "echo")
        {
            string name = commmands[1];
            fileSystem->echo(commmands[1], commmands[2], commmands[3]);
        }
        else if (commmands[0] == "mkdir")
        {
            string path = commmands[1];
            fileSystem->mkdir(path);
        }
        else if (commmands[0] == "rm")
        {
            /* code */
        }
        else if (commmands[0] == "mv")
        {
            /* code */
        }
        else if (commmands[0] == "cat")
        {
            fileSystem->cat(commmands[1]);
        }
        else if (commmands[0] == "find")
        {
            /* code */
        }
    }
    delete fileSystem;
}
void handlePath(string path)
{
}

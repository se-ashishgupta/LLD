#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Component Interface
class FileSystemComponent
{
public:
    virtual void printContents() = 0;
    virtual ~FileSystemComponent() = default;
};

// Leaf - File
class File : public FileSystemComponent
{
private:
    string fileName;

public:
    File(string name)
    {
        this->fileName = name;
    }

    void printContents() override
    {
        cout << "File Name: " << this->fileName << endl;
    }
};

// Compsite - Folder
class Directory : public FileSystemComponent
{
private:
    string directoryName;
    vector<FileSystemComponent *> childrens;

public:
    Directory(string name)
    {
        this->directoryName = name;
    }

    void add(FileSystemComponent *fileSystemComponent)
    {
        childrens.push_back(fileSystemComponent);
    }

    void remove(FileSystemComponent *fileSystemComponent)
    {
        childrens.erase(std::remove(childrens.begin(), childrens.end(), fileSystemComponent), childrens.end());
    }

    void printContents() override
    {
        cout << "Directory Name: " << this->directoryName << endl;
        for (FileSystemComponent *child : childrens)
        {
            child->printContents();
        }
    }
};

int main()
{
    cout << "Creating file system structure..." << endl;

    Directory *root = new Directory("root");
    Directory *home = new Directory("home");
    Directory *user = new Directory("user");

    File *file1 = new File("file1.txt");
    File *file2 = new File("file2.txt");
    File *file3 = new File("file3.txt");

    root->add(home);
    root->add(file1);
    home->add(user);
    user->add(file2);
    user->add(file3);

    cout << "Printing file system structure..." << endl;
    root->printContents();

    delete root;

    return 0;
}
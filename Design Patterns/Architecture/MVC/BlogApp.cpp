#include <iostream>
#include <iomanip>
#include <ctime>

using namespace std;

// Model class: Blog - Holds data about a single blog post.
class Blog
{
private:
    string title;
    string content;
    string author;
    time_t createdAt;

public:
    Blog(string title, string content, string author, time_t date)
    {
        this->title = title;
        this->content = content;
        this->author = author;
        this->createdAt = date;
    }

    string getTitle()
    {
        return this->title;
    }

    void setTitle(string title)
    {
        this->title = title;
    }

    string getContent()
    {
        return this->content;
    }

    void setContent(string content)
    {
        this->content = content;
    }

    string getAuthor()
    {
        return this->author;
    }

    void setAuthor(string author)
    {
        this->author = author;
    }

    time_t getCreatedAt()
    {
        return this->createdAt;
    }

    void setCreatedAt(time_t createdAt)
    {
        this->createdAt = createdAt;
    }
};

// View class: BlogView
// Responsible for displaying blog post details in the console.
// No business logic — just formatting and printing.
class BlogView
{
public:
    // Display a single blog post
    void displayBlogDetails(Blog &blog)
    {

        time_t createdAt = blog.getCreatedAt();
        tm *timeInfo = localtime(&createdAt);

        cout << "===== Blog Post =====" << endl;
        cout << "Title   : " << blog.getTitle() << endl;
        cout << "Author  : " << blog.getAuthor() << endl;

        cout << "Date    : "
             << put_time(timeInfo, "%d-%m-%Y %H:%M:%S")
             << endl;

        cout << "Content : " << blog.getContent() << endl;
    }

    // Display a list of all blog posts
    void displayAllBlogs(vector<Blog> &blogs)
    {

        cout << "===== All Blog Posts =====" << endl;

        for (Blog &blog : blogs)
        {
            cout << "- " << blog.getTitle()
                 << " by " << blog.getAuthor()
                 << endl;
        }
    }
};

// Controller class: BlogController
// Acts as a bridge between Model (Blog) and View (BlogView).
// Handles creation, updating, and displaying of blog posts.
class BlogController
{
private:
    vector<Blog> blogs; // acts as an in-memory database
    BlogView &view;

public:
    // Constructor connects controller with the view
    BlogController(BlogView &view) : view(view)
    {
    }

    // Add a new blog post
    void addBlog(string title, string content, string author)
    {
        Blog blog(title, content, author, time(nullptr));

        blogs.push_back(blog);

        cout << "[+] Blog added successfully!" << endl;
    }

    // Update an existing blog by index
    void updateBlog(int index, string newTitle, string newContent)
    {

        if (index >= 0 && index < blogs.size())
        {

            Blog &blog = blogs[index];

            blog.setTitle(newTitle);
            blog.setContent(newContent);

            cout << "[+] Blog updated successfully!" << endl;
        }
        else
        {
            cout << "[+] Invalid blog index!" << endl;
        }
    }

    // Delete a blog post
    void deleteBlog(int index)
    {

        if (index >= 0 && index < blogs.size())
        {

            blogs.erase(blogs.begin() + index);

            cout << "[+] Blog deleted successfully!" << endl;
        }
        else
        {
            cout << "[+] Invalid blog index!" << endl;
        }
    }

    // Display a single blog post
    void showBlog(int index)
    {

        if (index >= 0 && index < blogs.size())
        {

            view.displayBlogDetails(blogs[index]);
        }
        else
        {
            cout << "[+] Invalid blog index!" << endl;
        }
    }

    // Display all blogs
    void showAllBlogs()
    {
        view.displayAllBlogs(blogs);
    }
};

int main()
{

    cout << "\n###### MVC Pattern Demo ######\n"
         << endl;

    // Create the view
    BlogView view;

    // Create the controller and connect it with the view
    BlogController controller(view);

    // Add some blog posts
    controller.addBlog(
        "MVC Pattern in C++",
        "Learn how to structure C++ apps using MVC.",
        "Alice");

    controller.addBlog(
        "Understanding Design Patterns",
        "Design patterns make your code reusable and clean.",
        "Bob");

    controller.addBlog(
        "C++ Collections",
        "Learn about different collections and their use cases.",
        "Charlie");

    // Display all blogs
    controller.showAllBlogs();

    // Show details of a specific blog
    controller.showBlog(0);

    // Update first blog
    controller.updateBlog(
        0,
        "MVC Pattern in C++ - Updated",
        "Updated content for the MVC post.");

    // Show updated blog
    controller.showBlog(0);

    // Delete second blog
    controller.deleteBlog(1);

    // Show remaining blogs
    controller.showAllBlogs();

    return 0;
}

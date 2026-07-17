#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Book
{
private:
    string title;
    string author;
    string isbn;
    int price;

public:
    Book(string title, string author, string isbn, int price)
        : title(title), author(author), isbn(isbn), price(price) {}

    string getTitle()
    {
        return this->title;
    }

    string getAuther()
    {
        return this->author;
    }

    string getIsbn()
    {
        return this->isbn;
    }

    int getPrice()
    {
        return this->price;
    }

    string toString()
    {
        return "Book [Title=" + title + ", Author=" + author + ", ISBN=" + isbn + "]";
    }
};

class Iterator
{
public:
    virtual bool hasNext() = 0;
    virtual Book next() = 0;
    virtual ~Iterator() = default;
};

class LibraryIterator : public Iterator
{
private:
    vector<Book> books;
    int index;

public:
    LibraryIterator(vector<Book> books)
    {
        this->books = books;
        this->index = 0;
    }

    bool hasNext() override
    {
        return index < books.size();
    }

    Book next() override
    {
        if (hasNext())
        {
            return books[index++];
        }
        else
        {
            throw out_of_range("No more books in the collection.");
        }
    }
};

class ReverseLibraryIterator : public Iterator
{
private:
    vector<Book> books;
    int index;

public:
    ReverseLibraryIterator(vector<Book> books)
    {
        this->books = books;
        this->index = books.size() - 1;
    }

    bool hasNext() override
    {
        return index >= 0;
    }

    Book next() override
    {
        if (hasNext())
        {
            return books[index--];
        }
        else
        {
            throw out_of_range("No more books in the collection.");
        }
    }
};

class BookCollection
{
public:
    virtual Iterator *createIterator() = 0;
    virtual Iterator *createReverseIterator() = 0;
};

class Library : public BookCollection
{
private:
    vector<Book> books;

public:
    Library(vector<Book> books) : books(books) {}

    Iterator *createIterator() override
    {
        return new LibraryIterator(books);
    }

    Iterator *createReverseIterator() override
    {
        return new ReverseLibraryIterator(books);
    }
};

int main()
{
    cout << "###### Iterator Pattern Demo ######\n";

    vector<Book> bookList = {
        {"To Kill a Mockingbird", "Harper Lee", "978-0-74-7356-5", 10},
        {"The Great Gatsby", "F. Scott Fitzgerald", "778-0-24-7156-5", 15},
        {"The Catcher in the Rye", "J.D. Salinger", "333-0-28-7446-8", 12},
        {"The Hobbit", "J.R.R. Tolkien", "783-0-14-1951-8", 20},
        {"Rich Dad Poor Dad", "Robert Kiyosaki", "183-0-12-1491-8", 18},
        {"Pride and Prejudice", "Jane Austen", "289-0-12-1678-8", 14}};

    Library library(bookList);

    Iterator *it = library.createIterator();
    cout << "Books in the library (forward):\n";
    while (it->hasNext())
    {
        cout << it->next().toString() << endl;
    }
    delete it;

    Iterator *reverseIt = library.createReverseIterator();
    cout << "\nBooks in the library (reverse):\n";
    while (reverseIt->hasNext())
    {
        cout << reverseIt->next().toString() << endl;
    }
    delete reverseIt;

    return 0;
};
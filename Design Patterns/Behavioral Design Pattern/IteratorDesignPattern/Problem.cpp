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

public:
    Book(string title, string author, string isbn)
        : title(title), author(author), isbn(isbn) {}

    static vector<Book> getBooks()
    {
        return {
            {"To Kill a Mockingbird", "Harper Lee", "978-0-74-7356-5"},
            {"The Great Gatsby", "F. Scott Fitzgerald", "778-0-24-7156-5"},
            {"The Catcher in the Rye", "J.D. Salinger", "333-0-28-7446-8"},
            {"The Hobbit", "J.R.R. Tolkien", "783-0-14-1951-8"},
            {"Rich Dad Poor Dad", "Robert Kiyosaki", "183-0-12-1491-8"},
            {"Pride and Prejudice", "Jane Austen", "289-0-12-1678-8"}};
    }

    friend ostream &operator<<(ostream &os, const Book &b)
    {
        os << "Book [Title=" << b.title
           << ", Author=" << b.author
           << ", ISBN=" << b.isbn << "]";
        return os;
    }
};

int main()
{
    cout << "###### Problem without Iterator Pattern Demo ######\n";

    // Client directly gets the entire collection
    vector<Book> bookList = Book::getBooks();

    // Client knows the underlying data structure (vector)
    for (const Book &book : bookList)
    {
        cout << book << endl;
    }

    return 0;
}

// Problems with this approach
//     Data Exposure
//         The client gets the entire vector<Book>
//             .It can modify the collection :
// bookList.clear();
// bookList.pop_back();

// No Encapsulation
//     The library exposes its internal
//     storage(vector)
//         .If later you change vector to list,
//     every client must change.

// Tight Coupling
//         Client depends on the concrete container type.Traversal logic is written by the client.

// Violates Open  Closed Principle
//         Adding new traversal methods(reverse, filtered, odd books, etc.)
//             requires changing
//         client code.
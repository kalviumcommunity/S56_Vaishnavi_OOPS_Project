#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Book class (Handles individual book details and actions)
class Book {
protected:
    string title;
    string author;
    bool isBorrowed;

public:
    Book(string title, string author)
        : title(title), author(author), isBorrowed(false) {}

    string getTitle() const { return title; }

    void borrowBook() {
        if (!isBorrowed) {
            isBorrowed = true;
            cout << title << " has been borrowed.\n";
        } else {
            cout << title << " is already borrowed.\n";
        }
    }

    void returnBook() {
        if (isBorrowed) {
            isBorrowed = false;
            cout << title << " has been returned.\n";
        } else {
            cout << title << " was not borrowed.\n";
        }
    }

    virtual void displayDetails() const {
        cout << "Title: " << title << ", Author: " << author
             << (isBorrowed ? " (Borrowed)" : " (Available)") << "\n";
    }

    virtual ~Book() {}
};

// EBook class (Handles additional details for eBooks)
class EBook : public Book {
private:
    double fileSize;

public:
    EBook(string title, string author, double fileSize)
        : Book(title, author), fileSize(fileSize) {}

    void displayDetails() const override {
        cout << "EBook -> Title: " << title << ", Author: " << author
             << ", File Size: " << fileSize << "MB"
             << (isBorrowed ? " (Borrowed)" : " (Available)") << "\n";
    }
};

// PrintedBook class (Handles additional details for printed books)
class PrintedBook : public Book {
private:
    int pageCount;

public:
    PrintedBook(string title, string author, int pageCount)
        : Book(title, author), pageCount(pageCount) {}

    void displayDetails() const override {
        cout << "Printed Book -> Title: " << title << ", Author: " << author
             << ", Pages: " << pageCount
             << (isBorrowed ? " (Borrowed)" : " (Available)") << "\n";
    }
};

// Library class (Handles the collection and management of books)
class Library {
private:
    vector<Book*> books;

public:
    void addBook(Book* book) {
        books.push_back(book);
        cout << "Added book: " << book->getTitle() << "\n";
    }

    void displayBooks() const {
        cout << "Library Collection:\n";
        for (const auto& book : books) {
            book->displayDetails();
        }
    }

    ~Library() {
        for (auto book : books) {
            delete book;
        }
    }
};

// Statistics class (Handles library statistics, like total books)
class LibraryStatistics {
public:
    static void displayTotalBooks(const Library& library) {
        // In real implementation, track total books dynamically.
        cout << "Total books in the library: " << library.books.size() << "\n";
    }
};

int main() {
    Library library;

    // Add books to the library
    library.addBook(new EBook("Digital Fortress", "Dan Brown", 5.2));
    library.addBook(new PrintedBook("To Kill a Mockingbird", "Harper Lee", 281));

    // Display all books
    library.displayBooks();

    return 0;
}

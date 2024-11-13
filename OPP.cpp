#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Abstract Base Class (Book)
class Book {
protected:
    string title;
    string author;

public:
    Book(string title, string author) : title(title), author(author) {}

    string getTitle() const { return title; }

    virtual void borrowBook() const {
        cout << title << " can be borrowed.\n";
    }

    virtual void displayDetails() const = 0;

    virtual ~Book() {}
};

// Derived Class: EBook
class EBook : public Book {
private:
    double fileSize;

public:
    EBook(string title, string author, double fileSize)
        : Book(title, author), fileSize(fileSize) {}

    void borrowBook() const override {
        cout << title << " can be accessed online.\n"; // Specialized behavior
    }

    void displayDetails() const override {
        cout << "EBook -> Title: " << title << ", Author: " << author
             << ", File Size: " << fileSize << "MB\n";
    }
};

// Derived Class: ReferenceBook (Cannot be borrowed)
class ReferenceBook : public Book {
public:
    ReferenceBook(string title, string author) : Book(title, author) {}

    void borrowBook() const override {
        cout << title << " is a reference book and cannot be borrowed.\n"; // LSP-compliant restriction
    }

    void displayDetails() const override {
        cout << "Reference Book -> Title: " << title << ", Author: " << author << "\n";
    }
};

// Derived Class: PrintedBook
class PrintedBook : public Book {
private:
    int pageCount;

public:
    PrintedBook(string title, string author, int pageCount)
        : Book(title, author), pageCount(pageCount) {}

    void displayDetails() const override {
        cout << "Printed Book -> Title: " << title << ", Author: " << author
             << ", Pages: " << pageCount << "\n";
    }
};

// Library Class: Manages the collection of books
class Library {
private:
    vector<Book*> books;

public:
    void addBook(Book* book) {
        books.push_back(book);
        cout << "Added book: " << book->getTitle() << "\n";
    }

    void borrowBook(const string& bookTitle) const {
        for (const auto& book : books) {
            if (book->getTitle() == bookTitle) {
                book->borrowBook(); // Uses polymorphism for specific book behavior
                return;
            }
        }
        cout << "Book not found: " << bookTitle << "\n";
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

int main() {
    Library library;

    // Add books to the library
    library.addBook(new EBook("Digital Fortress", "Dan Brown", 5.2));
    library.addBook(new ReferenceBook("Encyclopedia of Science", "John Doe"));
    library.addBook(new PrintedBook("To Kill a Mockingbird", "Harper Lee", 281));

    // Display all books
    library.displayBooks();

    // Attempt to borrow books
    library.borrowBook("Digital Fortress");
    library.borrowBook("Encyclopedia of Science");

    return 0;
}

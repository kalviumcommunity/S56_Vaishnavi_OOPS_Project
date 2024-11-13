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
    Book(string title, string author)
        : title(title), author(author) {}

    string getTitle() const { return title; }

    virtual void displayDetails() const = 0; // Pure virtual function for display

    virtual ~Book() {}
};

// EBook class (Derived class from Book)
class EBook : public Book {
private:
    double fileSize;

public:
    EBook(string title, string author, double fileSize)
        : Book(title, author), fileSize(fileSize) {}

    void displayDetails() const override {
        cout << "EBook -> Title: " << title << ", Author: " << author
             << ", File Size: " << fileSize << "MB\n";
    }
};

// PrintedBook class (Derived class from Book)
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

// AudioBook class (New functionality without modifying existing classes)
class AudioBook : public Book {
private:
    double duration; // in hours

public:
    AudioBook(string title, string author, double duration)
        : Book(title, author), duration(duration) {}

    void displayDetails() const override {
        cout << "AudioBook -> Title: " << title << ", Author: " << author
             << ", Duration: " << duration << " hours\n";
    }
};

// Library class (Manages a collection of books)
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
            book->displayDetails(); // Uses polymorphism to display different book types
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

    // Add various types of books to the library
    library.addBook(new EBook("Digital Fortress", "Dan Brown", 5.2));
    library.addBook(new PrintedBook("To Kill a Mockingbird", "Harper Lee", 281));
    library.addBook(new AudioBook("The Alchemist", "Paulo Coelho", 4.5));

    // Display all books
    library.displayBooks();

    return 0;
}

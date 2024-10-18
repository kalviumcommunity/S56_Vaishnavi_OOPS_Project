#include <iostream>
#include <string>
using namespace std;

// Abstract Class (Interface for Library)
class LibraryInterface {
public:
    virtual void addBook(class Book* book) = 0;  // Pure virtual function
    virtual void displayBooks() const = 0;       // Pure virtual function
    virtual ~LibraryInterface() {}               // Virtual destructor
};

// Book class (Base class for EBook and PrintedBook)
class Book {
protected:
    string title;
    string author;
    bool isBorrowed;

public:
    // Default Constructor
    Book() : title(""), author(""), isBorrowed(false) {
        cout << "Book object created with default constructor.\n";
    }

    // Constructor with title
    Book(string title) : title(title), author("Unknown"), isBorrowed(false) {
        cout << "Book object created with title: " << title << ", author: Unknown.\n";
    }

    // Constructor with title and author
    Book(string title, string author) : title(title), author(author), isBorrowed(false) {
        cout << "Book object created with title: " << title << ", author: " << author << ".\n";
    }

    // Destructor
    virtual ~Book() {
        cout << "Book object (" << title << ") destroyed.\n";
    }

    // Getter for title
    string getTitle() const {
        return this->title;
    }

    // Function to borrow the book (Virtual function)
    virtual void borrowBook() {
        if (!this->isBorrowed) {
            this->isBorrowed = true;
            cout << this->title << " has been borrowed.\n";
        } else {
            cout << this->title << " is already borrowed.\n";
        }
    }

    // Function to return the book (Virtual function)
    virtual void returnBook() {
        if (this->isBorrowed) {
            this->isBorrowed = false;
            cout << this->title << " has been returned.\n";
        } else {
            cout << this->title << " was not borrowed.\n";
        }
    }

    // Virtual function to display book details
    virtual void displayDetails() const {
        cout << "Title: " << this->title << ", Author: " << this->author;
        if (this->isBorrowed) {
            cout << " (Borrowed)\n";
        } else {
            cout << " (Available)\n";
        }
    }
};

// Derived class EBook from base class Book
class EBook : public Book {
private:
    double fileSize;

public:
    EBook(string title, string author, double fileSize) : Book(title, author), fileSize(fileSize) {
        cout << "EBook object created with file size: " << fileSize << "MB\n";
    }

    // Overriding the displayDetails function
    void displayDetails() const override {
        cout << "E-Book -> Title: " << title << ", Author: " << author << ", File Size: " << fileSize << "MB";
        if (isBorrowed) {
            cout << " (Borrowed)\n";
        } else {
            cout << " (Available)\n";
        }
    }
};

// Derived class PrintedBook from base class Book
class PrintedBook : public Book {
private:
    int pageCount;

public:
    PrintedBook(string title, string author, int pageCount) : Book(title, author), pageCount(pageCount) {
        cout << "PrintedBook object created with " << pageCount << " pages.\n";
    }

    // Overriding the displayDetails function
    void displayDetails() const override {
        cout << "Printed Book -> Title: " << title << ", Author: " << author << ", Pages: " << pageCount;
        if (isBorrowed) {
            cout << " (Borrowed)\n";
        } else {
            cout << " (Available)\n";
        }
    }
};

// Concrete Library class that implements the abstract class (Single Inheritance)
class DigitalLibrary : public LibraryInterface {
protected:
    Book** books;
    int bookCount;
    int capacity;

    static int totalBooksAdded;

public:
    DigitalLibrary(int maxBooks) : bookCount(0), capacity(maxBooks) {
        books = new Book*[capacity];
        for (int i = 0; i < capacity; i++) {
            books[i] = nullptr;
        }
        cout << "Digital Library created with capacity of " << capacity << " books.\n";
    }

    ~DigitalLibrary() {
        for (int i = 0; i < bookCount; i++) {
            delete books[i];
        }
        delete[] books;
        cout << "Digital Library destroyed and memory deallocated.\n";
    }

    // Override addBook function to add a book to the library
    void addBook(Book* book) override {
        if (bookCount < capacity) {
            books[bookCount] = book;
            bookCount++;
            totalBooksAdded++;
            cout << "Book added: " << book->getTitle() << "\n";
        } else {
            cout << "Library is full, cannot add more books.\n";
        }
    }

    // Override displayBooks function to display all books in the library
    void displayBooks() const override {
        cout << "Library Collection:\n";
        for (int i = 0; i < bookCount; i++) {
            books[i]->displayDetails();
        }
    }

    static void displayTotalBooksAdded() {
        cout << "Total number of books ever added: " << totalBooksAdded << "\n";
    }
};

// Initialize static variable
int DigitalLibrary::totalBooksAdded = 0;

int main() {
    // Create DigitalLibrary object
    DigitalLibrary myDigitalLibrary(100);

    // Create EBook and PrintedBook objects
    EBook ebook1("Digital Fortress", "Dan Brown", 5.2);
    PrintedBook pbook1("To Kill a Mockingbird", "Harper Lee", 281);

    // Add books to the digital library
    myDigitalLibrary.addBook(&ebook1);
    myDigitalLibrary.addBook(&pbook1);

    // Display all books in the library
    myDigitalLibrary.displayBooks();

    // Display the total number of books ever added
    DigitalLibrary::displayTotalBooksAdded();

    return 0;
}

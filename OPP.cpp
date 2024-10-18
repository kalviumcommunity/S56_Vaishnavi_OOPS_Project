#include <iostream>
#include <string>
using namespace std;

// Base class Book with Encapsulation
class Book {
protected:  // Changed to protected so that derived classes can access these members
    string title;
    string author;
    bool isBorrowed;

public:
    // Default Constructor
    Book() : title(""), author(""), isBorrowed(false) {
        cout << "Book object created with default constructor.\n";
    }

    // Parameterized Constructor
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

    // Function to borrow the book
    virtual void borrowBook() {
        if (!this->isBorrowed) {
            this->isBorrowed = true;
            cout << this->title << " has been borrowed.\n";
        } else {
            cout << this->title << " is already borrowed.\n";
        }
    }

    // Function to return the book
    virtual void returnBook() {
        if (this->isBorrowed) {
            this->isBorrowed = false;
            cout << this->title << " has been returned.\n";
        } else {
            cout << this->title << " was not borrowed.\n";
        }
    }

    // Function to display book details
    virtual void displayDetails() const {
        cout << "Title: " << this->title << ", Author: " << this->author;
        if (this->isBorrowed) {
            cout << " (Borrowed)\n";
        } else {
            cout << " (Available)\n";
        }
    }
};

// Derived class EBook from base class Book (Single Inheritance)
class EBook : public Book {
private:
    double fileSize;  // Additional property for EBook

public:
    // Parameterized Constructor
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

// Derived class PrintedBook from base class Book (Hierarchical Inheritance)
class PrintedBook : public Book {
private:
    int pageCount;  // Additional property for PrintedBook

public:
    // Parameterized Constructor
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

// Base class Library with Encapsulation
class Library {
protected:
    Book** books;  // Array of pointers to Book objects
    int bookCount;  // Number of books currently in the library
    int capacity;  // Capacity of the library

    static int totalBooksAdded;  // Static variable to track the total number of books added

public:
    // Constructor to initialize the library
    Library(int maxBooks) : bookCount(0), capacity(maxBooks) {
        books = new Book*[capacity];  // Allocate array of pointers
        for (int i = 0; i < capacity; i++) {
            books[i] = nullptr;  // Initialize all pointers to nullptr
        }
        cout << "Library created with capacity of " << capacity << " books.\n";
    }

    // Destructor to free allocated memory
    virtual ~Library() {
        for (int i = 0; i < bookCount; i++) {
            delete books[i];  // Delete each dynamically allocated Book object
        }
        delete[] books;  // Delete the array of pointers
        cout << "Library destroyed and memory deallocated.\n";
    }

    // Function to add a book to the library
    virtual void addBook(Book* book) {
        if (bookCount < capacity) {
            books[bookCount] = book;  // Add the Book object
            bookCount++;
            Library::incrementTotalBooksAdded();  // Increment the static variable
            cout << "Book added: " << book->getTitle() << "\n";
        } else {
            cout << "Library is full, cannot add more books.\n";
        }
    }

    // Function to display all books in the library
    void displayBooks() const {
        cout << "Library Collection:\n";
        for (int i = 0; i < bookCount; i++) {
            books[i]->displayDetails();
        }
    }

    // Static function to increment the total number of books added
    static void incrementTotalBooksAdded() {
        totalBooksAdded++;
    }

    // Static function to display the total number of books ever added to the library
    static void displayTotalBooksAdded() {
        cout << "Total number of books ever added: " << totalBooksAdded << "\n";
    }
};

// Derived class DigitalLibrary from Library (Single Inheritance)
class DigitalLibrary : public Library {
public:
    // Constructor that calls the base class constructor
    DigitalLibrary(int maxBooks) : Library(maxBooks) {
        cout << "Digital Library created.\n";
    }

    // Destructor
    ~DigitalLibrary() {
        cout << "Digital Library destroyed.\n";
    }

    // Overriding the addBook function for digital libraries (optional)
    void addBook(Book* book) override {
        cout << "Adding a digital book to the library.\n";
        Library::addBook(book);  // Call base class method
    }
};

// Initialize the static variable
int Library::totalBooksAdded = 0;

// Main function to demonstrate the functionality
int main() {
    // Create DigitalLibrary object with a maximum capacity of 100 books
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
    Library::displayTotalBooksAdded();

    return 0;
}

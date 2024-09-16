#include <iostream>
#include <string>
using namespace std;

// Abstract class to define the library interface
class LibraryInterface {
public:
    // Abstract methods (pure virtual)
    virtual void addBook(const string & title, const string & author) = 0;
    virtual void removeBook(const string & title) = 0;
    virtual void borrowBook(const string & title) = 0;
    virtual void returnBook(const string & title) = 0;
    virtual void displayBooks() const = 0;
    virtual ~LibraryInterface() = default; 
};

// Book class definition with Encapsulation
class Book {
private:
    string title;
    string author;
    bool isBorrowed;

public:
    // Constructor
    Book() : title(""), author(""), isBorrowed(false) {}

    Book(string title, string author) : title(title), author(author), isBorrowed(false) {}

    // Getter for title
    string getTitle() const {
        return this->title;
    }

    // Getter for author
    string getAuthor() const {
        return this->author;
    }

    // Function to borrow the book
    void borrowBook() {
        if (!this->isBorrowed) {
            this->isBorrowed = true;
            cout << this->title << " has been borrowed.\n";
        } else {
            cout << this->title << " is already borrowed.\n";
        }
    }

    // Function to return the book
    void returnBook() {
        if (this->isBorrowed) {
            this->isBorrowed = false;
            cout << this->title << " has been returned.\n";
        } else {
            cout << this->title << " was not borrowed.\n";
        }
    }

    // Function to display book details
    void displayDetails() const {
        if (!this->title.empty()) {
            cout << "Title: " << this->title << ", Author: " << this->author;
            if (this->isBorrowed) {
                cout << " (Borrowed)\n";
            } else {
                cout << " (Available)\n";
            }
        }
    }

    // Function to check if the book is empty
    bool isEmpty() const {
        return this->title.empty();
    }
};

// Library class definition implementing LibraryInterface
class Library : public LibraryInterface {
private:
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
    }

    // Destructor to free allocated memory
    ~Library() override {
        for (int i = 0; i < bookCount; i++) {
            delete books[i];  // Delete each dynamically allocated Book object
        }
        delete[] books;  // Delete the array of pointers
    }

    // Implementing addBook from LibraryInterface
    void addBook(const string& title, const string& author) override {
        if (bookCount < capacity) {
            books[bookCount] = new Book(title, author);  // Dynamically allocate a new Book object
            bookCount++;
            Library::incrementTotalBooksAdded();  // Increment the static variable
            cout << "Book added: " << title << "\n";
        } else {
            cout << "Library is full, cannot add more books.\n";
        }
    }

    // Implementing removeBook from LibraryInterface
    void removeBook(const string& title) override {
        for (int i = 0; i < bookCount; i++) {
            if (books[i]->getTitle() == title) {
                delete books[i];  // Delete the Book object
                cout << "Book removed: " << title << "\n";
                // Shift all the books to fill the gap
                for (int j = i; j < bookCount - 1; j++) {
                    books[j] = books[j + 1];
                }
                books[bookCount - 1] = nullptr;
                bookCount--;
                return;
            }
        }
        cout << "Book not found: " << title << "\n";
    }

    // Implementing borrowBook from LibraryInterface
    void borrowBook(const string& title) override {
        for (int i = 0; i < bookCount; i++) {
            if (books[i]->getTitle() == title) {
                books[i]->borrowBook();
                return;
            }
        }
        cout << "Book not found: " << title << "\n";
    }

    // Implementing returnBook from LibraryInterface
    void returnBook(const string& title) override {
        for (int i = 0; i < bookCount; i++) {
            if (books[i]->getTitle() == title) {
                books[i]->returnBook();
                return;
            }
        }
        cout << "Book not found: " << title << "\n";
    }

    // Implementing displayBooks from LibraryInterface
    void displayBooks() const override {
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

// Initialize the static variable
int Library::totalBooksAdded = 0;

// Main function to demonstrate the functionality using abstraction
int main() {
    // Create Library object with a maximum capacity of 100 books
    Library myLibrary(100);

    // Add books to the library
    myLibrary.addBook("The Great Gatsby", "F. Scott Fitzgerald");
    myLibrary.addBook("1984", "George Orwell");

    // Display all books in the library
    myLibrary.displayBooks();

    // Borrow a book
    myLibrary.borrowBook("1984");

    // Return the book
    myLibrary.returnBook("1984");

    // Remove a book from the library
    myLibrary.removeBook("The Great Gatsby");

    // Display all books in the library
    myLibrary.displayBooks();

    // Display the total number of books ever added
    Library::displayTotalBooksAdded();

    return 0;
}

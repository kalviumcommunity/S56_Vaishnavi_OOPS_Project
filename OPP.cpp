#include <iostream>
#include <string>
using namespace std;

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

    // Setter for title (if required)
    void setTitle(const string& title) {
        this->title = title;
    }

    // Getter for author
    string getAuthor() const {
        return this->author;
    }

    // Setter for author (if required)
    void setAuthor(const string& author) {
        this->author = author;
    }

    // Getter for isBorrowed status
    bool isBookBorrowed() const {
        return this->isBorrowed;
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

// Library class definition with Encapsulation
class Library {
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
    ~Library() {
        for (int i = 0; i < bookCount; i++) {
            delete books[i];  // Delete each dynamically allocated Book object
        }
        delete[] books;  // Delete the array of pointers
    }

    // Function to add a book to the library
    void addBook(const Book& book) {
        if (bookCount < capacity) {
            books[bookCount] = new Book(book);  // Dynamically allocate a new Book object
            bookCount++;
            Library::incrementTotalBooksAdded();  // Increment the static variable
            cout << "Book added: " << book.getTitle() << "\n";
        } else {
            cout << "Library is full, cannot add more books.\n";
        }
    }

    // Function to remove a book from the library by title
    void removeBook(const string& title) {
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

    // Function to display all books in the library
    void displayBooks() const {
        cout << "Library Collection:\n";
        for (int i = 0; i < bookCount; i++) {
            books[i]->displayDetails();
        }
    }

    // Function to borrow a book by title
    void borrowBook(const string& title) {
        for (int i = 0; i < bookCount; i++) {
            if (books[i]->getTitle() == title) {
                books[i]->borrowBook();
                return;
            }
        }
        cout << "Book not found: " << title << "\n";
    }

    // Function to return a book by title
    void returnBook(const string& title) {
        for (int i = 0; i < bookCount; i++) {
            if (books[i]->getTitle() == title) {
                books[i]->returnBook();
                return;
            }
        }
        cout << "Book not found: " << title << "\n";
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

// Main function to demonstrate the functionality
int main() {
    // Create Library object with a maximum capacity of 100 books
    Library myLibrary(100);

    // Create Book objects
    Book book1("The Great Gatsby", "F. Scott Fitzgerald");
    Book book2("1984", "George Orwell");

    // Add books to the library
    myLibrary.addBook(book1);
    myLibrary.addBook(book2);

    // Display all books in the library
    myLibrary.displayBooks();

    // Display the total number of books ever added
    Library::displayTotalBooksAdded();

    // Borrow a book
    myLibrary.borrowBook("1984");

    // Try to borrow the same book again
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

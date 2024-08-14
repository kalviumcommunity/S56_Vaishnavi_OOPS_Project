#include <iostream>
#include <string>
using namespace std;

const int MAX_BOOKS = 100;  // Maximum number of books the library can hold

// Book class definition
class Book {
    // Private data members
    string title;
    string author;
    bool isBorrowed;

public:
    // Constructor
    Book() : title(""), author(""), isBorrowed(false) {}

    Book(string title, string author) : title(title), author(author), isBorrowed(false) {}

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

    // Getter function to access the title
    string getTitle() const {
        return this->title;
    }

    // Function to check if the book is borrowed
    bool isBookBorrowed() const {
        return this->isBorrowed;
    }

    // Function to check if the book is empty (used for removing books)
    bool isEmpty() const {
        return this->title.empty();
    }
};

// Library class definition
class Library {
    // Private data members
    Book books[MAX_BOOKS];  // Array of Book objects
    int bookCount;  // Number of books currently in the library

public:
    // Constructor to initialize the library
    Library() : bookCount(0) {}

    // Function to add a book to the library
    void addBook(const Book& book) {
        if (bookCount < MAX_BOOKS) {
            books[bookCount] = book;
            bookCount++;
            cout << "Book added: " << book.getTitle() << "\n";
        } else {
            cout << "Library is full, cannot add more books.\n";
        }
    }

    // Function to remove a book from the library by title
    void removeBook(const string& title) {
        for (int i = 0; i < bookCount; i++) {
            if (books[i].getTitle() == title) {
                books[i] = Book();  // Remove the book by setting it to an empty book
                cout << "Book removed: " << title << "\n";
                // Shift all the books to fill the gap
                for (int j = i; j < bookCount - 1; j++) {
                    books[j] = books[j + 1];
                }
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
            books[i].displayDetails();
        }
    }

    // Function to borrow a book by title
    void borrowBook(const string& title) {
        for (int i = 0; i < bookCount; i++) {
            if (books[i].getTitle() == title) {
                books[i].borrowBook();
                return;
            }
        }
        cout << "Book not found: " << title << "\n";
    }

    // Function to return a book by title
    void returnBook(const string& title) {
        for (int i = 0; i < bookCount; i++) {
            if (books[i].getTitle() == title) {
                books[i].returnBook();
                return;
            }
        }
        cout << "Book not found: " << title << "\n";
    }
};

// Main function to demonstrate the functionality
int main() {
    // Create Library object
    Library myLibrary;

    // Create Book objects
    Book book1("The Great Gatsby", "F. Scott Fitzgerald");
    Book book2("1984", "George Orwell");

    // Add books to the library
    myLibrary.addBook(book1);
    myLibrary.addBook(book2);

    // Display all books in the library
    myLibrary.displayBooks();

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

    return 0;
}

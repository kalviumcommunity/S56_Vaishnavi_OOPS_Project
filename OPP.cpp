#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Book class definition
class Book {
    // Private data members
    string title;
    string author;
    bool isBorrowed;

public:
    // Constructor
    Book() : title(""), author(""), isBorrowed(false) {}

    Book(string t, string a) : title(t), author(a), isBorrowed(false) {}

    // Function to borrow the book
    void borrowBook() {
        if (!isBorrowed) {
            isBorrowed = true;
            cout << title << " has been borrowed.\n";
        } else {
            cout << title << " is already borrowed.\n";
        }
    }

    // Function to return the book
    void returnBook() {
        if (isBorrowed) {
            isBorrowed = false;
            cout << title << " has been returned.\n";
        } else {
            cout << title << " was not borrowed.\n";
        }
    }

    // Function to display book details
    void displayDetails() const {
        if (!title.empty()) {
            cout << "Title: " << title << ", Author: " << author;
            if (isBorrowed) {
                cout << " (Borrowed)\n";
            } else {
                cout << " (Available)\n";
            }
        }
    }

    // Getter function to access the title
    string getTitle() const {
        return title;
    }

    // Function to check if the book is borrowed
    bool isBookBorrowed() const {
        return isBorrowed;
    }
};

// Library class definition
class Library {
    // Private data members
    vector<Book> books;

public:
    // Function to add a book to the library
    void addBook(const Book& book) {
        books.push_back(book);
        cout << "Book added: " << book.getTitle() << "\n";
    }

    // Function to remove a book from the library by title
    void removeBook(const string& title) {
        for (auto it = books.begin(); it != books.end(); ++it) {
            if (it->getTitle() == title) {
                books.erase(it);
                cout << "Book removed: " << title << "\n";
                return;
            }
        }
        cout << "Book not found: " << title << "\n";
    }

    // Function to display all books in the library
    void displayBooks() const {
        cout << "Library Collection:\n";
        for (const auto& book : books) {
            book.displayDetails();
        }
    }

    // Function to borrow a book by title
    void borrowBook(const string& title) {
        for (auto& book : books) {
            if (book.getTitle() == title) {
                book.borrowBook();
                return;
            }
        }
        cout << "Book not found: " << title << "\n";
    }

    // Function to return a book by title
    void returnBook(const string& title) {
        for (auto& book : books) {
            if (book.getTitle() == title) {
                book.returnBook();
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

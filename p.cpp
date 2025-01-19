#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Book {
public:
    string id;
    string title;
    string author;
    string publisher;
    string isbn;
    int quantity;

    Book(string id, string title, string author, string publisher, string isbn, int quantity)
        : id(id), title(title), author(author), publisher(publisher), isbn(isbn), quantity(quantity) {}
};

class Library {
private:
    vector<Book> books;

public:
    void addBook(const Book& book) {
        auto it = find_if(books.begin(), books.end(),
            [&book](const Book& b) { return b.isbn == book.isbn; });
        
        if (it != books.end()) {
            cout << "Book with ISBN " << book.isbn << " already exists. Updating quantity." << endl;
            it->quantity += book.quantity;
        } else {
            books.push_back(book);
            cout << "Book added successfully." << endl;
        }
    }

    void searchBook(const string& query) {
        bool found = false;
        for (const auto& book : books) {
            if (book.title.find(query) != string::npos ||
                book.author.find(query) != string::npos ||
                book.isbn.find(query) != string::npos) {
                displayBook(book);
                found = true;
            }
        }
        if (!found) {
            cout << "No books found matching the query." << endl;
        }
    }

    void displayAllBooks() {
        if (books.empty()) {
            cout << "The library is empty." << endl;
            return;
        }
        for (const auto& book : books) {
            displayBook(book);
        }
    }

    void checkOutBook(const string& isbn) {
        auto it = find_if(books.begin(), books.end(),
            [&isbn](const Book& b) { return b.isbn == isbn; });
        
        if (it != books.end() && it->quantity > 0) {
            it->quantity--;
            cout << "Book checked out successfully." << endl;
        } else if (it != books.end() && it->quantity == 0) {
            cout << "Sorry, this book is currently out of stock." << endl;
        } else {
            cout << "Book not found in the library." << endl;
        }
    }

    void checkInBook(const string& isbn) {
        auto it = find_if(books.begin(), books.end(),
            [&isbn](const Book& b) { return b.isbn == isbn; });
        
        if (it != books.end()) {
            it->quantity++;
            cout << "Book checked in successfully." << endl;
        } else {
            cout << "Book not found in the library." << endl;
        }
    }

private:
    void displayBook(const Book& book) {
        cout << "ID: " << book.id << "\n"
            << "Title: " << book.title << "\n"
            << "Author: " << book.author << "\n"
            << "Publisher: " << book.publisher << "\n"
            << "ISBN: " << book.isbn << "\n"
            << "Quantity: " << book.quantity << "\n"
            << "------------------------" << endl;
    }
};

int main() {
    Library library;

    // Adding some sample books
    library.addBook(Book("1", "The Great Gatsby", "F. Scott Fitzgerald", "Scribner", "9780743273565", 5));
    library.addBook(Book("2", "To Kill a Mockingbird", "Harper Lee", "J. B. Lippincott & Co.", "9780446310789", 3));
    library.addBook(Book("3", "1984", "George Orwell", "Secker & Warburg", "9780451524935", 4));

    int choice;
    string query, isbn;

    do {
        cout << "\nLibrary Management System\n";
        cout << "1. Add a book\n";
        cout << "2. Search for a book\n";
        cout << "3. Display all books\n";
        cout << "4. Check out a book\n";
        cout << "5. Check in a book\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string id, title, author, publisher, isbn;
                int quantity;
                cout << "Enter book details:\n";
                cout << "ID: ";
                cin >> id;
                cin.ignore();
                cout << "Title: ";
                getline(cin, title);
                cout << "Author: ";
                getline(cin, author);
                cout << "Publisher: ";
                getline(cin, publisher);
                cout << "ISBN: ";
                cin >> isbn;
                cout << "Quantity: ";
                cin >> quantity;
                library.addBook(Book(id, title, author, publisher, isbn, quantity));
                break;
            }
            case 2:
                cout << "Enter search query: ";
                cin.ignore();
                getline(cin, query);
                library.searchBook(query);
                break;
            case 3:
                library.displayAllBooks();
                break;
            case 4:
                cout << "Enter ISBN of the book to check out: ";
                cin >> isbn;
                library.checkOutBook(isbn);
                break;
            case 5:
                cout << "Enter ISBN of the book to check in: ";
                cin >> isbn;
                library.checkInBook(isbn);
                break;
            case 0:
                cout << "Exiting the program. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}
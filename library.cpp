#include <iostream>
#include <vector>
#include <fstream>
#include <limits>

using namespace std;

class Book {
public:
    int id;
    string title;
    string author;
    bool available;

    Book(int _id, string _title, string _author) {
        id = _id;
        title = _title;
        author = _author;
        available = true;
    }

    void display() {
        cout << id << " | " << title << " | " << author
             << " | " << (available ? "Available" : "Issued") << endl;
    }
};

// Book list (Load from File)
vector<Book> books;

void loadBooks() {
    ifstream file("../data/books.dat");
    if (!file) return;

    int id;
    string title, author;
    bool available;
    while (file >> id) {
        file.ignore();
        getline(file, title);
        getline(file, author);
        file >> available;
        books.emplace_back(id, title, author);
        books.back().available = available;
    }
    file.close();
}

void saveBooks() {
    ofstream file("../data/books.dat");
    for (Book &b : books) {
        file << b.id << endl << b.title << endl << b.author << endl << b.available << endl;
    }
    file.close();
}

void addBook() {
    int id;
    string title, author;

    cin >> id;
    cin.ignore();
    getline(cin, title);
    getline(cin, author);

    books.push_back(Book(id, title, author));
    saveBooks();
}

void displayBooks() {
    loadBooks();
    if (books.empty()) {
        cout << "No books available.\n";
    } else {
        for (Book &b : books) {
            b.display();
        }
    }
}

void issueBook() {
    int id;
    cin >> id;
    
    for (Book &b : books) {
        if (b.id == id) {
            if (b.available) {
                b.available = false;
                cout << "Book issued successfully!\n";
                saveBooks();
                return;
            } else {
                cout << "Book already issued!\n";
                return;
            }
        }
    }
    cout << "Book not found!\n";
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Invalid arguments\n";
        return 1;
    }

    int option = stoi(argv[1]);

    switch (option) {
        case 1: addBook(); break;
        case 2: displayBooks(); break;
        case 3: issueBook(); break;
        default: cout << "Invalid choice\n";
    }

    return 0;
}

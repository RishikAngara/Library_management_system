#include <stdio.h>
#include <stdlib.h>

struct Book {
    int id;
    char title[50];
    char author[50];
    int available;
};

void addBook() {
    struct Book b;
    FILE *file = fopen("../data/books.dat", "ab");

    printf("Enter Book ID: ");
    scanf("%d", &b.id);
    printf("Enter Title: ");
    scanf(" %[^\n]", b.title);
    printf("Enter Author: ");
    scanf(" %[^\n]", b.author);
    b.available = 1;

    fwrite(&b, sizeof(struct Book), 1, file);
    fclose(file);
    printf("Book added successfully!\n");
}

void displayBooks() {
    struct Book b;
    FILE *file = fopen("../data/books.dat", "rb");

    while (fread(&b, sizeof(struct Book), 1, file)) {
        printf("%d | %s | %s | %s\n", b.id, b.title, b.author, b.available ? "Available" : "Issued");
    }
    fclose(file);
}

int main() {
    addBook();
    displayBooks();
    return 0;
}

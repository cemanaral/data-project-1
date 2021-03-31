/*
    Cem Anaral 150119761
    Tevfik Arici 1
    Ali Yetim 150

*/

#include <stdio.h>
#include <stdlib.h> // For malloc
#include <string.h> // For strtok()

// File name macros
#define CUSTOMER_FILE "customer.txt"
#define BASKET_FILE "basket.txt"
#define PRODUCT_FILE "product.txt"
#define BUFFER 30 // for reading files

struct Customer {
    int id;
    char* name;
    char* surname;
    struct Basket* basketList;
};

struct Basket {
    int id;
    struct Product* productList;
    int amount; // Total price
};

struct Product {
    int id;
    char* name;
    char* category;
    struct Product* nextPtr;
};

// Typedefs
typedef struct Customer Customer;
typedef Customer* CustomerPtr;

typedef struct Basket Basket;
typedef Basket* BasketPtr;

typedef struct Product Product;
typedef Product* ProductPtr;
////////


// Global head ptrs for convinience
CustomerPtr headCustomer = NULL;
BasketPtr headBasket = NULL;
ProductPtr headProduct = NULL;
///////////////

void readCustomerFile() {
    /*
        Reads CUSTOMER_FILE and inserts into headCustomer
    */
    FILE* file;
    char currentLine[100];  // 100 is our buffer.

    file = fopen(CUSTOMER_FILE, "r");

    // For reading the file
    int id;
    char name[BUFFER];
    char surname[BUFFER];

    // Reading starts here
    while(fgets(currentLine, 100, file)) {
        sscanf(currentLine, "%d %s %s", &id, name, surname);

        printf("id: %d, name: %s, surname: %s\n", id, name, surname);
    }

    fclose(file);
}

int main() {
    readCustomerFile();


    return 0;
}


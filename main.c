/*
    Cem Anaral 150119761
    Tevfik Arici 1
    Ali Yetim 150

*/

#include <stdio.h>
#include <stdlib.h>

// File name macros
#define CUSTOMER_FILE "customer.txt"
#define BASKET_FILE "basket.txt"
#define PRODUCT_FILE "product.txt"

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

    while(fgets(currentLine, 100, file)) {
        printf("%s\n", currentLine);
    }

    fclose(file);
}

int main() {
    readCustomerFile();


    return 0;
}


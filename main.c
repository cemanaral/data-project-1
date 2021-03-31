/*
    Cem Anaral 150119761
    Tevfik Arici 1
    Ali Yetim 150

*/

#include <stdio.h>
#include <stdlib.h>

// File name macros
#define CUSTOMER_FILE "customer.txt";
#define BASKET_FILE "basket.txt";
#define PRODUCT_FILE "product.txt";

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



int main() {
    return 0;
}


/*
    Cem Anaral 150119761
    Tevfik Arici 1
    Ali Yetim 150

*/

#include <stdio.h>
#include <stdlib.h>

struct Customer {
    int id;
    char* name;
    char* surname;
    struct Basket* basketList;
};

typedef struct Customer Customer;
typedef Customer* CustomerPtr;


struct Basket {
    int id;
    struct Product* productList;
    int amount; // Total price
};

typedef struct Basket Basket;
typedef Basket* BasketPtr;

struct Product {
    int id;
    char* name;
    char* category;
    struct Product* nextPtr;
};

typedef struct Product Product;
typedef Product* ProductPtr;



int main() {
    return 0;
}


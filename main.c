#include <stdio.h>
#include <stdlib.h>

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




int main() {
    return 0;
}


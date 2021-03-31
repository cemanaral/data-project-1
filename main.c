#include <stdio.h>
#include <stdlib.h>

struct Customer {
    char* name;
    char* surname;
    struct Basket* basketList;
};

struct Basket {
    int id;
    int amount;
    struct Product* productList;
};


struct Product {
    int id;
    struct Product* nextPtr;
};




int main() {
    return 0;
}


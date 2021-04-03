/*
    Cem Anaral 150119761
    Tevfik Arici 1
    Ali Yetim 150119803

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
    struct Customer* nextPtr;
};

struct Basket {
    int id;
    struct Product* productList;
    int amount; // Total price
    struct Basket* nextPtr;
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

// TODO: findName() 


void addCustomer(CustomerPtr* headCustomer, int id, char* name, char* surname) {
    /*
        Adds customer to headCustomer linked list.
    */
    CustomerPtr newCustomerPtr = (CustomerPtr)malloc(sizeof(Customer));
    CustomerPtr currentCustomerPtr = *headCustomer;

    // insert starts here
    newCustomerPtr->id = id;
    strcpy( newCustomerPtr->name, name );
    strcpy( newCustomerPtr->surname, surname );
    newCustomerPtr->basketList = NULL;
    newCustomerPtr->nextPtr = NULL;
    ///////////

    // If linked list is empty, inserts to head and terminates function
    if (*headCustomer == NULL) {
        *headCustomer = newCustomerPtr;
        return;
    }


    // Finds the last node
    while (currentCustomerPtr->nextPtr != NULL) {
        currentCustomerPtr = currentCustomerPtr->nextPtr;
    }
    
    currentCustomerPtr->nextPtr = newCustomerPtr;
}

void printCustomers() {
    CustomerPtr currentNode = headCustomer;

    if (headCustomer == NULL) {
        puts("Customer List is empty");
        return;
    }

    puts("**Customer List**");
    while (currentNode->nextPtr != NULL) {
        printf("id: %d, name: %s, surname: %s\n", 
            currentNode->id, currentNode->name, currentNode->surname);
        currentNode = currentNode->nextPtr;
    }
    printf("\n");
}

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
        printf("%d", id);
        addCustomer(&headCustomer, id, name, surname);
    }

    fclose(file);
}

int main() {
    readCustomerFile();
    printCustomers();

    return 0;
}


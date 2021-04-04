/*
    Cem Anaral 150119761
    Tevfik Arici 1
    Ali Yetim 150119803

*/

#include <stdio.h>
#include <stdlib.h> // For malloc
#include <string.h>

// File name macros
#define CUSTOMER_FILE "customer.txt"
#define BASKET_FILE "basket.txt"
#define PRODUCT_FILE "product.txt"
#define BUFFER 100 // for reading files and to determine max length of strings

struct Customer {
    int id;
    char name[BUFFER / 2];
    char surname[BUFFER / 2];
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
    char name[BUFFER / 2];
    char category[BUFFER / 2];
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

int isEmpty(void *headPtr) {
    /*
        If head pointer is empty, returns 1
        else returns 0
    */

    return headPtr == 0;
}


CustomerPtr findCustomer(int id) {
    /*
        Finds customer by id and returns its memory address.
    */
    CustomerPtr currentCustomerPtr = NULL;
    
    if (!isEmpty(headCustomer)) {    // If list is not empty, finds the currentCustomerPtr
        currentCustomerPtr = headCustomer;
        while (currentCustomerPtr != NULL && currentCustomerPtr->id != id) {
            currentCustomerPtr = currentCustomerPtr->nextPtr;
        }
        
    }

    return currentCustomerPtr;
} 


void addCustomer(int id, char* name, char* surname) {
    /*
        Adds customer to headCustomer linked list.
    */
    CustomerPtr newCustomerPtr = (CustomerPtr)malloc(sizeof(Customer));
    CustomerPtr currentCustomerPtr = headCustomer;

    // insertion to data fields of newCustomerPtr
    newCustomerPtr->id = id;
    strcpy(newCustomerPtr->name, name);
    strcpy( newCustomerPtr->surname, surname );
    newCustomerPtr->basketList = NULL;
    newCustomerPtr->nextPtr = NULL;
    ///////////

    // If linked list is empty, inserts to headCustomer and terminates function
    if (isEmpty(headCustomer)) {
        headCustomer = newCustomerPtr;
        return;
    }


    // Finds the last node
    while (currentCustomerPtr->nextPtr != NULL) {
        currentCustomerPtr = currentCustomerPtr->nextPtr;
    }
    
    currentCustomerPtr->nextPtr = newCustomerPtr;
}


void printCustomers() {
    /*
        Prints customers that are in headCustomer linked list.
    */
    CustomerPtr currentNode = headCustomer;

    if (isEmpty(headCustomer)) {
        puts("Customer List is empty");
        return;
    }

    puts("**Customer List**");
    while (currentNode->nextPtr != NULL) {
        printf("id: %d, name: %s, surname: %s\n", 
            currentNode->id, currentNode->name, currentNode->surname);
        currentNode = currentNode->nextPtr;
    }
    printf("id: %d, name: %s, surname: %s\n", 
            currentNode->id, currentNode->name, currentNode->surname);
    printf("\n");
}

void readCustomerFile() {
    /*
        Reads CUSTOMER_FILE and inserts into headCustomer
    */
    FILE* file;
    char currentLine[BUFFER];  // 100 is our buffer.

    file = fopen(CUSTOMER_FILE, "r");

    // For reading the file
    int id;
    char name[BUFFER / 2];
    char surname[BUFFER / 2];

    // Reading starts here
    while(fgets(currentLine, BUFFER, file)) {
        sscanf(currentLine, "%d %s %s", &id, name, surname);
        // printf( "%d %s %s\n", id, name, surname);
        addCustomer(id, name, surname);
    }

    fclose(file);
}

int main() {
    // printf("is empty customer: %d\n", isEmpty(headCustomer));
    readCustomerFile();
    printCustomers();
    // printf("is empty customer: %d\n", isEmpty(headCustomer));

    // printf("is empty product: %d\n", isEmpty(headProduct));
    // printf("is empty basket: %d\n", isEmpty(headBasket));
    
    printf("address of id 6 is %p", findCustomer(6));
    
    return 0;
}


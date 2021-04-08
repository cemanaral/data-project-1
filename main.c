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

///////////////////
// For struct Basket
struct ProductList {
    int productID;
    struct ProductList* next;
};

struct Basket {
    int id;
    int amount; // Total price
    struct Basket* nextPtr;
    struct ProductList* productList;
};
///////////////////


// For an indepented linked list for products
struct Product {
    int id;
    int price;
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

typedef struct ProductList ProductList;
typedef ProductList* ProductListPtr;
////////

// function declerations (only needed ones for compilation)
void addBasket(int customerID, int basketID, int productID);
BasketPtr getBasket(CustomerPtr customer, int basketID);
void addProductList(BasketPtr basket, int productID);
void printBaskets(CustomerPtr customer);
void printProductList(ProductListPtr currentProductList);
CustomerPtr getCustomer(int customerID);
void incrementBasketPrice(BasketPtr basket);
ProductPtr getProductInfo(int productID);
int isEmpty(void *headPtr);
CustomerPtr findCustomer(int id);
///////////////

// Global head ptrs for convinience
CustomerPtr headCustomer = NULL;
ProductPtr  headProduct = NULL;
///////////////

// imports functions from other files
#include "Customer.h"
#include "Basket.h"
#include "Product.h"
////////////////////////////////////


int isEmpty(void *headPtr) {
    /*
        If head pointer is empty, returns 1
        else returns 0
    */

    return headPtr == 0;
}

void instructions() {
    /*
        Prints main menu instructions
    */

    puts("1. Add a customer");
    puts("2. Add basket");
    puts("3. Remove customer");
    puts("4. List the customers who bought a specific product");
    puts("5. List the total shopping amounts of each customer");
    puts("6. Exit\n");

}

int getChoice() {
    /*
        Gets choice from STDIN and returns it
    */

    int choice;
    printf("? ");
    scanf("%d", &choice);
    return choice;
}

int isUnique(char name[BUFFER/2], char surname[BUFFER/2]) {
    /*      
        Checks whether the name and surname are unique
        If unique returns 1
        if not, returns 0
    */
    
    CustomerPtr currentCustomer = headCustomer;
    int isNameUnique;
    int isSurnameUnique;
    
    while (currentCustomer != NULL)
    {
        isNameUnique = strcmp(currentCustomer->name, name) == 0;
        isSurnameUnique = strcmp(currentCustomer->surname, surname) == 0;
        if (isNameUnique && isSurnameUnique) {
            printf("%s %s is already in the system!\n", name, surname);
            return 0;

        }
        currentCustomer = currentCustomer->nextPtr;
    }
    return 1;
}



int main() {

    // Reading operations
    readCustomerFile();
    // printCustomers();    
    readProductFile();
    // printProducts();
    readBasketFile();
    ////////////////////

    // increments amount of every basket after reading
    CustomerPtr currentCustomer = headCustomer;
    BasketPtr currentBasket;

    while (currentCustomer != NULL) { // Loops every customer
        currentBasket = currentCustomer->basketList;
        while (currentBasket != NULL) { // Loops every basket of the customer
            incrementBasketPrice(currentBasket);    // increments the basket
            currentBasket = currentBasket->nextPtr;
        }
        currentCustomer = currentCustomer->nextPtr;
    }
    /////////////////////////////////////////////////

    puts("Data Structures PROJECT #1 E-COMMERCE SYSTEM");
    puts("Cem Anaral | Ali Yetim | Tevfik Arici");
    int choice;
    instructions();
    while ((choice = getChoice()) != 6 ) // While choice is not 6 (which is the exit condition)
    {
        // Add a customer
        if (choice == 1) {
            puts("1");

            // Print all customers name and surname etc
            printCustomers();

            // Gets a name and surname
            char newName[BUFFER/2];
            char newSurname[BUFFER/2];

            // while name and surname is not unique
            // gets name and surname from stdin
            do {
                printf("please enter name and surname (? Name Surname)\n? ");
                scanf("%s %s", newName, newSurname);

            } while (!isUnique(newName, newSurname));    


            // gets the last ID in customer list
            int lastID;
            CustomerPtr currentCustomer = headCustomer;

            //  currentCustomer != NULL to not get segmentation fault if no one is in the list
            while (currentCustomer != NULL && currentCustomer->nextPtr != NULL)
                currentCustomer = currentCustomer->nextPtr;
            
            if (currentCustomer == NULL) // If list is empty, ID of the customer will be 1.
                lastID = 1;
            else // ID will be 1 more than the last
                lastID = currentCustomer->id + 1;
            /////////////////////////////////////////////////

            printf("%d \n", lastID);
            // Adds the customer
            addCustomer(lastID, newName, newSurname);
            printCustomers();
        }

        else if (choice == 2) {
            puts("2");
        }

        else if (choice == 3) {
            puts("3");
        }

        else if (choice == 4) {
            puts("4");
        }

        else if (choice == 5) {
            puts("5");
        }

        instructions();
    }

    return 0;

}


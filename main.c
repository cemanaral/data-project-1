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

void CLI_addCustomer() {
    /*
        Adds customer from STDIN
    */

    // Print all customers
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

void CLI_addBasket() {
    /*
        Adds basket from STDIN
    */

    // 2.a. List customers    
    printCustomers();

    // 2.b. Select one of the customers
    CustomerPtr customer;
    int customerID;
    printf("Please type the ID of the customer\n? ");
    scanf("%d", &customerID);
    customer = getCustomer(customerID);

    // 2.c. List the products
    printProducts();

    // 2.d Add a product
    
    // gets basket id
    int basketID;
    BasketPtr basket;
    if (customer->basketList == NULL)
    {
        basketID = 1;
        customer->basketList = (BasketPtr)malloc(sizeof(Basket));
        customer->basketList->id = basketID;
        customer->basketList->amount = 0;
        customer->basketList->nextPtr = NULL;
        basket = customer->basketList;
    }
    else {  // finds the last basket ID and increments it
        BasketPtr currentBasket = customer->basketList;
        while (currentBasket != NULL && currentBasket->nextPtr != NULL)
            currentBasket = currentBasket->nextPtr;
        basketID = currentBasket->id + 1;
        basket = (BasketPtr)malloc(sizeof(Basket));
        basket->amount = 0;
        basket->id = basketID;
        basket->nextPtr = NULL;

        currentBasket->nextPtr = basket;
    }
    
    
    
    int productID;
    ProductListPtr currentProductNode;
    ProductListPtr newProductNode;
    do {
        printf("Please type product id (-1 to exit)\n? ");
        scanf("%d", &productID);
        if (productID == -1)
            break;

        // add to basket
        addBasket(customerID, basketID, productID);
        /*
        currentProductNode = basket->productList;
        if (basket->productList == NULL) {
            basket->productList->productID = productID;
            basket->productList->next = NULL;
        } else {
            while (currentProductNode->next != NULL)
                currentProductNode = currentProductNode->next;
            newProductNode = (ProductListPtr)malloc(sizeof(ProductList));
            newProductNode->productID = productID;
            newProductNode->next = NULL;
            currentProductNode->next = newProductNode;
        }
        */

        // increments amount of the basket
        // incrementBasketPrice(basket);
        basket->amount += getProductInfo(productID)->price;

    } while (1);

    printBaskets(customer);
    // !!!BUG!!!!! onceden customer ekleyip cikarinca bi sorun olmuyor
    // 2.e Complete shopping



}

void CLI_removeCustomer() {
    // List all customers
    printCustomers();
    
    char name[BUFFER/2];
    char surname[BUFFER/2];
    printf("Please enter name and surname which will be deleted (? name surname)\n? ");
    scanf("%s %s", name, surname);

    deleteCustomer(name, surname);
    printCustomers();
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
            CLI_addCustomer();
        }

        // Add basket:
        else if (choice == 2) {
            CLI_addBasket();
        }

        // Remove Customer
        else if (choice == 3) {
            CLI_removeCustomer();
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


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

// function declerations
void addBasket(int customerID, int basketID, int productID);
BasketPtr getBasket(CustomerPtr customer, int basketID);
void addProductList(BasketPtr basket, int productID);
void printBaskets(CustomerPtr customer);
void printProductList(ProductListPtr currentProductList);
////////

// Global head ptrs for convinience
CustomerPtr headCustomer = NULL;
ProductPtr  headProduct = NULL;
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
    
    // insertion to the basketList
    newCustomerPtr->basketList = NULL; // creates an empty basket
    newCustomerPtr->nextPtr = NULL;
    /////////////////////////////////////////////

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

void printProducts() {
    /*
        Prints headProduct list.
    */
    ProductPtr currentNode = headProduct;

    if (isEmpty(headProduct)) {
        puts("Product list is empty.");
        return;
    }

    puts("**Product List**");

    while(currentNode->nextPtr != NULL) {
        printf("id: %d name: %s category: %s price: %d\n",
            currentNode->id, currentNode->name,
            currentNode->category, currentNode->price);

        currentNode = currentNode->nextPtr;
    }
    printf("id: %d name: %s category: %s price: %d\n",
            currentNode->id, currentNode->name,
            currentNode->category, currentNode->price);
    printf("\n");


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



void readBasketFile() {
    /*
        Reads basket.txt
    */
    FILE* file;
    char currentLine[BUFFER];

    file = fopen(BASKET_FILE, "r");

    int customerID;
    int basketID;
    int productID;

    while(fgets(currentLine, BUFFER, file)) {
        sscanf(currentLine, "%d %d %d", &customerID, &basketID, &productID);
        addBasket(customerID,basketID, productID);
        // printf( "customerID: %d basketID: %d productID: %d\n", customerID, basketID, productID);
    }

    fclose(file);    
}


// TODO: findProduct()


void addBasket(int customerID, int basketID, int productID) {
    /*
        Adds basket to customer
        and puts product in the basket.
    */
    CustomerPtr customer = findCustomer(customerID);
    BasketPtr currentBasket = customer->basketList;

    // if basket does not exists, creates new basket
    // and appends it to end
   if (getBasket(customer, basketID) == NULL) {
        BasketPtr newBasket = (BasketPtr)malloc(sizeof(Basket));
        
        newBasket->id = basketID;
        newBasket->amount = 0;
        newBasket->nextPtr = NULL;

        // finds the correct location to add new basket
        if (customer->basketList == NULL)
            customer->basketList = newBasket;
        else {
            while (currentBasket->nextPtr != NULL) {
                currentBasket = currentBasket->nextPtr;
            }
            currentBasket->nextPtr = newBasket;
        }
    }

    
    currentBasket = customer->basketList;
    // finds the correct basket to add product
    while (currentBasket->nextPtr != NULL && currentBasket->id != basketID) 
        currentBasket = currentBasket->nextPtr;

    if (currentBasket == NULL) {
        puts("Error! currentBasket is NULL");
        return;
    }

    // If currentBasket->productList is empty
    if (currentBasket->productList == NULL) {
        currentBasket->productList = (ProductListPtr)malloc(sizeof(ProductList));
        currentBasket->productList->productID = productID;
        currentBasket->productList->next = NULL;
    }

    else {
        // getting to the end of productlist
        // to append new product node
        ProductListPtr currentProductListPtr = currentBasket->productList;
        while (currentProductListPtr->next != NULL)
            currentProductListPtr = currentProductListPtr->next;
        
        currentProductListPtr->next = (ProductListPtr)malloc(sizeof(ProductList));
        currentProductListPtr->next->productID = productID;
    }
     

}

void addProductList(BasketPtr basket, int productID) {
    /*
        Adds product to basket
    */
    ProductListPtr newProductListPtr = (ProductListPtr)malloc(sizeof(ProductList));
    ProductListPtr currentProductListPtr = basket->productList;

    newProductListPtr->next = NULL;
    newProductListPtr->productID = productID;

    // if productlist is empty
    if (isEmpty(basket->productList)) {
        basket->productList = newProductListPtr;
        return;
    }

    // Finds the last node
    while (currentProductListPtr->next != NULL) {
        currentProductListPtr = currentProductListPtr->next;
    }

    currentProductListPtr->next = newProductListPtr;

}

BasketPtr getBasket(CustomerPtr customer, int basketID) {
    /*
        Returns the desired basket of Customer
    */
    BasketPtr currentBasket = customer->basketList;

    // finds the correct basket
    while (currentBasket != NULL && currentBasket->id != basketID) {
        currentBasket = currentBasket->nextPtr;
    }

    if (currentBasket != NULL && currentBasket->id != basketID) {
        puts("basket does not exist");
        return NULL;
    }
    return currentBasket;
}

void addProduct(int id, char *name, char *category, int price) {
    /*
        Adds product to headProduct linked list.
    */
    ProductPtr previousPtr = NULL;
    ProductPtr currentPtr = headProduct;
    ProductPtr newProductPtr = (ProductPtr) malloc(sizeof(Product));

    // data insertion
    newProductPtr->id = id;
    strcpy(newProductPtr->name, name);
    strcpy(newProductPtr->category, category);
    newProductPtr->price = price;

    // while (currentPtr != NULL && currentPtr->name[0] <= newProductPtr->name[0])
    while (currentPtr != NULL &&  currentPtr->name[0] <= newProductPtr->name[0] ){
        previousPtr = currentPtr;
        currentPtr = currentPtr->nextPtr;
    }

    if (previousPtr == NULL) { // If list is empty
        newProductPtr->nextPtr = NULL;
        headProduct = newProductPtr;
    }

    else {
        previousPtr->nextPtr = newProductPtr;
        newProductPtr->nextPtr = currentPtr;
    }

}

void readProductFile() {
    FILE* file;
    char currentLine[BUFFER];

    file = fopen(PRODUCT_FILE, "r");

    int id;
    char name[BUFFER / 2];
    char category[BUFFER / 2];
    int price;

    while(fgets(currentLine, BUFFER, file)) {
        sscanf(currentLine, "%d %s %s %d", 
            &id, name, category, &price);


        addProduct(id, name, category, price);
        // printf( "id: %d name: %s category: %s price: %d\n",
        //     id, name, category, price);
    }

    fclose(file);


}


void deleteCustomer(char *name, char *surname) {

    CustomerPtr temp = headCustomer;

    while (strcmp(temp->nextPtr->name, name) && strcmp(temp->nextPtr->surname, surname) && temp->nextPtr != NULL) {
        temp = temp->nextPtr;
    }

    if (temp->nextPtr->nextPtr != NULL) {
        CustomerPtr temp1 = temp->nextPtr;
        temp->nextPtr = temp1->nextPtr;
        free(temp1);
    } else {
        CustomerPtr temp1 = temp->nextPtr;
        free(temp1->nextPtr);
    }
}

void printBaskets(CustomerPtr customer) {
    /*
        Prints all baskets (and products) of a customer
    */

    BasketPtr currentBasket = customer->basketList;
    ProductListPtr currentProductList;
    while (currentBasket != NULL) {
        currentProductList = currentBasket->productList;

        printf("\tBasket id: %d \n", currentBasket->id);
        while (currentProductList != NULL) {
            printf("\t\tProduct id: %d \n", currentProductList->productID);
            currentProductList = currentProductList->next;
        }
        currentBasket = currentBasket->nextPtr;
    }
        


}

void printProductList(ProductListPtr currentProductList) {
    /*
        Prints a productList linked list
    */
    while (currentProductList->next != NULL)
        printf(" %d", currentProductList->productID);
    printf(" %d", currentProductList->productID);
}

int main() {
    readCustomerFile();
    // printCustomers();
    
    readProductFile();
    // printProducts();

    readBasketFile();

    
    CustomerPtr currentcustomer = headCustomer;
    printBaskets(headCustomer);
            
    return 0;
}


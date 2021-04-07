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
    }

    fclose(file);    
}



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




void printBaskets(CustomerPtr customer) {
    /*
        Prints all baskets (and products) of a customer
    */

    BasketPtr currentBasket = customer->basketList;
    ProductListPtr currentProductList;
    
    printf("Customer ID: %d\n", customer->id);

    while (currentBasket != NULL) {
        currentProductList = currentBasket->productList;

        printf("\tBasket id: %d  |  Total Amount: %d \n", currentBasket->id, currentBasket->amount);
        while (currentProductList != NULL) {
            printf("\t\tProduct id: %d \n", currentProductList->productID);
            currentProductList = currentProductList->next;
        }
        currentBasket = currentBasket->nextPtr;
    }
    printf("\n");
}



void incrementBasketPrice(BasketPtr basket) {
    /*
        Increments basket prices
        after reading operations are done
    */

    ProductListPtr currentProductNode = basket->productList;
    int price;
    while (currentProductNode != NULL) {
        price = getProductInfo(currentProductNode->productID)->price;
        basket->amount += price;
        currentProductNode = currentProductNode->next;
    }

    return;
}
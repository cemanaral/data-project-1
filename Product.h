
void printProducts() {
    /*
        Prints headProduct list.
    */
    ProductPtr currentNode = headProduct;

    while (currentNode != NULL) {
        printf("Product id: %d name: %s category: %s  price: $%d \n", 
            currentNode->id, currentNode->name, currentNode->category, currentNode->price);

        currentNode = currentNode->nextPtr;
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
    while (currentPtr != NULL) {


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
    /*
        Reads Product txt file
    */
    FILE* file;
    char currentLine[BUFFER];

    file = fopen(PRODUCT_FILE, "r");

    int id;
    char name[BUFFER / 2];
    char category[BUFFER / 2];
    int price;

    while(fgets(currentLine, BUFFER, file)) { // reads the file
        sscanf(currentLine, "%d %s %s %d", 
            &id, name, category, &price);


        addProduct(id, name, category, price);
        // printf( "id: %d name: %s category: %s price: %d\n",
        //     id, name, category, price);
    }

    fclose(file);


}


void printProductList(ProductListPtr currentProductList) {
    /*
        Prints a productList linked list
    */
    while (currentProductList->next != NULL)
        printf(" %d", currentProductList->productID);
    printf(" %d", currentProductList->productID);
}

ProductPtr getProductInfo(int productID) {
    /*
        Returns ProductPtr from productID
    */
    ProductPtr currentProduct = headProduct;

    while (currentProduct != NULL && currentProduct->id != productID) { // Loops every product
        currentProduct = currentProduct->nextPtr;
    }
    return currentProduct;
}


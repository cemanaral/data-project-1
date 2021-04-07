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


CustomerPtr getCustomer(int customerID) {
    /*
        Returns CustomerPtr by customerID
    */

    CustomerPtr currentCustomer = headCustomer;
    while (currentCustomer != NULL && currentCustomer->id != customerID)
    {
        currentCustomer = currentCustomer->nextPtr;
    }
    
    return currentCustomer;
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


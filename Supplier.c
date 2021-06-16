

#include "Supplier.h"

void freeSupplier(void *supplier){
    /*Free supplier name data*/
    checked_free(((Supplier*) supplier)->supplier_name);
}

void deleteAllSuppliers(Tree* supplierTree){
    /*Use generic func to remove all suppliers*/
    freeTree(supplierTree );
}

void printSuppliers(void* suppRoot) {
    /* Print all supplier details*/
    Supplier *tmp = suppRoot;
    printf("-------------------------\n");
    printf("SUPPLIER : \n");
    printf("Supplier name: %s\nDealer number: %s\nSupplier phone number: %s\nNumber of deals: %d\n"
           "Sum of deals in general: %ld\n\n",
           tmp->supplier_name,
           tmp->authorized_dealer_num,
           tmp->supplier_phone_num,
           tmp->number_of_deals_withSupp,
           tmp->sum_of_general_deals_withSupp);
}

void* initSupplier() {
    /*Initializing supplier struct */
    int check = 9;
    char authorized_dealer_num[AUTH_DEALER_NUM_LEN + 1];
    char *supplier_name = (char *) checked_malloc(sizeof(char) * 1024);
    char supplier_phone_num[SUPP_PHONE_LEN + 1];
    long sum_of_general_deals_withSupp;
    int number_of_deals_withSupp;
    Supplier *temporarySupp = (Supplier *) checked_malloc(sizeof(Supplier));
    /*authorized_dealer_num check */
    while (check != 1) {
        printf("enter authorized dealer num (10 DIGITS): ");
        scanf("%s", authorized_dealer_num);
        if ((valid_digit_check(authorized_dealer_num) == 0) ||
            (check_equal_size(authorized_dealer_num, AUTH_DEALER_NUM_LEN) == 0)) {
            printf("authorized dealer number not valid\n");
        } else {
            strcpy(temporarySupp->authorized_dealer_num, authorized_dealer_num);
            check = 1;
        }
    }
    check = 0;
    /*supplier_name check */
    while (check != 1) {
        printf("enter supplier name : ");
        scanf("%s", supplier_name);
        if (valid_char_check(supplier_name) == 0) {
            printf("supplier name not valid\n");
        } else {
            temporarySupp->supplier_name = dupstr(supplier_name);
            check = 1;
        }
    }
    check = 0;
    /*supplier_phone_num check*/
    while (check != 1) {
        printf("enter  supplier phone num (10 DIGITS): ");
        scanf("%s", supplier_phone_num);
        if ((check_equal_size(supplier_phone_num, SUPP_PHONE_LEN) == 0) ||
            (valid_digit_check(supplier_phone_num) == 0)) {
            printf("supplier phone number not valid\n");
        } else {
            strcpy(temporarySupp->supplier_phone_num, supplier_phone_num);
            check = 1;
        }
    }
    check = 0;
    /*number of deals withSupp check*/
    while (check != 1) {
        printf("enter  number of deals withSupp (5 DIGITS): ");
        scanf("%d", &number_of_deals_withSupp);
        if (valid_int(number_of_deals_withSupp, MIN_NUM_DEALS, MAX_NUM_DEALS) == 0) {
            printf("number of deals not valid\n");
        } else {
            temporarySupp->number_of_deals_withSupp = number_of_deals_withSupp;
            check = 1;
        }
    }
    check = 0;
    /*sum of general deals withSupp check*/
    while (check != 1) {
        printf("enter  sum of general deals withSupp (10 DIGITS): ");
        scanf("%ld", &sum_of_general_deals_withSupp);
        if (valid_long(sum_of_general_deals_withSupp, MIN_SUM_DEALS, MAX_SUM_DEALS) == 0) {
            printf("sum of general deals not valid\n");
        } else {
            temporarySupp->sum_of_general_deals_withSupp = sum_of_general_deals_withSupp;
            check = 1;
        }}
    return temporarySupp;
}

int supplierKeyCompare(void * supplier , void *root){
    /*Compare func between key node(supplier authorized dealer number) to add new supplier to the tree*/
    return (strcmp(((Supplier *) supplier)->authorized_dealer_num , ((Node *)root)->key ));
}

int authDealerNumCompare(void * authorized_dealer_num , void *supplier){
    /*Compare func between given supplier authorized dealer number to remove supplier from tree*/
    return (strcmp(((char *) authorized_dealer_num), ((Supplier *) supplier)->authorized_dealer_num));
}

void *supplierGetKey(void *supplier){
    /*return supplier authorized dealer number*/
    return (((Supplier *) supplier)->authorized_dealer_num);
}

int addNewSupplier(Tree *supplierTree){
    /*Add new supplier by help from generic add node func*/
    return addNewNode(supplierTree );
}

void* createSupplierTree(){
    /*Create new supplier tree by help from generic create tree func*/
    return createTree(initSupplier ,supplierKeyCompare , supplierGetKey  ,freeSupplier  , printSuppliers);
}

int deleteSupplier(Tree *suppTree){
    /*Removing supplier by authorized dealer number get help from generic remove node  func*/
    int tmpCount = suppTree->elementCount;
    int check;
    char authorized_dealer_num[AUTH_DEALER_NUM_LEN + 1];
    if (tmpCount == 0) {
        printf("NO SUPPLIERS\n");
        return 0;
    }
    printf("enter authorized_dealer_num (10 DIGITS): ");
    scanf("%s", authorized_dealer_num);
    check = removeNode(suppTree, authorized_dealer_num, authDealerNumCompare);
    if (check == 0) {
        printf("Supplier doesn't found\n");
    } else{
        printf("Supplier has been deleted\n");
    }
    return check;
}

double getSumOfDeals(void * supplier){
    /*Return sum of deals of supplier*/
    return ((Supplier*)supplier)->sum_of_general_deals_withSupp;
}

double averageOfSupplierMoney(Tree* supplierTree){
    /*return average Of Supplier Money by help from generic average func*/
    return averageKey(supplierTree->root ,getSumOfDeals , supplierTree->elementCount );
}


void threeGreatSuppliersHelper(Node *head,long check, char biggestSupplier[AUTH_DEALER_NUM_LEN + 1],
                               char threeGreatSupp[3][11]) {
    /*Find the three greatest Suppliers  */
    if (head == NULL) {
        return;
    }
    if ((((Supplier*)head->data)->sum_of_general_deals_withSupp > check) &&
        (strcmp(((Supplier*)head->data)->authorized_dealer_num, threeGreatSupp[0]) != 0) &&
        (strcmp(((Supplier*)head->data)->authorized_dealer_num, threeGreatSupp[1]) != 0)) {
        check = ((Supplier*)head->data)->sum_of_general_deals_withSupp;
        strcpy(biggestSupplier, ((Supplier*)head->data)->authorized_dealer_num);
    }

    threeGreatSuppliersHelper(head->left,  check, biggestSupplier, threeGreatSupp);
    threeGreatSuppliersHelper(head->right,   check, biggestSupplier, threeGreatSupp);
}


char **threeGreatestSuppliers(Tree *supptree, char threeGreatSupp[3][11]) {
    /*return and prints the three greatest suppliers get help from threeGreatSuppliersHelper func*/
    int countDown = 3;
    long check = 0;
    int index = 0;
    int i = 0;
    char biggestSupplier[AUTH_DEALER_NUM_LEN + 1];
    Node *temp = supptree->root;
    if (supptree->elementCount == 0) {
        printf("NO SUPPLIERS \n");
    }
    while (countDown > 0) {
        strcpy(biggestSupplier, "0");
        threeGreatSuppliersHelper(temp,  check, biggestSupplier, threeGreatSupp);
        strcpy(threeGreatSupp[index], biggestSupplier);
        countDown--;
        index++;
        check = 0;
        strcpy(biggestSupplier, "");
    }
    printf("Three great suppliers are: \n");
    for (i = 0; i < 3; i++) {
        printf("%d : %s\n" , i+1 , threeGreatSupp[i]);
        }
    return (char **) threeGreatSupp;
}






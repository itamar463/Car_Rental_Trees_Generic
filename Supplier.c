

#include "Supplier.h"

void freeSupplier(void *supplier){
    checked_free(((Supplier*) supplier)->supplier_name);
}

void deleteAllSuppliers(Tree* supplierTree){
    freeTree(supplierTree );
}

void printSuppliers(void* suppRoot) {
    /* Prints all supplier*/
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
        }
    }

    return temporarySupp;
}

int supplierCompare(void * authorized_dealer_num , void *authorized_dealer_num1){
    return (strcmp((char*)authorized_dealer_num , (char *) authorized_dealer_num1));
}

void *supplierGetKey(void *supplier){
    return (((Supplier *) supplier)->authorized_dealer_num);
}

int addNewSupplier(Tree *supplierTree){
    return addNewNode(supplierTree );
}

void* createSupplierTree(){
    createTree(initSupplier ,supplierCompare , supplierGetKey  ,freeSupplier  , printSuppliers);
}





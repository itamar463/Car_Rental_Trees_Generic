

#ifndef CAR_RENTAL_TREES_GENERIC_SUPPLIER_H
#define CAR_RENTAL_TREES_GENERIC_SUPPLIER_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "ValidInput.h"
#include "matam.h"
#include "Generic.h"

#define AUTH_DEALER_NUM_LEN 10
#define SUPP_PHONE_LEN 10
#define MIN_NUM_DEALS 9999
#define MAX_NUM_DEALS 100000
#define MIN_SUM_DEALS 999999999
#define MAX_SUM_DEALS 10000000000


typedef struct {
    char authorized_dealer_num[AUTH_DEALER_NUM_LEN + 1];
    char *supplier_name;
    char supplier_phone_num[SUPP_PHONE_LEN + 1];
    int number_of_deals_withSupp;
    long sum_of_general_deals_withSupp;
} Supplier;

void* createSupplierTree();
int addNewSupplier(Tree *supplierTree);
void deleteAllSuppliers(Tree* supplierTree);
int deleteSupplier(Tree *suppTree);
void printSuppliers(void* suppRoot);
double averageOfSupplierMoney(Tree* supplierTree);
char **threeGreatestSuppliers(Tree *supptree, char threeGreatSupp[3][11]);

#endif

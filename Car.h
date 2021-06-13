
#ifndef CAR_RENTAL_TREES_GENERIC_CAR_H
#define CAR_RENTAL_TREES_GENERIC_CAR_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "ValidInput.h"
#include "matam.h"
#include "Generic.h"


#define LICENSE_NUM_LEN 7
#define CHASSIS_NUM_LEN 5

typedef struct Car {
    char license_number[LICENSE_NUM_LEN + 1];
    char chassis_number[CHASSIS_NUM_LEN + 1];
    char *maker;
    char *model;
    char *color;
    int year_manufacture;
    int year_get_on_road;
    int price_that_paid;
    int present_car_price;
    int engine_cap;
} Car;
void *createCarTree();
int addNewCar(Tree *carTree);
int deleteCar(Tree *tree);
int deleteAllCars(void * tree);
int carNumberWithGivenCapacity(void * tree);

#endif

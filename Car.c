
#include "Generic.h"
#include "Car.h"
/**/
void *init_car() {
    /* init a Vehicle struct by given details*/
    Car *car = (Car *) checked_malloc(sizeof(Car));
    char license_number[LICENSE_NUM_LEN * 3];
    char chassis_number[CHASSIS_NUM_LEN * 3];
    char *maker = (char *) checked_malloc(sizeof(char) * 1024);
    char *model = (char *) checked_malloc(sizeof(char) * 1024);
    char *color = (char *) checked_malloc(sizeof(char) * 1024);
    int year_manufacture;
    int year_get_on_road;
    int price_that_paid;
    int present_car_price;
    int engine_cap;
    int check = 0;
    printf("NEW CAR : \n");
    /* Check license number*/
    while (check != 1) {
        printf("Enter license number (7 digits) : \n");
        scanf("%s", license_number);
        if ((check_equal_size(license_number, LICENSE_NUM_LEN) == 0) || (valid_digit_check(license_number) == 0)) {
            printf("license number not valid\n");
        } else {
            strcpy(car->license_number, license_number);
            check = 1;
        }
    }
    check = 0;
    /* Check chassis number*/
    while (check != 1) {
        printf("Enter chassis number (5 digits) : \n");
        scanf("%s", chassis_number);
        if ((check_equal_size(chassis_number, CHASSIS_NUM_LEN) == 0) || (valid_digit_check(chassis_number) == 0)) {
            printf("Chassis number not valid\n");
        } else {
            strcpy(car->chassis_number, chassis_number);
            check = 1;
        }
    }
    check = 0;
    /* Check maker*/
    while (check != 1) {
        printf("Enter maker : \n");
        scanf("%s", maker);
        if (valid_char_check(maker) == 0) {
            printf("Maker not valid\n");
        } else {
            car->maker = dupstr(maker);
            check = 1;
        }
    }
    check = 0;
    /* Check model*/
    while (check != 1) {
        printf("Enter model : \n");
        scanf("%s", model);
        if (valid_char_check(model) == 0) {
            printf("Model not valid\n");
        } else {
            car->model = dupstr(model);
            check = 1;
        }
    }
    check = 0;
    /* Check color*/
    while (check != 1) {
        printf("Enter color :\n");
        scanf("%s", color);
        if (valid_char_check(color) == 0) {
            printf("Color not valid\n");
        } else {
            car->color = dupstr(color);
            check = 1;
        }
    }
    check = 0;
    /* Check year of manufacture*/
    while (check != 1) {
        printf("Enter year of manufacture (number of 4 digits):\n");
        scanf("%d", &year_manufacture);
        if (valid_int(year_manufacture, 1930, 2022) == 0) {
            printf("Manufacture year not valid\n");
        } else {
            car->year_manufacture = year_manufacture;
            check = 1;
        }
    }
    check = 0;
    /* Check price that paid */
    while (check != 1) {
        printf("Enter price that paid for the car:\n");
        scanf("%d", &price_that_paid);
        if (valid_int(price_that_paid, 0, 1000000) == 0) {
            printf("Price that paid not valid\n");
        } else {
            car->price_that_paid = price_that_paid;
            check = 1;
        }
    }
    check = 0;
    /* Check year that car get on road */
    while (check != 1) {
        printf("Enter year that car get on road (number of 4 digits):\n");
        scanf("%d", &year_get_on_road);
        if (valid_int(year_get_on_road, year_manufacture - 1, 2022) == 0) {
            printf("Year that car get on road not valid\n");
        } else {
            car->year_get_on_road = year_get_on_road;
            check = 1;
        }
    }
    check = 0;
    /* Check present car price */
    while (check != 1) {
        printf("Enter present car price :\n");
        scanf("%d", &present_car_price);
        if (valid_int(present_car_price, 0, 1000000) == 0) {
            printf("Present car price not valid\n");
        } else {
            car->present_car_price = present_car_price;
            check = 1;
        }
    }
    check = 0;
    /* Check engine capacity */
    while (check != 1) {
        printf("Enter engine capacity (number of 4 digits):\n");
        scanf("%d", &engine_cap);
        if (valid_int(engine_cap, 1000, 10000) == 0) {
            printf("Engine capacity not valid\n");
        } else {
            car->engine_cap = engine_cap;
            check = 1;
        }
    }

    return car;
}

int carKeyCompare(void *car, void *root) {
    return (strcmp(((Car *) car)->license_number, ((Node *) root)->key));
}

int licenseNumberCompare(void *licenseNumberCheck, void *car) {
    return (strcmp(((char *) licenseNumberCheck), ((Car *) car)->license_number));
}

void *carGetKey(void *car) {
    return ((Car *) car)->license_number;
}

double carGetNumber(void *car) {
    return (double )((Car *) car)->present_car_price;
}

void *getLicenseNumber(void *check) {
    char licenseNumberCheck[LICENSE_NUM_LEN + 1];
    printf("Enter license number of car to be deleted: \n");
    scanf("%s", licenseNumberCheck);
    if (valid_digit_check(licenseNumberCheck) == 0 || check_equal_size(licenseNumberCheck, LICENSE_NUM_LEN) == 0) {
        printf("License number is not valid\n");
        return NULL;
    }
    strcpy(check, licenseNumberCheck);
    return (char *) check;

}

void freeCar(void *car) {
    /*Free memory of car */
    checked_free(((Car *) car)->color);
    checked_free(((Car *) car)->maker);
    checked_free(((Car *) car)->model);
}


void *createCarTree() {
    return createTree(init_car, carKeyCompare, carGetKey, freeCar);
}


int addNewCar(Tree *carTree) {
    return addNewNode(carTree);
}

int deleteCar(Tree *carTree) {
    return removeNode(carTree, getLicenseNumber, licenseNumberCompare);
}
LinkedNode * findCar(Tree *carTree){
    return findNode(carTree,getLicenseNumber,licenseNumberCompare);
}
double priceAverage(Tree *carTree){
    return averageKey(carTree->root,carGetNumber,carTree->elementCount);
}

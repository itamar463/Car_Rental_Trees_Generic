
#include "Generic.h"
#include "Car.h"


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
    /*compare between license numbers */
    return (strcmp(((Car *) car)->license_number, ((Node *) root)->key));
}

int licenseNumberCompare(void *licenseNumberCheck, void *car) {
    /*compare between license numbers */
    return (strcmp(((char *) licenseNumberCheck), ((Car *) car)->license_number));
}

void *carGetKey(void *car) {
    /*return car license numbers */
    return ((Car *) car)->license_number;
}


void printCar(void *root) {
    /*print car details*/
    Car *car = root;
    printf("Car :\n License number: %s\n"
           "Chassis number: %s\n"
           "Maker: %s\n"
           "Model: %s\n"
           "Color: %s\n"
           "Year manufacture: %d\n"
           "Year get on road: %d\n"
           "Price that paid: %d\n"
           "Current price: %d\n"
           "Engine capacity: %d\n\n", car->license_number, car->chassis_number, car->maker, car->model, car->color,
           car->year_manufacture,car->year_get_on_road,car->price_that_paid,car->present_car_price,car->engine_cap);
}

void freeCar(void *car) {
    /*Free memory of car */
    checked_free(((Car *) car)->color);
    checked_free(((Car *) car)->maker);
    checked_free(((Car *) car)->model);
}


void *createCarTree() {
    /* initalize a new car tree by generic func */
    return createTree(init_car, carKeyCompare, carGetKey, freeCar, printCar);
}


int addNewCar(Tree *carTree) {
    /*add new car to tree by generic func */
    return addNewNode(carTree);
}

int deleteCar(Tree *carTree) {
    /*delete car by license number using generic func */
    int check;
    char licenseNumberCheck[LICENSE_NUM_LEN * 4];
    printf("Enter license number of car to be deleted: \n");
    scanf("%s", licenseNumberCheck);
    if (valid_digit_check(licenseNumberCheck) == 0 || check_equal_size(licenseNumberCheck, LICENSE_NUM_LEN) == 0) {
        printf("License number is not valid\n");
        return 0;
    }
    check = removeNode(carTree, licenseNumberCheck, licenseNumberCompare);
    if (check == 0) {
        printf("Car doesn't found\n");
    } else {
        printf("Car has been deleted\n");
    }
    return check;
}


void deleteAllCars(Tree *carTree) {
    /*delete all cars from tree by using generic func */
    freeTree(carTree);
}

int carNumberWithGivenCapacityHelper(Node *root, int engineCapacity) {
    /* return the number of cars with the same capacity*/
    int sumR, sumL;
    int counter = 0;
    if (root == NULL) {
        return 0;
    }
    if (((Car *) root->data)->engine_cap == engineCapacity) {
        counter = 1;
    } else {
        counter = 0;
    }
    sumR = carNumberWithGivenCapacityHelper(root->right, engineCapacity);
    sumL = carNumberWithGivenCapacityHelper(root->left, engineCapacity);
    return sumR + sumL + counter;
}


int carNumberWithGivenCapacity(Tree *tree) {
    /* return the number of cars with the same capacity*/
    int counter = 0;
    int engineCapacity;
    if (tree == NULL) {
        printf("No cars\n");
        return 0;
    }
    printf("Enter engine capacity\n");
    scanf("%d", &engineCapacity);

    counter = carNumberWithGivenCapacityHelper(tree->root, engineCapacity);
    return counter;

}

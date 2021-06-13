#include <stdio.h>

#include "Car.h"
int main() {
    Tree * carTree = createCarTree();
    addNewCar(carTree);
    addNewCar(carTree);
    addNewCar(carTree);
    deleteCar(carTree);
    return 0;
}

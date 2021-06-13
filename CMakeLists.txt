cmake_minimum_required(VERSION 3.19)
project(Car_Rental_Trees_Generic C)

set(CMAKE_C_STANDARD 90)

add_executable(Car_Rental_Trees_Generic main.c Generic.c Generic.h ValidInput.c ValidInput.h matam.h matam.c Common.h Common.c Car.c Car.h Supplier.c Supplier.h Client.c Client.h)
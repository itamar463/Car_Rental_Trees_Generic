
#include "Client.h"
#include <stdio.h>


Date create_date(int year, int month, int day) {
    /*CREATING A DATE BY GIVEN DETAILS RETURN TRUE IF SUCCEED ELSE FALSE*/
    Date today = {0, 0, 0};
    if (date_valid(year, month, day) == FALSE) {
        printf("date not valid \n");
        return today;
    } else {
        today.year = year;
        today.month = month;
        today.day = day;
    }
    return today;
}

Time create_time(int hour, int minute) {
    /*CREATING A TIME STRUCT BY GIVEN DETAILS RETURN TRUE IF SUCCEED ELSE FALSE*/
    Time current_hour = {0, 0};
    if (time_valid(hour, minute) == FALSE) {
        printf("time not valid \n");
        return current_hour;
    } else {
        current_hour.hour = hour;
        current_hour.minute = minute;
    }
    return current_hour;
}

void print_date(Date d) {
    /*PRINTING DATE FORMAT*/
    smaller_than_ten(d.day);
    printf("%d/", d.day);
    smaller_than_ten(d.month);
    printf("%d/%d\n", d.month, d.year);
}

void print_time(Time t) {
    /*PRINTING TIME FORMAT*/
    smaller_than_ten(t.hour);
    printf("%d:", t.hour);
    smaller_than_ten(t.minute);
    printf("%d\n", t.minute);
}

void *initClient() {
    /*INIT CLIENT BY GIVEN DETAILS AND USING client_valid func*/
    Client *client = (Client *) checked_malloc(sizeof(Client));
    char id[ID_LEN * 3];
    char license_num[LICENSE_LEN * 3];
    char *first_name = (char *) checked_malloc(sizeof(char) * 1024);
    char *last_name = (char *) checked_malloc(sizeof(char) * 1024);
    Date date_of_rent;
    int year, month, day, hour, minute;
    Time time_of_rent;
    int price_per_rent;
    int check = 0;
    printf("NEW CLIENT : \n");
    /* Check ID*/
    while (check != 1) {
        printf("Enter ID (9 digits): \n");
        scanf("%s", id);
        if (valid_digit_check(id) == FALSE || check_equal_size(id, ID_LEN) == FALSE) {
            printf("Id client number not valid\n");
        } else {
            strcpy(client->id, id);
            check = 1;
        }
    }
    check = 0;
    /* Check first name*/
    while (check != 1) {
        printf("Enter first name: \n");
        scanf("%s", first_name);
        if (valid_char_check(first_name) == FALSE) {
            printf("Client first name not valid\n");
        } else {
            client->first_name = dupstr(first_name);
            check = 1;
        }
    }
    check = 0;
    /* Check last name*/
    while (check != 1) {
        printf("Enter last name: \n");
        scanf("%s", last_name);
        if (valid_char_check(last_name) == FALSE) {
            printf("Client last name not valid\n");
        } else {
            client->last_name = dupstr(last_name);
            check = 1;
        }
    }
    check = 0;
    /* Check license number*/
    while (check != 1) {
        printf("Enter license number (7 digits): \n");
        scanf("%s", license_num);
        if (valid_digit_check(license_num) == FALSE || check_equal_size(license_num, LICENSE_LEN) == FALSE) {
            printf("Client license number not valid\n");
        } else {
            strcpy(client->license_number, license_num);
            check = 1;
        }
    }
    check = 0;
    /* Check date*/
    while (check != 1) {
        printf("Enter date: year , month , day\n");
        scanf("%d %d %d", &year, &month, &day);
        date_of_rent = create_date(year, month, day);
        if (date_of_rent.day == 0) {
            printf("Date not valid\n");
        } else {
            client->date_of_rent = date_of_rent;
            check = 1;
        }
    }
    check = 0;
    /* Check time*/
    while (check != 1) {
        printf("Enter time: hour , minute\n");
        scanf("%d %d", &hour, &minute);
        time_of_rent = create_time(hour, minute);
        if (time_of_rent.hour == 0) {
            printf("Time not valid\n");
        } else {
            client->hour_of_rent = time_of_rent;
            check = 1;
        }
    }
    check = 0;
    /* Check price per rent for 24 hours*/
    while (check != 1) {
        printf("Enter price per rent for 24 hours (number of 3 digits): \n");
        scanf("%d", &price_per_rent);

        if (valid_int(price_per_rent, 100, 999) == FALSE) {
            printf("Price per rent not valid\n");
        } else {
            client->price_per_rent = price_per_rent;
            check = 1;
        }
    }

    return client;

}


int clientKeyCompare(void *client, void *root) {
    /*return strcmp between given license number */
    return (strcmp(((Client *) client)->id, ((Node *) root)->key));
}

int idCompare(void *IdCheck, void *client) {
    /*return strcmp between given license number */
    return (strcmp(((char *) IdCheck), ((Client *) client)->id));
}

void *clientGetKey(void *client) {
    /*return client ID */
    return ((Client *) client)->id;
}

void printClient(void *root) {
    /*print client details */
    Client *client = root;
    printf("CLIENT :\n"
           "first name : %s\n"
           "last name : %s\n"
           "id : %s\n"
           "car licence number : %s\n"
           "rent price for 24 hours : %d \n\n", client->first_name, client->last_name,
           client->id,
           client->license_number, client->price_per_rent);
    printf("rent date : ");
    print_date(client->date_of_rent);
    printf("rent time : ");
    print_time(client->hour_of_rent);
}

void freeClient(void *client) {
    /*Free memory of client */
    checked_free(((Client *) client)->first_name);
    checked_free(((Client *) client)->last_name);
}


void *createClientTree() {
    /*initialize new client tree ny generic func */
    return createTree(initClient, clientKeyCompare, clientGetKey, freeClient, printClient);
}

int addNewClient(Tree *clientTree) {
    /* add new node to the tree by generic func*/
    return addNewNode(clientTree);
}

int deleteClient(Tree *clientTree) {
    /*delete client from tree by generic func */
    int check;
    char idCheck[ID_LEN * 4];
    printf("Enter ID of client to be deleted: \n");
    scanf("%s", idCheck);
    if (valid_digit_check(idCheck) == 0 || check_equal_size(idCheck, ID_LEN) == 0) {
        printf("ID is not valid\n");
        return 0;
    }
    check = removeNode(clientTree, idCheck, idCompare);
    if (check == 0) {
        printf("Client doesn't found\n");
    } else {
        printf("Client has been deleted\n");
    }
    return check;
}


void deleteAllClients(Tree *clientTree) {
    /*delete all clients from tree */
    freeTree(clientTree);
}


int printClientCarsForGivenRentDateHelper(Node *root, int year, int month, int day, int *counter) {
    /*help in recursion to print all clients with the same date */
    if (root == NULL) {
        return 0;
    }

    if ((((Client *) root->data)->date_of_rent.day == day) &&
        (((Client *) root->data)->date_of_rent.month == month)
        && (((Client *) root->data)->date_of_rent.year == year)) {
        printClient(root->data);
        (*counter)++;
    }
    printClientCarsForGivenRentDateHelper(root->left, year, month, day, counter);
    printClientCarsForGivenRentDateHelper(root->right, year, month, day, counter);
    return *counter;
}

int printClientCarsForGivenRentDate(Tree *clientTree) {
    /*PRINT CLIENTS WITH THE SAME RENT DATE*/
    int check = 0;
    int year, month, day;
    if (clientTree->root == NULL) {
        printf("THERE NO CLIENTS\n");
        return FALSE;
    }

    printf("Enter date: year , month , day\n");
    scanf("%d %d %d", &year, &month, &day);
    if (date_valid(year, month, day) == 0) {
        printf("date not valid \n");
        return 0;
    }
    printClientCarsForGivenRentDateHelper(clientTree->root, year, month, day, &check);
    if (check == 0) printf("Clients were not found\n");
    return TRUE;
}

int dateCompare(void *date, void *client) {
    /* date compare func return 0 if equal*/
    if ((((Date *) date)->year == ((Client *) client)->date_of_rent.year) &&
        (((Date *) date)->month == ((Client *) client)->date_of_rent.month) &&
        (((Date *) date)->day == ((Client *) client)->date_of_rent.day)) {
        return 0;
    }
    return 1;
}

void findClient(Tree *clientTree,LinkedNode** linkedNode) {
    /*find client and return linked list by ID or by date */
    int option, year, month, day;
    int flag = FALSE;
    Date* dateCheck = (Date*) checked_malloc(sizeof(Date));
    char* idCheck = (char *) checked_malloc(sizeof(char )*256);
    if (clientTree->root == NULL) {
        printf("No clients\n");
        return ;
    }

    printf("For find by ID enter 1:\n");
    printf("For find by date enter 2:\n");
    scanf("%d", &option);
    if (option == 1) {
        while (flag == FALSE) {
            printf("Enter ID for finding: \n");
            scanf("%s", idCheck);
            if (valid_digit_check(idCheck) == FALSE || check_equal_size(idCheck, ID_LEN) == FALSE) {
                printf("Invalid ID try again\n");
            } else flag = TRUE;
        }
        (*linkedNode) =  findNode(clientTree, idCheck, idCompare);
    }
    if (option == 2) {
        while (flag == FALSE) {
            printf("Enter date: year , month , day\n");
            scanf("%d %d %d", &year, &month, &day);
            if (date_valid(year, month, day) == FALSE) {
                printf("Date not valid try again\n");
            } else flag = TRUE;
        }
        (*dateCheck) = create_date(year,month,day);
        (*linkedNode) = findNode(clientTree,dateCheck,dateCompare);

    }
    checked_free(idCheck);
    checked_free(dateCheck);

}


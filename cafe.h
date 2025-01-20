#ifndef CAFE_H
#define CAFE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<stdint.h>
#include <time.h>

typedef struct MenuItem {
    char name[50];
    float price;
    unsigned int  stock; 
    struct MenuItem *next,*previous;
} MenuItem;

typedef struct MenuCategory {
    char categoryName[50];
    MenuItem *items;
    struct MenuCategory *next,*preivous;
} MenuCategory;

void readpass(char password[]);

void changePass();

int adminlog();

MenuCategory* readMenu();

void displayMenu(MenuCategory *currentCategory, int *flag);

void writeMenu(MenuCategory *menu);

void addItem(MenuCategory *menu);

void deleteItem(MenuCategory *menu);

void changePrice(MenuCategory *menu);

void updateStock(MenuCategory *menu);

void takeorder(MenuCategory *menu);

void updateMenu(MenuCategory *menu);

void viewsale();

void clearsalesreport();

#endif

/*
 * cafemain.c
 * University Autometed cafeteria - Main File
 * Author: Team ProgBuddy
 *
 * Description:
 * This header file contains the definitions of data structures and function prototypes
 * used in the University Café Management System. It provides the interface for menu
 * management, order handling, and administrative functionalities.
 */

#ifndef CAFE_H
#define CAFE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include <conio.h>

// File paths for storing data
#define PASSWORD_FILE "adminpass.txt" // File for storing the admin password
#define MENU_FILE "menu.txt"         // File for storing the menu data
#define SALES_REPORT_FILE "salereport.txt" // File for storing sales reports

/*
 * Structure representing a menu item.
 * Fields:
 * - name: The name of the menu item (max 20 characters).
 * - price: The price of the item.
 * - stock: The quantity of the item available in stock.
 * - next: Pointer to the next item in the linked list.
 * - previous: Pointer to the previous item in the linked list.
 */
typedef struct MenuItem {
    char name[20];
    float price;
    uint32_t stock;
    struct MenuItem *next, *previous;
} MenuItem;

/*
 * Structure representing a menu category.
 * Fields:
 * - categoryName: The name of the category (max 15 characters).
 * - items: Pointer to the linked list of items in the category.
 * - next: Pointer to the next category in the linked list.
 * - previous: Pointer to the previous category in the linked list.
 */
typedef struct MenuCategory {
    char categoryName[15];
    MenuItem *items;
    struct MenuCategory *next, *previous;
} MenuCategory;

/*
 * Function Prototypes
 */

/**
 * Reads the admin password from the password file.
 * @param password: Array to store the password read from the file.
 */
void read_pass(char password[]);

/**
 * Allows the admin to change their password.
 */
void change_pass();

/**
 * Handles admin login by validating the entered password.
 * @return 1 if the login is successful, 0 otherwise.
 */
int admin_log();

/**
 * Reads the menu data from the menu file and constructs a linked list of categories and items.
 * @return Pointer to the head of the linked list of menu categories.
 */
MenuCategory* read_menu();

/**
 * Displays the menu categories and their items.
 * @param currentCategory: Pointer to the current category to display.
 * @param flag: Pointer to an integer to track menu display state.
 */
void display_menu(MenuCategory *currentCategory, int *flag);

/**
 * Writes the updated menu data to the menu file.
 * @param menu: Pointer to the head of the menu category linked list.
 */
void write_menu(MenuCategory *menu);

/**
 * Adds a new item to a specific menu category.
 * @param menu: Pointer to the head of the menu category linked list.
 */
void add_item(MenuCategory *menu);

/**
 * Deletes an item from a specific menu category.
 * @param menu: Pointer to the head of the menu category linked list.
 */
void delete_item(MenuCategory *menu);

/**
 * Changes the price of an item in a specific menu category.
 * @param menu: Pointer to the head of the menu category linked list.
 */
void change_price(MenuCategory *menu);

/**
 * Updates the stock quantity of an item in a specific menu category.
 * @param menu: Pointer to the head of the menu category linked list.
 */
void update_stock(MenuCategory *menu);

/**
 * Generates a unique token number for customer orders.
 * @return The generated token number.
 */
int generate_token();

/**
 * Handles customer order placement.
 * @param menu: Pointer to the head of the menu category linked list.
 */
void take_order(MenuCategory *menu);

/**
 * Provides admin options to update the menu (add, delete, change price, update stock).
 * @param menu: Pointer to the head of the menu category linked list.
 */
void update_menu(MenuCategory *menu);

/**
 * Displays the sales report from the sales report file.
 */
void view_sale();

/**
 * Clears the sales report by overwriting the file with an empty state.
 */
void clear_sales_report();

/**
 * admin operation handles with this function
 */
void admin(MenuCategory *menu,MenuCategory *currentCategory,uint32_t *login);

/**
 * homepage for the admin and customer and exit 
 */
void homepage();

#endif // CAFE_H

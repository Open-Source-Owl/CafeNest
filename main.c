/*
 * cafemain.c
 * University Autometed cafeteria - Main File
 * Author: Team ProgBuddy
 *
 * Description:
 * This is the main file for the University Café Management System.
 * It serves as the entry point of the application, providing a menu-driven
 * interface for both admins and customers to interact with the system.
 */

#include <stdio.h>
#include "cafe.c"

/*
 * Main function of the program.
 * Provides options for admin login, customer interaction, and system exit.
 * @return 0 on successful execution.
 */
int main() {
    MenuCategory *menu = readMenu(); // Load the menu from the file
    MenuCategory *currentCategory = menu;
    uint32_t choice; // Variable to store user input for menu options
    uint32_t login = 0; // Login state (0: not logged in, 1: logged in as admin)

    while (1) {
        if (login == 0) {
            // Main menu for guests
            printf("\nWelcome to Automated Cafeteria\n");
            printf("1. Log in as Admin\n");
            printf("2. Log in as Customer\n");
            printf("3. Exit\n");
            printf("Enter your choice: ");
            scanf("%u", &choice);

            switch (choice) {
                case 1:
                    // Admin login
                    if (adminlog()) {
                        login = 1;
                        printf("Welcome to the system.\n");
                    } else {
                        login = 0;
                        printf("Returning to main menu.\n");
                    }
                    break;
                case 2:
                    // Customer interaction
                    takeorder(menu);
                    break;
                case 3:
                    // Exit the program
                    printf("Exiting the program. Goodbye!\n");
                    exit(0);
                default:
                    printf("Invalid choice. Please try again.\n");
            }
        } else {
            // Admin menu
            printf("\nAdmin Options:\n");
            printf("1. Update Menu\n");
            printf("2. Display Menu\n");
            printf("3. View Sales Report\n");
            printf("4. Clear Sales Report\n");
            printf("5. Change Password\n");
            printf("6. Log Out\n");
            printf("7. Exit\n");
            uint32_t x = 1;
            printf("Enter your choice: ");
            scanf("%u", &choice);

            switch (choice) {
                case 1:
                    // Update menu
                    updateMenu(menu);
                    break;
                case 2:
                    // Display menu
                    x = 1;
                    while (currentCategory) {
                        displayMenu(currentCategory, &x);
                        currentCategory = currentCategory->next;
                    }
                    currentCategory = menu;
                    break;
                case 3:
                    // View sales report
                    viewsale();
                    break;
                case 4:
                    // Clear sales report
                    clearsalesreport();
                    break;
                case 5:
                    // Change admin password
                    changePass();
                    break;
                case 6:
                    // Log out
                    login = 0;
                    printf("Admin logged out.\n");
                    break;
                case 7:
                    // Exit the program
                    printf("Exiting the program. Goodbye!\n");
                    exit(1);
                default:
                    printf("Invalid choice. Please try again.\n");
            }
        }
    }

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define MenuItem struct
typedef struct MenuItem {
    char name[50];
    float price;
    unsigned int available; // 1 = available, 0 = unavailable
    struct MenuItem *next;
} MenuItem;

// Define MenuCategory struct
typedef struct MenuCategory {
    char categoryName[50];  // Category name (e.g., Starters)
    MenuItem *items;        // Pointer to the first item in the category
    struct MenuCategory *next;
} MenuCategory;

// Function prototypes
MenuCategory* loadMenu(const char *filename);
void displayMenu(MenuCategory *menu);
void takeCategoryOrder(MenuCategory *menu, const char *orderFile);
void freeMenu(MenuCategory *menu);
void saveMenuToFile(MenuCategory *menu, const char *filename);

// Admin functions
void adminMenu(MenuCategory *menu, const char *filename);
void changePrice(MenuCategory *menu);
void updateStock(MenuCategory *menu);
void deleteProduct(MenuCategory *menu);
void addProduct(MenuCategory *menu);

// Main function
int main() {
    const char *menuFile = "menu.txt";
    const char *orderFile = "orders.txt";

    // Load the menu from the file
    MenuCategory *menu = loadMenu(menuFile);
    if (!menu) {
        printf("Failed to load menu from %s\n", menuFile);
        return 1;
    }

    int choice;
    while (1) {
        printf("\n========== MENU ==========\n");
        printf("1. Display Menu\n");
        printf("2. Place Order (by Category)\n");
        printf("3. Admin Access\n");
        printf("4. Exit\n");
        printf("==========================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline character

        switch (choice) {
        case 1:
            displayMenu(menu);
            break;
        case 2:
            takeCategoryOrder(menu, orderFile);
            break;
        case 3:
            adminMenu(menu, menuFile);
            break;
        case 4:
            printf("Thank you for visiting!\n");
            freeMenu(menu);
            return 0;
        default:
            printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}

// Function to load the menu from a file
MenuCategory* loadMenu(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening menu file");
        return NULL;
    }

    MenuCategory *head = NULL, *currentCategory = NULL;
    char line[256];

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0; // Remove newline

        if (line[0] == '#') {
            // New category
            MenuCategory *newCategory = (MenuCategory *)malloc(sizeof(MenuCategory));
            strcpy(newCategory->categoryName, line + 1); // Skip the '#'
            newCategory->items = NULL;
            newCategory->next = NULL;

            if (!head) {
                head = newCategory;
            } else {
                currentCategory->next = newCategory;
            }
            currentCategory = newCategory;
        } else if (currentCategory) {
            // Add item to current category
            MenuItem *newItem = (MenuItem *)malloc(sizeof(MenuItem));
            if (sscanf(line, "%49[^,],%f,%u", newItem->name, &newItem->price, &newItem->available) == 3) {
                newItem->next = currentCategory->items;
                currentCategory->items = newItem;
            } else {
                printf("Invalid line format: %s\n", line);
                free(newItem);
            }
        }
    }

    fclose(file);
    return head;
}

// Function to display the menu
void displayMenu(MenuCategory *menu) {
    MenuCategory *currentCategory = menu;
    while (currentCategory) {
        printf("\n--- %s ---\n", currentCategory->categoryName);
        MenuItem *currentItem = currentCategory->items;
        int index = 1;
        while (currentItem) {
            if (currentItem->available) {
                printf("%d. %s - $%.2f\n", index, currentItem->name, currentItem->price);
            }
            currentItem = currentItem->next;
            index++;
        }
        currentCategory = currentCategory->next;
    }
}

// Function to take category order
void takeCategoryOrder(MenuCategory *menu, const char *orderFile) {
    FILE *file = fopen(orderFile, "a");
    if (!file) {
        printf("Error opening order file: %s\n", orderFile);
        return;
    }

    MenuCategory *currentCategory = menu;
    while (currentCategory) {
        printf("\n--- %s ---\n", currentCategory->categoryName);
        MenuItem *currentItem = currentCategory->items;

        int index = 1;
        while (currentItem) {
            if (currentItem->available) {
                printf("%d. %s - $%.2f\n", index, currentItem->name, currentItem->price);
            }
            currentItem = currentItem->next;
            index++;
        }

        printf("Enter item numbers to order (space-separated, 0 to skip this category): ");
        char input[256];
        fgets(input, sizeof(input), stdin);

        if (strcmp(input, "0\n") == 0) {
            currentCategory = currentCategory->next;
            continue;
        }

        // Parse input and place order
        currentItem = currentCategory->items;
        index = 1;
        char *token = strtok(input, " ");
        while (token) {
            int choice = atoi(token);
            if (choice == index && currentItem && currentItem->available) {
                fprintf(file, "Ordered: %s, Price: $%.2f\n", currentItem->name, currentItem->price);
                printf("%s added to your order.\n", currentItem->name);
            }
            currentItem = currentItem->next;
            index++;
            token = strtok(NULL, " ");
        }

        currentCategory = currentCategory->next;
    }

    fclose(file);
    printf("Order saved successfully!\n");
}

// Function to free the menu
void freeMenu(MenuCategory *menu) {
    while (menu) {
        MenuCategory *tempCategory = menu;
        menu = menu->next;

        MenuItem *currentItem = tempCategory->items;
        while (currentItem) {
            MenuItem *tempItem = currentItem;
            currentItem = currentItem->next;
            free(tempItem);
        }
        free(tempCategory);
    }
}

// Function to save the menu back to the file
void saveMenuToFile(MenuCategory *menu, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Error opening file for saving: %s\n", filename);
        return;
    }

    MenuCategory *currentCategory = menu;
    while (currentCategory) {
        fprintf(file, "#%s\n", currentCategory->categoryName);
        MenuItem *currentItem = currentCategory->items;
        while (currentItem) {
            fprintf(file, "%s,%.2f,%u\n", currentItem->name, currentItem->price, currentItem->available);
            currentItem = currentItem->next;
        }
        currentCategory = currentCategory->next;
    }

    fclose(file);
    printf("Menu saved successfully to %s\n", filename);
}

// Function for the admin menu
void adminMenu(MenuCategory *menu, const char *filename) {
    int choice;
    while (1) {
        printf("\n========== ADMIN MENU ==========\n");
        printf("1. Change Product Price\n");
        printf("2. Update Stock Availability\n");
        printf("3. Delete Product\n");
        printf("4. Add New Product\n");
        printf("5. Save and Exit\n");
        printf("================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline character

        switch (choice) {
        case 1:
            changePrice(menu);
            break;
        case 2:
            updateStock(menu);
            break;
        case 3:
            deleteProduct(menu);
            break;
        case 4:
            addProduct(menu);
            break;
        case 5:
            saveMenuToFile(menu, filename);
            return;
        default:
            printf("Invalid choice! Try again.\n");
        }
    }
}

// Function to change product price
void changePrice(MenuCategory *menu) {
    char category[50], product[50];
    printf("Enter category name: ");
    fgets(category, sizeof(category), stdin);
    category[strcspn(category, "\n")] = 0;

    printf("Enter product name: ");
    fgets(product, sizeof(product), stdin);
    product[strcspn(product, "\n")] = 0;

    MenuCategory *currentCategory = menu;
    while (currentCategory) {
        if (strcmp(currentCategory->categoryName, category) == 0) {
            MenuItem *currentItem = currentCategory->items;
            while (currentItem) {
                if (strcmp(currentItem->name, product) == 0) {
                    printf("Enter new price for %s: ", product);
                    scanf("%f", &currentItem->price);
                    getchar();
                    printf("Price updated successfully!\n");
                    return;
                }
                currentItem = currentItem->next;
            }
        }
        currentCategory = currentCategory->next;
    }
    printf("Product not found!\n");
}

// Function to update stock availability
void updateStock(MenuCategory *menu) {
    char category[50], product[50];
    printf("Enter category name: ");
    fgets(category, sizeof(category), stdin);
    category[strcspn(category, "\n")] = 0;

    printf("Enter product name: ");
    fgets(product, sizeof(product), stdin);
    product[strcspn(product, "\n")] = 0;

    MenuCategory *currentCategory = menu;
    while (currentCategory) {
        if (strcmp(currentCategory->categoryName, category) == 0) {
            MenuItem *currentItem = currentCategory->items;
            while (currentItem) {
                if (strcmp(currentItem->name, product) == 0) {
                    printf("Enter availability (1 for available, 0 for unavailable): ");
                    scanf("%u", &currentItem->available);
                    getchar();
                    printf("Stock updated successfully!\n");
                    return;
                }
                currentItem = currentItem->next;
            }
        }
        currentCategory = currentCategory->next;
    }
    printf("Product not found!\n");
}

// Function to delete a product
void deleteProduct(MenuCategory *menu) {
    char category[50], product[50];
    printf("Enter category name: ");
    fgets(category, sizeof(category), stdin);
    category[strcspn(category, "\n")] = 0;

    printf("Enter product name: ");
    fgets(product, sizeof(product), stdin);
    product[strcspn(product, "\n")] = 0;

    MenuCategory *currentCategory = menu;
    while (currentCategory) {
        if (strcmp(currentCategory->categoryName, category) == 0) {
            MenuItem *currentItem = currentCategory->items, *prevItem = NULL;
            while (currentItem) {
                if (strcmp(currentItem->name, product) == 0) {
                    if (prevItem) {
                        prevItem->next = currentItem->next;
                    } else {
                        currentCategory->items = currentItem->next;
                    }
                    free(currentItem);
                    printf("Product deleted successfully!\n");
                    return;
                }
                prevItem = currentItem;
                currentItem = currentItem->next;
            }
        }
        currentCategory = currentCategory->next;
    }
    printf("Product not found!\n");
}

// Function to add a new product
void addProduct(MenuCategory *menu) {
    char category[50], product[50];
    float price;
    unsigned int availability;

    printf("Enter category name: ");
    fgets(category, sizeof(category), stdin);
    category[strcspn(category, "\n")] = 0;

    MenuCategory *currentCategory = menu;
    while (currentCategory) {
        if (strcmp(currentCategory->categoryName, category) == 0) {
            MenuItem *newItem = (MenuItem *)malloc(sizeof(MenuItem));
            printf("Enter product name: ");
            fgets(product, sizeof(product), stdin);
            product[strcspn(product, "\n")] = 0;
            strcpy(newItem->name, product);

            printf("Enter price: ");
            scanf("%f", &price);
            getchar();
            newItem->price = price;

            printf("Enter availability (1 for available, 0 for unavailable): ");
            scanf("%u", &availability);
            getchar();
            newItem->available = availability;

            newItem->next = currentCategory->items;
            currentCategory->items = newItem;
            printf("Product added successfully!\n");
            return;
        }
        currentCategory = currentCategory->next;
    }
    printf("Category not found!\n");
}


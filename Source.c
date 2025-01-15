// discount, re-enter password, stock (done )
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<stdint.h>
#define PASSWORD_FILE "adminpass.txt"
#define MENU_FILE "menu.txt"
#define SALES_REPORT_FILE "salereport.txt"
typedef struct MenuItem {
    char name[50];
    float price;
    unsigned int  stock; // 1 = available, 0 = unavailable
    struct MenuItem *next,*previous;
} MenuItem ;

typedef struct MenuCategory {
    char categoryName[50];
    MenuItem *items;
    struct MenuCategory *next,*previous;
} MenuCategory;


void readpass(char password[]) {
    FILE *file = fopen(PASSWORD_FILE, "r");

    if (file == NULL) {
        perror("Error opening admin password file");
        exit(EXIT_FAILURE);
    }

    fscanf(file, "%s", password);

    fclose(file);
}
void changePass(){
    char enteredpass[10];
     char correctpass[10];

     readpass(correctpass);

    FILE *file = fopen(PASSWORD_FILE, "w");

    if (file == NULL) {
        perror("Error opening admin password file");
        exit(0);
    }
      printf(" Enter old Admin Password: ");
     int i = 0;
    while (1) {
        char ch = getch();

        if (ch == '\r' || ch == '\n') {
            break;  // Enter key = terminate the loop
        } else if (ch == '\b' && i >=0) {
            if(i==0){
                    printf("*");
              printf("\b \b");
            }
            else{
                printf("\b \b");
            i--;}
        } else {
            enteredpass[i] = ch;
            i++;
            printf("*");
        }
    }

    enteredpass[i] = '\0';

    // Compare the entered password with the correct password
    if (strcmp(enteredpass, correctpass) == 0) {
        printf("\nCorrect password\n");

    char pass[50];
    printf("Write new pass: ");

    fflush(stdin);//to fix an undefined behavior
    gets(pass);

    int i=0;
    while(pass[i]!='\0')
    {
    if(pass[i]==' ')
    {
        printf("Error, your password cannot contain space.\nTry again,\n");
        changePass();
    }
    else
        fprintf(file, "%c", pass[i]);
    i++;
    }
    fclose(file);

    printf("Thank you. Your new password set successfully.\n");
    }
    else {
        printf("Wrong password.Try again");
    }
}
int adminlog(){
    char enteredpass[10];
    char correctpass[10];

     readpass(correctpass);

    printf("Admin Password: ");

    int i = 0;
    while (1) {
        char ch = getch();

        if (ch == '\r' || ch == '\n') {
            break;  // Enter key = terminate the loop
        } else if (ch == '\b' && i >=0) {
            if(i==0){
                    printf("*");
              printf("\b \b");
            }
            else{
                printf("\b \b");
            i--;}
        } else {
            enteredpass[i] = ch;
            i++;
            printf("*");
        }
    }

    enteredpass[i] = '\0';

    // Compare the entered password with the correct password
    if (strcmp(enteredpass, correctpass) == 0) {
        printf("\nAdmin login successful.\n");
        return 1;
    } else {
        printf("\nInvalid admin password. Access denied.\n");
        printf("1.Try again\n2.Back\n");
        int choice;
        printf("Enter your choice: ");
        scanf("%d",&choice);
        while(1)
   {
       if(choice==1 || choice==2)
       {
       break;
       }
       printf("Invalid choice. Please enter correct choice\n");
       printf("Please  Enter your choice again:");
       scanf("%d",&choice);

   }
        switch(choice)
        {
    case 1:
        adminlog();
        break;
    case 2:
        return 0;
        break;
    default:
        printf("Invalid choice.\n");

        }

    }
}

MenuCategory* readMenu() {
    FILE *file = fopen(MENU_FILE, "r");
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
            if (sscanf(line, "%49[^,],%f,%u", newItem->name, &newItem->price, &newItem->stock) == 3) {
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
void displayMenu(MenuCategory *currentCategory,unsigned int x){
      if(x==0){
    printf("\n--- %s ---\n", currentCategory->categoryName);
        MenuItem *currentItem = currentCategory->items;
        int index = 1;
        while (currentItem) {

                printf("%d. %s - $%.2f - %u \n", index, currentItem->name, currentItem->price,currentItem->stock);

            currentItem = currentItem->next;
            index++;
        }
      }
      else {
        printf("\n--- %s ---\n", currentCategory->categoryName);
        MenuItem *currentItem = currentCategory->items;
        int index = 1;
        while (currentItem) {
                      if(currentItem->stock>0){
                printf("%d. %s - $%.2f\n", index, currentItem->name, currentItem->price);
                      }
            currentItem = currentItem->next;
            index++;
        }
    }
}

void writeMenu(MenuCategory *menu) {
    FILE *file = fopen(MENU_FILE, "w");
    if (!file) {
        printf("Error opening file for saving");
        return;
    }
    MenuCategory *currentCategory = menu;
    while (currentCategory) {
        fprintf(file, "#%s\n", currentCategory->categoryName);
        MenuItem *currentItem = currentCategory->items;
        while (currentItem) {
            fprintf(file, "%s,%.2f,%u\n", currentItem->name, currentItem->price, currentItem->stock);
            currentItem = currentItem->next;
        }
        currentCategory = currentCategory->next;
    }
    fclose(file);
    printf("Menu saved successfully menu file");
}

void addItem(MenuCategory *menu) {

    float price;
    unsigned int availability;
     MenuCategory *currentCategory = menu;
    unsigned int choice;

       printf("\n Here is the list of  categories: ");
       printf("\n1.Starters\n2.Main Course\n3.Desserts\n4.Drinks\nEnter your choice");
       scanf("%d",&choice);
    for(int i=1;i<choice;i++){
       currentCategory=currentCategory->next;
    }
            MenuItem *newItem = (MenuItem *)malloc(sizeof(MenuItem));
            printf("Enter product name: ");
            scanf("%s",&newItem->name);

            printf("Enter price: ");
            scanf("%f", &price);
            newItem->price = price;

            printf("Enter stock : ");
            scanf("%u", &availability);
            newItem->stock = availability;

            newItem->next = currentCategory->items;
            currentCategory->items = newItem;
            printf("Product added successfully!\n");
            writeMenu(menu);
            return;

}

void deleteItem(MenuCategory *menu){
     MenuCategory *currentCategory = menu;
    unsigned int choice;

       printf("\n Here is the category: ");
       printf("\n1.Starters\n2.Main Course\n3.Desserts\n4.Drinks\nSelect a category for delete an item:");
       scanf("%d",&choice);
    for(int i=1;i<choice;i++){
       currentCategory=currentCategory->next;
    }

          //Incomplete//

}
void changePrice(MenuCategory *menu){
    MenuCategory *currentCategory = menu;
      while(currentCategory){
        displayMenu(currentCategory,0);
        currentCategory=currentCategory->next;
        }
        unsigned int choice;
    printf("\n Here is the list of  categories: ");
       printf("\n1.Starters\n2.Main Course\n3.Desserts\n4.Drinks\nEnter your choice");
       scanf("%d",&choice);
       currentCategory =menu;

    for(int i=1;i<choice;i++){
       currentCategory=currentCategory->next;
    }
    MenuItem *currentMenu=currentCategory->items;
    printf("Enter the number of the item from category %s to change the price : ",currentCategory->categoryName);
    int item_number_price;
    scanf("%d", &item_number_price);
    for(int i=1;i<item_number_price;i++){
        currentMenu=currentMenu->next;
    }
     printf("Enter new for %s : ",currentMenu->name);
     scanf("%f",&currentMenu->price);
     writeMenu(menu);
     printf("Successfully Updated");
}
void updateStock(MenuCategory *menu){
     MenuCategory *currentCategory = menu;
     unsigned int choice;
    printf("\n Here is the list of  categories: ");
    printf("\n1.Starters\n2.Main Course\n3.Desserts\n4.Drinks\nEnter your choice");
    scanf("%u",&choice);
    if(choice<0 && choice>4){
        printf("Invalid choice");
        return;
    }

    for(int i=1;i<choice;i++){
       currentCategory=currentCategory->next;
    }
    MenuItem *currentMenu=currentCategory->items;
    printf("Enter the number of the item from category %s to add stock : ",currentCategory->categoryName);
   unsigned int item_number,quantity;
    scanf("%d", &item_number);
    for(int i=1;i<item_number;i++){
        currentMenu=currentMenu->next;
    }
    unsigned int a;
    do{
        printf("Enter new stock: ");
         scanf("%u", &a);
        if(a<0){
            printf("Invalid quantity. Please enter a quantity greater than 0.\n");
        }
        else {
            currentMenu->stock=a;
        }
    }while(a<0);
    printf("Successfully updated stock");
 }

void takeorder(MenuCategory *menu) {/*
    FILE *file = fopen(SALES_REPORT_FILE, "a");
    if (!file) {
        printf("Error opening order file");
        return;
    }

    MenuCategory *currentCategory = menu;
    while(currentCategory){
        displayMenu(currentCategory);
        currentCategory=currentCategory->next;
        }
        currentCategory=menu;


       int choice;
        printf(" Enter 0 for Back from customer option:");
        scanf("%d",&choice);
         if (choice==0) {
           return;
        }
        choice=NULL;
         time_t current_time;
    struct tm *local_time;

    time(&current_time);
    local_time = localtime(&current_time);

    FILE *order_file = fopen(SALES_REPORT_FILE, "a");

    if (order_file == NULL)
    {
        perror("Error opening order file");
        exit(EXIT_FAILURE);
    }

    fprintf(order_file, "-----\n");
    fprintf(order_file, "Order Date: %04d-%02d-%02d | Order Time: %02d:%02d:%02d\n",
            local_time->tm_year + 1900, local_time->tm_mon + 1, local_time->tm_mday,
            local_time->tm_hour, local_time->tm_min, local_time->tm_sec);
        printf("Enter item numbers to order (space-separated, 0 to skip this category): ");

        scanf("%d",&choice);
        if (choice==0) {
            currentCategory = currentCategory->next;
            continue;
        }
        MenuItem *item=currentCategory->items;
         for(int i=1;i<choice;i++){
          item=item->next;
       }
        int quantity;
         printf("Enter quantity : ");
         scanf("%d",&quantity);
         if()
      /*  // Parse input and place order
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
    printf("Order saved successfully!\n");*/
}

 void updateMenu(MenuCategory *menu ){
     MenuCategory *currentCategory = menu;
      while(currentCategory){
        displayMenu(currentCategory,0);
        currentCategory=currentCategory->next;
        }
    int choice;
    printf("\nMenu Update Options:\n");

    printf("1. Add Item\n");
    printf("2. Delete Item\n");
    printf("3. Change Item Price\n");
    printf("4. Add Stock\n");
    printf("5. Back to Admin option\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1 : addItem(menu);
            updateMenu(menu);
              break;
    case 2 : deleteItem(menu);
            updateMenu(menu);
              break;
    case 3 : changePrice(menu);
            updateMenu(menu);
              break;
    case 4 : updateStock(menu);
            updateMenu(menu);
              break;
    case 5 :return 0;
    default:
        printf("Invalid choice.");
    }
}
void viewsale(){
      FILE *sales_report_file = fopen(SALES_REPORT_FILE, "r");

    if (sales_report_file == NULL) {
        perror("Error opening sales report file");
        exit(EXIT_FAILURE);
    }

    printf("\nSales Report:\n");
    char buffer[500];
    while (fgets(buffer, sizeof(buffer), sales_report_file) != NULL) {
        // Check if the line contains the "Order Time" string
        if (strstr(buffer, "Order Time") != NULL) {
            printf("%s", buffer); // Print the date and time line
        } else {
            printf("%s", buffer); // Print the rest of the lines
        }
    }

    fclose(sales_report_file);
}
void clearsalesreport(){
      FILE *sales_report_file = fopen(SALES_REPORT_FILE, "w");

    if (sales_report_file == NULL  ) {
        perror("Error opening sales report file");
        exit(EXIT_FAILURE);
    }
    fclose(sales_report_file);
    printf("Sales report cleared successfully.");
}
int main(){
    MenuCategory *menu = readMenu();
    MenuCategory *currentCategory = menu;
    unsigned int choice;
     unsigned login =0;
     while(1){
        if (login ==0){
            printf("\n Welcome to Automated Cafeteria\n");
            printf("1. Log in as Admin\n");
            printf("2. Log in as Customer\n");
            printf("3. Exit\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);
             switch (choice) {
                case 1:
                    if (adminlog()) {
                        login = 1;
                        printf("Welcome to the system.\n");
                    } else {
                        login = 0;
                        printf("Return to main system.\n");
                    }
                    break;
                case 2:
                        takeorder(menu);
                    break;
                case 3:
                    printf("Exiting the program. Goodbye!\n");
                    exit(0);
                default:
                    printf("Invalid choice. Please try again.\n"); }
        }
        else {
            printf("\nAdmin Options:\n");

            printf("1. Update Menu\n");
            printf("2. Display menu \n");
            printf("3. View Sales Report\n");
            printf("4. Clear Sales Report\n");
            printf("5. Change password\n");
            printf("6. Log out\n");
            printf("7. Exit\n");

            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice) {

                case 1:
                    updateMenu(menu);
                    break;
                case 2:
                     while(currentCategory){
                     displayMenu(currentCategory,0);
                      currentCategory=currentCategory->next;
                     }
                    break;
                case 3:
                   viewsale();
                    break;
                case 4:
                    clearsalesreport();
                    break;
                case 5:
                     changePass();
                    break;
                case 6:
                   login = 0;
                    printf("Admin logged out.\n");
                    break;
                case 7:
                    printf("Exiting the program. Goodbye!\n");
                    exit(1);
                    break;
                default:
                    printf("Invalid choice. Please try again.\n");
            }
        }
     }
 return 0;
}

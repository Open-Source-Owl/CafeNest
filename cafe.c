#include "cafe.h"
#include<stdio.h>


void read_pass(char password[]) {

    FILE *file = fopen(PASSWORD_FILE, "r");

    if (file == NULL) {
        printf("Error opening admin password file");
        exit(EXIT_FAILURE);
    }
    fscanf(file, "%s", password);
    fclose(file);
}

void change_pass(){
     char enteredpass[10];
     char correctpass[10];

     read_pass(correctpass);

    FILE *file = fopen(PASSWORD_FILE, "w");

    if (file == NULL) {
        perror("Error opening admin password file");
        exit(0);
    }
      printf(" Enter old Admin Password: ");
    uint32_t i = 0;
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

    char pass[10];
    printf("Write new pass: ");

    fflush(stdin);//to fix an undefined behavior
    gets(pass);

    uint32_t i=0;
    while(pass[i]!='\0')
    {
    if(pass[i]==' ')
    {
        printf("Error, your password cannot contain space.\nTry again,\n");
        change_pass();
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
int admin_log(){
    char enteredpass[10];
    char correctpass[10];

     read_pass(correctpass);

    printf("Admin Password: ");

    uint32_t i = 0;
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
        admin_log();
        break;
    case 2:
        return 0;
        break;
    default:
        printf("Invalid choice.\n");

        }

    }
}

MenuCategory* read_menu() {
    FILE *file = fopen(MENU_FILE, "r");
    if (!file) {
        printf("Error opening menu file");
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
void display_menu(MenuCategory *currentCategory, int *flag){
   if(*flag==1){
    printf("\n--- %s ---\n", currentCategory->categoryName);
        MenuItem *currentItem = currentCategory->items;
        int index = 1;
        while (currentItem) {

                printf("%d. %s - BDT %.2f - %u\n", index, currentItem->name, currentItem->price,currentItem->stock);

            currentItem = currentItem->next;
            index++;
        }
   }
   else {
              printf("\n--- %s ---\n", currentCategory->categoryName);
        MenuItem *currentItem = currentCategory->items;
        int index = 1;
        while (currentItem) {
            if (currentItem->stock>0) {
                printf("%d. %s - BDT %.2f\n", index, currentItem->name, currentItem->price);
                index++;
            }
            currentItem = currentItem->next;

        }
         *flag=index-1;
   }
}

void write_menu(MenuCategory *menu) {

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

}
void add_item(MenuCategory *menu) {

    float price;
    uint32_t availability;
     MenuCategory *currentCategory = menu;
    uint32_t choice;

       printf("\n Here is the list of  categories: ");
       printf("\n1.Starters\n2.Main Course\n3.Desserts\n4.Drinks\nEnter your choice");
       scanf("%u",&choice);
        while(choice<1 || choice >4){
        printf("Invalid input. Try again\nEnter your choice:");
        scanf("%u",&choice);
       }
    for(uint32_t i=1;i<choice;i++){
       currentCategory=currentCategory->next;
    }
            MenuItem *newItem = (MenuItem *)malloc(sizeof(MenuItem));
            printf("Enter product name: ");
            scanf("%s",&newItem->name);

            printf("Enter price: ");
            scanf("%f", &price);
            newItem->price = price;

            printf("Enter stock: ");
            scanf("%u", &availability);
            newItem->stock = availability;

            newItem->next = currentCategory->items;
            currentCategory->items = newItem;
            printf("Product added successfully!\n");
            write_menu(menu);
            return;

}

void delete_item(MenuCategory *menu) {
    MenuCategory *currentCategory = menu;
    uint32_t choice;

    printf("\n--- Categories ---");
    printf("\n1. Starters");
    printf("\n2. Main Course");
    printf("\n3. Desserts");
    printf("\n4. Drinks");
    printf("\nEnter the category number to delete an item: ");
    scanf("%u", &choice);
     while(choice<1 || choice >4){
        printf("Invalid input. Try again\nEnter your choice:");
        scanf("%u",&choice);
       }

    // Find the way in the selected category
    for ( uint32_t i = 1; i < choice; i++) {
        if (currentCategory->next) {
            currentCategory = currentCategory->next;
        } else {
            printf("Invalid category selection.\n");
            return;
        }
    }

    // Display items in the selected category
    MenuItem *currentItem = currentCategory->items;
    if (!currentItem) {
        printf("No items available in the selected category.\n");
        return;
    }

    printf("\n--- Items in %s ---\n", currentCategory->categoryName);
    uint32_t index = 1;
    while (currentItem) {
        printf("%d. %s - $%.2f - %u\n", index, currentItem->name, currentItem->price, currentItem->stock);
        currentItem = currentItem->next;
        index++;
    }

    // Get item number to delete
    printf("Enter the item number to delete: ");
    uint32_t itemNumber;
    scanf("%u", &itemNumber);

    if (itemNumber < 1 || itemNumber >= index) {
        printf("Invalid item number.\n");
        return;
    }

    // Find the item to delete
    currentItem = currentCategory->items;
    MenuItem *prevItem = NULL;

    for (uint32_t i = 1; i < itemNumber; i++) {
        prevItem = currentItem;
        currentItem = currentItem->next;
    }

    // Remove the item
    if (prevItem) {
        prevItem->next = currentItem->next;
    } else {
        currentCategory->items = currentItem->next;
    }

    free(currentItem);
    printf("Item deleted successfully.\n");

    // Update the menu file
    write_menu(menu);
}

void change_price(MenuCategory *menu){

    MenuCategory *currentCategory = menu;

        uint32_t choice;
        printf("\n Here is the list of  categories: ");
       printf("\n1.Starters\n2.Main Course\n3.Desserts\n4.Drinks\nEnter your choice:");
       scanf("%u",&choice);
       while(choice<1 || choice >4){
        printf("Invalid input. Try again\nEnter your choice:");
        scanf("%u",&choice);
       }
       
       currentCategory =menu;

    for(uint32_t i=1;i<choice;i++){
       currentCategory=currentCategory->next;
    }
    MenuItem *currentMenu=currentCategory->items;
    printf("Enter the number of the item from category %s to change the price : ",currentCategory->categoryName);
    uint32_t item_number_price;
    scanf("%u", &item_number_price);
    for(uint32_t i=1;i<item_number_price;i++){
        currentMenu=currentMenu->next;
    }
     printf("Enter new for %s : ",currentMenu->name);
     scanf("%f",&currentMenu->price);
     write_menu(menu);
     printf("Successfully Updated");

}

void update_stock(MenuCategory *menu){

     MenuCategory *currentCategory = menu;
     uint32_t choice;
    printf("\n Here is the list of  categories: ");
    printf("\n1.Starters\n2.Main Course\n3.Desserts\n4.Drinks\nEnter your choice");
    scanf("%u",&choice);
     while(choice<1 || choice >4){
        printf("Invalid input. Try again\nEnter your choice:");
        scanf("%u",&choice);
       }

    for(uint32_t i=1;i<choice;i++){
       currentCategory=currentCategory->next;
    }
    MenuItem *currentMenu=currentCategory->items;
    printf("Enter the number of the item from category %s to add stock : ",currentCategory->categoryName);
   uint32_t item_number,quantity;
    scanf("%u", &item_number);
    for(uint32_t i=1;i<item_number;i++){
        currentMenu=currentMenu->next;
    }
    uint32_t a;
    printf("Enter new stock: "); 
    scanf("%u",&a);
    while(a<1){
        printf("Invalid! Enter stock more than zero: ");
        scanf("%u",&a);
       }
     currentMenu->stock=a;
     write_menu(menu);
     printf("Successfully Updated");
 }
int generate_token(){
    uint32_t num;
    FILE *file = fopen(SALES_REPORT_FILE, "r+");
     if (!file) {
        printf("Error opening menu file");
        exit(1);
    }
   
    fscanf(file,"%u",&num);
    if(num==0){
        num=1;
    }
    else {
    num=num+1;
    fseek(file,0,SEEK_SET);
    fprintf(file,"%u\n",num);
    }
    fclose(file);
    return num;
}

void take_order(MenuCategory *menu){
         
    MenuCategory *currentCategory = menu;
    uint32_t x=0;
    while(currentCategory){
        display_menu(currentCategory,&x);
        currentCategory=currentCategory->next;
        }
        currentCategory=menu;

       uint32_t choice;
        printf("\nWhat you wants to do ?\n1.Place order\n2.Back to home :");
        scanf("%u",&choice);
        while(choice<1 || choice>2){
            printf("Invalid inputs. Please enter a valid input (1/2) : ");
             scanf("%u",&choice);
        }
         if (choice==2) {
           return;
        }
        else if(choice ==1){

        choice=0;
 
     uint32_t token_num=generate_token();

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
    fprintf(order_file, "Token number is %u \nOrder Date: %04d-%02d-%02d | Order Time: %02d:%02d:%02d\n",token_num,
            local_time->tm_year + 1900, local_time->tm_mon + 1, local_time->tm_mday,
            local_time->tm_hour, local_time->tm_min, local_time->tm_sec);

        float totalBill=0;
        uint32_t totalOderCount=0;


        while(currentCategory){
            printf("Select item from %s to place order ",currentCategory->categoryName);
        uint32_t itemCount=0;
         display_menu(currentCategory,&itemCount);

        printf("\nEnter 0 for skip this category.\nHow many types of item do you want to buy from category %s ? ", currentCategory->categoryName);
        uint32_t numbers_of_item;
        scanf("%u",&numbers_of_item);

        if (numbers_of_item==0) {
            currentCategory = currentCategory->next;
            continue;
        }

        for(uint32_t i=0;i<numbers_of_item;i++){
        printf("Enter item numbers to order : ");
        scanf("%u",&choice);
        while(choice<0 || choice>itemCount){
            printf("Invalid item number. Please enter a valid and available item number: \n");
            scanf("%u",&choice);
        }
        MenuItem *item=currentCategory->items;
         for(uint32_t i=1;i<choice;i++){
          item=item->next;
       }
        uint32_t quantity;
         printf("Enter quantity : ");
         scanf("%u",&quantity);
         if(quantity <= item->stock){
            float subtotalBill=quantity*(item->price);
                             fprintf(order_file, "%s - Quantity: %u - Subtotal: %.2f Taka\n", item->name, quantity, subtotalBill);
                    item->stock -= quantity;

                    totalBill += subtotalBill;
                    totalOderCount++;
                    printf("%s Price in subtotal : %.2f Taka\n", item->name, subtotalBill);
         }
         else {
            printf("Insufficient stock. Please choose a quantity less than or equal to %u.\n", item->stock);
            i--;
         }
        }
        currentCategory=currentCategory->next;
     }
    
    fprintf(order_file," Total Bill of this customer: %0.2f Taka \n",totalBill);
    fprintf(order_file,"=========================================\n");

    fclose(order_file);
    
    printf("Order Summary:\n");
    printf("Token number is %u \nOrder Date: %04d-%02d-%02d | Order Time: %02d:%02d:%02d\n",token_num,
            (*local_time).tm_year + 1900, (*local_time).tm_mon + 1, (*local_time).tm_mday,
            (*local_time).tm_hour, (*local_time).tm_min, (*local_time).tm_sec);
    printf("Number of types of item ordered: %u\n", totalOderCount);
    printf("Total Bill: %.2f Taka\n", totalBill);
    printf("Thanks for coming.\n ");
    write_menu(menu);
     }
     else {
        printf("Invalid inputs");
     }
}

 void update_menu(MenuCategory *menu ){
     MenuCategory *currentCategory = menu;
     uint32_t x=1;
     while(currentCategory){
        display_menu(currentCategory,&x);
        currentCategory=currentCategory->next;
        }
    uint32_t choice;
    printf("\nMenu Update Options:\n");

    printf("1. Add Item\n");
    printf("2. Delete Item\n");
    printf("3. Change Item Price\n");
    printf("4. Add Stock\n");
    printf("5. Back to Admin option\n");
    printf("Enter your choice: ");
    scanf("%u", &choice);
    switch (choice)
    {
    case 1 :add_item(menu);
            update_menu(menu);
              break;
    case 2 :delete_item(menu);
            update_menu(menu);
              break;
    case 3 :change_price(menu);
            update_menu(menu);
              break;
    case 4 :update_stock(menu);
            update_menu(menu);
              break;
    case 5 :return ;
    default:
        printf("Invalid choice.");
    }
}
void view_sale(){
    
      FILE *sales_report_file = fopen(SALES_REPORT_FILE, "r");

    if (sales_report_file == NULL) {
        perror("Error opening sales report file");
        exit(EXIT_FAILURE);
    }

    printf("\nSales Report:\n");
    char buffer[200];
    uint32_t is_first_line=1;
    while (fgets(buffer, sizeof(buffer), sales_report_file) != NULL) {
        if(is_first_line){
            is_first_line=0;
            continue;
        }
        // Check if the line contains the "Order Time" string
        if (strstr(buffer, "Order Time") != NULL) {
            printf("%s", buffer); // Print the date and time line
        } else {
            printf("%s", buffer); // Print the rest of the lines
        }
    }

    fclose(sales_report_file);
}
void clear_sales_report(){
      FILE *sales_report_file = fopen(SALES_REPORT_FILE, "w");

    if (sales_report_file == NULL) {
        perror("Error opening sales report file");
        exit(EXIT_FAILURE);
    }
    fclose(sales_report_file);
    printf("Sales report cleared successfully.");
}

/*
 * admin function of the program.
 * Provides options for admin login.
 */

void admin(MenuCategory *menu,MenuCategory *currentCategory,uint32_t *login){

     // Admin menu
            printf("\nAdmin Options:\n");
            printf("1. Update Menu\n");
            printf("2. Display Menu\n");
            printf("3. View Sales Report\n");
            printf("4. Clear Sales Report\n");
            printf("5. Change Password\n");
            printf("6. Log Out\n");
            printf("7. Exit\n");
            uint32_t x = 1,choice;
            printf("Enter your choice: ");
            scanf("%u", &choice);

            switch (choice) {
                case 1:
                    // Update menu
                    update_menu(menu);
                    break;
                case 2:
                    // Display menu
                    x = 1;
                    while (currentCategory) {
                        display_menu(currentCategory, &x);
                        currentCategory = currentCategory->next;
                    }
                    currentCategory = menu;
                    break;
                case 3:
                    // View sales report
                    view_sale();
                    break;
                case 4:
                    // Clear sales report
                    clear_sales_report();
                    break;
                case 5:
                    // Change admin password
                    change_pass();
                    break;
                case 6:
                    // Log out
                    *login = 0;
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

/*
 * homepage function of the program.
 * Provides options for admin login, customer interaction, and system exit.
 */

void homepage(){
 MenuCategory *menu = read_menu(); // Load the menu from the file
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
                    if (admin_log()) {
                        login = 1;
                        printf("Welcome to the system.\n");
                    } else {
                        login = 0;
                        printf("Returning to main menu.\n");
                    }
                    break;
                case 2:
                    // Customer interaction
                    take_order(menu);
                    break;
                case 3:
                    // Exit the program
                    printf("Exiting the program. Goodbye!\n");
                    exit(0);
                default:
                    printf("Invalid choice. Please try again.\n");
            }
        } else {
           admin(menu,currentCategory,&login);
        }
    }


}

#include<stdio.h>
#include "cafe.c"

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
                    printf("Invalid choice. Please try again.\n");
             }
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
            unsigned int x=1;
            printf("Enter your choice: ");
            scanf("%d", &choice);
            
            switch (choice) {

                case 1:
                    updateMenu(menu);
                    break;
                case 2:
                     x=1;
                     while(currentCategory){
                     displayMenu(currentCategory,&x);
                      currentCategory=currentCategory->next;
                     }
                     currentCategory=menu;
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

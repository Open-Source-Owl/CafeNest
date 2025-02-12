### README for University Automated Cafeteria System

---

##  Automated Cafeteria 

### **Overview**
This project is an automated cafeteria management system designed to streamline operations in a university café. It provides a menu-driven interface for both administrators and customers, enabling functionalities like managing menu items, placing orders, and generating sales reports.

---

### **Key Features**
1. **Admin Features**:
   - Secure login system with password validation.
   - Menu management:
     - Add, update, or delete items.
     - Change item prices and update stock quantities.
   - View and clear sales reports.
   - Password management for added security.

2. **Customer Features**:
   - View the menu with available items and prices.
   - Place orders with real-time stock updates.
   - Automatic bill generation and receipt printing with token-based order tracking.

3. **Persistence**:
   - All data is stored in files for menu information, sales reports, and admin passwords, ensuring persistence across program runs.

---

### **Files in the Project**
1. **`cafe.h`**:
   - Contains data structure definitions (`MenuItem`, `MenuCategory`) and function prototypes for menu management, order handling, and admin functionalities.

2. **`cafe.c`**:
   - Implements the core logic for the cafeteria system, including menu handling, admin login, order placement, and sales report management.

3. **`cafemain.c`**:
   - Serves as the entry point of the program.
   - Provides a menu-driven interface for administrators and customers.

---

### **How to Run the Program**
1. **Prerequisites**:
   - A C compiler (e.g., GCC).
   - Create the necessary files in the same directory:
     - `menu.txt`: Contains menu data in the required format.
     - `adminpass.txt`: Stores the initial admin password.
     - `salereport.txt`: Tracks sales data.

2. **Build**:
   - Compile the program using:
     ```
     gcc cafemain.c -o cafeteria
     ```

3. **Run**:
   - Execute the compiled binary:
     ```
     ./cafeteria
     ```

---

### **File Formats**
1. **`menu.txt`**:
   - Stores the menu data with categories and items.
   - Format:
     ```
     #CategoryName
     ItemName,Price,Stock
     ```
     Example:
     ```
     #Drinks
     Coffee,5.00,10
     Tea,3.50,15
     ```

2. **`adminpass.txt`**:
   - Contains the admin password (default: set manually).
   - Example:
     ```
     admin123
     ```

3. **`salereport.txt`**:
   - Logs all sales transactions and token-based order details.
   - Example:
     ```
     ----- 
     Token number is 1
     Order Date: 2025-01-22 | Order Time: 10:30:25
     Coffee - Quantity: 2 - Subtotal: 10.00 Taka
     Total Bill of this customer: 10.00 Taka
     ```

---

### **Project Structure**
- **Data Structures**:
  - `MenuCategory`: Represents a menu category.
  - `MenuItem`: Represents an individual item within a category.
- **Core Functions**:
  - `readMenu`: Loads the menu from `menu.txt`.
  - `takeorder`: Handles customer order placement and billing.
  - `updateMenu`: Allows the admin to modify menu data.
  - `viewsale`: Displays the sales report.
  - `clearsalesreport`: Clears the sales data.

---

### **Admin Guide**
1. **Login**:
   - Select "Log in as Admin" and provide the correct password.
   - The admin interface provides options to manage the menu, view reports, and modify passwords.

2. **Menu Management**:
   - Use options to add, update, or delete menu items, as well as modify item prices and stock levels.

3. **Sales Reports**:
   - View a detailed sales report or clear the report for a fresh start.

---

### **Customer Guide**
1. **Viewing the Menu**:
   - Select "Log in as Customer" to browse the available menu.
   - Items with insufficient stock are hidden.

2. **Placing Orders**:
   - Select items and specify the quantities to add to your order.
   - A unique token is generated for every order.

---

### **Error Handling**
- **File Issues**:
  - The program gracefully handles missing or inaccessible files, printing appropriate error messages.
- **Input Validation**:
  - All user inputs are validated to ensure robustness against invalid or unexpected entries.

---

### **Future Improvements**
- Implement a graphical user interface (GUI).
- Enhance order management with a queueing system.
- Add support for multiple admin accounts with role-based access control.

---

Enjoy the seamless experience of managing and interacting with the University Automated Cafeteria System!

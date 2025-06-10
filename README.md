# ECPI_Agile_Project  

## Team Members:  
- Damien Harmon  
- Stephanie Abney  
- John Hunter  
- Geovanny Pantoja  

## Project Overview  
This project contains the following structs and arrays:  

- 2 custom structs named `Income` and `Expense` with the following data:  
  - **Date**: `char[]` Specific format **yyyy-mm-dd**.  
  - **Description**: `char[]` Max 50 chars.  
  - **Category**: `char[]` Max 21 chars (only for `Expense` struct).  
  - **Amount**: `float` (Negative numbers not allowed).  
- 1 Array of struct `Income` named `incomes`.  
- 1 Array of struct `Expense` named `expenses`.  

This project is written in **C** and includes the following functions:  

- A **menu function** with **seven choices** that returns the user's selected option.  
- A **loop function** that processes the returned option from the menu and calls other functions based on the user's selection.  
- **Option 1 and 2**: Functions that allow the user to add **Income** and **Expense** amounts, which are stored in a custom data structure containing:  
  - **Date**  
  - **Description**  
  - **Amount**
  - **Category** (Expenses only)
- **Option 3**: A function that displays stored transactions in the **Income and Expense** data structure.  
- **Option 4 and 5**: Functions that display a summary of **Income and Expenses**, including:  
  - **Total number of transactions**  
  - **Total amount of Income and Expense transactions**  
- **Option 6**: A function that writes the user's entered information to a **CSV file** (available in the menu and automatically runs upon exiting the program).  
- **Option 7**: Exits the program.  
- A function that **reads and loads information from a CSV file** if it exists in the same folder as the `.c` file when the program starts.  

## Cloning and Running the Program  

1. **Open your command terminal**.  
2. **Navigate to the desired folder** (an empty folder is recommended).  
3. **Execute the following command**:  

   ```sh
   git clone https://github.com/Geovanny-Pantoja/ECPI_Agile_Project.git
   
Open DevC++ IDE.

Press F11 to compile and run the program.

Notes
Ensure you have a C compiler installed (e.g., gcc or clang).

Only authorized users can make changes to this repository.
  



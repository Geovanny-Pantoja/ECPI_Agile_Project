# ECPI_Agile_Project
## Team members: 
- Damien Harmon
-  Stephanie Abney
-  John Hunter
-  Geovanny Pantoja
## This project is written in C with the following functions:
- It has a menu function with 7 choices that returns the user chosen option.
- a loop function that handles the returned option from the menu function and calls other functions based on the user selection
- Option 1 and 2 contains two functions that allows the user to add Income and Expense ammounts to be stored in a custom data struct that contains the following:
  - Date
  - Description
  - Ammount
- Option 3 contains a function that displays the stored transations in the income and expense data struct
- Option 4 and 5 contains functions that display the summary of income and expenses.
  - Total number of transactions
  - Total amount of income and expense transactions
- Option 6 contains a function to write the information entered by the user to an excel file (available in the menu and auto runs upon exiting the program).
- Option 7 Exits the program
- A function that reads and loads information from a CSV file if it exists in the same folder as the .c file when the program starts.



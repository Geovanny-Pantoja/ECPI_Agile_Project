#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_RECORDS 100
#define MAX_DATE 11
#define MAX_DESC 51
#define MAX_CAT 21

// Struct Definitions
typedef struct {
    char date[MAX_DATE];
    char description[MAX_DESC];
    float amount;
} Income;

typedef struct {
    char date[MAX_DATE];
    char description[MAX_DESC];
    char category[MAX_CAT];
    float amount;
} Expense;

// Function Prototypes
void mainLoop(Income incomes[], Expense expenses[], int *incomeCount, int *expenseCount);
int menu();
int addIncome(Income incomes[], int count);
int addExpense(Expense expenses[], int count);
void displayTransactions(Income incomes[], int incomeCount, Expense expenses[], int expenseCount);
void displayIncomeSummary(Income incomes[], int incomeCount);
void displayExpenseSummary(Expense expenses[], int expenseCount);
void exportToFile(Income incomes[], int incomeCount, Expense expenses[], int expenseCount);
void loadFromFile(Income incomes[], int *incomeCount, Expense expenses[], int *expenseCount);
void flushInput();
void clearScreen();
int isValidDate(const char *date);

int main() {
    Income incomes[MAX_RECORDS];
    Expense expenses[MAX_RECORDS];
    int incomeCount = 0;
    int expenseCount = 0;

    loadFromFile(incomes, &incomeCount, expenses, &expenseCount);
    mainLoop(incomes, expenses, &incomeCount, &expenseCount);    
    exportToFile(incomes, incomeCount, expenses, expenseCount);

    printf("Exiting application. Goodbye.\n");
    return 0;
}

void mainLoop(Income incomes[], Expense expenses[], int *incomeCount, int *expenseCount){
	int option;
    do {
        option = menu();
        switch(option) {
            case 1:
                *incomeCount = addIncome(incomes, *incomeCount);
                break;
            case 2:
                *expenseCount = addExpense(expenses, *expenseCount);
                break;
            case 3:
                displayTransactions(incomes, *incomeCount, expenses, *expenseCount);
                break;
            case 4:
                displayIncomeSummary(incomes, *incomeCount);
                break;
            case 5:
                displayExpenseSummary(expenses, *expenseCount);
                break;
            case 6:
                exportToFile(incomes, *incomeCount, expenses, *expenseCount);
                break;
            case 7:
                break;
            default:
                printf("Invalid option. Press enter to try again.\n");
                getchar();
        }
    } while (option != 7);
	
}

int menu() {
    int option;
    clearScreen();
    printf("=== Personal Finance Tracker ===\n");
    printf("1. Add Income\n");
    printf("2. Add Expense\n");
    printf("3. Display All Transactions\n");
    printf("4. Display Income Summary\n");
    printf("5. Display Expense Summary\n");
    printf("6. Export Transactions to File\n");
    printf("7. Exit\n");
    printf("Select option: ");
    scanf("%d", &option);
    flushInput();
    return option;
}

int addIncome(Income incomes[], int count) {
    if (count >= MAX_RECORDS) {
        printf("Income list full. Cannot add more entries.\n");
        printf("Press enter to continue.\n");    
        getchar();
        return count;
    }

  while(1) {
        printf("Enter date (YYYY-MM-DD): ");
        fgets(incomes[count].date, MAX_DATE, stdin);
        int len = strlen(incomes[count].date);
        //get rid of \n..fgets includes \n
    
       if (len > 0 && incomes[count].date[len - 1] == '\n') {
          incomes[count].date[len - 1] = '\0';
       } else {
       	   flushInput();
	   }
       
	          
       if (isValidDate(incomes[count].date)) {
            break;
        } 
		
   }

    while (1) {
      printf("Enter description (max %d characters): ", MAX_DESC - 1);
      fgets(incomes[count].description, MAX_DESC, stdin);

      int len = strlen(incomes[count].description);

      // If input too long (no newline), flush remaining chars and retry
      if (len > 0 && incomes[count].description[len - 1] != '\n') {
         flushInput();
         printf("Input too long. Please enter up to %d characters.\n\n", MAX_DESC - 1);
         continue; // back to start of while loop
      }

      // Remove trailing newline if it exists
      if (len > 0 && incomes[count].description[len - 1] == '\n') {
          incomes[count].description[len - 1] = '\0';
      }
      
      if (strlen(incomes[count].description) == 0) {
        printf("Description cannot be empty. Please try again.\n\n");
        continue;
    }

      break; // valid input, exit loop
    }

    while (1){
	    printf("Enter amount: ");
        if(scanf("%f", &incomes[count].amount) != 1){
        	printf("Invalid input, it should be numeric. Please enter a number.\n");
        	flushInput();
        	continue;
		}
		if(incomes[count].amount <= 0){
			printf("Amount needs to be more than 0. Please enter a correct amount.\n");
			flushInput();
        	continue;
		}
        flushInput();
        break;
    }
    printf("Income entry added successfully.\n");
    printf("Press enter to continue.\n");    
    getchar();
    return count + 1;
}

int addExpense(Expense expenses[], int count) {
    if (count >= MAX_RECORDS) {
        printf("Expense list full. Cannot add more entries.\n");
        printf("Press enter to continue.\n");    
        getchar();
        return count;
    }

  while(1) {
        printf("Enter date (YYYY-MM-DD): ");
        fgets(expenses[count].date, MAX_DATE, stdin);
        int len = strlen(expenses[count].date);
        //get rid of \n..fgets includes \n
    
       if (len > 0 && expenses[count].date[len - 1] == '\n') {
          expenses[count].date[len - 1] = '\0';
       }else {
       	   flushInput();
	   }
       
       if (isValidDate(expenses[count].date)) {
            break;
        } 
		
   }   
    
    while (1) {
      printf("Enter description (max %d characters): ", MAX_DESC - 1);
      fgets(expenses[count].description, MAX_DESC, stdin);

      int len = strlen(expenses[count].description);

      // If input too long (no newline), flush remaining chars and retry
      if (len > 0 && expenses[count].description[len - 1] != '\n') {
         flushInput();
         printf("Input too long. Please enter up to %d characters.\n\n", MAX_DESC - 1);
         continue; // back to start of while loop
      }

      // Remove trailing newline if it exists
      if (len > 0 && expenses[count].description[len - 1] == '\n') {
          expenses[count].description[len - 1] = '\0';
      }
      
      if (strlen(expenses[count].description) == 0) {
        printf("Description cannot be empty. Please try again.\n\n");
        continue;
    }

      break; // valid input, exit loop
    }

    while (1){
	    printf("Enter amount: ");
        if(scanf("%f", &expenses[count].amount) != 1){
        	printf("Invalid input, it should be numeric. Please enter a number.\n");
        	flushInput();
        	continue;
		}
		if(expenses[count].amount <= 0){
			printf("Amount needs to be more than 0. Please enter a correct amount.\n");
			flushInput();
        	continue;
		}
        flushInput();
        break;
    }
    printf("Expense entry added successfully.\n");
    printf("Please press enter to continue.\n");
    getchar();
    return count + 1;
}

void displayTransactions(Income incomes[], int incomeCount, Expense expenses[], int expenseCount) {
    if (incomeCount == 0 && expenseCount == 0){
    	printf("No transaction to display.\n");
    	return;
	}
	
	if(incomeCount > 0){
		printf("\n--- Income Transactions ---\n");
		int i;
		for (i = 0; i < incomeCount; i++){
			printf("Income #%d:\n", i + 1);
			printf("Date: %s\n", incomes[i].date);
			printf("Description: %s\n", incomes[i].description);
			printf("Amount: $%.2f\n", incomes[i].amount);
			printf("---------------------------\n");
		}
	}
	else {
		printf("\nNo income records found.\n");
	}
	if(expenseCount > 0){
		printf("\n--- Expense Transactions ---\n");
		int i;
		for (i = 0; i < expenseCount; i++){
			printf("Expense #%d:\n", i + 1);
			printf("Date: %s\n", expenses[i].date);
			printf("Description: %s\n", expenses[i].description);
			printf("Amount: $%.2f\n", expenses[i].amount);
			printf("---------------------------\n");
		}
	}
	else {
		printf("\nNo expense records found.\n");
	}
    
    printf("Please press enter to continue.\n");
    getchar();
}

void displayIncomeSummary(Income incomes[], int incomeCount) {
    float total = 0;
    
    printf("-----Income Summary-------\n");
    if(incomeCount == 0){
    	printf("There are no records to display.\n");
	}
	else{
		int i;
		for(i = 0; i < incomeCount; i++){
			total += incomes[i].amount;
		}
		printf("Total Transactions: %d\n", incomeCount);
		printf("Total Income: $%.2f\n", total);
	}
    printf("Please press enter to continue.\n");
    getchar();
}

void displayExpenseSummary(Expense expenses[], int expenseCount) {
    
     float total = 0;
    
    printf("-----Expense Summary-------\n");
    if(expenseCount == 0){
    	printf("There are no records to display.\n");
	}
	else{
		int i;
		for(i = 0; i < expenseCount; i++){
			total += expenses[i].amount;
		}
		printf("Total Transactions: %d\n", expenseCount);
		printf("Total Expenses: $%.2f\n", total);
	}
    
    printf("Please press enter to continue.\n");
    getchar();
}

void exportToFile(Income incomes[], int incomeCount, Expense expenses[], int expenseCount) {
    
    //handle case if there are no transactions to write 
    if (incomeCount == 0 && expenseCount ==0){
    	printf("No transactions to write. CSV file not updated.\n");
    	
    	printf("Please press enter to continue.\n");
        getchar();
    	return;
	}
	
	//open file or create if it does not exist 
	FILE *file = fopen("transaction.csv", "w");
	if (file == NULL){
		perror("Error opening file");
		return;
	}
	//Write headers
	fprintf(file, "Type,Date,Description,Amount\n");
	
	//write income 
	int i;
	for(i = 0; i < incomeCount; i++){
		fprintf(file, "Income,%s,%s,%.2f\n", incomes[i].date, incomes[i].description, incomes[i].amount);
	}
	
	//write expenses
	for(i = 0; i < expenseCount; i++){
		fprintf(file, "Expense,%s,%s,%.2f\n", expenses[i].date, expenses[i].description, expenses[i].amount);
	}
	fclose(file);
	if(incomeCount == 0){
		printf("Expenses successfully written to transaction.csv.\nThere were no Income transactions to report.\n");
	}
	else if (expenseCount == 0){
	    printf("Income successfully written to transaction.csv.\nThere were no Expense transactions to report.\n");
	}
	else {
		printf("Data successfully written to transaction.csv\n");
	}
	
    printf("Please press enter to continue.\n");
    getchar();
}

void loadFromFile(Income incomes[], int *incomeCount, Expense expenses[], int *expenseCount) {
    
    FILE *file = fopen("transaction.csv","r");
    if (file == NULL) {
        printf("No existing CSV file found. Starting with an empty record.\n");
        return;  // Exit gracefully if no file exists
    }

    char buffer[256];
    fgets(buffer, sizeof(buffer), file);  // Skip header

    int warningPrintedIncome = 0;  // Prevent repeated warnings for Income
    int warningPrintedExpense = 0; // Prevent repeated warnings for Expense

    while (fgets(buffer, sizeof(buffer), file)) {
        char type[10], date[15], description[50];
        float amount;

        // Tokenize the CSV line
        char *token = strtok(buffer, ",");
        if (token == NULL) continue; // Skip invalid rows

        strcpy(type, token);

        token = strtok(NULL, ",");
        if (token == NULL) continue;
        strcpy(date, token);

        token = strtok(NULL, ",");
        if (token == NULL) continue;
        strcpy(description, token);

        token = strtok(NULL, ",");
        if (token == NULL) continue;
        amount = atof(token);  // Convert string to float

        // Handle Income Records
        if (strcmp(type, "Income") == 0) {
            if (*incomeCount >= MAX_RECORDS) {
                if (!warningPrintedIncome) {  // Print only once
                    printf("Warning: Income records exceeded limit (%d). Some entries will be skipped.\n", MAX_RECORDS);
                    warningPrintedIncome = 1;
                }
                continue;  // Skip extra records
            }
            strcpy(incomes[*incomeCount].date, date);
            strncpy(incomes[*incomeCount].description, description, sizeof(incomes[*incomeCount].description) - 1);
            incomes[*incomeCount].description[sizeof(incomes[*incomeCount].description) - 1] = '\0';
            incomes[*incomeCount].amount = amount;
            (*incomeCount)++; 
        }

        // Handle Expense Records
        else if (strcmp(type, "Expense") == 0) {
            if (*expenseCount >= MAX_RECORDS) {
                if (!warningPrintedExpense) {  // Print only once
                    printf("Warning: Expense records exceeded limit (%d). Some entries will be skipped.\n", MAX_RECORDS);
                    warningPrintedExpense = 1;
                }
                continue;  // Skip extra records
            }
            strcpy(expenses[*expenseCount].date, date);
            strncpy(expenses[*expenseCount].description, description, sizeof(expenses[*expenseCount].description) - 1);
            expenses[*expenseCount].description[sizeof(expenses[*expenseCount].description) - 1] = '\0';
            expenses[*expenseCount].amount = amount;
            (*expenseCount)++; 
        }
    }

    fclose(file);  // Close file properly
    printf("CSV data successfully loaded!\n");
    printf("Please enter to continue.");
    getchar();
}

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void flushInput() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
int isValidDate(const char *date) {
    if (strlen(date) != 10 || date[4] != '-' || date[7] != '-') {
        printf("Error: Date must be in YYYY-MM-DD format.\n");
        return 0;
    }

    int year, month, day;
    if (sscanf(date, "%4d-%2d-%2d", &year, &month, &day) != 3) {
        printf("Error: Failed to parse the date components.\n");
        return 0;
    }

    if (year < 1900 || year > 2100) {
        printf("Error: Year must be between 1900 and 2100.\n");
        return 0;
    }

    if (month < 1 || month > 12) {
        printf("Error: Month must be between 1 and 12.\n");
        return 0;
    }

    if (day < 1 || day > 31) {
        printf("Error: Day must be between 1 and 31.\n");
        return 0;
    }

    int daysInMonth[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

    // Leap year check
    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
        daysInMonth[1] = 29;

    if (day > daysInMonth[month - 1]) {
        printf("Error: Invalid day for the specified month.\n");
        return 0;
    }

    // Check if the date is in the future
    time_t t = time(NULL);
    struct tm *current = localtime(&t);

    int currYear = current->tm_year + 1900;
    int currMonth = current->tm_mon + 1;
    int currDay = current->tm_mday;

    if (year > currYear) {
        printf("Error: Year is in the future.\n");
        return 0;
    }
    if (year == currYear && month > currMonth) {
        printf("Error: Month is in the future.\n");
        return 0;
    }
    if (year == currYear && month == currMonth && day > currDay) {
        printf("Error: Day is in the future.\n");
        return 0;
    }

    return 1;
}


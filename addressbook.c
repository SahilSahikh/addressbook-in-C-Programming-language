/*
I’m Sahil Shaikh, excited to introduce my project, Address Book.
I believe in the power of collaboration and welcome contributions.
Let’s share ideas and enhance this project together!
Looking forward to connecting with all of you!
*/



#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include<unistd.h>
#include<windows.h>
#include<ctype.h>
#include <stdio.h>
#include <time.h>

/*----------------colors----------------------*/

#define BBLK "\e[1;30m"
#define BRED "\e[1;31m"
#define BGRN "\e[1;32m"
#define BYEL "\e[1;33m"
#define BBLU "\e[1;34m"
#define BMAG "\e[1;35m"
#define BCYN "\e[1;36m"
#define BWHT "\e[1;37m"
#define COLOR_RESET "\033[0m"
/*---------------------------------------------------*/
// Structure for address book entry
struct abEntry {
    char name[50];
    char address[50];
    char number[12];
    char email[30];
    time_t createdAt;
    time_t lastModified;
};

// Function prototypes
void print_with_animation2(const char *text);
void set_color(const char *color);

void reset_color();
void displayMenu();
void addEntry();
void searchEntry();
void displayAllEntries();
void editEntry();
void deleteEntry();
void saveAndExit();
void sortdata();
/*-------validation---------*/
void getName(char *name);
void getAddress(char *address);
void getPhoneNumber(char *number);
void getEmail(char *email);
/*--------------------------*/
bool isDuplicate(const char* number, const char* email, FILE* fptr, bool* foundNumber, bool* foundEmail);
void printContactsBySearch(const char *searchTerm, int choice); 
int compareContacts(const char *entry1, const char *entry2);
/*-------------------------------------------------*/
void printCyberAttackTitle(const char *title, const char *color);
/*----------------------------------------------*/

// File names
const char* dataFile = "data.csv";
const char* tempFile = "temp.csv";

// Main function
int main() {
    
    printf("\n");
    printCyberAttackTitle("\t\t\t\t\t\t\t\t  <------------------------->",BCYN);
    srand(time(NULL)); // Seed for random number generation
    printCyberAttackTitle("\t\t\t\t\t\t\t\t  |       ADDRESSBOOK       |", BYEL);
    printCyberAttackTitle("\t\t\t\t\t\t\t\t  <------------------------->",BCYN);
    printf("\n");
    int choice;
    char continueOption;

    do {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addEntry();
                break;
            case 2:
                searchEntry();
                break;
            case 3:
                displayAllEntries();
                break;
            case 4:
                editEntry();
                break;
            case 5:
                deleteEntry();
                break;
            case 6:
                saveAndExit();
                break;
            default:
                print_with_animation2("Invalid option! Please try again.\n");
        }
        set_color("\e[1;35m");
        print_with_animation2("\n\t\t\t Do you want to continue? (y/n): ");
        reset_color();
        scanf(" %c", &continueOption);
    } while (continueOption == 'y' || continueOption == 'Y');

    return 0;
}



void displayMenu() {
    
    
    set_color("\e[1;36m");
    print_with_animation2("\t\t\t\t\t\t\t\t  <------------------------->\n");
    print_with_animation2("\t\t\t\t\t\t\t\t  |  1. Add Entry           | \n");
    print_with_animation2("\t\t\t\t\t\t\t\t  |  2. Search Entry        | \n");
    print_with_animation2("\t\t\t\t\t\t\t\t  |  3. Display All Entries | \n");
    print_with_animation2("\t\t\t\t\t\t\t\t  |  4. Edit Entry          | \n");
    reset_color();
    set_color("\e[1;31m");
    print_with_animation2("\t\t\t\t\t\t\t\t  |  5. Delete Entry        | \n"); 
    reset_color();
    set_color("\e[1;36m");
    print_with_animation2("\t\t\t\t\t\t\t\t  |  6. Save and Exit       |\n");
    print_with_animation2("\t\t\t\t\t\t\t\t  <------------------------->");
    reset_color();
    
    set_color("\e[1;37m");
    print_with_animation2("\n\t\t\t\t\t\t\t\t  Choose an option -->> ");
    reset_color();
}



void addEntry() {
    struct abEntry newEntry;
    FILE *fptr, *originalFile;
    int count = 0;
    const char *dataFile = "data.csv";
    const char *tempFile = "temp.csv";
    char buffer[1024]; // Buffer size increased to handle larger lines

    // Open the original file in read mode to get the current count and data
    fptr = fopen(dataFile, "r");
    if (!fptr) {
        printf("Error: Could not open %s for reading.\n", dataFile);
        return;
    }

    // Read the first line (the count of entries)
    if (fgets(buffer, sizeof(buffer), fptr)) {
        count = atoi(buffer); // Convert first line to integer (the count)
    }

    // Start gathering input with validation
    getName(newEntry.name);
    getAddress(newEntry.address);

    // Duplicate check loop
    while (1) {
        getPhoneNumber(newEntry.number);
        getEmail(newEntry.email);

        bool foundNumber = false, foundEmail = false;
        rewind(fptr); // Move back to the start of the file after the count is read
        fgets(buffer, sizeof(buffer), fptr); // Skip the count line again

        if (isDuplicate(newEntry.number, newEntry.email, fptr, &foundNumber, &foundEmail)) {
            if (foundNumber) {
                set_color("\e[1;31m");
                printf("\t\t\t\t\t\t\t\t\t\t\tError: The phone number already exists. Please provide a unique phone number.\n");
                reset_color();
            }
            if (foundEmail) {
                set_color("\e[1;31m");
                printf("\t\t\t\t\t\t\t\t\t\t\tError: The email already exists. Please provide a unique email address.\n");
                reset_color();
            }
        } else {
            break; // No duplicates found, proceed to add the entry
        }
    }

    // Close file after checking for duplicates
    fclose(fptr);

    // Set timestamps
    newEntry.createdAt = time(NULL);
    newEntry.lastModified = newEntry.createdAt;

    // Open the temporary file for writing (this will be our new data file)
    fptr = fopen(tempFile, "w");
    if (!fptr) {
        printf("Error: Could not open %s for writing.\n", tempFile);
        return;
    }

    // Write updated count to temp file
    count++;
    fprintf(fptr, "%d\n", count);

    // Reopen original file to copy old entries (skipping the count line)
    originalFile = fopen(dataFile, "r");
    if (!originalFile) {
        printf("Error: Could not reopen %s for reading.\n", dataFile);
        fclose(fptr);
        return;
    }

    fgets(buffer, sizeof(buffer), originalFile); // Skip count line

    // Copy existing entries to temp file
    while (fgets(buffer, sizeof(buffer), originalFile)) {
        fputs(buffer, fptr);
    }
    fclose(originalFile);

    // Add new entry to the temp file
    fprintf(fptr, "%s,%s,%s,%s,%ld,%ld\n", newEntry.name, newEntry.address, newEntry.number, newEntry.email, newEntry.createdAt, newEntry.lastModified);

    // Close the temp file after writing the new entry
    fclose(fptr);

    // Replace the original file with the temporary file
    if (remove(dataFile) != 0) {
        printf("Error: Could not delete original file %s.\n", dataFile);
        return;
    }
    if (rename(tempFile, dataFile) != 0) {
        printf("Error: Could not rename temp file %s to %s.\n", tempFile, dataFile);
        return;
    }
    set_color("\e[1;32m");
    print_with_animation2("\n\t\t\t\t\t\t\t\t\t\t\t\tEntry added successfully.\n");
    reset_color();
}


/*---------------------------------------------------------------------------------------------------------*/
// Function to validate name (alphabetic characters and spaces only)
void getName(char *name) {
    while (1) {
        set_color("\e[1;36m");
        printf("\n\n\t\t\t\t\t\t\t\t  Enter name: ");
        reset_color();
        scanf(" %[^\n]", name); // Allows for spaces in the name

        int valid = 1; // Assume valid
        for (int i = 0; name[i] != '\0'; i++) {
            if (!isalpha(name[i]) && name[i] != ' ') {
                valid = 0; // Found an invalid character
                break;
            }
        }

        if (valid) {
            break; // Valid name entered
        } else {
            set_color("\e[1;31m");
            print_with_animation2("\t\t\t\t\t\t\t\t\t\t\tInvalid name format. Please enter alphabets only.\n");
            reset_color();
        }
    }
}
/*----------------------------------------------------------------------------------------------------------------------------------*/
// Function to validate address (alphabetic characters, digits, and spaces only)
void getAddress(char *address) {
    while (1) {
        set_color("\e[1;36m");
        printf("\t\t\t\t\t\t\t\t  Enter address: ");
        reset_color();
        scanf(" %[^\n]", address); // Allows spaces in the address

        int valid = 1; // Assume valid
        for (int i = 0; address[i] != '\0'; i++) {
            if (!isalpha(address[i]) && !isdigit(address[i]) && address[i] != ' ') {
                valid = 0; // Found an invalid character
                break;
            }
        }

        if (valid) {
            break; // Valid address entered
        } else {
            set_color("\e[1;31m");
            printf("Invalid address format. Please enter alphabets and digits only.\n");
            reset_color();
        }
    }
}

// Function to validate phone number (exactly 10 digits)
void getPhoneNumber(char *number) {
    while (1) {
        set_color("\e[1;36m");
        printf("\t\t\t\t\t\t\t\t  Enter number: ");
        reset_color();
        scanf("%s", number); // Read as a string to validate length and digits

        // Check if the number is exactly 10 digits and consists only of digits
        if (strlen(number) == 10 && strspn(number, "0123456789") == 10) {
            break; // Valid number entered
        } else {
            printf("\t\t\t\t\t\t\t\t\t\t\tInvalid number format. Please enter exactly 10 digits.\n");
        }
    }
}

// Function to validate email (must end with @gmail.com and no newline before @)
void getEmail(char *email) {
    while (1) {
        set_color("\e[1;36m");
        printf("\t\t\t\t\t\t\t\t  Enter email: ");
        reset_color();
        char tempEmail[40]; // Increased size to accommodate full email

        // Read the input
        if (scanf("%39s", tempEmail) == 1) {
            // Check if it ends with @gmail.com
            const char *gmailDomain = "@gmail.com";
            size_t emailLength = strlen(tempEmail);
            size_t domainLength = strlen(gmailDomain);
            
            // Validate that the email ends with @gmail.com
            if (emailLength > domainLength && strcmp(tempEmail + emailLength - domainLength, gmailDomain) == 0) {
                // Check for invalid characters before '@'
                bool valid = true;
                for (size_t i = 0; i < emailLength - domainLength; i++) {
                    if (!(isalnum(tempEmail[i]) || tempEmail[i] == '.' || tempEmail[i] == '_' || tempEmail[i] == '-')) {
                        valid = false;
                        break;
                    }
                }

                if (valid) {
                    strcpy(email, tempEmail); // Valid email entered
                    break; // Exit the loop
                } else {
                    printf("\t\t\t\t\t\t\t\tEmail contains invalid characters. Please use letters, numbers, '.', '_', or '-'.\n");
                }
            } else {
                printf("\t\t\t\t\t\t\t\tInvalid email format. Please ensure it ends with @gmail.com.\n");
            }
        } else {
            printf("\t\t\t\t\t\t\t\tInput error. Please try again.\n");
        }

        // Clear the input buffer
        while (getchar() != '\n');
    }
}

void searchEntry() {
    FILE *file = fopen("data.csv", "r");
    if (!file) {
        printf("Error opening file for reading.\n");
        return;
    }

    char searchTerm[50], buffer[256], name[50], address[50], number[12], email[30];
    time_t createdAt, lastModified;
    int choice;

    // Get user's choice for search criteria
    set_color("\e[1;36m");
    printf("\t\t\t\t\tSearch by:\n");
    printf("\t\t\t\t\t\t1. Name\n");
    printf("\t\t\t\t\t\t2. Phone number\n");
    printf("\t\t\t\t\t\t3. Email\n");
    printf("\t\t\t\t\t\tEnter choice (1-3): ");
    reset_color();
    scanf("%d", &choice);
    getchar();  // Clear the newline from the input buffer

    // Get the search term based on the user's choice
    switch (choice) {
        case 1:
            set_color("\e[1;34m");
            printf("\n\t\t\t\t\t\t\t\t  Enter name to search: ");
            fgets(searchTerm, sizeof(searchTerm), stdin);
            searchTerm[strcspn(searchTerm, "\n")] = 0;  // Remove the newline character
            break;
        case 2:
            printf("\t\t\t\t\t\t\t\t  Enter phone number to search: ");
            fgets(searchTerm, sizeof(searchTerm), stdin);
            searchTerm[strcspn(searchTerm, "\n")] = 0;  // Remove the newline character
            break;
        case 3:
            printf("\t\t\t\t\t\t\t\t  Enter email to search : ");
            fgets(searchTerm, sizeof(searchTerm), stdin);
            searchTerm[strcspn(searchTerm, "\n")] = 0;  // Remove the newline character
            reset_color();
            break;
        default:
            printf("Invalid choice.\n");
            fclose(file);
            return;
    }

    // Skip the first line (contact count)
    fgets(buffer, sizeof(buffer), file);

    // Store found contacts for multiple matches
    int found = 0;
    printf("\nMatching contacts:\n\n");

    while (fgets(buffer, sizeof(buffer), file)) {
        sscanf(buffer, "%49[^,],%49[^,],%11[^,],%29[^,],%ld,%ld", name, address, number, email, &createdAt, &lastModified);

        int match = 0;

        // Determine match based on user's choice
        if (choice == 1 && strstr(name, searchTerm)) {
            match = 1;
        } else if (choice == 2 && strcmp(number, searchTerm) == 0) {
            match = 1;
        } else if (choice == 3 && strncmp(email, searchTerm, strlen(searchTerm)) == 0) {
            match = 1;
        }

        if (match) {
            found = 1;
            
            
            
            // Print all data in a single line
            set_color("\e[1;36m");
            printf("\t\t\tFOUND : ");
            reset_color();
            set_color("\e[1;32m");
            print_with_animation2(name);
            print_with_animation2(", ");
            print_with_animation2(address);
            print_with_animation2(", ");
            print_with_animation2(number);
            print_with_animation2(", ");
            print_with_animation2(email);
            reset_color();
            printf("\n");
            // Print the separator line
            
        }

    }

    if (!found) {
        printf("No matching contacts found.\n");
    }

    fclose(file);
}

void displayAllEntries() {
    FILE *file;
    char buffer[256];
    const char *dataFile = "data.csv";
    int count = 0;

    file = fopen(dataFile, "r");
    if (file == NULL) {
        printf("Error: Unable to open file.\n");
        return;
    }

    // Read the first line (contact count)
    if (fgets(buffer, sizeof(buffer), file)) {
        count = atoi(buffer);
        set_color("\e[1;35m");
        printf("Total Contacts: %d\n\n", count);
        reset_color();
    }

    // Print CSV header
    
    set_color("\e[1;36m");
    print_with_animation2("\t\t\t\t<------------------------------------------------------------------------------------------>\n");
    print_with_animation2("\t\t\t\t|       Name        |      Address        |        Number         |         Email          |     Created At\n");
    print_with_animation2("\t\t\t\t|-------------------|---------------------|-----------------------|------------------------|\n");
    reset_color();
    // Read and display each contact entry
    while (fgets(buffer, sizeof(buffer), file)) {
    char name[50], address[50], number[12], email[30];
    time_t createdAt;

    // Parse the CSV line
    sscanf(buffer, "%49[^,],%49[^,],%11[^,],%29[^,],%ld", name, address, number, email, &createdAt);

    // Print in CSV-like format with @gmail.com directly appended to the email
    printf("\t\t\t\t| %s%-17s%s | %s%-19s%s | %s%-21s%s | %s%-22s%s | %s%-24s%s",
       BYEL, name, COLOR_RESET,
       BGRN, address, COLOR_RESET,
       BBLU, number, COLOR_RESET,
       BMAG, email, COLOR_RESET,
       BBLK, ctime(&createdAt), COLOR_RESET);
    set_color("\e[1;37m");
    print_with_animation2("\t\t\t\t<-------------------|---------------------|-----------------------|------------------------>\n");    
    reset_color();
    }


    fclose(file);
}
/*--------------------------------------------------------------------------------------------------*/
#define TAB_SPACES "   \t\t\t\t\t\t\t     " 
void printCyberAttackTitle(const char *title, const char *color) {
    int length = strlen(title);
    int iterations = 20; // Number of iterations for the glitch effect

    for (int i = 0; i < iterations; i++) {
        // Print random characters
        printf("%s",TAB_SPACES);
        for (int j = 0; j < length; j++) {
            char randomChar = (rand() % 26) + 'A'; // Generate a random uppercase letter
            printf("%c", randomChar);
        }
        printf("\r"); // Carriage return to overwrite the line
        fflush(stdout); // Ensure the output is displayed immediately

        // Sleep for 50 milliseconds
        struct timespec req = {0};
        req.tv_sec = 0;
        req.tv_nsec = 50000000; // 50 milliseconds in nanoseconds
        nanosleep(&req, NULL);
        printf("%s%*s\r", TAB_SPACES, length, " "); // Clear the line
    }

    // Print the actual title
    printf("%s%s%s\n", " ", color, title, COLOR_RESET);
}
/*---------------------------------------------------------------------------------------------------*/
void editEntry() {
    char searchTerm[50];          // Variable to store the search term
    char continueChoice;          // Variable to store user's choice to continue editing
    char editMore;                // Variable to ask if user wants to edit more contacts

    do {
        // Display options for editing
        printf("Choose how to search for the entry you want to edit:\n");
        printf("1. Enter number to edit\n");
        printf("2. Enter name to edit\n");
        printf("3. Enter email to edit (excluding @gmail.com)\n");
        
        int choice;
        printf("Enter Choice: ");

        // Validate the choice input
        if (scanf("%d", &choice) != 1) {
            printf("Invalid choice. Please enter a number.\n");
            while (getchar() != '\n'); // Clear the input buffer
            continue; // Skip to the next iteration if input is invalid
        }

        getchar(); // Clear the newline character from the buffer

        // Switch statement to handle different choices
        switch (choice) {
            case 1:
                printf("Enter the number to edit: ");
                getPhoneNumber(searchTerm); // Get phone number from the user
                break;
            case 2:
                printf("Enter the name to edit: ");
                getName(searchTerm); // Get name from the user
                break;
            case 3:
                printf("Enter the email to edit (excluding @gmail.com): ");
                getEmail(searchTerm); // Get email from the user
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                continue; // Restart the loop for a valid choice
        }

        // Remove newline character if present in the search term
        searchTerm[strcspn(searchTerm, "\n")] = 0;

        // Call the function to print matching contacts based on the search term
        printContactsBySearch(searchTerm, choice);

        // Ask the user if they want to edit more contacts
        set_color("\e[1;35m");
        printf("Do you want to edit more contacts? (y/n): ");
        reset_color();
        scanf(" %c", &editMore);
        getchar(); // Clear the newline character from the buffer

    } while (editMore == 'y' || editMore == 'Y'); // Continue if the user inputs 'y' or 'Y'

    // After finishing edits, display the main menu
    displayMenu(); // Call the function to display the main menu
    printf("Exiting edit entry.\n"); // Message when exiting the edit entry function
}

/*-----------------------------------------------------------------------------------*/
void printContactsBySearch(const char *searchTerm, int choice) {
    char buffer[256];
    char name[50], address[50], number[12], email[30];
    time_t createdAt;
    FILE *file = fopen("data.csv", "r");

    if (!file) {
        printf("Error opening file.\n");
        return;
    }

    printf("\nMatching contacts:\n\n");
    int index = 0;
    while (fgets(buffer, sizeof(buffer), file)) {
        sscanf(buffer, "%49[^,],%49[^,],%11[^,],%29[^,],%ld", name, address, number, email, &createdAt);

        int match = 0;
        if (choice == 1 && strcmp(searchTerm, number) == 0) {
            match = 1;
        } else if (choice == 2 && strcmp(searchTerm, name) == 0) {
            match = 1;
        } else if (choice == 3 && strncmp(searchTerm, email, strlen(searchTerm)) == 0) {
            match = 1;
        }

        if (match) {
            printf("[%d] Name: %s, Address: %s, Number: %s, Email: %s, Created At: %s\n", 
                   index++, name, address, number, email, ctime(&createdAt));
        }
    }

    if (index == 0) {
        printf("No matching contacts found.\n");
        fclose(file);
        return;
    }

    printf("Select the index of the contact you want to edit (0 to %d): ", index - 1);
    int selectedIndex;
    scanf("%d", &selectedIndex);
    getchar(); // Clear newline character from buffer

    if (selectedIndex < 0 || selectedIndex >= index) {
        printf("Invalid selection.\n");
        fclose(file);
        return;
    }

    // Go back to the beginning to find the selected entry
    fseek(file, 0, SEEK_SET);
    index = 0;
    char selectedBuffer[256];

    while (fgets(buffer, sizeof(buffer), file)) {
        sscanf(buffer, "%49[^,],%49[^,],%11[^,],%29[^,],%ld", name, address, number, email, &createdAt);

        if ((choice == 1 && strcmp(searchTerm, number) == 0) || 
            (choice == 2 && strcmp(searchTerm, name) == 0) || 
            (choice == 3 && strncmp(searchTerm, email, strlen(searchTerm)) == 0)) {
            if (index == selectedIndex) {
                strcpy(selectedBuffer, buffer);
                break;
            }
            index++;
        }
    }

    fclose(file);

    // Edit the selected entry
    printf("\nEditing entry: %s\n", selectedBuffer);
    sscanf(selectedBuffer, "%49[^,],%49[^,],%11[^,],%29[^,],%ld", name, address, number, email, &createdAt);

    printf("Enter new name (leave blank to keep unchanged): ");
    char newName[50];
    fgets(newName, sizeof(newName), stdin);
    if (strlen(newName) > 1) {
        strncpy(name, newName, sizeof(name) - 1);
        name[strcspn(name, "\n")] = 0; // Remove newline
    }

    printf("Enter new address (leave blank to keep unchanged): ");
    char newAddress[50];
    fgets(newAddress, sizeof(newAddress), stdin);
    if (strlen(newAddress) > 1) {
        strncpy(address, newAddress, sizeof(address) - 1);
        address[strcspn(address, "\n")] = 0; // Remove newline
    }

    printf("Enter new number (leave blank to keep unchanged): ");
    char newNumber[12];
    fgets(newNumber, sizeof(newNumber), stdin);
    if (strlen(newNumber) > 1) {
        strncpy(number, newNumber, sizeof(number) - 1);
        number[strcspn(number, "\n")] = 0; // Remove newline
    }

    printf("Enter new email (leave blank to keep unchanged): ");
    char newEmail[30];
    fgets(newEmail, sizeof(newEmail), stdin);
    if (strlen(newEmail) > 1) {
        strncpy(email, newEmail, sizeof(email) - 1);
        email[strcspn(email, "\n")] = 0; // Remove newline
    }

    // Write updated entry back to the file
    FILE *tempFile = fopen("temp.csv", "w");
    file = fopen("data.csv", "r");
    if (!tempFile || !file) {
        printf("Error opening files for writing.\n");
        return;
    }

    while (fgets(buffer, sizeof(buffer), file)) {
        if (strcmp(buffer, selectedBuffer) == 0) {
            fprintf(tempFile, "%s,%s,%s,%s,%ld\n", name, address, number, email, createdAt);
        } else {
            fprintf(tempFile, "%s", buffer);
        }
    }

    fclose(file);
    fclose(tempFile);

    // Replace the original file with the updated temporary file
    remove("data.csv");
    rename("temp.csv", "data.csv");

    printf("Editing complete.\n");
}

/*----------------------------------------------------------------------------------------------------------*/

void deleteEntry() {
    char searchTerm[50];        // Variable to store the search term
    char continueChoice;        // Variable to store user's choice to continue deleting
    char buffer[256];           // Buffer for reading lines from the file
    int choice;

    do {
        // Display options for deleting
        printf("Choose how to search for the entry you want to delete:\n");
        printf("1. Enter number to delete\n");
        printf("2. Enter name to delete\n");
        printf("3. Enter email to delete (excluding @gmail.com)\n");

        // Validate the choice input
        printf("Enter Choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid choice. Please enter a number.\n");
            while (getchar() != '\n'); // Clear the input buffer
            continue;
        }
        getchar(); // Clear the newline character from the buffer

        // Prompt for search term based on the user's choice
        switch (choice) {
            case 1:
                printf("Enter the number to delete: ");
                getPhoneNumber(searchTerm); // Get phone number from the user
                break;
            case 2:
                printf("Enter the name to delete: ");
                getName(searchTerm); // Get name from the user
                break;
            case 3:
                printf("Enter the email to delete (excluding @gmail.com): ");
                getEmail(searchTerm); // Get email from the user
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                continue;
        }

        // Open the original file and a temporary file for writing
        FILE *file = fopen("data.csv", "r");
        FILE *tempFile = fopen("temp.csv", "w");
        if (!file || !tempFile) {
            printf("Error opening files.\n");
            return;
        }

        bool found = false;   // Flag to track if a contact was found
        int contactCount = 0; // Variable to count contacts
        int matchCount = 0;   // Count how many matches are found
        int lineNumber = 0;   // Line number for identifying the entries
        struct abEntry matches[50]; // Store matching entries (adjust size as needed)
        int matchIndexes[50];       // Store line numbers of matching entries

        // Read each line from the original file
        while (fgets(buffer, sizeof(buffer), file)) {
            char name[50], address[50], number[12], email[30];
            time_t createdAt;

            // Parse the CSV line
            if (sscanf(buffer, "%49[^,],%49[^,],%11[^,],%29[^,],%ld", name, address, number, email, &createdAt) == 5) {
                lineNumber++; // Track line numbers for identification
                contactCount++; // Increment the contact count

                // Check if the current entry matches the search term
                bool match = false;
                if (choice == 1 && strcmp(searchTerm, number) == 0) {
                    match = true;
                } else if (choice == 2 && strcmp(searchTerm, name) == 0) {
                    match = true;
                } else if (choice == 3 && strncmp(searchTerm, email, strlen(searchTerm)) == 0) {
                    match = true;
                }

                // If a match is found, store it for later confirmation
                if (match) {
                    found = true;
                    matches[matchCount].createdAt = createdAt;
                    strcpy(matches[matchCount].name, name);
                    strcpy(matches[matchCount].address, address);
                    strcpy(matches[matchCount].number, number);
                    strcpy(matches[matchCount].email, email);
                    matchIndexes[matchCount] = lineNumber;
                    matchCount++;
                }
            }
        }

        // If multiple entries match, ask user to select the one to delete
        if (matchCount > 1) {
            printf("Multiple entries found with the same search term:\n");
            for (int i = 0; i < matchCount; i++) {
                printf("%d. Name: %s, Address: %s, Phone: %s, Email: %s\n", i + 1,
                       matches[i].name, matches[i].address, matches[i].number, matches[i].email);
            }

            int entryChoice;
            printf("Enter the number of the entry you want to delete: ");
            scanf("%d", &entryChoice);

            if (entryChoice < 1 || entryChoice > matchCount) {
                printf("Invalid selection. Deletion aborted.\n");
                fclose(file);
                fclose(tempFile);
                return;
            }

            // Mark the selected entry for deletion
            lineNumber = matchIndexes[entryChoice - 1];
        } else if (matchCount == 1) {
            // Only one match, delete it
            lineNumber = matchIndexes[0];
        } else {
            printf("\nNo matching entries found for deletion.\n");
            fclose(file);
            fclose(tempFile);
            return;
        }

        // Rewind file and copy all except the matching line to temp
        rewind(file);
        int currentLine = 0;
        while (fgets(buffer, sizeof(buffer), file)) {
            currentLine++;
            if (currentLine != lineNumber) {
                fputs(buffer, tempFile); // Copy non-matching lines
            } else {
                printf("\nDeleted entry: %s", buffer); // Display the deleted entry
                contactCount--; // Adjust contact count
            }
        }

        // Close the files
        fclose(file);
        fclose(tempFile);

        // Update the count in the data.csv file
        file = fopen("data.csv", "w");
        if (!file) {
            printf("Error opening file to update count.\n");
            return;
        }
        fprintf(file, "%d\n", contactCount); // Write the updated count

        // Append remaining entries from the temp file
        tempFile = fopen("temp.csv", "r");
        while (fgets(buffer, sizeof(buffer), tempFile)) {
            fprintf(file, "%s", buffer); // Write remaining entries
        }

        fclose(file);
        fclose(tempFile);

        printf("Deletion complete.\n");

        // Ask the user if they want to delete more contacts
        set_color("\e[1;35m");
        printf("Do you want to delete more contacts? (y/n): ");
        reset_color();
        scanf(" %c", &continueChoice);
        getchar(); // Clear the newline character from the buffer

    } while (continueChoice == 'y' || continueChoice == 'Y');

    printf("Exiting delete entry.\n"); // Message when exiting the delete entry function
}



/*---------------------------------------------------------------------------------------------------*/


void saveAndExit() {
    // Sort the data before saving
    sortdata();

    // Open the sorted file in read/write mode to update the contact count
    FILE *file = fopen("data.csv", "r+");
    
    if (!file) {
        printf("Error opening file to save data.\n");
        return;
    }

    // Calculate contact count and update the count at the top of the file
    char buffer[256];
    int count = 0;

    // Skip the first line (which is the count)
    fgets(buffer, sizeof(buffer), file);

    // Count the number of contacts
    while (fgets(buffer, sizeof(buffer), file)) {
        count++;
    }

    // Reopen the file in write mode and update the contact count
    file = freopen("data.csv", "r+", file);
    fprintf(file, "%d\n", count);  // Write the updated contact count at the top

    fclose(file);
    set_color("\e[1;32m");
    print_with_animation2("All changes have been saved, data sorted, and contact count updated. Exiting the program...\n");
    reset_color();
    // Perform any additional cleanup here

    exit(0);
}


/*--------------------------------------------------------------------------------------------*/

void sortdata() {
    FILE *file = fopen("data.csv", "r");
    FILE *tempFile = fopen("temp.csv", "w+");
    
    if (!file || !tempFile) {
        printf("Error opening file for sorting.\n");
        return;
    }

    char buffer[256];
    char lines[100][256];  // Temporary storage for file lines (adjust size if needed)
    int count = 0;

    // Skip the first line (assumed to be the contact count)
    fgets(buffer, sizeof(buffer), file);

    // Read all data into lines array
    while (fgets(buffer, sizeof(buffer), file)) {
        strcpy(lines[count], buffer);
        count++;
    }

    // Sort the lines based on the name (first field in CSV)
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            char name1[50], name2[50];
            sscanf(lines[i], "%49[^,]", name1);
            sscanf(lines[j], "%49[^,]", name2);

            if (strcmp(name1, name2) > 0) {
                char temp[256];
                strcpy(temp, lines[i]);
                strcpy(lines[i], lines[j]);
                strcpy(lines[j], temp);
            }


            
        }
    }

    // Write the contact count at the top
    fprintf(tempFile, "%d\n", count);

    // Write the sorted data back to the temp file
    for (int i = 0; i < count; i++) {
        fputs(lines[i], tempFile);
    }

    fclose(file);
    fclose(tempFile);

    // Replace the original file with the sorted file
    remove("data.csv");
    rename("temp.csv", "data.csv");
    set_color("\e[1;32m");
    print_with_animation2("\nData has been sorted and count updated.\n");
    reset_color();
}

/*----------------------------------------------------------------------------------------------------*/

// Function to compare two entries based on name for sorting
int compareContacts(const char *entry1, const char *entry2) {
    char name1[50], name2[50];
    sscanf(entry1, "%49[^,]", name1); // Extract name from entry1
    sscanf(entry2, "%49[^,]", name2); // Extract name from entry2
    return strcmp(name1, name2); // Compare names
}

/*-----------------------------------------------------------------------------------------------*/

bool isDuplicate(const char* number, const char* email, FILE* fptr, bool* foundNumber, bool* foundEmail) {
    char line[256];
    char storedName[50], storedAddress[50], storedNumber[12], storedEmail[30];
    time_t createdAt, lastModified;

    // Check if the file pointer is valid
    if (fptr == NULL) {
        printf("Error: Could not open file.\n");
        return false;
    }

    // Rewind the file pointer to the beginning
    rewind(fptr);

    // Initialize flags
    *foundNumber = false;
    *foundEmail = false;

    // Read each line in the file
    while (fgets(line, sizeof(line), fptr)) {
        // Parse the line into the relevant fields
        sscanf(line, "%[^,],%[^,],%[^,],%[^,],%ld,%ld", storedName, storedAddress, storedNumber, storedEmail, &createdAt, &lastModified);

        // Check for duplicate number and email
        if (strcmp(storedNumber, number) == 0) {
            *foundNumber = true; // Duplicate number found
        }
        if (strcmp(storedEmail, email) == 0) {
            *foundEmail = true; // Duplicate email found
        }
    }

    return (*foundNumber || *foundEmail); // Return true if any duplicate is found
}



/*---------------------------------------------------------------------------------------------*/
void print_with_animation2(const char *text) {
    while (*text) {
        putchar(*text++);
        fflush(stdout); // Ensure the character is printed immediately
        #ifdef _WIN32
            Sleep(8);  // Sleep for 50ms on Windows
        #else
            usleep(8000);  // Sleep for 50ms on Unix-like systems
        #endif
    }
    // putchar('\n');
}
void set_color(const char *color) {
    printf("%s", color);
}
void reset_color() {
    printf("\033[0m");
}

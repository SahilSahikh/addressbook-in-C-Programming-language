#include "addressBook.h"



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

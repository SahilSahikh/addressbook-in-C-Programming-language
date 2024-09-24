#include "addressBook.h"

const char *dataFile2 = "C:/addressBook/data/data.csv";
const char *tempFile2 = "C:/addressBook/data/temp.csv";


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
        FILE *file = fopen(dataFile2, "r");
        FILE *tempFile = fopen(tempFile2, "w");
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
        file = fopen(dataFile2, "w");
        if (!file) {
            printf("Error opening file to update count.\n");
            return;
        }
        fprintf(file, "%d\n", contactCount); // Write the updated count

        // Append remaining entries from the temp file
        tempFile = fopen(tempFile2, "r");
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

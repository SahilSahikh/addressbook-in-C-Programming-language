#include "addressBook.h"

const char *dataFile6 = "C:/addressBook/data/data.csv";
const char *tempFile6 = "C:/addressBook/data/temp.csv";

void searchEntry() {
    int continueSearching = 1; // Variable to control the loop

    while (continueSearching) {
        FILE *file = fopen(dataFile6, "r");
        if (!file) {
            printf("Error opening file for reading.\n");
            return;
        }

        char searchTerm[50], buffer[256], name[50], address[50], number[12], email[30];
        time_t createdAt, lastModified;
        int choice;

        // Get user's choice for search criteria
        set_color("\e[1;36m");
        printf("\n\t\t\t\t\tSearch by:\n");
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
                set_color("\e[1;33m");
                printf("\n\t\t\t\t\t\t\t\t  Enter name to search: ");
                reset_color();
                fgets(searchTerm, sizeof(searchTerm), stdin);
                searchTerm[strcspn(searchTerm, "\n")] = 0;  // Remove the newline character
                break;
            case 2:
                set_color("\e[1;33m");
                printf("\n\t\t\t\t\t\t\t\t  Enter phone number to search: ");
                reset_color();
                fgets(searchTerm, sizeof(searchTerm), stdin);
                searchTerm[strcspn(searchTerm, "\n")] = 0;  // Remove the newline character
                break;
            case 3:
                set_color("\e[1;33m");
                printf("\n\t\t\t\t\t\t\t\t  Enter email to search: ");
                reset_color();
                fgets(searchTerm, sizeof(searchTerm), stdin);
                searchTerm[strcspn(searchTerm, "\n")] = 0;  // Remove the newline character
                reset_color();
                break;
            default:
                set_color("\e[1;33m");
                printf("\n\nInvalid choice.\n");
                fclose(file);
                printf("\nDo you want to continue searching? (1 for Yes, 0 for No): \n");
                reset_color();
                scanf("%d", &continueSearching);
                continueSearching = (continueSearching == 1); // Update the loop variable
                fclose(file);
                continue; // Skip the rest of the loop and prompt again
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
                printf("\t\t-->>> FOUND : ");
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
            }
        }

        if (!found) {
            set_color("\e[1;36m");
            printf("\nNo matching contacts found.\n");
            reset_color();
        }

        fclose(file);

        // Ask the user if they want to continue searching
        set_color("\e[1;36m");
        printf("\nDo you want to continue searching? (1 for Yes, 0 for No): ");
        reset_color();
        scanf("%d", &continueSearching);
    }
}

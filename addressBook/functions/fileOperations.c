#include "addressBook.h"

const char *dataFile5 = "C:/addressBook/data/data.csv";
const char *tempFile5 = "C:/addressBook/data/temp.csv";


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

void printContactsBySearch(const char *searchTerm, int choice) {
    char buffer[256];
    char name[50], address[50], number[12], email[30];
    time_t createdAt;
    FILE *file = fopen(dataFile5, "r");

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
    FILE *tempFile = fopen(tempFile5, "w");
    file = fopen(dataFile5, "r");
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
    remove(dataFile5);
    rename(tempFile5, dataFile5);

    printf("Editing complete.\n");
}


int compareContacts(const char *entry1, const char *entry2) {
    char name1[50], name2[50];
    sscanf(entry1, "%49[^,]", name1); // Extract name from entry1
    sscanf(entry2, "%49[^,]", name2); // Extract name from entry2
    return strcmp(name1, name2); // Compare names
}

void saveAndExit() {
    // Sort the data before saving
    sortdata();

    // Open the sorted file in read/write mode to update the contact count
    FILE *file = fopen(dataFile5, "r+");
    
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
    file = freopen(dataFile5, "r+", file);
    fprintf(file, "%d\n", count);  // Write the updated contact count at the top

    fclose(file);
    set_color("\e[1;32m");
    print_with_animation2("All changes have been saved, data sorted, and contact count updated. Exiting the program...\n");
    reset_color();
    // Perform any additional cleanup here

    exit(0);
}

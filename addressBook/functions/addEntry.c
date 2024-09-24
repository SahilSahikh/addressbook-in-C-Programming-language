#include "addressBook.h"

const char *dataFile1 = "C:/addressBook/data/data.csv";
const char *tempFile1 = "C:/addressBook/data/temp.csv";



void addEntry() {
    struct abEntry newEntry;
    FILE *fptr, *originalFile;
    int count = 0;
    
    char buffer[1024]; // Buffer size increased to handle larger lines

    // Open the original file in read mode to get the current count and data
    fptr = fopen(dataFile1, "r");
    if (!fptr) {
        printf("Error: Could not open %s for reading.\n", dataFile1);
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
    fptr = fopen(tempFile1, "w");
    if (!fptr) {
        printf("Error: Could not open %s for writing.\n", tempFile1);
        return;
    }

    // Write updated count to temp file
    count++;
    fprintf(fptr, "%d\n", count);

    // Reopen original file to copy old entries (skipping the count line)
    originalFile = fopen(dataFile1, "r");
    if (!originalFile) {
        printf("Error: Could not reopen %s for reading.\n", dataFile1);
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
    if (remove(dataFile1) != 0) {
        printf("Error: Could not delete original file %s.\n", dataFile1);
        return;
    }
    if (rename(tempFile1, dataFile1) != 0) {
        printf("Error: Could not rename temp file %s to %s.\n", tempFile1, dataFile1);
        return;
    }
    set_color("\e[1;32m");
    print_with_animation2("\n\t\t\t\t\t\t\t\t\t\t\t\tEntry added successfully.\n");
    reset_color();
}

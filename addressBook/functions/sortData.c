#include "addressBook.h"


const char *dataFile7 = "C:/addressBook/data/data.csv";
const char *tempFile7 = "C:/addressBook/data/temp.csv";


void sortdata() {
    FILE *file = fopen(dataFile7, "r");
    FILE *tempFile = fopen(tempFile7, "w+");
    
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
    remove(dataFile7);
    rename(tempFile7, dataFile7);
    set_color("\e[1;32m");
    print_with_animation2("\nData has been sorted and count updated.\n");
    reset_color();
}

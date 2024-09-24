#include "addressBook.h"

const char *dataFile3 = "C:/addressBook/data/data.csv";
const char *tempFile3 = "C:/addressBook/data/temp.csv";


#include<unistd.h>

void displayAllEntries() {
    FILE *file;
    char buffer[256];
    int count = 0;

     if (access(dataFile3, F_OK) != 0) {
        printf("File not found: %s\n", dataFile3);
        return;
    }

    file = fopen(dataFile3, "r");
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
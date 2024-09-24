#include "addressBook.h"

const char *dataFile = "C:/addressBook/data/data.csv";
const char *tempFile = "C:/addressBook/data/temp.csv";

void displayMenu() {
    
    // printf("\n");
    // printCyberAttackTitle("\t\t\t\t\t\t\t\t  <------------------------->",BCYN);
    // srand(time(NULL)); // Seed for random number generation
    // printCyberAttackTitle("\t\t\t\t\t\t\t\t  |        ADDRESSBOOK      |", BYEL);
    // printCyberAttackTitle("\t\t\t\t\t\t\t\t  <------------------------->",BCYN);
    // printf("\n");
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


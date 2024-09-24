#include "addressBook.h"


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
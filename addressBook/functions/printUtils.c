#include "addressBook.h"


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
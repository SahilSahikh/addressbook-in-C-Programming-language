#ifndef ADDRESSBOOK_H
#define ADDRESSBOOK_H

// Declare the file paths as extern (they will be defined in one .c file)
// const char *dataFile = "C:/addressBook/data/data.csv";
// const char *tempFile = "C:/addressBook/data/temp.csv";


#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include<unistd.h>
#include<windows.h>
#include<ctype.h>

#define BBLK "\e[1;30m"
#define BRED "\e[1;31m"
#define BGRN "\e[1;32m"
#define BYEL "\e[1;33m"
#define BBLU "\e[1;34m"
#define BMAG "\e[1;35m"
#define BCYN "\e[1;36m"
#define BWHT "\e[1;37m"
#define COLOR_RESET "\033[0m"

struct abEntry {
    char name[50];
    char address[50];
    char number[12];
    char email[30];
    time_t createdAt;
    time_t lastModified;
};


// Function declarations
void print_with_animation2(const char *text);
void set_color(const char *color);
void reset_color();
void displayMenu();
void addEntry();
void searchEntry();
void displayAllEntries();
void editEntry();
void deleteEntry();
void saveAndExit();
void sortdata();

/*-------validation---------*/
void getName(char *name);
void getAddress(char *address);
void getPhoneNumber(char *number);
void getEmail(char *email);

/*--------------------------*/
bool isDuplicate(const char* number, const char* email, FILE* fptr, bool* foundNumber, bool* foundEmail);
void printContactsBySearch(const char *searchTerm, int choice);
int compareContacts(const char *entry1, const char *entry2);

/*-------------------------------------------------*/
void printCyberAttackTitle(const char *title, const char *color);

#endif // ADDRESSBOOK_H

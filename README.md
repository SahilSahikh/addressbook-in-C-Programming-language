# Address Book Project

## Overview

This project is a command-line Address Book program written in C. It allows users to:

- **Add, Edit, and Delete contacts** with details like name, address, phone number, and email.
- **Search contacts** by name, phone number, or email.
- **Display all contacts** with sorting options.
- **Save and Exit**, ensuring that all updates are reflected in a CSV file.

The project is modular and keeps contact information in a CSV file located in the `data/` folder.

### Project Structure

```
addressBook/
├── data/
│   ├── data.csv      # Stores all contact information
│   └── temp.csv      # Temporary file for editing contacts
├── functions/        # Function implementations
├── include/          # Header files
└── main.c            # Main program logic

```

---

## Features

- **Add Entry**: Add a new contact to the CSV file.
- **Search Entry**: Search for a contact by name, number, or email.
- **Display All Entries**: View all contacts stored in the CSV.
- **Edit/Delete Entries**: Modify or remove contacts.
- **Data Persistence**: All entries are saved to the `data.csv` file for future use.

---

## Setup Instructions

### Prerequisites

- **GCC compiler** or any C compiler that supports C99.
- Make sure you have the necessary directory structure (`data/`) and CSV files (`data.csv`, `temp.csv`) in place.

### Clone the Repository

To clone this project, run:

```bash
git clone <https://github.com/SahilSahikh/addressbook-in-C-Programming-language.git>

```

### Directory Setup

Ensure the `data` folder exists with the following structure:

```
addressBook/
└── data/
    ├── data.csv
    └── temp.csv

```

You can create the `data.csv` and `temp.csv` files if they don't exist. They will be updated automatically as you add contacts.

### Compilation

To compile the project, use this command:

```bash
gcc -o addressBook main.c functions/*.c -Iinclude

```

### Running the Program

After compiling, you can run the executable as follows:

```bash
./addressBook

```

---

## Usage

Once the program is running, you can perform the following actions:

1. **Add Entry**: Choose option `1` from the menu to add a new contact.
2. **Search Entry**: Use option `2` to search for a contact by name, number, or email.
3. **Display All Entries**: View all contacts stored in the CSV by choosing option `3`.
4. **Edit Entry**: Choose option `4` to modify an existing contact.
5. **Delete Entry**: Remove an entry by selecting option `5`.
6. **Save and Exit**: Save the changes and exit the program using option `6`.

---

## Example of CSV Data Format

The contacts are saved in the following CSV format:

```
Name,Address,Phone Number,Email,Created At,Last Modified
John Doe,123 Elm St,5551234567,johndoe@example.com,1629907200,1630040400

```

---

## Contribution Guidelines

Welcome who wants to contribute!😊
---



---

## Author

This project was developed and maintained by Sahil Shaikh.

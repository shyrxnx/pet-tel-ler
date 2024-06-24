#include <iostream.h>
#include <iomanip.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <dos.h>
#include <fstream.h>


// Main
void mainMenu();
void login();
void logout();
void printTitle(char title[]);
void saveEmployeesInfo();
void loadEmployeesInfo();
void savePetInfo();
void loadPetInfo();
void saveBundlesInfo();
void loadBundlesInfo();


// Admin Menu
void adminMenu();


// Admin Employee Management
void adminEM();
void adminAddUser();
void adminUpdateUser();
void adminChangeUserStatus();
void displayUsersInfo();


// Admin Pet Records
void adminPR();


// Admin Bundle Offer Management
void adminBOM();
void viewBundles();
void createBundle();
void updateBundle();
void removeBundle();


// Admin Reports and Analytics
void adminRA();
void countPetSizes(int& countSmall, int& countMedium, int& countLarge);


// Employee Menu
void employeeMenu();


// Shared Functions
void petRegister();
void viewAllPets();
void viewDetailedInfo();
void archivePet();
void viewArchivedPets();
void detailedSearch();
void updatePetInfo();
void petSearchName();
void petSearchDate();
void petSearchOwner();
void petSearchGender();
void petSearchSize();
void petSearchBreed();
void petSearchAge();
void searchAndDisplayRecords(char info[], char data[][20]);
void generateBillingReport();


// Global Variables
int choice;
int logged;
int role; // 0 - Admin and 1 - Employee

// Struct for Admin
struct Admin {
    char username[10];
    char password[10];
};

Admin admins[5] = { {"admin", "admin"}, {"shy", "shy"} };
int countAdmin = 2;


// Struct for Employee
struct Employee {
    char fullname[50];
    char contact[20];
    char username[10];
    char password[10];
    int status; // 0 - Enabled, 1 - Deactivated
} employees[10];

int countEmployee;


// Arrays for Pet Informations
char petReservationDate[50][20]; // YYYY-MM-DD
char petOwners[50][20];
char petOwnerCellNum[50][15];
char petNames[50][20];
char petGenders[50][20];
char petAge[50][20];
char petSize[50][20];
char petBreed[50][20];
char petAllergies[50][100];
char petAllergyNotes[50][100]; //contains information and/or instruction about the pet's allergy
char petMobilityIssues[50][100];
char petMobilityIssueNotes[50][100]; //contains information and/or instruction about the pet's mobility issue
char petChronicIllness[50][100];
char petChronicIllnessNotes[50][100]; //contains information and/or instruction about the pet's chronic illness
int petBundle[50];
int stayDurations[50];
int petArchived[50]; // 0 - Active, 1 - Archived 
char paymentStatus[50][10]; // "Paid" or "Unpaid"
int countPet = 0;


// Struct for Bundle Information
struct Bundle {
    char name[50];
    int stayDuration;
    char description[300];
    int price;
} bundles[15];

int countBundles;


// ======================================================================================= SAVE AND LOAD ==============================================================================================

// Save Employees Info to File
void saveEmployeesInfo() {
    ofstream file("0emp.txt");

    file << countEmployee << "\n";

    // Write each employee's data to the file
    for (int i = 0; i < countEmployee; i++) {
    file << employees[i].username << "\n"
         << employees[i].password << "\n"
         << employees[i].fullname << "\n"
         << employees[i].contact << "\n"
         << employees[i].status << "\n";
    }

    file.close();
}


// Load Employees Info from File
void loadEmployeesInfo() {
    ifstream file("0emp.txt");

    file >> countEmployee;
    file.ignore(); // Ignore the newline character after the count

    for (int i = 0; i < countEmployee; i++) {
    file.getline(employees[i].username, 10);
    file.getline(employees[i].password, 10);
    file.getline(employees[i].fullname, 20);
    file.getline(employees[i].contact, 15);
    file >> employees[i].status;
    file.ignore(); // Ignore the newline character after the int
    }

    file.close();
}


// Save Pet Infos to File
void savePetInfo() {
    ofstream file("0pet.txt");

    file << countPet << "\n";

    // Write each pet's data to the file
    for (int i = 0; i < countPet; i++) {
        file << petReservationDate[i] << "\n"
             << petOwners[i] << "\n"
             << petOwnerCellNum[i] << "\n"
             << petNames[i] << "\n"
             << petGenders[i] << "\n"
             << petAge[i] << "\n"
             << petBreed[i] << "\n"
             << petSize[i] << "\n"
             << petAllergies[i] << "\n"
             << petAllergyNotes[i] << "\n"
             << petMobilityIssues[i] << "\n"
             << petMobilityIssueNotes[i] << "\n"
             << petChronicIllness[i] << "\n"
             << petChronicIllnessNotes[i] << "\n"
             << petBundle[i] << "\n"
             << stayDurations[i] << "\n"
             << petArchived[i] << "\n"
             << paymentStatus[i] << "\n";
    }

    file.close();
}

// Load Pets Info from File
void loadPetInfo() {
    ifstream file("0pet.txt"); // Attempt to open the file for reading

    if (file) {
        file >> countPet;
        file.ignore(); // Ignore the newline character after the count

        for (int i = 0; i < countPet; i++) {
            file.getline(petReservationDate[i], 20);
            file.getline(petOwners[i], 20);
            file.getline(petOwnerCellNum[i], 15);
            file.getline(petNames[i], 20);
            file.getline(petGenders[i], 15);
            file.getline(petAge[i], 10);
            file.getline(petBreed[i], 25);
            file.getline(petSize[i], 15);
            file.getline(petAllergies[i], 50);
            file.getline(petAllergyNotes[i], 150);
            file.getline(petMobilityIssues[i], 50);
            file.getline(petMobilityIssueNotes[i], 150);
            file.getline(petChronicIllness[i], 50);
            file.getline(petChronicIllnessNotes[i], 150);
            file >> petBundle[i];
            file >> stayDurations[i];
            file >> petArchived[i];            
            file.ignore(); // Ignore the newline character after the int
            file.getline(paymentStatus[i], 10);
        }

        file.close();
    } else {
        cout << "Unable to open pet data file for reading.\n";
    }
}


// Save Bundles Info to File
void saveBundlesInfo() {
    ofstream file("0bund.txt");

    file << countBundles << "\n";

    // Write each bundle's data to the file
    for (int i = 0; i < countBundles; i++) {
        file << bundles[i].name << "\n"
             << bundles[i].stayDuration << "\n"
             << bundles[i].description << "\n"
             << bundles[i].price << "\n";
    }

    file.close();
}


// Load Bundles Info from File
void loadBundlesInfo() {
    ifstream file("0bund.txt");

    if (!file) {
        cout << "Failed to open file for reading.\n";
        return;
    }

    file >> countBundles;
    file.ignore(); // Ignore the newline character after the count

    for (int i = 0; i < countBundles; i++) {
        file.getline(bundles[i].name, 50);
        file >> bundles[i].stayDuration;
        file.ignore(); // Ignore the newline character after the int
        file.getline(bundles[i].description, 300);
        file >> bundles[i].price;
        file.ignore(); // Ignore the newline character after the int
    }

    file.close();
}

// ======================================================================================= SAVE AND LOAD ==============================================================================================


// =========================================================================================== MAIN ===================================================================================================

// Header for Each Functions
void printTitle(char title[]) {
    clrscr();
    cout << "========================== " << title << " ==========================" << endl;
}

// Start of the Program
void main() {
    clrscr();
    loadEmployeesInfo();
    loadPetInfo();    
    loadBundlesInfo();
    
    mainMenu();
    getch();
}


// Display Main Menu
void mainMenu() {
    printTitle("PetTelLer");
    cout << "1 - Admin" << endl;
    cout << "2 - Employee" << endl;
    cout << "3 - Exit" << endl << endl;
    cout << "Enter choice: ";
    cin >> choice;

    switch (choice) {
    case 1:
        role = 0; // Set role to admin
        login();
        break;
    case 2:
        role = 1; // Set role to employee
        login();
        break;
    case 3:
        clrscr();
        savePetInfo();
        cout << "Exiting in 2 seconds..." << endl;
        delay(2000);
        exit(0);
    default:
        clrscr();
        cout << "\nWrong input!" << endl;
        cout << "Press any key to go back.";
        getch();
        mainMenu(); // Re-display the main menu on invalid input
    }
    getch();
}


// Implementation for Login
void login() {
    char n[50], p[50];
    printTitle("Login");

    if (role == 0) { // Admin login
    cout << "Username\t: ";
    gets(n);

    for (int i = 0; i < countAdmin; i++) {
        if (strcmp(n, admins[i].username) == 0) {
        cout << "Password\t: ";
        gets(p);

        if (strcmp(p, admins[i].password) == 0) {
            logged = i;

            cout << endl << "Login successful!" << endl;
            cout << "Press any key to go to the admin menu.";

            adminMenu();
            return;
        } else {
            cout << "\nIncorrect password!\n";
            getch();
            mainMenu();
            return;
        }
        }
    }
    } else if (role == 1) { // Employee login
    cout << "Username\t: ";
    gets(n);

    for (int i = 0; i < countEmployee; i++) {
        if (strcmp(n, employees[i].username) == 0) {
        cout << "Password\t: ";
        gets(p);

            if (employees[i].status != 0) {
                clrscr();
                cout << "This account has been deactivated. Please contact the administrator.";
                getch();
                mainMenu();
            }        

        if (strcmp(p, employees[i].password) == 0) {
            logged = i;

            cout << endl << "Login successful!" << endl;
            cout << "Press any key to go to the employee menu.";

            employeeMenu();
            return;
        } else {
            cout << "\nIncorrect password!\n";
            getch();
            mainMenu();
            return;
        }
        }
    }
    }

    cout << "\nUsername not found!";
    getch();
    mainMenu();
}


// Implementation for Logout
void logout() {
    clrscr();
    saveEmployeesInfo();

    cout << "Logging out in 2 seconds..." << endl;
    delay(2000);
    mainMenu();
    getch();
}


// Admin Menu Logic
void adminMenu() {
    clrscr();
    printTitle("Admin Menu");
    cout << "1 - Employee Management" << endl;
    cout << "2 - Pet Records" << endl;
    cout << "3 - Bundle Offer Management" << endl;
    cout << "4 - Reports and Analytics" << endl;
    cout << "5 - Generate Billing Report" << endl;
    cout << "6 - Logout" << endl;
    cout << "7 - Exit" << endl << endl;
    cout << "Enter choice: ";
    cin >> choice;

    switch (choice) {
    case 1:
        adminEM();
        break;
    case 2:
        adminPR();;
        break;
    case 3:
        adminBOM();
        break;
    case 4:
        adminRA();
        break;
    case 5:
        generateBillingReport();
        break;
    case 6:
        logout();
        break;
    case 7:
        clrscr();
        cout << "Exiting in 2 seconds..." << endl;
        delay(2000);
        exit(0);
    default:
        cout << "Invalid choice. Press any key to try again." << endl;
        getch();
        adminMenu(); // Re-display the admin menu on invalid input
        break;
    }

    getch();
}

// ================================================= Admin Employee Management =================================================

void adminEM() {
    printTitle("Employee Management");
    cout << "1 - Add user"
     << "\n2 - Update user"
     << "\n3 - Deactivate/Reactivate user"
     << "\n4 - Go Back" << endl
     << "\nEnter choice: ";
    cin >> choice;

    switch (choice) {
    case 1:
    adminAddUser();
    break;
    case 2:
    adminUpdateUser();
    break;
    case 3:
    adminChangeUserStatus();
    break;
    case 4:
    adminMenu();
    break;
    default:
    clrscr();
    cout << "Wrong input!" << endl;
    cout << "Press any key to go back...";
    getch();
    adminEM();
    }
}


// Add User
void adminAddUser() {
    printTitle("Add User");

    if (countEmployee >= 10) {
    clrscr();
    cout << "Cannot add more users.";
    cout << "\nPress any key to go back!";
    getch();
    adminEM();
    }

    cout << "Enter username     \t:  ";
    gets(employees[countEmployee].username);

    for (int i = 0; i < countEmployee; i++) {
        if (strcmp(employees[countEmployee].username, employees[i].username) == 0) {
            cout << "\nUsername already taken!";
            getch();
            adminEM();
        }
    }

    cout << "Enter password     \t:  ";
    gets(employees[countEmployee].password);

    cout << "Enter fullname     \t:  ";
    gets(employees[countEmployee].fullname);

    cout << "Enter contact number\t:  ";
    gets(employees[countEmployee].contact);

    employees[countEmployee].status = 0;
    countEmployee++;

    saveEmployeesInfo();

    cout << "\n\nUser added successfully.\nPress any key to return to main menu...";
    getch();
    adminEM();
}


// Update User
void adminUpdateUser() {
    int employeeIndex;

    printTitle("Update User");
    displayUsersInfo();

    cout << "\n\nEnter ID No. to update: ";
    cin >> employeeIndex;

    if (employeeIndex < 0 || employeeIndex >= countEmployee) {
    clrscr();
    cout << "Wrong input!" << endl;
    cout << "Press any key to go back...";
    getch();
    adminEM();
    }

selectUpdate:
    printTitle("Update User");
    cout << "Select detail to update:\n"
     << "\n1 - Username\n2 - Password\n3 - Fullname\n4 - Contact Number\n5 - Cancel\n"
     << "\nEnter choice: ";
    cin >> choice;

    if (choice <= 0 || choice > 5) {
    clrscr();
    cout << "\nWrong input!\nPress any key to go back...";
        getch();
        goto selectUpdate;
    }

    printTitle("Update User");
    switch (choice) {
    case 1:
    cout << "Enter new username     \t:  ";
    gets(employees[employeeIndex].username);
    break;
    case 2:
    cout << "Enter new password     \t:  ";
    gets(employees[employeeIndex].password);
    break;
    case 3:
    cout << "Enter new fullname     \t:  ";
    gets(employees[employeeIndex].fullname);
    break;
    case 4:
    cout << "Enter new contact number\t:  ";
    gets(employees[employeeIndex].contact);
    break;
    case 5:
    adminEM();
    }

    saveEmployeesInfo();

    cout << "\nUpdate successful!";
    getch();
    adminEM();
}


// Deactivate/Reactivate User
void adminChangeUserStatus() {
    printTitle("Deactivate/Reactivate User");
    displayUsersInfo();

    int employeeIndex;
    cout << "\n\nEnter ID No. to change access status: ";
    cin >> employeeIndex;

    if (employeeIndex < 0 || employeeIndex >= countEmployee) {
    clrscr();
    cout << "Wrong input!" << endl;
    cout << "Press any key to go back...";
    }
    else {
    printTitle("Deactivate/Reactivate User");
    employees[employeeIndex].status = !employees[employeeIndex].status;
    saveEmployeesInfo();
    displayUsersInfo();
    cout << "\n\n\nSuccessfully changed.\nPress any key to go back...";
    }

    getch();
    adminEM();
}

// ****** DISPLAY USERS INFO ******
void displayUsersInfo() {
    if (countEmployee <= 0) {
        clrscr();
    cout << "No registered users!\n\nPress any key to return to main menu...";
        getch();
    adminMenu();
    }

    cout << setfill(' ') << setw(6) << "ID No." << setw(20) << "Fullname" << setw(15) << "Contact" << setw(12) << "Username" << setw(12) << "Password" << setw(11) << "Access" << "\n\n";

    for (int i = 0; i < countEmployee; ++i) {
    cout << setw(6) << i << setw(20) << employees[i].fullname << setw(15) << employees[i].contact << setw(12) << employees[i].username << setw(12) << employees[i].password << setw(11) << ((employees[i].status == 0) ? "Enabled" : "Disabled") << endl;
    }
}

// ======================================================= Pet Records =======================================================

void adminPR() {
    clrscr();
    printTitle("Pet Record");
    cout << "1 - View All Pets" << endl;
    cout << "2 - Register a Pet" << endl;
    cout << "3 - Search by Field" << endl;
    cout << "4 - View Archived Pets" << endl;
    cout << "5 - Go Back" << endl << endl;
    cout << "Enter choice: ";
    cin >> choice;

    switch (choice) {
    case 1:
    viewAllPets();
    break;
    case 2:
    petRegister();
    break;
    case 3:
    detailedSearch();
    break;
    case 4:
    viewArchivedPets();
    break;
    case 5:
    if (role == 0) {
        adminMenu();
    } else if (role == 1) {
        employeeMenu();
    }
    default:
    cout << "Invalid choice. Press any key to try again." << endl;
    getch();
    adminPR();
    break;
    }
}


// View All Pets
void viewAllPets() {
    clrscr();
    printTitle("View All Pets");

    int page = 0;
    int itemPerPage = 10;
    int command;

    // Calculate the total number of active pets
    int activePetCount = 0;
    for (int i = 0; i < countPet; i++) {
        if (petArchived[i] == 0) {
            activePetCount++;
        }
    }

    do {
        clrscr();

        int totalPage = (activePetCount + itemPerPage - 1) / itemPerPage;

        cout << "Page " << page + 1 << " of " << totalPage << endl;
        cout << "===============================================================================" << endl;

        cout << setfill(' ') << setw(6) << "ID No."
             << setw(13) << "Start Date"
             << setw(14) << "Owner"
             << setw(9) << "Name"
             << setw(9) << "Size"
             << setw(18) << "Breed"
             << setw(9) << "S. Days"
             << "\n";

        int displayedItems = 0;
        for (int i = 0, displayedCount = 0; i < countPet && displayedCount < itemPerPage; i++) {
            if (petArchived[i] == 0) {
                if (displayedItems >= page * itemPerPage && displayedItems < (page + 1) * itemPerPage) {
                    cout << setw(6) << i
                         << setw(13) << petReservationDate[i]
                         << setw(14) << petOwners[i]
                         << setw(9) << petNames[i]
                         << setw(9) << petSize[i]
                         << setw(18) << petBreed[i]
                         << setw(9) << stayDurations[i]
                         << endl;
                    displayedCount++;
                }
                displayedItems++;
            }
        }

        cout << endl << "Menu:\n1 - Next\n2 - Previous\n3 - View Pet Detailed Info\n4 - Register a Pet\n5 - Update Pet Info\n6 - Archive a Pet\n7 - View Archived Pets\n8 - Go Back\n\nEnter choice: ";
        cin >> command;

        if (command == 1) {
            if ((page + 1) * itemPerPage < activePetCount) page++;
        } else if (command == 2) {
            if (page > 0) page--;
        } else if (command == 3) {
            viewDetailedInfo();
        } else if (command == 4) {
            petRegister();
        } else if (command == 5) {
            updatePetInfo();
        } else if (command == 6) {
            archivePet();
        } else if (command == 7) {
            viewArchivedPets();
        } else if (command == 8) {
            if (role == 0) {
                adminPR();
            } else {
                employeeMenu();
            }
        } else {
            cout << "Invalid input!";
            getch();
            if (role == 0) {
                adminPR();
            } else {
                employeeMenu();
            }
        }

    } while (command != 8);

    if (role == 0) {
        adminPR();
    } else {
        employeeMenu();
    }
}


// View Pet Detailed Information
void viewDetailedInfo() {
    clrscr();
    printTitle("Pet Detailed Info");

    int petId;

    cout << "Enter the ID No. of the pet to show detailed info: ";
    cin >> petId;

    if (petId >= 0 && petId < countPet) {
        clrscr();
        printTitle("Pet Detailed Info");

        cout << "ID No.                        : " << petId << endl;
        cout << "Start Date                    : " << petReservationDate[petId] << endl;
        cout << "Owner                         : " << petOwners[petId] << endl;
        cout << "Owner Contact Number          : " << petOwnerCellNum[petId] << endl;
        cout << "Pet Name                      : " << petNames[petId] << endl;
        cout << "Gender                        : " << petGenders[petId] << endl;
        cout << "Pet Age                       : " << petAge[petId] << endl;
        cout << "Pet Breed                     : " << petBreed[petId] << endl;
        cout << "Pet Size                      : " << petSize[petId] << endl;
        cout << "Allergies                     : " << petAllergies[petId] << endl;
        cout << "Allergy Instructions          : " << petAllergyNotes[petId] << endl;
        cout << "Mobility Issues               : " << petMobilityIssues[petId] << endl;
        cout << "Mobility Issue Instructions   : " << petMobilityIssueNotes[petId] << endl;
        cout << "Chronic Illness               : " << petChronicIllness[petId] << endl;
        cout << "Chronic Illness Instructions  : " << petChronicIllnessNotes[petId] << endl;
        cout << "Bundle                        : " << petBundle[petId] << endl;
        cout << "Stay Duration                 : " << stayDurations[petId] << endl;
        cout << "Archived                      : " << (petArchived[petId] ? "Yes" : "No") << endl;
        cout << "-----------------------------------------------------------------------" << endl;
    } else {
        cout << "\nInvalid Pet ID No." << endl;
    }

    cout << "\nPress any key to go back...";
    getch();

    // Return to the appropriate menu
    if (role == 0) {
        adminPR();
    } else {
        employeeMenu();
    }
}


// Register a Pet
void petRegister() {
    clrscr();

    if (countPet >= 50) {
        if (role == 0) {
            cout << "Pet registry is full. Cannot register more pets." << endl;
            cout << "\nPress any key to go back...";            
            getch();
            adminPR();
        } else {
            cout << "Pet registry is full. Cannot register more pets." << endl;
            cout << "\nPress any key to go back...";                        
            getch();
            employeeMenu();
        }
    }

    cout << "Enter Pet Reservation Date (YYYY-MM-DD): ";
    gets(petReservationDate[countPet]);

    cout << "Enter Owner's Name: ";
    gets(petOwners[countPet]);

    cout << "Enter Owner's Contact Number: ";
    gets(petOwnerCellNum[countPet]);

    cout << "Enter Pet Name: ";
    gets(petNames[countPet]);

    cout << "Enter Pet Gender: ";
    gets(petGenders[countPet]);

    cout << "Enter Pet Age: ";
    gets(petAge[countPet]);

    cout << "Enter Pet Breed: ";
    gets(petBreed[countPet]);

    cout << "Enter Pet Size: ";
    gets(petSize[countPet]);

    int answer;

    cout << "Does The Pet Require Special Attention (Allergies, Mobility Issues, and/or Chronic Illnesses)?" << endl
         << "1 - Yes" << endl
         << "2 - No" << endl
         << endl;
    cout << "Enter Choice: ";
    cin >> answer;

    if (answer == 1) {
        cout << "\nDoes your pet have allergies?" << endl
             << "1 - Yes\n2 - No" << endl;
        cout << "Enter Choice: ";
        cin >> answer;

        if (answer == 1) {
            cout << "Type of Allergy: ";
            gets(petAllergies[countPet]);

            cout << "Instructions for the Allergy: ";
            gets(petAllergyNotes[countPet]);
        }

        cout << "\nDoes your pet have mobility issues?" << endl
             << "1 - Yes\n2 - No" << endl;
        cout << "Enter Choice: ";
        cin >> answer;

        if (answer == 1) {
            cout << "What's the Mobility Issue?: ";
            gets(petMobilityIssues[countPet]);

            cout << "Instructions for the Mobility Issue: ";
            gets(petMobilityIssueNotes[countPet]);
        }

        cout << "\nDoes your pet have chronic illnesses?" << endl
             << "1 - Yes\n2 - No" << endl;
        cout << "Enter Choice: ";
        cin >> answer;

        if (answer == 1) {
            cout << "What's the Chronic Illness?: ";
            gets(petChronicIllness[countPet]);

            cout << "Instructions for the Chronic Illness: ";
            gets(petChronicIllnessNotes[countPet]);
        }
    }

    clrscr();

    printTitle("Offered Bundles");
    for (int i = 0; i < countBundles; ++i) {
        cout << "Bundle " << i << ": " << bundles[i].name << endl;
        cout << "Stay Duration: " << bundles[i].stayDuration << " days" << endl;
        cout << "Description: " << bundles[i].description << endl;
        cout << "Price: Php. " << bundles[i].price << endl;
        cout << "--------------------------------------------------------------" << endl;
    }

    cout << "Please choose a bundle: ";
    cin >> petBundle[countPet];

    // Set initial stay duration based on the chosen bundle
    stayDurations[countPet] = bundles[petBundle[countPet]].stayDuration;

    // Set initial payment status
    strcpy(paymentStatus[countPet], "Unpaid");

    countPet++;

    if (role == 0) {
        savePetInfo();        
        cout << "Pet registered successfully!" << endl;
        cout << "\nPress any key to go back...";
        getch();
        adminPR();        
    } else {
        savePetInfo();        
        cout << "Pet registered successfully!" << endl;
        cout << "\nPress any key to go back...";
        getch();
        employeeMenu();
    }

}


// Update Pet Information
void updatePetInfo() {
    int petID;
    clrscr();
    printTitle("Update Pet Information");

    cout << "Enter ID No. to update: ";
    cin >> petID;

    if (petID < 0 || petID >= countPet || petArchived[petID] != 0) {
        if (role == 0) {   
        cout << "\nInvalid or archived pet ID!" << endl;
            cout << "Press any key to go back...";
            getch();
            adminPR();        
        } else {         
            cout << "\nInvalid or archived pet ID!" << endl;
            cout << "Press any key to go back...";
            getch();
            employeeMenu(); 
        }        
    }

    printTitle("Update Pet");
    cout << "Select detail to update:" << endl;
    cout << "1 - Reservation Date" << endl;
    cout << "2 - Owner" << endl;
    cout << "3 - Owner Contact Number" << endl;
    cout << "4 - Name" << endl;
    cout << "5 - Gender" << endl;
    cout << "6 - Age" << endl;
    cout << "7 - Breed" << endl;
    cout << "8 - Size" << endl;
    cout << "9 - Allergies" << endl;
    cout << "10 - Allergy Instructions" << endl;
    cout << "11 - Mobility Issues" << endl;
    cout << "12 - Mobility Issues Instructions" << endl;
    cout << "13 - Chronic Illness" << endl;
    cout << "14 - Chronic Illness Instructions" << endl;
    cout << "15 - Bundle" << endl;
    cout << "16 - Go Back" << endl << endl;
    cout << "Enter choice: ";
    cin >> choice;

    printTitle("Update Pet");
    switch (choice)
    {
    case 1:
        cout << "Enter new reservation date (YYYY-MM-DD):  ";
        gets(petReservationDate[petID]);
        break;
    case 2:
        cout << "Enter new owner's name:  ";
        gets(petOwners[petID]);
        break;
    case 3:
        cout << "Enter new owner's contact number':  ";
        gets(petOwnerCellNum[petID]);
        break;
    case 4:
        cout << "Enter new pet name:  ";
        gets(petNames[petID]);
        break;
    case 5:
        cout << "Enter new pet gender:  ";
        gets(petGenders[petID]);
        break;
    case 6:
        cout << "Enter new pet age:  ";
        gets(petAge[petID]);
        break;
    case 7:
        cout << "Enter new pet breed: ";
        gets(petBreed[petID]);
        break;
    case 8:
        cout << "Enter new pet size: ";
        gets(petSize[petID]);
        break;
    case 9:
        cout << "Enter new pet allergies: ";
        gets(petAllergies[petID]);
        break;
    case 10:
        cout << "Enter new pet allergy instructions: ";
        gets(petAllergyNotes[petID]);
        break;
    case 11:
        cout << "Enter new pet mobility issues: ";
        gets(petMobilityIssues[petID]);
        break;
    case 12:
        cout << "Enter new pet mobility issue instructions: ";
        gets(petMobilityIssueNotes[petID]);
        break;
    case 13:
        cout << "Enter new pet chronic illness: ";
        gets(petChronicIllness[petID]);
        break;
    case 14:
        cout << "Enter new pet chronic illness instructions: ";
        gets(petChronicIllnessNotes[petID]);
        break;
    case 15:
    cout << "Enter new bundle (0 to " << countBundles - 1 << "): ";
        cin >> petBundle[petID];
    if (petBundle[petID] < 0 || petBundle[petID] >= countBundles) {
        cout << "Invalid bundle! Please enter a valid bundle index (0 to " << countBundles - 1 << ")." << endl;
            getch();
            updatePetInfo();
        }
        stayDurations[petID] = bundles[petBundle[petID]].stayDuration;
        break;
    case 16:
        viewAllPets();
        break;
    default:
            cout << "\nWrong input! Please try again.";
            getch();
            updatePetInfo(); // Call the function again to repeat the process
    }

    if (role == 0) {
    cout << "\nUpdate successful!";
    savePetInfo();
        cout << "\nPress any key to go back...";
    getch();
    adminPR();
    } else {
    cout << "\nUpdate successful!";
    savePetInfo();
        cout << "\nPress any key to go back...";
        getch();
        employeeMenu(); 
    }

}


// Archive a Pet
void archivePet() {
    clrscr();
    printTitle("Archive Pet");

    int petId;
    char confirm;

    cout << "Enter the ID No. of the pet to archive: ";
    cin >> petId;

    if (petId >= 0 && petId < countPet) {
        if (petArchived[petId] == 1) {
            cout << "\nPet ID No. " << petId << " is already archived." << endl;
            cout << "Press any key to continue...";
            getch();
        } else {
            clrscr();
            printTitle("Confirm Archive Pet");

            cout << "Are you sure you want to archive the following pet?\n";
            cout << "ID No.: " << petId << endl;
            cout << "Start Date: " << petReservationDate[petId] << endl;
            cout << "Owner: " << petOwners[petId] << endl;
            cout << "Pet Name: " << petNames[petId] << endl;
            cout << "Gender: " << petGenders[petId] << endl;
            cout << "Pet Age: " << petAge[petId] << endl;
            cout << "Pet Breed: " << petBreed[petId] << endl;
            cout << "Pet Size: " << petSize[petId] << endl;
            cout << "Allergies: " << petAllergies[petId] << endl;
            cout << "Allergy Instructions: " << petAllergyNotes[petId] << endl;
            cout << "Mobility Issues: " << petMobilityIssues[petId] << endl;
            cout << "Mobility Issue Instructions: " << petMobilityIssueNotes[petId] << endl;
            cout << "Chronic Illness: " << petChronicIllness[petId] << endl;
            cout << "Chronic Illness Instructions: " << petChronicIllnessNotes[petId] << endl;
            cout << "Bundle: " << petBundle[petId] << endl;
            cout << "Stay Duration: " << stayDurations[petId] << endl;
            cout << "-----------------------------------------------------------" << endl;

            cout << "\nEnter 'Y' to confirm archiving, 'N' to cancel: ";
            cin >> confirm;

            if (confirm == 'Y' || confirm == 'y') {
                //  Set payment status to paid
		strcpy(paymentStatus[petId], "Paid");
                petArchived[petId] = 1;
                savePetInfo();
                cout << "\nPet ID No. " << petId << " has been archived." << endl;
                getch();
            } else {
                cout << "\nArchiving cancelled." << endl;
                getch();
            }
        }
    } else {
        cout << "\nInvalid Pet ID No." << endl;
        getch();
    }

    // Return to the appropriate menu
    if (role == 0) {
        savePetInfo();
        adminPR();
    } else {
        savePetInfo();        
        employeeMenu();
    }
}


// View Archived Pets
void viewArchivedPets() {
    clrscr();
    printTitle("View All Archived Pets");

    int page = 0;
    int itemPerPage = 10;
    int command;

    // Calculate the total number of archived pets
    int totalArchivedPets = 0;
    for (int i = 0; i < countPet; i++) {
        if (petArchived[i] != 0) {
            totalArchivedPets++;
        }
    }

    do {
        clrscr();

        int totalPage = (totalArchivedPets + itemPerPage - 1) / itemPerPage;

        cout << "Page " << page + 1 << " of " << totalPage << endl;
        cout << "===============================================================================" << endl;

        int start = page * itemPerPage;
        int end = start + itemPerPage;

        if (end > totalArchivedPets) {
            end = totalArchivedPets;
        }

        cout << setfill(' ') << setw(6) << "ID No."
             << setw(13) << "Start Date"
             << setw(14) << "Owner"
             << setw(9) << "Name"
             << setw(9) << "Size"
             << setw(18) << "Breed"
             << setw(9) << "S. Days"
             << "\n";

        // Variable to count the number of archived pets displayed
        int displayedPets = 0;

        for (int i = 0; i < countPet; i++) {
            if (petArchived[i] != 0) {
                if (displayedPets >= start && displayedPets < end) {
                    cout << setw(6) << i
                         << setw(13) << petReservationDate[i]
                         << setw(14) << petOwners[i]
                         << setw(9) << petNames[i]
                         << setw(9) << petSize[i]
                         << setw(18) << petBreed[i]
                         << setw(9) << stayDurations[i]
                         << endl;
                }
                displayedPets++;
            }
        }

        cout << endl << "Menu:\n1 - Next\n2 - Previous\n3 - View Pet Detailed Info\n4 - Go Back\n\nEnter choice: ";
        cin >> command;

        if (command == 1) {
            if ((page + 1) * itemPerPage < totalArchivedPets) page++;
        } else if (command == 2) {
            if (page > 0) page--;
        } else if (command == 3) {
            viewDetailedInfo();
        } else if (command == 4) {
            if (role == 0) {
                adminPR();
            } else {
                employeeMenu();
            }     
        } else {
            cout << "Invalid input!";
            getch();
            if (role == 0) {
                adminPR();
            } else {
                employeeMenu();
            }
        }

    } while (command != 3);

    if (role == 0) {
        adminPR();
    } else {
        employeeMenu();
    }
}


// Search by field
void detailedSearch() {
    int choice;
    printTitle("Search base on field");
    cout << "1 - Search name"
         << "\n2 - Search date"
         << "\n3 - Search owner"
         << "\n4 - Search gender"
         << "\n5 - Search size"
         << "\n6 - Search breed"
         << "\n7 - Search age"
         << "\n8 - Go Back"
         << endl << endl
         << "Enter choice: ";
    cin >> choice;

    switch (choice) {
    case 1: 
        petSearchName(); 
        break;
    case 2: 
        petSearchDate(); 
        break;
    case 3: 
        petSearchOwner(); 
        break;
    case 4: 
        petSearchGender(); 
        break;
    case 5: 
        petSearchSize(); 
        break;
    case 6: 
        petSearchBreed(); 
        break;
    case 7: 
        petSearchAge(); 
        break;
    case 8:
        if (role == 0) {
            adminPR();
        } else {
            employeeMenu();
        }
    default:
        clrscr();
        cout << "\nWrong input!" << endl;
        cout << "Press any key to try again...";
        getch();
        detailedSearch();
    }
}

// ****** SEARCH NAME ******
void petSearchName() {
    printTitle("Search Name");

    char searchName[20];
    cout << "Enter pet name to search: ";
    gets(searchName);

    searchAndDisplayRecords(searchName, petNames);
}

void petSearchDate() {
    printTitle("Search Date");

    char searchDate[20];
    cout << "Enter start date to search: ";
    gets(searchDate);

    searchAndDisplayRecords(searchDate, petReservationDate);
}

// ****** SEARCH OWNER ******
void petSearchOwner() {
    printTitle("Search Owner");

    char searchOwner[20];
    cout << "Enter pet owner name to search: ";
    gets(searchOwner);

    searchAndDisplayRecords(searchOwner, petOwners);
}

// ****** SEARCH GENDER ******
void petSearchGender() {
    printTitle("Search Gender");

    char searchGender[20];
    cout << "Enter pet gender to search: ";
    gets(searchGender);

    searchAndDisplayRecords(searchGender, petGenders);
}

// ****** SEARCH SIZE ******
void petSearchSize() {
    printTitle("Search Size");

    char searchSize[20];
    cout << "Enter pet size to search: ";
    gets(searchSize);

    searchAndDisplayRecords(searchSize, petSize);
}

// ****** SEARCH BREED ******
void petSearchBreed() {
    printTitle("Search Breed");

    char searchBreed[20];
    cout << "Enter pet breed to search: ";
    gets(searchBreed);

    searchAndDisplayRecords(searchBreed, petBreed);
}

// ****** SEARCH AGE ******
void petSearchAge() {
    printTitle("Search Age");

    char searchAge[20];
    cout << "Enter pet age to search: ";
    gets(searchAge);

    searchAndDisplayRecords(searchAge, petAge);
}



// ****** SEARCH & DISPLAY RECORDS ******
void searchAndDisplayRecords(char info[], char data[][20]) {
    clrscr();
    int matchCount = 0;
    int matches[100]; // Array to store indices of matching pets

    // Store matching indices
    for (int i = 0; i < countPet; i++) {
        if (strcmpi(info, data[i]) == 0 && petArchived[i] == 0) {
            matches[matchCount++] = i;
        }
    }

    if (matchCount == 0) {
        clrscr();
        cout << "\nNo records found related to (" << info << ").";
        cout << "\nPress any key to go back...";
        getch();
        detailedSearch();
        return;
    }

    int page = 0;
    int itemPerPage = 10;
    int command;

    do {
        clrscr();
        int totalPage = (matchCount + itemPerPage - 1) / itemPerPage;

        cout << "Found " << matchCount << " matches for (" << info << ")." << endl;
        cout << "Page " << page + 1 << " of " << totalPage << endl;
        cout << "===============================================================================" << endl;

        cout << setfill(' ') << setw(6) << "ID No."
             << setw(13) << "Start Date"
             << setw(14) << "Owner"
             << setw(9) << "Name"
             << setw(9) << "Size"
             << setw(18) << "Breed"
             << setw(9) << "S. Days"
             << "\n";

        int start = page * itemPerPage;
        int end = start + itemPerPage;
        if (end > matchCount) end = matchCount;

        for (int i = start; i < end; i++) {
            int idx = matches[i];
            cout << setw(6) << idx
                 << setw(13) << petReservationDate[idx]
                 << setw(14) << petOwners[idx]
                 << setw(9) << petNames[idx]
                 << setw(9) << petSize[idx]
                 << setw(18) << petBreed[idx]
                 << setw(9) << stayDurations[idx]
                 << endl;
        }

        cout << endl << "Menu:\n1 - Next\n2 - Previous\n3 - View Detailed Information\n4 - Go Back\n\nEnter choice: ";
        cin >> command;

        if (command == 1) {
            if ((page + 1) * itemPerPage < matchCount) page++;
        } else if (command == 2) {
            if (page > 0) page--;
        } else if (command == 3) {
            viewDetailedInfo();
        } else if (command == 4) {
            detailedSearch();
            return;
        } else {
            cout << "Invalid input!";
            getch();
        }

    } while (command != 4);

    detailedSearch();
}


// ============================================ Admin Bundle Offer Management ==============================================

// Bundle Offer Management Menu
void adminBOM() {
    clrscr();
    printTitle("Bundle Offer Management");
    cout << "1 - View Bundles" << endl;
    cout << "2 - Create Bundle" << endl;
    cout << "3 - Update Bundle" << endl;
    cout << "4 - Remove Bundle" << endl;
    cout << "5 - Go Back" << endl << endl;
    cout << "Enter choice: ";
    cin >> choice;

    switch(choice) {
    case 1: viewBundles(); break;
    case 2: createBundle(); break;
    case 3: updateBundle(); break;
    case 4: removeBundle(); break;
    case 5: adminMenu(); break;
    default:
        cout << "Invalid choice. Press any key to try again." << endl;
        getch();
        adminBOM(); // Re-display the bundle management menu on invalid input
        break;
    }

    getch();
}


// View All Bundles
void viewBundles() {
    clrscr();
    printTitle("View Bundles");

    int page = 0;
    int itemPerPage = 2;
    int command;

    do {
        clrscr();

        int totalPage = (countBundles + itemPerPage - 1) / itemPerPage;

        cout << "Page " << page + 1 << " of " << totalPage << endl;
        cout << "=============================================================================" << endl;

        int start = page * itemPerPage;
        int end = start + itemPerPage;

        if (end > countBundles) {
            end = countBundles;
        }

        for (int i = start; i < end; i++) {
            cout << "Bundle " << i << "      : " << bundles[i].name << endl;
            cout << "Stay Duration : " << bundles[i].stayDuration << " days" << endl;
            cout << "Description   : " << bundles[i].description << endl;
            cout << "Price         : Php. " << bundles[i].price << endl << endl;
        }

        cout << endl << "Menu:\n1 - Next\n2 - Previous\n3 - Create Bundle\n4 - Update Bundle\n5 - Remove Bundle\n6 - Go Back\n\nEnter choice: ";
        cin >> command;

        if (command == 1) {
             if ((page + 1) * itemPerPage < countBundles) page++;
        } else if (command == 2) {
             if (page > 0) page--;
        } else if (command == 3) {
             createBundle();
        } else if (command == 4) {
            updateBundle();
        } else if (command == 5) {
            removeBundle();
        } else if (command == 6) {
            adminBOM();
        } else {
            cout << "Invalid input!";
            getch();
            adminBOM();
        }

    } while (command != 6);

    adminBOM();
}


// Create Bundle
void createBundle() {
    clrscr();
    printTitle("Create Bundle");

    if (countBundles >= 15) {
    clrscr();
    cout << "Maximum number of bundles reached. Cannot create more bundles." << endl;
    cout << "Press any key to go back.";
    getch();
    adminBOM();
    }

    cout << "Enter bundle name: ";
    cin.ignore();
    gets(bundles[countBundles].name);

    cout << "Enter stay duration (in days): ";
    cin >> bundles[countBundles].stayDuration;

    cout << "Enter description: ";
    cin.ignore();
    gets(bundles[countBundles].description);

    cout << "Enter price: ";
    cin >> bundles[countBundles].price;

    countBundles++;
    saveBundlesInfo();

    cout << "\nBundle created successfully!" << endl;
    cout << "Press any key to go back.";

    getch();
    adminBOM();
}


// Update Bundle
void updateBundle() {
    int bundleIndex;
    clrscr();
    printTitle("Update Bundles");

    for (int i = 0; i < countBundles; ++i) {
        cout << "Bundle " << i << ": " << bundles[i].name << endl;
        cout << "Stay Duration: " << bundles[i].stayDuration << " days" << endl;
        cout << "Description: " << bundles[i].description << endl;
        cout << "Price: Php. " << bundles[i].price << endl;
        cout << "-----------------------------------------" << endl;
    }
    cout << "Enter the bundle index to update: ";
    cin >> bundleIndex;

    if (bundleIndex < 0 || bundleIndex >= countBundles) {
        cout << "Invalid index. Returning to menu." << endl;
        getch();
        adminBOM();
    }

    clrscr();
    printTitle("Update Bundle");
    cout << "Editing Bundle " << bundleIndex << ": " << bundles[bundleIndex].name << endl << endl;
    cout << "1 - Modify Name" << endl;
    cout << "2 - Modify Stay Duration" << endl;
    cout << "3 - Modify Price" << endl;
    cout << "4 - Modify Description" << endl;
    cout << "5 - Go Back" << endl;
    cout << "Enter choice: ";
    cin >> choice;

    switch (choice) {
        case 1:
            cout << "Enter new bundle name: ";
            cin.ignore();
            gets(bundles[bundleIndex].name);
            cout << "Bundle name updated successfully!" << endl;
            break;
        case 2:
            cout << "Enter new stay duration (in days): ";
            cin >> bundles[bundleIndex].stayDuration;
            cout << "Stay duration updated successfully!" << endl;
            break;
        case 3:
            cout << "Enter new price: ";
            cin >> bundles[bundleIndex].price;
            cout << "Price updated successfully!" << endl;
            break;
        case 4:
            cout << "Enter new description: ";
            cin.ignore();
            gets(bundles[bundleIndex].description);
            cout << "Description updated successfully!" << endl;
            break;
        case 5:
            adminBOM();
            break;
        default:
            cout << "Invalid choice. Press any key to try again." << endl;
            getch();
            updateBundle(); // Re-display the update bundle menu on invalid input
            break;
    }

    saveBundlesInfo();

    cout << "Press any key to go back.";
    getch();
    adminBOM();
}


// Remove Bundle
void removeBundle() {
    int bundleIndex;
    clrscr();
    printTitle("Remove Bundle");
    cout << "Enter the bundle index to remove: ";
    cin >> bundleIndex;

    if (bundleIndex < 0 || bundleIndex >= countBundles) {
        cout << "Invalid index. Returning to menu." << endl;
        getch();
        adminBOM();
        return;
    }

    for (int i = bundleIndex; i < countBundles - 1; ++i) {
        strcpy(bundles[i].name, bundles[i + 1].name);
        bundles[i].stayDuration = bundles[i + 1].stayDuration;
        strcpy(bundles[i].description, bundles[i + 1].description);
        bundles[i].price = bundles[i + 1].price;
    }

    countBundles--;
    saveBundlesInfo();

    cout << "Bundle removed successfully!" << endl;
    cout << "Press any key to go back.";

    getch();
    adminBOM();
}


// ============================================== Admin Reports - Analytics and Billing ================================================

// Function to count the sizes of pets
void countPetSizes(int& countSmall, int& countMedium, int& countLarge) {
    countSmall = 0;
    countMedium = 0;
    countLarge = 0;

    for (int i = 0; i < countPet; ++i) {
        char lowercaseSize[20];
        strcpy(lowercaseSize, petSize[i]);
        strlwr(lowercaseSize); // Convert to lowercase for comparison
        if (strcmp(lowercaseSize, "small") == 0) {
            countSmall++;
        } else if (strcmp(lowercaseSize, "medium") == 0) {
            countMedium++;
        } else if (strcmp(lowercaseSize, "large") == 0) {
            countLarge++;
        }
    }
}

// Report and Analytics
void adminRA() {
    int countArchivedPets = 0;
    int countSmallPets, countMediumPets, countLargePets;
    countPetSizes(countSmallPets, countMediumPets, countLargePets);

    // Calculate the number of archived pets
    for (int i = 0; i < countPet; ++i) {
        if (petArchived[i] != 0) {
            countArchivedPets++;
        }
    }

    printTitle("Report and Analytics");
    cout << "1. Total Number of Pets    : " << countPet << endl;
    cout << "2. Number of Active Pets   : " << (countPet - countArchivedPets) << endl;
    cout << "3. Number of Archived Pets : " << countArchivedPets << endl;
    cout << "4. Pet Size Distribution:" << endl;
    cout << "   - Small                 : " << countSmallPets << endl;
    cout << "   - Medium                : " << countMediumPets << endl;
    cout << "   - Large                 : " << countLargePets << endl;
    cout << "5. Bundle Utilization:" << endl;
    for (int x = 0; x < countBundles; x++) {
    int countPetsInBundle = 0;
    for (int j = 0; j < countPet; j++) {
        if (petBundle[j] == x) {
        countPetsInBundle++;
        }
    }
    cout << "   - Bundle " << x << "              : " << countPetsInBundle << endl;
    }

    cout << "\n\nMenu:\n1 - Go Back\n\nEnter choice: ";
    int choice;
    cin >> choice;

    if (choice == 1) {
        adminMenu();
    } else {
        cout << "Invalid choice. Going back to admin menu." << endl;
        adminMenu();
    }
}


// Billing Report
void generateBillingReport() {
    clrscr();

    const int itemsPerPage = 10;
    int page = 0;
    int totalPages = (countPet + itemsPerPage - 1) / itemsPerPage;

    do {
        clrscr();
        printTitle("Generate Billing Report");
        cout << "Billing Report - Page " << page + 1 << "/" << totalPages << endl;
        cout << "-------------------------------------------------------------------------------" << endl;
        cout << setw(5) << "ID" << setw(15) << "Pet Name" << setw(18) << "Owner" << setw(15) << "O. CellNum" << setw(15) << "Total Amount" << setw(11) << "Status" << endl;
        cout << "-------------------------------------------------------------------------------" << endl;

        // Calculate the start and end indices for pets on the current page
        int start = page * itemsPerPage;
        int end = start + itemsPerPage;
        if (end > countPet) {
            end = countPet;
        }

        // Iterate over pets on the current page
        for (int i = start; i < end; ++i) {
            // Get the bundle index for the pet
            int bundleIndex = petBundle[i];
            int amount = bundles[bundleIndex].price;

            // Display pet details and total amount
            cout << setw(5) << i << setw(15) << petNames[i] << setw(18) << petOwners[i] << setw(15) << petOwnerCellNum[i] << setw(15) << amount << setw(11) << paymentStatus[i] << endl;
        }

        cout << "-------------------------------------------------------------------------------" << endl;
        cout << "\n\nMenu:\n1 - Next\n2 - Previous\n3 - Mark as Paid\n4 - Go Back\n\nEnter choice: ";
        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                if (page < totalPages - 1) page++;
                break;
            case 2:
                if (page > 0) page--;
                break;
            case 3:
                cout << "Enter Pet ID No. to mark as paid: ";
                int petID;
                cin >> petID;
                if (petID >= 0 && petID < countPet) {
                    strcpy(paymentStatus[petID], "Paid");
                    savePetInfo();
                    cout << "Marked as paid successfully!";
                    getch();
                } else {
                    cout << "Invalid Pet ID No.";
                    getch();
                }
                break;
            case 4:
                if (role == 0) {
                    adminMenu();
                } else {
                    employeeMenu();
                }
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 4);
}


// ====================================================================================================================================================================================================

// Note: All the functions available to the employee are also available to the admin. These have already been implemented above.
// Employee Menu
void employeeMenu() {
    clrscr();
    printTitle("Employee Menu");
    cout << "1 - Register a Pet" << endl;
    cout << "2 - View All Pets" << endl;
    cout << "3 - Search by Field" << endl;
    cout << "4 - Update Pet Information" << endl;
    cout << "5 - Generate Billing Report" << endl;
    cout << "6 - Logout" << endl;
    cout << "7 - Exit" << endl << endl;
    cout << "Enter choice: ";
    cin >> choice;

    switch (choice) {
    case 1:
        petRegister();
        break;
    case 2:
        viewAllPets();
        break;
    case 3:
        detailedSearch();
        break;
    case 4:
        updatePetInfo();
    break;
    case 5:
        generateBillingReport();
        break;
    case 6:
    logout();
    break;
    case 7:
    clrscr();
    cout << "Exiting in 2 seconds..." << endl;
    delay(2000);
    exit(0);
    default:
    cout << "Invalid choice. Press any key to try again." << endl;
    getch();
    employeeMenu();
    break;
    }

    getch();
}
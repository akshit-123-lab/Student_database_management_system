// Student Database Management System

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STUDENTS 100
#define MAX_NAME_LENGTH 50
#define MAX_ID_LENGTH 20
#define MAX_DEPT_LENGTH 30
#define MAX_ADDRESS_LENGTH 100
#define FILENAME "student_database.dat"


typedef struct {
    char id[MAX_ID_LENGTH];
    char name[MAX_NAME_LENGTH];
    char department[MAX_DEPT_LENGTH];
    char address[MAX_ADDRESS_LENGTH];
    float gpa;
    int age;
} Student;


Student students[MAX_STUDENTS];
int studentCount = 0;
int isModified = 0;


void displayMenu();
void addStudent();
void searchStudent();
void modifyStudent();
void deleteStudent();
void displayAllStudents();
void saveToFile();
void loadFromFile();
void clearInputBuffer();
int validateID(char *id);
int findStudentByID(char *id);

int main() {
    int choice;
    
    
    loadFromFile();
    
    do {
        displayMenu();
        printf("Enter your choice (1-7): ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();
        
        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                searchStudent();
                break;
            case 3:
                modifyStudent();
                break;
            case 4:
                deleteStudent();
                break;
            case 5:
                displayAllStudents();
                break;
            case 6:
                saveToFile();
                break;
            case 7:
                printf("Saving changes before exit...\n");
                if (isModified) {
                    saveToFile();
                }
                printf("Thank you for using Student Database Management System!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
        
        if (choice != 7) {
            printf("\nPress Enter to continue...");
            getchar();
        }
        
    } while (choice != 7);
    
    return 0;
}

void displayMenu() {
    system("cls || clear"); 
    printf("\n========== STUDENT DATABASE MANAGEMENT SYSTEM ==========\n");
    printf("\n1. Add Student");
    printf("\n2. Search Student");
    printf("\n3. Modify Student");
    printf("\n4. Delete Student");
    printf("\n5. Display All Students");
    printf("\n6. Save Data to File");
    printf("\n7. Exit");
    printf("\n\n========================================================\n");
}

void addStudent() {
    Student newStudent;
    
    if (studentCount >= MAX_STUDENTS) {
        printf("Database is full! Cannot add more students.\n");
        return;
    }
    
    printf("\n========== ADD STUDENT ==========\n");
    
    
    do {
        printf("Enter Student ID: ");
        fgets(newStudent.id, MAX_ID_LENGTH, stdin);
        newStudent.id[strcspn(newStudent.id, "\n")] = '\0'; 
        
        if (!validateID(newStudent.id)) {
            printf("Invalid ID format. Use only letters and numbers.\n");
            continue;
        }
        
        if (findStudentByID(newStudent.id) != -1) {
            printf("Student ID already exists. Please use a unique ID.\n");
            continue;
        }
        
        break;
    } while (1);
    
    
    printf("Enter Name: ");
    fgets(newStudent.name, MAX_NAME_LENGTH, stdin);
    newStudent.name[strcspn(newStudent.name, "\n")] = '\0'; 
    
    printf("Enter Age: ");
    scanf("%d", &newStudent.age);
    clearInputBuffer();
    
    printf("Enter Department: ");
    fgets(newStudent.department, MAX_DEPT_LENGTH, stdin);
    newStudent.department[strcspn(newStudent.department, "\n")] = '\0'; 
    
    printf("Enter GPA: ");
    scanf("%f", &newStudent.gpa);
    clearInputBuffer();
    
    printf("Enter Address: ");
    fgets(newStudent.address, MAX_ADDRESS_LENGTH, stdin);
    newStudent.address[strcspn(newStudent.address, "\n")] = '\0'; 
    
    
    students[studentCount] = newStudent;
    studentCount++;
    isModified = 1;
    
    printf("\nStudent added successfully!\n");
}

void searchStudent() {
    char searchID[MAX_ID_LENGTH];
    int found = 0;
    int index;
    
    printf("\n========== SEARCH STUDENT ==========\n");
    printf("Enter Student ID to search: ");
    fgets(searchID, MAX_ID_LENGTH, stdin);
    searchID[strcspn(searchID, "\n")] = '\0'; 
    
    index = findStudentByID(searchID);
    
    if (index != -1) {
        printf("\nStudent Found!\n");
        printf("ID: %s\n", students[index].id);
        printf("Name: %s\n", students[index].name);
        printf("Age: %d\n", students[index].age);
        printf("Department: %s\n", students[index].department);
        printf("GPA: %.2f\n", students[index].gpa);
        printf("Address: %s\n", students[index].address);
    } else {
        printf("\nStudent with ID '%s' not found.\n", searchID);
    }
}

void modifyStudent() {
    char modifyID[MAX_ID_LENGTH];
    int index;
    int choice;
    
    printf("\n========== MODIFY STUDENT ==========\n");
    printf("Enter Student ID to modify: ");
    fgets(modifyID, MAX_ID_LENGTH, stdin);
    modifyID[strcspn(modifyID, "\n")] = '\0'; 
    
    index = findStudentByID(modifyID);
    
    if (index == -1) {
        printf("\nStudent with ID '%s' not found.\n", modifyID);
        return;
    }
    
    printf("\nStudent Found! Current details:\n");
    printf("1. Name: %s\n", students[index].name);
    printf("2. Age: %d\n", students[index].age);
    printf("3. Department: %s\n", students[index].department);
    printf("4. GPA: %.2f\n", students[index].gpa);
    printf("5. Address: %s\n", students[index].address);
    printf("6. Modify all fields\n");
    printf("7. Cancel modification\n");
    
    printf("\nEnter your choice (1-7): ");
    scanf("%d", &choice);
    clearInputBuffer();
    
    switch (choice) {
        case 1:
            printf("Enter new Name: ");
            fgets(students[index].name, MAX_NAME_LENGTH, stdin);
            students[index].name[strcspn(students[index].name, "\n")] = '\0';
            break;
        case 2:
            printf("Enter new Age: ");
            scanf("%d", &students[index].age);
            clearInputBuffer();
            break;
        case 3:
            printf("Enter new Department: ");
            fgets(students[index].department, MAX_DEPT_LENGTH, stdin);
            students[index].department[strcspn(students[index].department, "\n")] = '\0';
            break;
        case 4:
            printf("Enter new GPA: ");
            scanf("%f", &students[index].gpa);
            clearInputBuffer();
            break;
        case 5:
            printf("Enter new Address: ");
            fgets(students[index].address, MAX_ADDRESS_LENGTH, stdin);
            students[index].address[strcspn(students[index].address, "\n")] = '\0';
            break;
        case 6:
            printf("Enter new Name: ");
            fgets(students[index].name, MAX_NAME_LENGTH, stdin);
            students[index].name[strcspn(students[index].name, "\n")] = '\0';
            
            printf("Enter new Age: ");
            scanf("%d", &students[index].age);
            clearInputBuffer();
            
            printf("Enter new Department: ");
            fgets(students[index].department, MAX_DEPT_LENGTH, stdin);
            students[index].department[strcspn(students[index].department, "\n")] = '\0';
            
            printf("Enter new GPA: ");
            scanf("%f", &students[index].gpa);
            clearInputBuffer();
            
            printf("Enter new Address: ");
            fgets(students[index].address, MAX_ADDRESS_LENGTH, stdin);
            students[index].address[strcspn(students[index].address, "\n")] = '\0';
            break;
        case 7:
            printf("Modification cancelled.\n");
            return;
        default:
            printf("Invalid choice.\n");
            return;
    }
    
    isModified = 1;
    printf("\nStudent information updated successfully!\n");
}

void deleteStudent() {
    char deleteID[MAX_ID_LENGTH];
    int index;
    char confirm;
    
    printf("\n========== DELETE STUDENT ==========\n");
    printf("Enter Student ID to delete: ");
    fgets(deleteID, MAX_ID_LENGTH, stdin);
    deleteID[strcspn(deleteID, "\n")] = '\0'; 
    
    index = findStudentByID(deleteID);
    
    if (index == -1) {
        printf("\nStudent with ID '%s' not found.\n", deleteID);
        return;
    }
    
    printf("\nStudent Found! Details:\n");
    printf("ID: %s\n", students[index].id);
    printf("Name: %s\n", students[index].name);
    printf("Department: %s\n", students[index].department);
    
    printf("\nAre you sure you want to delete this student? (y/n): ");
    scanf("%c", &confirm);
    clearInputBuffer();
    
    if (tolower(confirm) == 'y') {
        
        for (int i = index; i < studentCount - 1; i++) {
            students[i] = students[i + 1];
        }
        studentCount--;
        isModified = 1;
        printf("\nStudent deleted successfully!\n");
    } else {
        printf("\nDeletion cancelled.\n");
    }
}

void displayAllStudents() {
    if (studentCount == 0) {
        printf("\nNo students in the database.\n");
        return;
    }
    
    printf("\n======================= ALL STUDENTS =======================\n");
    printf("%-10s %-20s %-5s %-15s %-5s\n", "ID", "Name", "Age", "Department", "GPA");
    printf("-----------------------------------------------------------\n");
    
    for (int i = 0; i < studentCount; i++) {
        printf("%-10s %-20s %-5d %-15s %.2f\n",
               students[i].id,
               students[i].name,
               students[i].age,
               students[i].department,
               students[i].gpa);
    }
    
    printf("\nTotal Students: %d\n", studentCount);
}

void saveToFile() {
    FILE *file = fopen(FILENAME, "wb");
    
    if (file == NULL) {
        printf("\nError opening file for writing.\n");
        return;
    }
    
    
    fwrite(&studentCount, sizeof(int), 1, file);
    
    
    fwrite(students, sizeof(Student), studentCount, file);
    
    fclose(file);
    isModified = 0;
    
    printf("\nData saved to file successfully!\n");
}

void loadFromFile() {
    FILE *file = fopen(FILENAME, "rb");
    
    if (file == NULL) {
        printf("\nNo existing database file found. Starting with an empty database.\n");
        return;
    }
    
    
    fread(&studentCount, sizeof(int), 1, file);
    
    
    fread(students, sizeof(Student), studentCount, file);
    
    fclose(file);
    
    printf("\nData loaded from file successfully!\n");
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int validateID(char *id) {
    
    for (int i = 0; id[i] != '\0'; i++) {
        if (!isalnum(id[i])) {
            return 0;
        }
    }
    return 1;
}

int findStudentByID(char *id) {
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].id, id) == 0) {
            return i;
        }
    }
    return -1; 
}
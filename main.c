#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

typedef enum {
    ENROLLED,
    GRADUATED,
    DROPPED_OUT
} studentStatus;

typedef struct {
    char studentID[15];
    char studentName[20];
    float GPA;
    studentStatus status;
} student;

int main() {
    int userChoice = 0;
    bool loop_q = true;
    student *database = NULL;

    while (loop_q) {
        printf("\n--- Student mini-DBMS ---\n");
        printf("1 = Add students\n");
        printf("2 = View all students\n");
        printf("3 = Update student\n");
        printf("4 = Delete student\n");
        printf("5 = Exit\n");
        printf("Enter option selection: ");
        
        if (scanf("%d", &userChoice) != 1) {
            printf("Invalid input. Exiting...\n");
            break;
        }

        // 1. ADD STUDENTS
        if (userChoice == 1) {
            int capacity = 0;
            printf("Number of students to add: ");
            scanf("%d", &capacity);

            free(database); // Clean up previous allocation
            database = malloc(capacity * sizeof(student));
            if (database == NULL) {
                printf("Failed to allocate memory!\n");
                return 1;
            }

            FILE *studentData = fopen("students.csv", "a");
            if (studentData == NULL) {
                printf("Error opening file!\n");
                free(database);
                return 1;
            }

            for (int counter = 0; counter < capacity; counter++) {
                printf("\nStudent %d\n", counter + 1);
                printf("Enter ID: ");
                scanf(" %14s", database[counter].studentID);
                printf("Enter Name: ");
                scanf(" %19s", database[counter].studentName);
                printf("Enter GPA: ");
                scanf(" %f", &database[counter].GPA);
                printf("Enter Status (0: Enrolled, 1: Graduated, 2: Dropped): ");
                scanf(" %d", (int *)&database[counter].status);

                fprintf(studentData, "%s,%s,%.2f,%d\n", 
                        database[counter].studentID, 
                        database[counter].studentName, 
                        database[counter].GPA, 
                        database[counter].status);
            }

            fclose(studentData);
            printf("All students saved successfully!\n");

        // 2. VIEW STUDENTS
        } else if (userChoice == 2) {
            int capacity = 0;
            int counterTwo = 0;

            printf("Number of students to print: ");
            scanf("%d", &capacity);

            free(database);
            database = malloc(capacity * sizeof(student));
            if (database == NULL) {
                printf("Failed to allocate memory!\n");
                continue;
            }

            FILE *studentData = fopen("students.csv", "r");
            if (studentData == NULL) {
                printf("No database file found or error opening file!\n");
                continue;
            }

            while (counterTwo < capacity && 
                   fscanf(studentData, " %14[^,],%19[^,],%f,%d", 
                          database[counterTwo].studentID, 
                          database[counterTwo].studentName, 
                          &database[counterTwo].GPA, 
                          (int *)&database[counterTwo].status) == 4) {

                printf("--------------------------------\n");
                printf("Student ID:   %s\n", database[counterTwo].studentID);
                printf("Student Name: %s\n", database[counterTwo].studentName);
                printf("GPA:          %.2f\n", database[counterTwo].GPA);

                switch (database[counterTwo].status) {
                    case ENROLLED:    printf("Status: Enrolled\n"); break;
                    case GRADUATED:   printf("Status: Graduated\n"); break;
                    case DROPPED_OUT: printf("Status: Dropped Out\n"); break;
                    default:          printf("Status: Unknown\n"); break;
                }
                counterTwo++;
            }
            fclose(studentData);

        // 3. UPDATE STUDENT
        } else if (userChoice == 3) {
            char studentChangeID[15] = "";
            char fieldName[15] = "";
            int numberOfFieldsChange = 0;
            int numberOfStudents = 10;
            int counterThree = 0;
            int targetIndex = -1;

            free(database);
            database = malloc(numberOfStudents * sizeof(student));
            if (database == NULL) return 1;

            printf("Enter student ID to make changes to: ");
            scanf(" %14s", studentChangeID);

            FILE *studentData = fopen("students.csv", "r");
            if (studentData == NULL) {
                printf("Error opening file!\n");
                continue;
            }

            while (fscanf(studentData, " %14[^,],%19[^,],%f,%d", 
                          database[counterThree].studentID, 
                          database[counterThree].studentName, 
                          &database[counterThree].GPA, 
                          (int *)&database[counterThree].status) == 4) {

                counterThree++;

                if (counterThree == numberOfStudents) {
                    numberOfStudents *= 2;
                    student *temp = realloc(database, numberOfStudents * sizeof(student));
                    if (temp == NULL) {
                        printf("Realloc failed!\n");
                        fclose(studentData);
                        break;
                    }
                    database = temp;
                }
            }
            fclose(studentData);

            for (int counterFour = 0; counterFour < counterThree; counterFour++) {
                if (strcmp(studentChangeID, database[counterFour].studentID) == 0) {
                    targetIndex = counterFour;
                    break;
                }
            }

            if (targetIndex != -1) {
                printf("How many fields would you like to change: ");
                scanf("%d", &numberOfFieldsChange);

                for (int counterFive = 0; counterFive < numberOfFieldsChange; counterFive++) {
                    printf("Enter field name (studentid, studentname, gpa, status): ");
                    scanf(" %14s", fieldName);

                    if (strcmp(fieldName, "studentid") == 0) {
                        printf("Change ID to: ");
                        scanf(" %14s", database[targetIndex].studentID);
                    } else if (strcmp(fieldName, "studentname") == 0) {
                        printf("Change Name to: ");
                        scanf(" %19s", database[targetIndex].studentName);
                    } else if (strcmp(fieldName, "gpa") == 0) {
                        printf("Change GPA to: ");
                        scanf("%f", &database[targetIndex].GPA);
                    } else if (strcmp(fieldName, "status") == 0) {
                        printf("Change status (0: Enrolled, 1: Graduated, 2: Dropped): ");
                        scanf("%d", (int *)&database[targetIndex].status);
                    }
                }

                FILE *updatedData = fopen("students.csv", "w");
                if (updatedData != NULL) {
                    for (int i = 0; i < counterThree; i++) {
                        fprintf(updatedData, "%s,%s,%.2f,%d\n", 
                                database[i].studentID, 
                                database[i].studentName, 
                                database[i].GPA, 
                                database[i].status);
                    }
                    fclose(updatedData);
                    printf("Student Data Updated Successfully!\n");
                }
            } else {
                printf("Student ID not found.\n");
            }

        // 4. DELETE STUDENT
        } else if (userChoice == 4) {
            char removeID[15] = "";
            char confirmDelete = '\0';
            int numberOfStudents = 10;
            int counterThree = 0;
            int targetIndex = -1;

            printf("Enter ID to remove: ");
            scanf(" %14s", removeID);

            free(database);
            database = malloc(numberOfStudents * sizeof(student));
            if (database == NULL) return 1;

            FILE *studentData = fopen("students.csv", "r");
            if (studentData == NULL) {
                printf("Error opening file!\n");
                continue;
            }

            while (fscanf(studentData, " %14[^,],%19[^,],%f,%d", 
                          database[counterThree].studentID, 
                          database[counterThree].studentName, 
                          &database[counterThree].GPA, 
                          (int *)&database[counterThree].status) == 4) {

                counterThree++;

                if (counterThree == numberOfStudents) {
                    numberOfStudents *= 2;
                    student *temp = realloc(database, numberOfStudents * sizeof(student));
                    if (temp == NULL) {
                        printf("Realloc failed!\n");
                        fclose(studentData);
                        break;
                    }
                    database = temp;
                }
            }
            fclose(studentData);

            for (int counterFour = 0; counterFour < counterThree; counterFour++) {
                if (strcmp(removeID, database[counterFour].studentID) == 0) {
                    targetIndex = counterFour;
                    break;
                }
            }

            if (targetIndex != -1) {
                printf("Delete student %s (%s)? (y/n): ", 
                       database[targetIndex].studentName, database[targetIndex].studentID);
                scanf(" %c", &confirmDelete);

                if (tolower(confirmDelete) == 'y') {
                    FILE *updatedData = fopen("students.csv", "w");
                    if (updatedData != NULL) {
                        for (int i = 0; i < counterThree; i++) {
                            if (i == targetIndex) continue; // Skip writing deleted item
                            fprintf(updatedData, "%s,%s,%.2f,%d\n", 
                                    database[i].studentID, 
                                    database[i].studentName, 
                                    database[i].GPA, 
                                    database[i].status);
                        }
                        fclose(updatedData);
                        printf("Student removed successfully!\n");
                    }
                } else {
                    printf("Deletion cancelled.\n");
                }
            } else {
                printf("Student ID not found.\n");
            }

        // 5. EXIT
        } else if (userChoice == 5) {
            loop_q = false;
        } else {
            printf("Invalid selection!\n");
        }
    }
    free(database);
    return 0;
}

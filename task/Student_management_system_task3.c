#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int id;
    char name[50];
    float marks;
};

void addStudent() {
    struct Student s;
    FILE *fp = fopen("students.dat", "ab");
    if(!fp) { printf("Error opening file!\n"); return; }

    printf("Enter ID: "); scanf("%d", &s.id);
    printf("Enter Name: "); scanf(" %[^\n]s", s.name);
    printf("Enter Marks: "); scanf("%f", &s.marks);

    fwrite(&s, sizeof(s), 1, fp);
    fclose(fp);
    printf("Student added successfully!\n");
}

void displayStudents() {
    struct Student s;
    FILE *fp = fopen("students.dat", "rb");
    if(!fp) { printf("No records found.\n"); return; }

    printf("\nID\tName\tMarks\n");
    while(fread(&s, sizeof(s), 1, fp)) {
        printf("%d\t%s\t%.2f\n", s.id, s.name, s.marks);
    }
    fclose(fp);
}

void searchStudent() {
    int id;
    struct Student s;
    FILE *fp = fopen("students.dat", "rb");
    if(!fp) { printf("No records found.\n"); return; }

    printf("Enter ID to search: "); scanf("%d", &id);
    int found = 0;

    while(fread(&s, sizeof(s), 1, fp)) {
        if(s.id == id) {
            printf("ID: %d\nName: %s\nMarks: %.2f\n", s.id, s.name, s.marks);
            found = 1;
            break;
        }
    }
    if(!found) printf("Student not found.\n");
    fclose(fp);
}

void updateStudent() {
    int id;
    struct Student s;
    FILE *fp = fopen("students.dat", "rb+");
    if(!fp) { printf("No records found.\n"); return; }

    printf("Enter ID to update: "); scanf("%d", &id);
    int found = 0;

    while(fread(&s, sizeof(s), 1, fp)) {
        if(s.id == id) {
            printf("Enter new Name: "); scanf(" %[^\n]s", s.name);
            printf("Enter new Marks: "); scanf("%f", &s.marks);
            fseek(fp, -sizeof(s), SEEK_CUR);
            fwrite(&s, sizeof(s), 1, fp);
            found = 1;
            printf("Student updated successfully!\n");
            break;
        }
    }
    if(!found) printf("Student not found.\n");
    fclose(fp);
}

void deleteStudent() {
    int id;
    struct Student s;
    FILE *fp = fopen("students.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");
    if(!fp || !temp) { printf("Error opening file!\n"); return; }

    printf("Enter ID to delete: "); scanf("%d", &id);
    int found = 0;

    while(fread(&s, sizeof(s), 1, fp)) {
        if(s.id != id) {
            fwrite(&s, sizeof(s), 1, temp);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if(found) printf("Student deleted successfully!\n");
    else printf("Student not found.\n");
}

int main() {
    int choice;

    do {
        printf("\n--- Student Management System ---\n");
        printf("1. Add Student\n2. Display Students\n3. Search Student\n4. Update Student\n5. Delete Student\n6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: printf("Exiting...\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while(choice != 6);

    return 0;
}

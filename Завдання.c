#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_STUDENTS 1000000000
#define MAX_LINE_LEN 256

typedef struct {
    char lastName[50];
    char firstName[50];
    int grade;
    int classroom;
    int bus;
    char teacherLastName[50];
    char teacherFirstName[50];
} Student;

Student students[MAX_STUDENTS];
int studentCount = 0;

// Функція для завантаження студентів з файлу
void loadStudents(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Could not open file");
        exit(EXIT_FAILURE);
    }

    char line[MAX_LINE_LEN];
    while (fgets(line, sizeof(line), file)) {
        Student s;
        sscanf(line, "%[^,], %[^,], %d, %d, %d, %[^,], %[^\n]",
               s.lastName, s.firstName, &s.grade, &s.classroom, &s.bus, s.teacherLastName, s.teacherFirstName);
        students[studentCount++] = s;
    }

    fclose(file);
}

// Пошук за прізвищем студента (клас і викладач)
void searchStudentByLastName(const char *lastName) {
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].lastName, lastName) == 0) {
            printf("%s %s is in grade %d, class %d. Teacher: %s %s\n",
                   students[i].firstName, students[i].lastName, students[i].grade, students[i].classroom,
                   students[i].teacherFirstName, students[i].teacherLastName);
        }
    }
}

// Пошук за прізвищем студента (автобус)
void searchStudentBusByLastName(const char *lastName) {
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].lastName, lastName) == 0) {
            printf("%s %s rides bus number %d\n", students[i].firstName, students[i].lastName, students[i].bus);
        }
    }
}

// Пошук за прізвищем викладача
void searchStudentsByTeacher(const char *teacherLastName) {
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].teacherLastName, teacherLastName) == 0) {
            printf("Student: %s %s\n", students[i].firstName, students[i].lastName);
        }
    }
}

// Пошук за номером класу
void searchStudentsByClassroom(int classroom) {
    for (int i = 0; i < studentCount; i++) {
        if (students[i].classroom == classroom) {
            printf("Student: %s %s\n", students[i].firstName, students[i].lastName);
        }
    }
}

// Пошук за номером автобусу
void searchStudentsByBus(int busNumber) {
    for (int i = 0; i < studentCount; i++) {
        if (students[i].bus == busNumber) {
            printf("Student: %s %s, Grade: %d, Classroom: %d\n",
                   students[i].firstName, students[i].lastName, students[i].grade, students[i].classroom);
        }
    }
}

// Головна функція
int main() {
    loadStudents("students.txt");

    char command[50];
    while (1) {
        printf("Enter a command (S[tudent], T[eacher], C[lassroom], B[us], Q[uit]): ");
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = 0;  // Видалення нової лінії

        clock_t start_time = clock();  // Початок вимірювання часу

        if (strncmp(command, "S ", 2) == 0) {
            char lastName[50];
            sscanf(command + 2, "%s", lastName);
            searchStudentByLastName(lastName);
        } else if (strncmp(command, "S", 1) == 0 && strstr(command, " B") != NULL) {
            char lastName[50];
            sscanf(command + 2, "%s", lastName);
            searchStudentBusByLastName(lastName);
        } else if (strncmp(command, "T ", 2) == 0) {
            char teacherLastName[50];
            sscanf(command + 2, "%s", teacherLastName);
            searchStudentsByTeacher(teacherLastName);
        } else if (strncmp(command, "C ", 2) == 0) {
            int classroom;
            sscanf(command + 2, "%d", &classroom);
            searchStudentsByClassroom(classroom);
        } else if (strncmp(command, "B ", 2) == 0) {
            int busNumber;
            sscanf(command + 2, "%d", &busNumber);
            searchStudentsByBus(busNumber);
        } else if (strcmp(command, "Q") == 0) {
            break;
        } else {
            printf("Unknown command. Please try again.\n");
        }

        clock_t end_time = clock();  // Кінець вимірювання часу
        double search_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
        printf("Search completed in %.4f seconds\n", search_time);
    }

    return 0;
}

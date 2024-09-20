#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_STUDENTS 1000000
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
        perror("Не вдалося відкрити файл");
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

// Пошук студентів за прізвищем
void searchStudentByLastName(const char *lastName, int busNumber) {
    int found = 0; // Змінна для перевірки, чи були знайдені студенти
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].lastName, lastName) == 0) {
            if (busNumber == -1 || students[i].bus == busNumber) { // Якщо busNumber == -1, ігноруємо перевірку
                printf("%s %s в класі %d, групі %d. Викладач: %s %s, Автобус: %d\n",
                       students[i].firstName, students[i].lastName, students[i].grade, students[i].classroom,
                       students[i].teacherFirstName, students[i].teacherLastName, students[i].bus);
                found = 1; // Встановлюємо прапорець, якщо студент знайдено
            }
        }
    }
    if (!found) {
        printf("Студента з прізвищем %s не знайдено.\n", lastName);
    }
}

// Пошук студентів за прізвищем викладача
void searchStudentsByTeacherLastName(const char *teacherLastName) {
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].teacherLastName, teacherLastName) == 0) {
            printf("%s %s в класі %d, групі %d. Викладач: %s %s, Автобус: %d\n",
                   students[i].firstName, students[i].lastName, students[i].grade, students[i].classroom,
                   students[i].teacherFirstName, students[i].teacherLastName, students[i].bus);
        }
    }
}

// Пошук студентів за номером автобуса
void searchStudentsByBus(int busNumber) {
    for (int i = 0; i < studentCount; i++) {
        if (students[i].bus == busNumber) {
            printf("%s %s в класі %d, групі %d. Викладач: %s %s, Автобус: %d\n",
                   students[i].firstName, students[i].lastName, students[i].grade, students[i].classroom,
                   students[i].teacherFirstName, students[i].teacherLastName, students[i].bus);
        }
    }
}

// Пошук студентів за класом
void searchStudentsByClassroom(int classroom) {
    int found = 0; // Змінна для перевірки, чи були знайдені студенти
    for (int i = 0; i < studentCount; i++) {
        if (students[i].classroom == classroom) {
            printf("%s %s в класі %d, групі %d. Викладач: %s %s, Автобус: %d\n",
                   students[i].firstName, students[i].lastName, students[i].grade, students[i].classroom,
                   students[i].teacherFirstName, students[i].teacherLastName, students[i].bus);
            found = 1; // Встановлюємо прапорець, якщо студент знайдено
        }
    }
    if (!found) {
        printf("Немає студентів у класі %d.\n", classroom); // Повідомлення, якщо студенти не знайдені
    }
}

// Функція для виводу меню
void displayMenu() {
    printf("1. Знайти студента за прізвищем\n");
    printf("2. Знайти маршрут автобуса за прізвищем студента\n");
    printf("3. Знайти студентів за прізвищем викладача\n");
    printf("4. Знайти студентів за номером автобусного маршруту\n");
    printf("5. Знайти студентів за номером класу\n");
    printf("0. Вийти\n");
    printf("Оберіть опцію: ");
}

// Головна функція
int main() {
    loadStudents("students.txt");

    int option;
    char lastName[50];
    int busNumber;
    int classroom; // Змінна для класу

    while (1) {
        displayMenu();
        scanf("%d", &option);

        switch (option) {
            case 1:
                printf("Введіть прізвище студента: ");
                scanf("%s", lastName);

                // Запит на пошук за номером автобуса
                printf("Чи хочите ви знайти студента за номером автобуса? (yes/no): ");
                char response[4];
                scanf("%s", response);

                // Пошук за прізвищем
                if (strcmp(response, "yes") == 0) {
                    printf("Введіть номер автобуса: ");
                    scanf("%d", &busNumber);
                    searchStudentByLastName(lastName, busNumber); // Пошук за прізвищем та номером автобуса
                } else {
                    searchStudentByLastName(lastName, -1); // Пошук лише за прізвищем
                }
                break;

            case 2:
                printf("Введіть прізвище студента: ");
                scanf("%s", lastName);
                searchStudentByLastName(lastName, -1);
                break;

            case 3:
                printf("Введіть прізвище викладача: ");
                scanf("%s", lastName);
                searchStudentsByTeacherLastName(lastName);
                break;

            case 4:
                printf("Введіть номер автобусу: ");
                scanf("%d", &busNumber);
                searchStudentsByBus(busNumber);
                break;

            case 5:
                printf("Введіть номер класу: ");
                scanf("%d", &classroom);
                searchStudentsByClassroom(classroom);
                break;

            case 0:
                printf("Вихід...\n");
                return 0;

            default:
                printf("Невірна опція. Спробуйте ще раз.\n");
                break;
        }
    }

    return 0;
}

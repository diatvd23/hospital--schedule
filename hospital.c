/*
    СИСТЕМА ЗА УПРАВЛЕНИЕ НА СМЕНИ В БОЛНИЦА

    КАК СЕ СТАРТИРА ПРОГРАМАТА:

    1. Компилиране:
       make hospital
       или
       gcc hospital.c -o hospital

    2. Стартиране:
       ./hospital

    ВАЖНО:
    - Всеки път, когато въвеждате лекар или сестра,
      програмата трябва да бъде стартирана отново.
    - За да въведете лекар или сестра, просто напишете
      doctor или nurse и цифра от 1 до 15 в терминала.
    - Данните не се запазват след изход от програмата.
*/

#include <stdio.h>
#include <string.h>

// Брой дни в януари
#define DAYS 31
// Брой лекари
#define DOCTORS 15
// Брой сестри
#define NURSES 15

// Масив с имената на дните от седмицата
const char *weekDays[] = {
    "Понеделник",
    "Вторник",
    "Сряда",
    "Четвъртък",
    "Петък",
    "Събота",
    "Неделя"
};

// Структура, която описва един служител
typedef struct {
    char role[10];      // Роля: "doctor" или "nurse"
    int id;             // Номер на служителя (1–15)
    int schedule[DAYS]; // Масив с графика за 31 дни
                        // 0 = почивка
                        // 1 = първа смяна
                        // 2 = втора смяна
                        // 3 = нощна смяна
} Employee;

// ====================== НОВ ГЕНЕРАТОР НА СМЕНИ ======================
// Генерира реален график: по 5 лекари/сестри на смяна на ден
void generateSchedule(Employee *employees, int totalEmployees)
{
    int shiftOrder[] = {1, 2, 3}; // 1=първа, 2=втора, 3=нощна

    for (int day = 0; day < DAYS; day++)
    {
        for (int i = 0; i < totalEmployees; i++)
        {
            // Разпределяме служителите на 3 групи по 5
            int shiftIndex = (i + day) % 3;
            employees[i].schedule[day] = shiftOrder[shiftIndex];
        }
    }
}

// Функция, която показва графика на един служител
void printSchedule(Employee e) {
    printf("\nГрафик за %s %d – Януари 2026\n", e.role, e.id);
    printf("-----------------------------------------------------\n");

    int startDayIndex = 3; // 1 януари 2026 е четвъртък

    for (int day = 0; day < DAYS; day++) {
        int weekIndex = (startDayIndex + day) % 7;
        printf("%2d януари (%s): ", day + 1, weekDays[weekIndex]);

        if (e.schedule[day] == 1)
            printf("Първа смяна (06:00–14:00)\n");
        else if (e.schedule[day] == 2)
            printf("Втора смяна (14:00–22:00)\n");
        else if (e.schedule[day] == 3)
            printf("Нощна смяна (22:00–06:00)\n");
        else
            printf("Почивка\n");
    }
}

// ====================== MAIN ======================
int main(void)
{
    printf("====================================\n");
    printf(" СИСТЕМА ЗА УПРАВЛЕНИЕ НА СМЕНИ В БОЛНИЦА\n");
    printf("====================================\n\n");

    printf("ВАЖНА ИНФОРМАЦИЯ:\n");
    printf("- Всеки път, когато въвеждате лекар или сестра,\n");
    printf("  ТРЯБВА да стартирате програмата отново.\n");
    printf("- Данните не се запазват след изход от програмата.\n\n");

    printf("Програмата стартира успешно.\n\n");

    // Масив с всички лекари и сестри
    Employee doctors[DOCTORS];
    Employee nurses[NURSES];

    // Инициализация на лекарите
    for (int i = 0; i < DOCTORS; i++) {
        strcpy(doctors[i].role, "doctor");
        doctors[i].id = i + 1;
    }

    // Инициализация на сестрите
    for (int i = 0; i < NURSES; i++) {
        strcpy(nurses[i].role, "nurse");
        nurses[i].id = i + 1;
    }

    // Генерираме график за всички едновременно
    generateSchedule(doctors, DOCTORS);
    generateSchedule(nurses, NURSES);

    // Вход от потребителя
    char role[10];
    int id;
    printf("Въведи служител (doctor/nurse) и номер (1-15): ");
    scanf("%s %d", role, &id);

    // Проверка за лекар
    if (strcmp(role, "doctor") == 0 && id >= 1 && id <= DOCTORS)
        printSchedule(doctors[id - 1]);
    // Проверка за сестра
    else if (strcmp(role, "nurse") == 0 && id >= 1 && id <= NURSES)
        printSchedule(nurses[id - 1]);
    else
        printf("Невалиден служител!\n");

    return 0;
}


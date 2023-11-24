
#include "Hospital.h"

void Hospital::displayMenu() {
    cout << "Виберіть опцію:\n";
    cout << "1. Ввести дані про палати та лікарів\n";
    cout << "2. Вивести інформацію про всі палати та створити текстовий звіт\n";
    cout << "3. Вивести загальну кількість вільних ліжок у всіх палатах\n";
    cout << "4. Вивести лікарів із вільними ліжками\n";
    cout << "0. Вийти з програми\n";
}



void Hospital::enterWardData() {
    cout << "Введіть кількість палат (не більше " << maxWardCount << "): ";

    while (!(cin >> wardCount) || wardCount > maxWardCount || wardCount <= 0) {
        cerr << "Некоректна кількість палат. Будь ласка, введіть правильні дані.\n";

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    for (int i = 0; i < wardCount; ++i) {
        int totalBeds, availableBeds;
        string doctorLastName;

        cout << "Введіть дані для палати " << i + 1 << ":\n";
        cout << "Загальна кількість ліжок: ";
        while (!(cin >> totalBeds) || totalBeds <= 0) {
            cerr << "Некоректна кількість ліжок. Будь ласка, введіть правильні дані.\n";

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cout << "Прізвище лікаря: ";
        cin >> doctorLastName;

        cout << "Кількість вільних ліжок: ";
        while (!(cin >> availableBeds) || availableBeds < 0 || availableBeds > totalBeds) {
            cerr << "Некоректна кількість вільних ліжок. Будь ласка, введіть правильні дані.\n";

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        wards[i] = Ward(totalBeds, doctorLastName, availableBeds);
    }
}



void Hospital::displayInfoAndCreateReport() {
    ofstream reportFile("report.txt");
    if (!reportFile.is_open()) {
        cerr << "Не вдалося відкрити файл для запису звіту.\n";
        return;
    }

    for (int i = 0; i < wardCount; ++i) {
        wards[i].displayInfo();
        reportFile << "Лікар: " << wards[i].getDoctorLastName() << "\n";
        reportFile << "Загальна кількість ліжок: " << wards[i].getTotalBeds() << "\n";
        reportFile << "Доступні ліжка: " << wards[i].getAvailableBeds() << "\n\n";
    }

    int totalAvailableBeds = 0;
    for (int i = 0; i < wardCount; ++i) {
        totalAvailableBeds += wards[i].getAvailableBeds();
    }

    cout << "Загальна кількість вільних ліжок у всіх палатах: " << totalAvailableBeds << "\n";
    reportFile << "Загальна кількість вільних ліжок у всіх палатах: " << totalAvailableBeds << "\n";

    char choice;
    cout << "Бажаєте переглянути лікарів із вільними ліжками? (Y/N): ";
    cin >> choice;

    if (choice == 'Y' || choice == 'y') {
        cout << "Лікарі у палатах з вільними ліжками:\n";
        reportFile << "Лікарі у палатах з вільними ліжками:\n";
        for (int i = 0; i < wardCount; ++i) {
            if (wards[i].getAvailableBeds() > 0) {
                cout << wards[i].getDoctorLastName() << "\n";
                reportFile << wards[i].getDoctorLastName() << "\n";
            }
        }
    }

    reportFile.close();
}

void Hospital::displayTotalAvailableBeds() {
    int totalAvailableBeds = 0;
    for (int i = 0; i < wardCount; ++i) {
        totalAvailableBeds += wards[i].getAvailableBeds();
    }

    cout << "Загальна кількість вільних ліжок у всіх палатах: " << totalAvailableBeds << "\n";
}

void Hospital::displayDoctorsWithAvailableBeds() {
    cout << "Лікарі у палатах з вільними ліжками:\n";
    for (int i = 0; i < wardCount; ++i) {
        if (wards[i].getAvailableBeds() > 0) {
            cout << wards[i].getDoctorLastName() << "\n";
        }
    }
}

void Hospital::run() {
    int choice;
    do {
        displayMenu();
        cout << "Ваш вибір: ";
        cin >> choice;

        switch (choice) {
        case 1:
            enterWardData();
            break;
        case 2:
            displayInfoAndCreateReport();
            break;
        case 3:
            displayTotalAvailableBeds();
            break;
        case 4:
            displayDoctorsWithAvailableBeds();
            break;
        case 0:
            cout << "Дякуємо за використання програми. Програма завершується.\n";
            break;
        default:
            cout << "Некоректний вибір. Спробуйте ще раз.\n";
        }
    } while (choice != 0);
}
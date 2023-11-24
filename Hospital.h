#pragma once
#pragma once
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Ward {
public:
    Ward() = default;
    Ward(int totalBeds, const string& doctorLastName, int availableBeds)
        : totalBeds_(totalBeds), doctorLastName_(doctorLastName), availableBeds_(availableBeds) {}

    string getDoctorLastName() const {
        return doctorLastName_;
    }

    int getTotalBeds() const {
        return totalBeds_;
    }

    int getAvailableBeds() const {
        return availableBeds_;
    }

    void displayInfo() const {
        cout << "Лікар: " << doctorLastName_ << "\n";
        cout << "Загальна кількість ліжок: " << totalBeds_ << "\n";
        cout << "Доступні ліжка: " << availableBeds_ << "\n";
    }

private:
    int totalBeds_;
    string doctorLastName_;
    int availableBeds_;
};

class Hospital {
public:
    void displayMenu();
    void enterWardData();
    void displayInfoAndCreateReport();
    void displayTotalAvailableBeds();
    void displayDoctorsWithAvailableBeds();
    void run();

private:
    static const int maxWardCount = 10;
    Ward wards[maxWardCount];
    int wardCount = 0;
};

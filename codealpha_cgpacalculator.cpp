#include <iostream>
#include <vector>
#include <string>
#include <iomanip> // for std::setprecision

// Struct to hold subject details
struct Subject {
    std::string title;
    double points;
    int units;
};

int main() {
    int subjectCount;
    double totalWeightedPoints = 0;
    int totalUnits = 0;

    std::cout << "How many subjects have you taken? ";
    std::cin >> subjectCount;

    std::vector<Subject> semester(subjectCount);

    // Input subject data
    for (int i = 0; i < subjectCount; ++i) {
        std::cout << "\nEnter information for subject " << i + 1 << ":\n";
        std::cout << "Title: ";
        std::cin.ignore(); // Clear newline before getline
        std::getline(std::cin, semester[i].title);

        std::cout << "Grade Points (0.0 - 4.0 scale): ";
        std::cin >> semester[i].points;

        std::cout << "Credit Units: ";
        std::cin >> semester[i].units;

        totalWeightedPoints += semester[i].points * semester[i].units;
        totalUnits += semester[i].units;
    }

    // CGPA Calculation
    double cumulativeGPA = (totalUnits == 0) ? 0.0 : totalWeightedPoints / totalUnits;

    // Display Report
    std::cout << "\n========== Academic Summary ==========\n";
    std::cout << std::left << std::setw(25) << "Subject"
              << std::setw(10) << "Points"
              << "Units\n";

    for (const auto& subj : semester) {
        std::cout << std::left << std::setw(25) << subj.title
                  << std::setw(10) << subj.points
                  << subj.units << '\n';
    }

    std::cout << "\nTotal Units: " << totalUnits;
    std::cout << "\nTotal Grade Points: " << totalWeightedPoints;
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "\nCumulative GPA: " << cumulativeGPA << '\n';

    return 0;
}

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

// Student class
class Student {
public:
    Student() : id(0), age(0), averageScore(0.0) {}
    Student(const std::string& name, int id, int age, double averageScore)
        : name(name), id(id), age(age), averageScore(averageScore) {}

    std::string getName() const { return name; }
    int getID() const { return id; }
    int getAge() const { return age; }
    double getAverageScore() const { return averageScore; }

private:
    std::string name;
    int id;
    int age;
    double averageScore;
};

// Global data structures
std::vector<Student> students;
std::unordered_map<std::string, Student> studentMap;

// Search functions
bool linearSearch(const std::vector<Student>& students, const std::string& name, Student& result) {
    for (const Student& student : students) {
        if (student.getName() == name) {
            result = student;
            return true;
        }
    }
    return false;
}

bool binarySearch(const std::vector<Student>& students, const std::string& name, Student& result) {
    int left = 0, right = students.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (students[mid].getName() == name) {
            result = students[mid];
            return true;
        } else if (students[mid].getName() < name) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return false;
}

// Sorting function
void quickSort(std::vector<Student>& students, int left, int right) {
    if (left >= right) return;

    int pivotIndex = left + (right - left) / 2;
    std::string pivotName = students[pivotIndex].getName();

    int i = left, j = right;
    while (i <= j) {
        while (students[i].getName() < pivotName) i++;
        while (students[j].getName() > pivotName) j--;
        if (i <= j) {
            std::swap(students[i], students[j]);
            i++;
            j--;
        }
    }

    quickSort(students, left, j);
    quickSort(students, i, right);
}

// Data management functions
void addStudent(const Student& student) {
    students.push_back(student);
    studentMap[student.getName()] = student;
}

void removeStudent(const std::string& name) {
    auto it = studentMap.find(name);
    if (it != studentMap.end()) {
        auto& student = it->second;
        students.erase(std::remove_if(students.begin(), students.end(), [&](const Student& s) { return s.getName() == student.getName(); }), students.end());
        studentMap.erase(it);
    }
}

void displayStudents() {
    for (const Student& student : students) {
        std::cout << "Name: " << student.getName() << ", ID: " << student.getID()
                  << ", Age: " << student.getAge() << ", Average Score: " << student.getAverageScore() << std::endl;
    }
}

// Main function
int main() {
    // Add some initial students
    addStudent(Student("Alice", 1, 20, 85.6));
    addStudent(Student("Bob", 2, 21, 92.3));
    addStudent(Student("Charlie", 3, 19, 78.1));

    int choice;
    do {
        std::cout << "Student Management System\n";
        std::cout << "1. Add Student\n";
        std::cout << "2. Remove Student\n";
        std::cout << "3. Display Students\n";
        std::cout << "4. Search Student (Linear)\n";
        std::cout << "5. Search Student (Binary)\n";
        std::cout << "6. Sort Students\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::string name;
                int id, age;
                double averageScore;
                std::cout << "Enter name: ";
                std::cin >> name;
                std::cout << "Enter ID: ";
                std::cin >> id;
                std::cout << "Enter age: ";
                std::cin >> age;
                std::cout << "Enter average score: ";
                std::cin >> averageScore;
                addStudent(Student(name, id, age, averageScore));
                break;
            }
            case 2: {
                std::string name;
                std::cout << "Enter name: ";
                std::cin >> name;
                removeStudent(name);
                break;
            }
            case 3:
                displayStudents();
                break;
            case 4: {
                std::string name;
                std::cout << "Enter name: ";
                std::cin >> name;
                Student result;
                if (linearSearch(students, name, result)) {
                    std::cout << "Found student: " << result.getName() << ", ID: " << result.getID()
                              << ", Age: " << result.getAge() << ", Average Score: " << result.getAverageScore() << std::endl;
                } else {
                    std::cout << "Student not found." << std::endl;
                }
                break;
            }
            case 5: {
                std::string name;
                std::cout << "Enter name: ";
                std::cin >> name;
                Student result;
                if (binarySearch(students, name, result)) {
                    std::cout << "Found student: " << result.getName() << ", ID: " << result.getID()
                              << ", Age: " << result.getAge() << ", Average Score: " << result.getAverageScore() << std::endl;
                } else {
                    std::cout << "Student not found." << std::endl;
                }
                break;
            }
            case 6:
                quickSort(students, 0, students.size() - 1);
                std::cout << "Students sorted by name." << std::endl;
                break;
            case 0:
                std::cout << "Exiting..." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Try again." << std::endl;
                break;
        }
    } while (choice != 0);

    return 0;
}
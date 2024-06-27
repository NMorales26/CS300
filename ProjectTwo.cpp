
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

using namespace std;

class Course {
public:
    string courseId;
    string title;
    vector<string> prerequisites;

    Course(string id, string name) {
        courseId = id;
        title = name;
    }

    void addPrerequisite(string prerequisite) {
        prerequisites.push_back(prerequisite);
    }
};

map<string, Course> loadCourses(string filename) {
    map<string, Course> courses;
    ifstream file(filename);
    string line;

    if (file.is_open()) {
        while (getline(file, line)) {
            istringstream ss(line);
            string id, name, prereq;
            getline(ss, id, ',');
            getline(ss, name, ',');
            Course course(id, name);
            while (getline(ss, prereq, ',')) {
                course.addPrerequisite(prereq);
            }
            courses[id] = course;
        }
        file.close();
    } else {
        cout << "Unable to open file" << endl;
    }

    return courses;
}

void printAllCourses(map<string, Course>& courses) {
    for (const auto& pair : courses) {
        cout << pair.second.courseId << ": " << pair.second.title << endl;
    }
}

void printCourseDetails(map<string, Course>& courses, string courseId) {
    if (courses.find(courseId) != courses.end()) {
        Course course = courses[courseId];
        cout << course.courseId << ": " << course.title << endl;
        cout << "Prerequisites: ";
        for (const string& prereq : course.prerequisites) {
            cout << prereq << " ";
        }
        cout << endl;
    } else {
        cout << "Course not found!" << endl;
    }
}

void displayMenu() {
    cout << "1. Load Courses" << endl;
    cout << "2. Print Course List" << endl;
    cout << "3. Print Course Details" << endl;
    cout << "9. Exit" << endl;
}

int main() {
    map<string, Course> courses;
    string filename;
    int choice;
    string courseId;

    do {
        displayMenu();
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter file name: ";
            cin >> filename;
            courses = loadCourses(filename);
            cout << "Courses loaded successfully!" << endl;
            break;
        case 2:
            printAllCourses(courses);
            break;
        case 3:
            cout << "Enter course ID: ";
            cin >> courseId;
            printCourseDetails(courses, courseId);
            break;
        case 9:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 9);

    return 0;
}

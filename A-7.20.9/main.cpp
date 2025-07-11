#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

struct Student {
    string firstName;
    string lastName;
    int quizScores[10];
    char grade;
};


char calculateGrade(const int scores[], int size) {
    int total = 0;
    for (int i = 0; i < size; ++i)
        total += scores[i];

    if (total >= 90) return 'A';
    else if (total >= 80) return 'B';
    else if (total >= 70) return 'C';
    else if (total >= 60) return 'D';
    else return 'F';
}


void printStudent(const Student& s) {
    cout << s.firstName << " " << s.lastName << " | Scores: ";
    for (int i = 0; i < 10; ++i)
        cout << s.quizScores[i] << " ";
    cout << "| Grade: " << s.grade << endl;
}

int main() {
    vector<Student> students;
    Student temp;


    while (cin >> temp.firstName >> temp.lastName) {
        for (int i = 0; i < 10; ++i) {
            cin >> temp.quizScores[i];
        }
        temp.grade = calculateGrade(temp.quizScores, 10);
        students.push_back(temp);
    }

    
    char grades[] = {'A', 'B', 'C', 'D', 'F'};
    for (char g : grades) {
        cout << "\nStudents with grade " << g << ":\n";
        for (const auto& s : students) {
            if (s.grade == g)
                printStudent(s);
        }
    }

    return 0;
}
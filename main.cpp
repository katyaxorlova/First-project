#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <random>

using namespace std;

// Function to calculate the median of a vector of integers
double calculateMedian(vector<int> values) {
    size_t size = values.size();
    sort(values.begin(), values.end());
    if (size % 2 == 0) {
        return (values[size / 2 - 1] + values[size / 2]) / 2.0;
    } else {
        return values[size / 2];
    }
}

int main() {
    vector<string> names;
    vector<vector<int>> homeworks;
    vector<int> exams;

    // Seed for random number generation
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> score_distribution(0, 10);

    while (true) {
        string first_name, last_name;
        cout << "Enter student's first name (or type 'stop' to quit): ";
        cin >> first_name;

        if (first_name == "stop") {
            break;
        }

        cout << "Enter student's last name: ";
        cin >> last_name;

        names.push_back(last_name + ", " + first_name);

        vector<int> homework_scores;
        int exam_score;

        cout << "Do you want to generate random homework scores? (y/n): ";
        char generate_homework;
        cin >> generate_homework;

        if (generate_homework == 'y' || generate_homework == 'Y') {
            for (size_t i = 0; i < names.size(); ++i) {
                homework_scores.push_back(score_distribution(gen));
            }
        } else {
            cout << "Enter " << first_name << " " << last_name << "'s homework scores (separated by spaces): ";
            int score;
            while (cin >> score) {
                if (score < 0 || score > 10) {
                    cout << "Homework score must be between 0 and 10. Try again: ";
                    continue;
                }
                homework_scores.push_back(score);
                if (homework_scores.size() == names.size()) {
                    break;
                }
            }
        }

        cin.clear(); // Clear error flags
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer

        cout << "Do you want to generate a random exam score? (y/n): ";
        char generate_exam;
        cin >> generate_exam;

        if (generate_exam == 'y' || generate_exam == 'Y') {
            exam_score = score_distribution(gen);
        } else {
            while (true) {
                cout << "Enter " << first_name << " " << last_name << "'s exam score (between 0 and 10): ";
                cin >> exam_score;
                if (exam_score >= 0 && exam_score <= 10) {
                    break;
                } else {
                    cout << "Exam score must be between 0 and 10. Try again." << endl;
                }
            }
        }

        homeworks.push_back(homework_scores);
        exams.push_back(exam_score);

        cin.clear(); // Clear error flags
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
    }

    cout << setw(20) << left << "Surname, First name" << setw(15) << "Final average" << setw(15) << "Final median" << endl;

    for (size_t i = 0; i < names.size(); ++i) {
        double homework_average = 0.0;
        for (size_t j = 0; j < homeworks[i].size(); ++j) {
            homework_average += homeworks[i][j];
        }
        homework_average /= homeworks[i].size();

        double final_score = 0.4 * homework_average + 0.6 * exams[i];
        double median = calculateMedian(homeworks[i]);

        cout << setw(20) << left << names[i] << setw(15) << fixed << setprecision(2) << final_score << setw(15) << median << endl;
    }

    return 0;
}

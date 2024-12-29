#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
using namespace std;

class Admission {
public:
    // Add student record to the file
    bool add(int sno, string name, int age, string branch, string session, int aadhar, string fatherName, string motherName, string city, int pincode) {
        ofstream file("Student.txt");
        if (!file.is_open()) {
            cout << "Error: Unable to open the file.\n";
            return false;
        }
        file << sno << " , " << name << " , " << age << " , " << branch << " , " << session << " , " << aadhar << " , " << fatherName << " , " << motherName << " , " << city << " , " << pincode << endl;
        file.close();
        cout << "Student record added successfully.\n";
        return true;
    }

    // Search for a student record by keyword
    void searchName(string keyword) {
        ifstream file("Student.txt");
        if (!file.is_open()) {
            cout << "Error: Unable to open the file.\n";
            return;
        }

        string line;
        bool found = false;
        while (getline(file, line)) {
            if (line.find(keyword) != string::npos) {
                cout << "Found: " << line << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "No record found matching the keyword \"" << keyword << "\".\n";
        }
        file.close();
    }

    // Edit a specific record by line number
    bool editData(int lineNumber, int sno, string name, int age, string branch, string session, int aadhar, string fatherName, string motherName, string city, int pincode) {
        vector<string> lines;
        if (!readFile(lines)) {
            return false;
        }

        if (lineNumber <= 0 || lineNumber > lines.size()) {
            cout << "Error: Invalid line number.\n";
            return false;
        }

        lines[lineNumber - 1] = to_string(sno) + " , " + name + " , " + to_string(age) + " , " + branch + " , " + session + " , " + to_string(aadhar) + " , " + fatherName + " , " + motherName + " , " + city + " , " + to_string(pincode);

        if (writeFile(lines)) {
            cout << "Record updated successfully.\n";
            return true;
        }
        return false;
    }

    // Delete a specific record by line number
    bool deleteRecord(int lineNumber) {
        vector<string> lines;
        if (!readFile(lines)) {
            return false;
        }

        if (lineNumber <= 0 || lineNumber > lines.size()) {
            cout << "Error: Invalid line number.\n";
            return false;
        }

        lines.erase(lines.begin() + lineNumber - 1);

        if (writeFile(lines)) {
            cout << "Record deleted successfully.\n";
            return true;
        }
        return false;
    }

    // Display all records
    void display() {
        ifstream file("Student.txt");
        if (!file.is_open()) {
            cout << "Error: Unable to open the file.\n";
            return;
        }

        cout << "Student Records:\n";
        cout << "----------------\n";
        string line;
        while (getline(file, line)) {
            cout << line << endl;
        }
        cout << "----------------\n";
        file.close();
    }

private:
    // Helper function to read all lines from the file
    bool readFile(vector<string>& lines) {
        ifstream file("Student.txt");
        if (!file.is_open()) {
            cout << "Error: Unable to open the file.\n";
            return false;
        }

        string line;
        while (getline(file, line)) {
            lines.push_back(line);
        }
        file.close();
        return true;
    }

    // Helper function to write all lines back to the file
    bool writeFile(const vector<string>& lines) {
        ofstream file("Student.txt");  // Default truncation mode
        if (!file.is_open()) {
            cout << "Error: Unable to open the file.\n";
            return false;
        }

        for (const string& line : lines) {
            file << line << endl;
        }
        file.close();
        return true;
    }
};

int main() {
    Admission admission;
    int choice;

    cout << "WELCOME TO ADMISSION MANAGEMENT SYSTEM\n";

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Add New Student\n";
        cout << "2. Edit Student Data\n";
        cout << "3. Search Student Data\n";
        cout << "4. Display All Records\n";
        cout << "5. Delete Student Data\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int sno, age, aadhar, pincode;
                string name, branch, session, fatherName, motherName, city;

                cout << "Enter S.No: ";
                cin >> sno;
                cout << "Enter Name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter Age: ";
                cin >> age;
                cout << "Enter Branch: ";
                cin.ignore();
                getline(cin, branch);
                cout << "Enter Session: ";
                getline(cin, session);
                cout << "Enter Aadhar: ";
                cin >> aadhar;
                cout << "Enter Father's Name: ";
                cin.ignore();
                getline(cin, fatherName);
                cout << "Enter Mother's Name: ";
                getline(cin, motherName);
                cout << "Enter City: ";
                getline(cin, city);
                cout << "Enter Pincode: ";
                cin >> pincode;

                admission.add(sno, name, age, branch, session, aadhar, fatherName, motherName, city, pincode);
                break;
            }
            case 2: {
                int lineNumber, sno, age, aadhar, pincode;
                string name, branch, session, fatherName, motherName, city;

                cout << "Enter Line Number to Edit: ";
                cin >> lineNumber;
                cout << "Enter New S.No: ";
                cin >> sno;
                cout << "Enter New Name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter New Age: ";
                cin >> age;
                cout << "Enter New Branch: ";
                cin.ignore();
                getline(cin, branch);
                cout << "Enter New Session: ";
                getline(cin, session);
                cout << "Enter New Aadhar: ";
                cin >> aadhar;
                cout << "Enter New Father's Name: ";
                cin.ignore();
                getline(cin, fatherName);
                cout << "Enter New Mother's Name: ";
                getline(cin, motherName);
                cout << "Enter New City: ";
                getline(cin, city);
                cout << "Enter New Pincode: ";
                cin >> pincode;

                admission.editData(lineNumber, sno, name, age, branch, session, aadhar, fatherName, motherName, city, pincode);
                break;
            }
            case 3: {
                string keyword;
                cout << "Enter Keyword to Search: ";
                cin.ignore();
                getline(cin, keyword);
                admission.searchName(keyword);
                break;
            }
            case 4: {
                admission.display();
                break;
            }
            case 5: {
                int lineNumber;
                cout << "Enter Line Number to Delete: ";
                cin >> lineNumber;
                admission.deleteRecord(lineNumber);
                break;
            }
            case 0:
                cout << "Exiting the system. Goodbye!\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}

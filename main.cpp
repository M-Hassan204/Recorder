#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct record {
private:
    int id;
    string name;
    double value;
    int age;

public:
    void addRecord(int i, const string& n, double v, int a) {
        id = i;
        name = n;
        value = v;
        age = a;
    }

    // setters
    void setId(int i) { id = i; }
    void setName(const string& n) { name = n; }
    void setValue(double v) { value = v; }
    void setAge(int a) { age = a; }

    // getters
    int getId() const { return id; }
    const string& getName() const { return name; }
    double getValue() const { return value; }
    int getAge() const { return age; }

    void display() const {
        cout << "ID: " << id << ", Name: " << name
             << ", Value: " << value << ", Age: " << age << endl;
    }

    // حفظ السجل في الملف
    void saveToFile(ofstream& out) const {
        out << id << "," << name << "," << value << "," << age << endl;
    }

    // تحميل السجل من سطر نصي
    static record fromString(const string& line) {
        record r;
        size_t p1 = line.find(',');
        size_t p2 = line.find(',', p1 + 1);
        size_t p3 = line.find(',', p2 + 1);

        r.id = stoi(line.substr(0, p1));
        r.name = line.substr(p1 + 1, p2 - p1 - 1);
        r.value = stod(line.substr(p2 + 1, p3 - p2 - 1));
        r.age = stoi(line.substr(p3 + 1));
        return r;
    }
};

int main() {
    vector<record> records;
    string filename = "records.txt";

    // تحميل البيانات من الملف عند بدء التشغيل
    ifstream fin(filename);
    if (fin) {
        string line;
        while (getline(fin, line)) {
            if (!line.empty())
                records.push_back(record::fromString(line));
        }
        fin.close();
        cout << " Data loaded from file.\n";
    }

    int choice;
    do {
        cout << "\n============================\n";
        cout << "       MAIN MENU\n";
        cout << "============================\n";
        cout << "1. Add Record\n";
        cout << "2. Edit Record\n";
        cout << "3. View All Records\n";
        cout << "4. Delete Record\n";
        cout << "5. Save to File\n";
        cout << "0. Exit\n";
        cout << "============================\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cout << endl;

        if (choice == 1) {
            int id, age;
            string name;
            double value;
            cout << "Enter ID: ";
            cin >> id;
            cout << "Enter Name: ";
            cin >> name;
            cout << "Enter Value: ";
            cin >> value;
            cout << "Enter Age: ";
            cin >> age;

            record r;
            r.addRecord(id, name, value, age);
            records.push_back(r);
            cout << " Record added!\n";
        }

        else if (choice == 2) {
            int id;
            cout << "Enter ID to edit: ";
            cin >> id;
            bool found = false;
            for (auto& r : records) {
                if (r.getId() == id) {
                    found = true;
                    cout << "\nWhat do you want to edit?\n";
                    cout << "1. Name\n";
                    cout << "2. Value\n";
                    cout << "3. Age\n";
                    cout << "4. All\n";
                    cout << "Enter your choice: ";
                    int editChoice;
                    cin >> editChoice;

                    if (editChoice == 1) {
                        string name;
                        cout << "Enter new name: ";
                        cin >> name;
                        r.setName(name);
                        cout << " Name updated!\n";
                    } 
                    else if (editChoice == 2) {
                        double value;
                        cout << "Enter new value: ";
                        cin >> value;
                        r.setValue(value);
                        cout << " Value updated!\n";
                    } 
                    else if (editChoice == 3) {
                        int age;
                        cout << "Enter new age: ";
                        cin >> age;
                        r.setAge(age);
                        cout << " Age updated!\n";
                    } 
                    else if (editChoice == 4) {
                        string name;
                        double value;
                        int age;
                        cout << "Enter new name: ";
                        cin >> name;
                        cout << "Enter new value: ";
                        cin >> value;
                        cout << "Enter new age: ";
                        cin >> age;
                        r.setName(name);
                        r.setValue(value);
                        r.setAge(age);
                        cout << " All fields updated!\n";
                    } 
                    else {
                        cout << " Invalid choice.\n";
                    }
                    break;
                }
            }
            if (!found)
                cout << " Record not found!\n";
        }

        else if (choice == 3) {
            cout << " All Records:\n";
            for (const auto& r : records)
                r.display();
            if (records.empty())
                cout << "No records found.\n";
        }

        else if (choice == 4) {
            int id;
            cout << "Enter ID to delete: ";
            cin >> id;
            bool found = false;
            for (auto it = records.begin(); it != records.end(); ++it) {
                if (it->getId() == id) {
                    records.erase(it);
                    cout << " Record deleted!\n";
                    found = true;
                    break;
                }
            }
            if (!found)
                cout << " Record not found!\n";
        }

        else if (choice == 5) {
            ofstream fout(filename);
            for (const auto& r : records)
                r.saveToFile(fout);
            fout.close();
            cout << " Data saved to file.\n";
        }

        else if (choice == 0) {
            ofstream fout(filename);
            for (const auto& r : records)
                r.saveToFile(fout);
            fout.close();
            cout << " Exiting... Data saved.\n";
        }

        else {
            cout << " Invalid choice! Try again.\n";
        }

    } while (choice != 0);

    return 0;
}

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct Pipe {
    string name = "";
    double length = 0.0;
    double diameter = 0.0;
    bool inRepair = false;
};

struct KS {
    string name = "";
    int numShops = 0;
    int workingShops = 0;
    double efficiency = 0;
};

// функции для работы с файлами
void savePipeData(const Pipe& pipe, const string& filename) {
    ofstream file(filename, ios::app); // Открытие файла в режиме добавления
    if (file.is_open()) {
        file << "Pipe\n" << pipe.name << " " << pipe.length << " " << pipe.diameter << " " << pipe.inRepair << endl;
        file.close();
        cout << "Pipe data saved to file " << filename << endl;
    }
    else {
        cout << "Error opening file!" << endl;
    }
}

void loadPipeData(Pipe& pipe, const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            if (line == "Pipe") {
                getline(file, pipe.name);
                file >> pipe.length >> pipe.diameter >> pipe.inRepair;
                file.ignore(); // Очистка остатка строки
            }
        }
        file.close();
        cout << "Pipe data loaded from file " << filename << endl;
    }
    else {
        cout << "Error opening file!" << endl;
    }
}

void saveKSData(const KS& ks, const string& filename) {
    ofstream file(filename, ios::app); // Открытие файла в режиме добавления
    if (file.is_open()) {
        file << "KS\n" << ks.name << " " << ks.numShops << " " << ks.workingShops << " " << ks.efficiency << endl;
        file.close();
        cout << "KS data saved to file " << filename << endl;
    }
    else {
        cout << "Error opening file!" << endl;
    }
}

void loadKSData(KS& ks, const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            if (line == "KS") {
                getline(file, ks.name);
                file >> ks.numShops >> ks.workingShops >> ks.efficiency;
                file.ignore(); // Очистка остатка строки
            }
        }
        file.close();
        cout << "KS data loaded from file " << filename << endl;
    }
    else {
        cout << "Error opening file!" << endl;
    }
}

// функции для вывода информации
void displayPipeInfo(const Pipe& pipe) {
    cout << "Pipe:\n";
    cout << "Pipe name: " << pipe.name << endl;
    cout << "Pipe length: " << pipe.length << endl;
    cout << "Pipe diameter: " << pipe.diameter << endl;
    cout << "Repair status: " << (pipe.inRepair ? "In repair" : "Not in repair") << endl;
}

void displayKSInfo(const KS& ks) {
    cout << "Compressor station:\n";
    cout << "KS name: " << ks.name << endl;
    cout << "Total shops: " << ks.numShops << endl;
    cout << "Working shops: " << ks.workingShops << endl;
    cout << "Efficiency: " << ks.efficiency << endl;
}

void addPipe(Pipe& pipe) {
    cout << "Enter pipe name (with spaces): ";
    getline(cin, pipe.name);
    cout << "Enter pipe length: ";
    cin >> pipe.length;
    cout << "Enter pipe diameter: ";
    cin >> pipe.diameter;
    pipe.inRepair = false;
}

void addKS(KS& ks) {
    cout << "Enter KS name (with spaces): ";
    getline(cin, ks.name);
    cout << "Enter number of shops: ";
    cin >> ks.numShops;
    cout << "Enter number of working shops: ";
    cin >> ks.workingShops;
    while (ks.workingShops > ks.numShops || ks.workingShops < 0) {
        cout << "Number of working shops cannot exceed total or be negative. Try again: ";
        cin >> ks.workingShops;
    }
    cout << "Enter KS efficiency: ";
    cin >> ks.efficiency;
}

void editPipe(Pipe& pipe) {
    pipe.inRepair = !pipe.inRepair;
    cout << "Repair status changed to: " << (pipe.inRepair ? "In repair" : "Not in repair") << endl;
}
void editKS(KS& ks) {
    cout << "1. Start shop\n2. Stop shop\n";
    int subChoice;
    cin >> subChoice;
    cin.ignore();
    if (subChoice == 1) {
        if (ks.workingShops < ks.numShops) {
            ks.workingShops++;
            cout << "Shop started. Now working shops: " << ks.workingShops << endl;
        }
        else {
            cout << "All shops are already working." << endl;
        }
    }
    else if (subChoice == 2) {
        if (ks.workingShops > 0) {
            ks.workingShops--;
            cout << "Shop stopped. Now working shops: " << ks.workingShops << endl;
        }
        else {
            cout << "No working shops." << endl;
        }
    }
    else {
        cout << "Invalid choice!" << endl;
    }
}

void showMenu() {
    cout << "1. Add pipe\n";
    cout << "2. Add KS\n";
    cout << "3. View all objects\n";
    cout << "4. Edit pipe\n";
    cout << "5. Edit KS\n";
    cout << "6. Save data\n";
    cout << "7. Load data\n";
    cout << "0. Exit\n";
}

int main() {
    Pipe pipe;
    KS ks;
    string filename = "lab1_file.txt";
    int choice;

    do {
        showMenu();
        cout << "Choose an action: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1:
            addPipe(pipe);
            break;
        case 2:
            addKS(ks);
            break;
        case 3:
            displayPipeInfo(pipe);
            displayKSInfo(ks);
            break;
        case 4:
            editPipe(pipe);
            break;
        case 5:
            editKS(ks);
            break;
        case 6:
            savePipeData(pipe, filename);
            saveKSData(ks, filename);
            break;
        case 7:
            loadPipeData(pipe, filename);
            loadKSData(ks, filename);
            break;
        case 0:
            cout << "Exiting the program.\n";
            break;
        default:
            cout << "Invalid choice, try again.\n";
        }
    } while (choice != 0);

    return 0;
}
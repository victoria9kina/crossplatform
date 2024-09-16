#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

// Structure for Pipe
struct Pipe {
    string name;         // Kilometer mark (name)
    double length;       // Length
    double diameter;     // Diameter
    bool inRepair;       // Repair flag

    // Input Pipe data
    void input() {
        cout << "Enter pipe name: ";
        cin >> name;
        cout << "Enter pipe length: ";
        while (!(cin >> length) || length <= 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a positive value for length: ";
        }
        cout << "Enter pipe diameter: ";
        while (!(cin >> diameter) || diameter <= 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a positive value for diameter: ";
        }
        inRepair = false; // By default, the pipe is not in repair
    }

    // Display Pipe data
    void display() const {
        cout << "Pipe " << name << " (Length: " << length << " km, Diameter: " << diameter << " m, "
            << (inRepair ? "In Repair" : "Not in Repair") << ")" << endl;
    }

    // Toggle repair status
    void toggleRepair() {
        inRepair = !inRepair;
        cout << "Pipe " << name << " is now " << (inRepair ? "in repair." : "not in repair.") << endl;
    }
};

// Structure for Compressor Station (CS)
struct Station {
    string name;           // Name
    int totalShops;        // Total number of shops
    int workingShops;      // Number of working shops
    double efficiency;     // Efficiency

    // Input Station data
    void input() {
        cout << "Enter station name: ";
        cin >> name;
        cout << "Enter total number of shops: ";
        while (!(cin >> totalShops) || totalShops <= 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a positive integer for total shops: ";
        }
        cout << "Enter number of working shops: ";
        while (!(cin >> workingShops) || workingShops < 0 || workingShops > totalShops) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a valid number of working shops: ";
        }
        cout << "Enter station efficiency: ";
        while (!(cin >> efficiency) || efficiency <= 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a positive value for efficiency: ";
        }
    }

    // Display Station data
    void display() const {
        cout << "Station " << name << " (Total Shops: " << totalShops << ", Working Shops: " << workingShops
            << ", Efficiency: " << efficiency << ")" << endl;
    }

    // Toggle working shops
    void toggleShop() {
        if (workingShops < totalShops) {
            workingShops++;
            cout << "One more shop is now working. Total working shops: " << workingShops << "." << endl;
        }
        else {
            workingShops--;
            cout << "One shop has stopped. Total working shops: " << workingShops << "." << endl;
        }
    }
};

// Save data to file
void saveToFile(const vector<Pipe>& pipes, const vector<Station>& stations) {
    ofstream outFile("data.txt");
    if (!outFile.is_open()) {
        cerr << "Error opening file!" << endl;
        return;
    }

    // Save pipes
    outFile << pipes.size() << endl;
    for (const auto& pipe : pipes) {
        outFile << pipe.name << ' ' << pipe.length << ' ' << pipe.diameter << ' ' << pipe.inRepair << endl;
    }

    // Save stations
    outFile << stations.size() << endl;
    for (const auto& station : stations) {
        outFile << station.name << ' ' << station.totalShops << ' ' << station.workingShops << ' ' << station.efficiency << endl;
    }

    cout << "Data saved successfully." << endl;
}

// Load data from file
void loadFromFile(vector<Pipe>& pipes, vector<Station>& stations) {
    ifstream inFile("data.txt");
    if (!inFile.is_open()) {
        cerr << "Error opening file!" << endl;
        return;
    }

    // Load pipes
    size_t pipeCount;
    inFile >> pipeCount;
    pipes.clear();
    for (size_t i = 0; i < pipeCount; ++i) {
        Pipe pipe;
        inFile >> pipe.name >> pipe.length >> pipe.diameter >> pipe.inRepair;
        pipes.push_back(pipe);
    }

    // Load stations
    size_t stationCount;
    inFile >> stationCount;
    stations.clear();
    for (size_t i = 0; i < stationCount; ++i) {
        Station station;
        inFile >> station.name >> station.totalShops >> station.workingShops >> station.efficiency;
        stations.push_back(station);
    }

    cout << "Data loaded successfully." << endl;
}

int main() {
    vector<Pipe> pipes;
    vector<Station> stations;

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Add pipe\n";
        cout << "2. Add station\n";
        cout << "3. View all objects\n";
        cout << "4. Edit pipe\n";
        cout << "5. Edit station\n";
        cout << "6. Save data\n";
        cout << "7. Load data\n";
        cout << "0. Exit\n";
        cout << "Choose an action: ";

        int choice;
        cin >> choice;

        switch (choice) {
        case 1: {
            Pipe pipe;
            pipe.input();
            pipes.push_back(pipe);
            break;
        }
        case 2: {
            Station station;
            station.input();
            stations.push_back(station);
            break;
        }
        case 3: {
            cout << "\nPipes:\n";
            for (const auto& pipe : pipes) {
                pipe.display();
            }
            cout << "\nStations:\n";
            for (const auto& station : stations) {
                station.display();
            }
            break;
        }
        case 4: {
            cout << "Select pipe index to edit: ";
            int index;
            cin >> index;
            if (index >= 0 && index < pipes.size()) {
                pipes[index].toggleRepair();
            }
            else {
                cout << "Invalid index!" << endl;
            }
            break;
        }
        case 5: {
            cout << "Select station index to edit: ";
            int index;
            cin >> index;
            if (index >= 0 && index < stations.size()) {
                stations[index].toggleShop();
            }
            else {
                cout << "Invalid index!" << endl;
            }
            break;
        }
        case 6:
            saveToFile(pipes, stations);
            break;
        case 7:
            loadFromFile(pipes, stations);
            break;
        case 0:
            return 0;
        default:
            cout << "Invalid choice. Try again." << endl;
        }
    }
}

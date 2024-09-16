#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;
struct Pipe {
    string name; 
    double length; 
    double diameter; 
    bool inRepair; 

    void input() {
        cout << "Enter the pipe name: ";
        cin >> name;

        cout << "Enter the pipe length (in km): ";
        cin >> length;
        while (length <= 0) {
            cout << "Please enter a valid positive length: ";
            cin >> length;
        }

        cout << "Enter the pipe diameter (in meters): ";
        cin >> diameter;
        while (diameter <= 0) {
            cout << "Please enter a valid positive diameter: ";
            cin >> diameter;
        }

        inRepair = false;
    }

    void display() {
        cout << "Pipe: " << name << ", Length: " << length << " km, Diameter: " << diameter << " m, ";
        if (inRepair) {
            cout << "Status: In repair\n";
        }
        else {
            cout << "Status: Not in repair\n";
        }
    }

    void toggleRepair() {
        inRepair = !inRepair; 
        if (inRepair) {
            cout << "Pipe " << name << " is now under repair.\n";
        }
        else {
            cout << "Pipe " << name << " is no longer under repair.\n";
        }
    }
};

struct Station {
    string name; 
    int totalShops; 
    int workingShops; 
    double efficiency;

    void input() {
        cout << "Enter the station name: ";
        cin >> name;

        cout << "Enter the total number of shops: ";
        cin >> totalShops;
        while (totalShops <= 0) {
            cout << "Please enter a valid number of shops: ";
            cin >> totalShops;
        }

        cout << "Enter the number of working shops: ";
        cin >> workingShops;
        while (workingShops < 0 || workingShops > totalShops) {
            cout << "Please enter a valid number of working shops: ";
            cin >> workingShops;
        }

        cout << "Enter the station efficiency: ";
        cin >> efficiency;
        while (efficiency <= 0) {
            cout << "Please enter a valid efficiency: ";
            cin >> efficiency;
        }
    }

    void display() {
        cout << "Station: " << name << ", Total Shops: " << totalShops
            << ", Working Shops: " << workingShops << ", Efficiency: " << efficiency << "\n";
    }

    void toggleShop() {
        if (workingShops < totalShops) {
            workingShops++; 
            cout << "One more shop is now working. Total working shops: " << workingShops << "\n";
        }
        else {
            cout << "All shops are already working.\n";
        }
    }
};

void saveToFile(vector<Pipe>& pipes, vector<Station>& stations) {
    ofstream file("lab1_data.txt");
    if (!file) {
        cout << "Error opening file for saving.\n";
        return;
    }

    file << pipes.size() << endl;
    for (const auto& pipe : pipes) {
        file << pipe.name << " " << pipe.length << " " << pipe.diameter << " " << pipe.inRepair << endl;
    }

    file << stations.size() << endl;
    for (const auto& station : stations) {
        file << station.name << " " << station.totalShops << " " << station.workingShops << " " << station.efficiency << endl;
    }

    cout << "Data saved successfully!\n";
}

void loadFromFile(vector<Pipe>& pipes, vector<Station>& stations) {
    ifstream file("lab1_data.txt");
    if (!file) {
        cout << "Error opening file for loading.\n";
        return;
    }

    int pipeCount;
    file >> pipeCount;
    pipes.clear();
    for (int i = 0; i < pipeCount; ++i) {
        Pipe pipe;
        file >> pipe.name >> pipe.length >> pipe.diameter >> pipe.inRepair;
        pipes.push_back(pipe);
    }

    int stationCount;
    file >> stationCount;
    stations.clear();
    for (int i = 0; i < stationCount; ++i) {
        Station station;
        file >> station.name >> station.totalShops >> station.workingShops >> station.efficiency;
        stations.push_back(station);
    }

    cout << "Data loaded successfully!\n";
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
        cout << "Select an option: ";

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
            for (auto& pipe : pipes) {
                pipe.display();
            }
            cout << "\nStations:\n";
            for (auto& station : stations) {
                station.display();
            }
            break;
        }
        case 4: {
            cout << "Enter pipe index to edit (starting from 0): ";
            int index;
            cin >> index;
            if (index >= 0 && index < pipes.size()) {
                pipes[index].toggleRepair();
            }
            else {
                cout << "Invalid index!\n";
            }
            break;
        }
        case 5: {
            cout << "Enter station index to edit (starting from 0): ";
            int index;
            cin >> index;
            if (index >= 0 && index < stations.size()) {
                stations[index].toggleShop();
            }
            else {
                cout << "Invalid index!\n";
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
            cout << "Invalid choice. Please try again.\n";
        }
    }
}

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

// Structure to describe a pipe
struct Pipe {
    string name; // Name of the pipe (kilometer mark)
    double length; // Length of the pipe
    double diameter; // Diameter of the pipe
    bool inRepair; // Is the pipe under repair?

    // Function to input pipe data
    void input() {
        cout << "Enter the pipe name: ";
        cin >> name;

        // Input length with basic validation
        cout << "Enter the pipe length (in km): ";
        cin >> length;
        while (length <= 0) {
            cout << "Please enter a valid positive length: ";
            cin >> length;
        }

        // Input diameter with basic validation
        cout << "Enter the pipe diameter (in meters): ";
        cin >> diameter;
        while (diameter <= 0) {
            cout << "Please enter a valid positive diameter: ";
            cin >> diameter;
        }

        // The pipe is not under repair by default
        inRepair = false;
    }

    // Function to display pipe information
    void display() {
        cout << "Pipe: " << name << ", Length: " << length << " km, Diameter: " << diameter << " m, ";
        if (inRepair) {
            cout << "Status: In repair\n";
        }
        else {
            cout << "Status: Not in repair\n";
        }
    }

    // Function to change the pipe's repair status
    void toggleRepair() {
        inRepair = !inRepair; // Change the repair status
        if (inRepair) {
            cout << "Pipe " << name << " is now under repair.\n";
        }
        else {
            cout << "Pipe " << name << " is no longer under repair.\n";
        }
    }
};

// Structure to describe a compressor station (CS)
struct Station {
    string name; // Station name
    int totalShops; // Total number of shops
    int workingShops; // Number of shops currently working
    double efficiency; // Efficiency of the station

    // Function to input station data
    void input() {
        cout << "Enter the station name: ";
        cin >> name;

        // Input total shops with validation
        cout << "Enter the total number of shops: ";
        cin >> totalShops;
        while (totalShops <= 0) {
            cout << "Please enter a valid number of shops: ";
            cin >> totalShops;
        }

        // Input working shops with validation
        cout << "Enter the number of working shops: ";
        cin >> workingShops;
        while (workingShops < 0 || workingShops > totalShops) {
            cout << "Please enter a valid number of working shops: ";
            cin >> workingShops;
        }

        // Input efficiency with validation
        cout << "Enter the station efficiency: ";
        cin >> efficiency;
        while (efficiency <= 0) {
            cout << "Please enter a valid efficiency: ";
            cin >> efficiency;
        }
    }

    // Function to display station information
    void display() {
        cout << "Station: " << name << ", Total Shops: " << totalShops
            << ", Working Shops: " << workingShops << ", Efficiency: " << efficiency << "\n";
    }

    // Function to toggle the number of working shops
    void toggleShop() {
        if (workingShops < totalShops) {
            workingShops++; // Increase number of working shops
            cout << "One more shop is now working. Total working shops: " << workingShops << "\n";
        }
        else {
            cout << "All shops are already working.\n";
        }
    }
};

// Save data to a file
void saveToFile(vector<Pipe>& pipes, vector<Station>& stations) {
    ofstream file("lab1_data.txt");
    if (!file) {
        cout << "Error opening file for saving.\n";
        return;
    }

    // Save pipes
    file << pipes.size() << endl;
    for (const auto& pipe : pipes) {
        file << pipe.name << " " << pipe.length << " " << pipe.diameter << " " << pipe.inRepair << endl;
    }

    // Save stations
    file << stations.size() << endl;
    for (const auto& station : stations) {
        file << station.name << " " << station.totalShops << " " << station.workingShops << " " << station.efficiency << endl;
    }

    cout << "Data saved successfully!\n";
}

// Load data from a file
void loadFromFile(vector<Pipe>& pipes, vector<Station>& stations) {
    ifstream file("lab1_data.txt");
    if (!file) {
        cout << "Error opening file for loading.\n";
        return;
    }

    // Load pipes
    int pipeCount;
    file >> pipeCount;
    pipes.clear();
    for (int i = 0; i < pipeCount; ++i) {
        Pipe pipe;
        file >> pipe.name >> pipe.length >> pipe.diameter >> pipe.inRepair;
        pipes.push_back(pipe);
    }

    // Load stations
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
    vector<Pipe> pipes; // List of pipes
    vector<Station> stations; // List of stations

    while (true) {
        // Menu for user to interact with
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

        // Menu actions based on user's input
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

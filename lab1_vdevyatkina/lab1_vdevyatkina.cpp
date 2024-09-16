#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;
struct Pipe {
    string name; // название трубы
    double length; // длина трубы
    double diameter; // ее диаметр 
    bool inRepair; // находится ли она в ремонте

    void input() { // функция ввода данных 
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

    void display() { // функция вывода данных на экран 
        cout << "Pipe: " << name << ", Length: " << length << " km, Diameter: " << diameter << " m, ";
        if (inRepair) {
            cout << "Status: In repair\n";
        }
        else {
            cout << "Status: Not in repair\n";
        }
    }

    void toggleRepair() { // функция ремонта труб 
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
    string name; // имя станции 
    int totalShops; // количество цехов
    int workingShops; // кол-во рабочих цехов
    double efficiency; // эффективность (1-100)

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

void saveToFile(vector<Pipe>& pipes, vector<Station>& stations) { // функция сохранения данных в файл 
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

void loadFromFile(vector<Pipe>& pipes, vector<Station>& stations) { // функция отбора данных их файла
    ifstream file("lab1_data.txt");
    if (!file) {
        cout << "Error opening file for loading.\n";
        return;
    }

    int pipeCount; // порядковый номер трубы
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

int main() { // основная функция
    vector<Pipe> pipes; 
    vector<Station> stations; 

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Add pipe\n"; // добавление трубы
        cout << "2. Add station\n"; // добавление станции 
        cout << "3. View all objects\n"; // просмтр введенных объектов
        cout << "4. Edit pipe\n"; // указать находится ли какая-либо труба на ремонте
        cout << "5. Edit station\n"; // указать находится ли какая-либо станция на ремонте
        cout << "6. Save data\n"; // сохранение в файл 
        cout << "7. Load data\n"; // вывод из файла
        cout << "0. Exit\n"; // завершение 
        cout << "Select an option: ";

        int choice;
        cin >> choice;

        switch (choice) { //switch(choice) конструкция для работы с несколькими вариантами кода
        case 1: {
            Pipe pipe; // объект pipe типа Pipe
            pipe.input(); // вызываю метод input() для запроса данных у пользователя о названии.длине и диаметре 
            pipes.push_back(pipe);// объект добавляется в  список pipes с помощью метода push_back()
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
            for (auto& pipe : pipes) { // цикл проходится по всем трубам добавленным в список pipes, а затем выводит все эти трубы на экран
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
            if (index >= 0 && index < pipes.size()) { //должен быть меньше размера вектора pipes
                pipes[index].toggleRepair(); // этот метод изменяет статус трубы, если она была в ремонте, она будет отмечена как рабочая и наоборот
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


#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Vehicle {
public:
    string make, model, year;

    void attributes() {
        cout << "Enter make of car: ";
        cin >> make;
        cout << "Enter model of car: ";
        cin >> model;
        cout << "Enter year of car: ";
        cin >> year;
    }

    virtual double CalculateRentalCost(int days) const { return 0; } // Pure virtual function
    virtual void display() const {
        cout << "Make: " << make << ", Model: " << model << ", Year: " << year;
    }
    virtual ~Vehicle() {} // Virtual destructor
};

class SUV : public Vehicle {
public:
    int weight;
    string cabin;

    void SUVatt() {
        attributes();
        cout << "Enter weight of car: ";
        cin >> weight;
        cout << "Is it single or double cabin: ";
        cin >> cabin;
    }

    double CalculateRentalCost(int days) const {
        return days * 3000;
    }
    void display() const{
        Vehicle::display();
        cout << ", Weight: " << weight << ", Cabin: " << cabin << endl;
    }
};

class Car : public Vehicle {
public:
    int passengers;
    string drive;

    void Caratt() {
        attributes();
        cout << "Enter number of passengers: ";
        cin >> passengers;
        cout << "Is it manual or automatic drive: ";
        cin >> drive;
    }

    double CalculateRentalCost(int days) const {
        return days * 1000;
    }
    void display() const {
        Vehicle::display();
        cout << ", Passengers: " << passengers << ", Drive: " << drive << endl;
    }
};

class Lorry : public Vehicle {
public:
    int load;
    string type;

    void Lorryatt() {
        attributes();
        cout << "Enter weight of load to be carried: ";
        cin >> load;
        cout << "Does it carry foodstuff or non-foodstuff load: ";
        cin >> type;
    }

    double CalculateRentalCost(int days) const {
        return days * 5000;
    }
    void display() const {
        Vehicle::display();
        cout << ", Load: " << load << ", Type: " << type << endl;
    }
};

void displayRentedVehicles(const vector<Vehicle*>& vehicles) {
    if (vehicles.empty()) {
        cout << "No vehicles have been rented yet." << endl;
        return;
    }

    cout << "Rented Vehicles:" << endl;
    for (size_t i = 0; i < vehicles.size(); ++i) {
        vehicles[i]->display();
    }
}

int main() {
    vector<Vehicle*> rentedVehicles;
    Vehicle* vehicle = NULL;
    int choice;
    int rentalDays;
    while (true) {
        cout << "Select the type of vehicle:\n";
        cout << "1. Car\n";
        cout << "2. SUV\n";
        cout << "3. Lorry\n";
        cout << "4. View Rented Vehicles\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                vehicle = new Car();
                static_cast<Car*>(vehicle)->Caratt();
                break;
            }
            case 2: {
                vehicle = new SUV();
                static_cast<SUV*>(vehicle)->SUVatt();
                break;
            }
            case 3: {
                vehicle = new Lorry();
                static_cast<Lorry*>(vehicle)->Lorryatt();
                break;
            }
            case 4: {
                displayRentedVehicles(rentedVehicles);
                continue;
            }
            case 5: {
                for (size_t i = 0; i < rentedVehicles.size(); ++i) {
                    delete rentedVehicles[i];
                }
                return 0;
            }
            default: {
                cout << "Invalid choice!" << endl;
                continue;
            }
        }

        cout << "Enter number of rental days: ";
        cin >> rentalDays;

        if (vehicle) {
            double cost = vehicle->CalculateRentalCost(rentalDays);
            cout << "Rental cost for " << rentalDays << " days: $" << cost << endl;
            rentedVehicles.push_back(vehicle); // Store the rented vehicle
        }
    }
    return 0;
}

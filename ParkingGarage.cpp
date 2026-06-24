#include <iostream>
#include <string>
#include <vector>
#include <memory>


class Car {
private:
    std::string brand;
    std::string license_plate;

public:

    Car(std::string car_brand, std::string car_license_plate) : brand(car_brand), license_plate(car_license_plate) {}

    std::string getBrand() const { return brand; }

    std::string getLicensePlate() const { return license_plate; }

};


class Garage {

private:
    std::vector<std::unique_ptr<Car>> parked_cars;

public:


    void park_new_car() {
        std::string new_car_brand;
        std::string new_car_license_plate;

        std::cout << "Please provide the brand of the car: " << std::endl;
        std::getline(std::cin, new_car_brand);
        std::cout << "Please provide the license plate of the car: " << std::endl;
        std::getline(std::cin, new_car_license_plate);


        parked_cars.push_back(std::make_unique<Car>(new_car_brand, new_car_license_plate));
    }


    void list_parked_cars() {
        int car_index = 1;
        for (auto&& car : parked_cars) {
            std::cout << car_index << ". Brand: " << car->getBrand() << ". License plate: " << car->getLicensePlate() << std::endl; 
            car_index++;
        }
    }


    void remove_parked_car() {

        std::string position_or_licenseplate_input;
        int retrieve_position_input;
        std::string retrieve_license_plate_input;

        std::cout << "Which car do you want to retrieve? Press 1 for car position or press 2 for license plate:  " << std::endl;
        std::cin >> position_or_licenseplate_input;

        if (position_or_licenseplate_input == "1") {
            std::cout << "Please provide the position of the car: " << std::endl;
            std::cin >> retrieve_position_input;
            parked_cars.erase(parked_cars.begin() + (retrieve_position_input - 1));
            std::cout << "Car retrieved!" << std::endl;
        }
        else if (position_or_licenseplate_input == "2") {
            std::cout << "Please provide the license plate of the car: " << std::endl;
            std::cin >> retrieve_license_plate_input;
            
            int car_index = 0;
            for (auto&& car : parked_cars) {
                if (car->getLicensePlate() == retrieve_license_plate_input) {
                    parked_cars.erase(parked_cars.begin() + car_index);
                    std::cout << "Car retrieved!" << std::endl;
                    break;
                }
                car_index++;
            }
        }
    }


};


int main() {

    int user_input;
    bool while_running = true;

    Garage car_garage;



    while (user_input != 4) {
        std::cout << std::endl;
        std::cout << "--- GARAGE MENU ---" << std::endl;
        std::cout << "1. Park a new car" << std::endl;
        std::cout << "2. List parked cars" << std::endl;
        std::cout << "3. Retrieve a car" << std::endl;
        std::cout << "4. Exit" << std::endl;
        std::cout << "Choose an option (number value): " << std::endl;
        std::cin >> user_input;
        std::cout << std::endl;

        switch (user_input) {
            case 1: 
                car_garage.park_new_car();
                std::cin.ignore();
                std::cin.get();
                break;
            case 2:
                car_garage.list_parked_cars();
                std::cin.ignore();
                std::cin.get();
                break;
            case 3:
                car_garage.list_parked_cars();
                car_garage.remove_parked_car();
                std::cin.ignore();
                std::cin.get();
                break;
            case 4:
                while_running = false;
                break;

        }

    }
}

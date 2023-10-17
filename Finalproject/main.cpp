#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <Windows.h>

using namespace std;

// Структура для представления информации об автомобиле
struct Car {
    string name;
    string brand;
    int year;
    double engineVolume;
    string bodyType;
    double price;
    // Дополнительные поля
};

// Структура для представления информации о менеджере
struct Manager {
    string lastName;
    string firstName;
    string middleName;
    int birthYear;
    int experience;
    string phoneNumber;
    string expertise;
    // Дополнительные поля
};

// Структура для представления информации о покупателе
struct Buyer {
    string lastName;
    string firstName;
    string middleName;
    string phoneNumber;
    string address;
    string idNumber;
    // Дополнительные поля
};

// Динамические массивы для хранения данных
vector<Car> cars;
vector<Manager> managers;
vector<Buyer> buyers;

// Функция для добавления информации об автомобиле
void AddCar(const Car& car) {
    cars.push_back(car);
   
}

// Функция для добавления информации о менеджере
void AddManager(const Manager& manager) {
    managers.push_back(manager);
    
}

// Функция для добавления информации о покупателе
void AddBuyer(const Buyer& buyer) {
    buyers.push_back(buyer);
    
}

// Функция для удаления информации об автомобиле по индексу
void DeleteCar(int index) {
    if (index >= 0 && index < cars.size()) {
        cars.erase(cars.begin() + index);
        
    }
}

// Функция для удаления информации о менеджере по индексу
void DeleteManager(int index) {
    if (index >= 0 && index < managers.size()) {
        managers.erase(managers.begin() + index);
        
    }
}

// Функция для удаления информации о покупателе по индексу
void DeleteBuyer(int index) {
    if (index >= 0 && index < buyers.size()) {
        buyers.erase(buyers.begin() + index);
        
    }
}

// Функция для поиска автомобиля по марке
vector<Car> SearchCarByBrand(const string& brand) {
    vector<Car> result;
    for (const Car& car : cars) {
        if (car.brand == brand) {
            result.push_back(car);
        }
    }
    return result;
}

// Функция для поиска менеджера по фамилии
vector<Manager> SearchManagerByLastName(const string& lastName) {
    vector<Manager> result;
    for (const Manager& manager : managers) {
        if (manager.lastName == lastName) {
            result.push_back(manager);
        }
    }
    return result;
}

// Функция для поиска покупателя по фамилии
vector<Buyer> SearchBuyerByLastName(const string& lastName) {
    vector<Buyer> result;
    for (const Buyer& buyer : buyers) {
        if (buyer.lastName == lastName) {
            result.push_back(buyer);
        }
    }
    return result;
}


void SaveDataToBinaryFile(const string& filename) {
    ofstream file(filename, ios::binary);
    if (!file.is_open()) {
        cerr << "Ошибка открытия файла для записи." << endl;
        return;
    }

    int numCars = cars.size();
    int numManagers = managers.size();
    int numBuyers = buyers.size();

    file.write(reinterpret_cast<const char*>(&numCars), sizeof(numCars));
    file.write(reinterpret_cast<const char*>(&numManagers), sizeof(numManagers));
    file.write(reinterpret_cast<const char*>(&numBuyers), sizeof(numBuyers));

    for (const Car& car : cars) {
        int nameLength = car.name.size();
        int brandLength = car.brand.size();
        int bodyTypeLength = car.bodyType.size();

        file.write(reinterpret_cast<const char*>(&nameLength), sizeof(nameLength));
        file.write(car.name.c_str(), nameLength);
        
    }

    for (const Manager& manager : managers) {
        int lastNameLength = manager.lastName.size();
        int firstNameLength = manager.firstName.size();
        int expertiseLength = manager.expertise.size();

        file.write(reinterpret_cast<const char*>(&lastNameLength), sizeof(lastNameLength));
        file.write(manager.lastName.c_str(), lastNameLength);
        
    }

    for (const Buyer& buyer : buyers) {
        int lastNameLength = buyer.lastName.size();
        int firstNameLength = buyer.firstName.size();
        int idNumberLength = buyer.idNumber.size();

        file.write(reinterpret_cast<const char*>(&lastNameLength), sizeof(lastNameLength));
        file.write(buyer.lastName.c_str(), lastNameLength);
      
    }

    file.close();
    cout << "Данные успешно сохранены в файл " << filename << endl;
}

// Функция для загрузки данных из бинарного файла
void LoadDataFromBinaryFile(const string& filename) {
    ifstream file(filename, ios::binary);
    if (!file.is_open()) {
        cerr << "Ошибка открытия файла для чтения." << endl;
        return;
    }

    int numCars, numManagers, numBuyers;
    file.read(reinterpret_cast<char*>(&numCars), sizeof(numCars));
    file.read(reinterpret_cast<char*>(&numManagers), sizeof(numManagers));
    file.read(reinterpret_cast<char*>(&numBuyers), sizeof(numBuyers));

    cars.clear();
    managers.clear();
    buyers.clear();

    for (int i = 0; i < numCars; ++i) {
        Car car;
        int nameLength, brandLength, bodyTypeLength;

        file.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));
        char buffer[256];

        file.read(buffer, nameLength);
        car.name = buffer;
       
        cars.push_back(car);
    }

    for (int i = 0; i < numManagers; ++i) {
        Manager manager;
        int lastNameLength, firstNameLength, expertiseLength;

        file.read(reinterpret_cast<char*>(&lastNameLength), sizeof(lastNameLength));
        char buffer[256];

        file.read(buffer, lastNameLength);
        manager.lastName = buffer;
        

        managers.push_back(manager);
    }

    for (int i = 0; i < numBuyers; ++i) {
        Buyer buyer;
        int lastNameLength, firstNameLength, idNumberLength;

        file.read(reinterpret_cast<char*>(&lastNameLength), sizeof(lastNameLength));
        char buffer[256];

        file.read(buffer, lastNameLength);
        buyer.lastName = buffer;
        

        buyers.push_back(buyer);
    }

    file.close();
    cout << "Данные успешно загружены из файла " << filename << endl;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // Примеры добавления данных
    Car car1 = { "Car1", "BMW", 2022, 2.0, "Sedan", 25000.0 };
    Car car2 = { "Car2", "Lada", 2021, 2.5, "SUV", 35000.0 };
    AddCar(car1);
    AddCar(car2);
    Manager manager1 = { "Manager1", "John", "Doe", 1980, 10, "123-456-7890", "Sales" };
    Manager manager2 = { "Manager2", "Jane", "Smith", 1985, 5, "987-654-3210", "Service" };
    AddManager(manager1);
    AddManager(manager2);
    Buyer buyer1 = { "Buyer1", "Alice", "Brown", "555-123-4567", "123 Main St", "ID12345" };
    Buyer buyer2 = { "Buyer2", "Bob", "Johnson", "555-987-6543", "456 Elm St", "ID67890" };
    AddBuyer(buyer1);
    AddBuyer(buyer2);
    // Пример поиска данных
    string searchBrand = "Brand1";
    vector<Car> foundCars = SearchCarByBrand(searchBrand);
    for (const Car& car : foundCars) {
        cout << "Найден автомобиль: " << car.name << " " << car.brand << " " << car.year << endl;
    }
    string searchLastName = "Manager1";
    vector<Manager> foundManagers = SearchManagerByLastName(searchLastName);
    for (const Manager& manager : foundManagers) {
        cout << "Найден менеджер: " << manager.lastName << " " << manager.firstName << " " << manager.middleName << endl;
    }
    string searchBuyerLastName = "Buyer1";
    vector<Buyer> foundBuyers = SearchBuyerByLastName(searchBuyerLastName);
    for (const Buyer& buyer : foundBuyers) {
        cout << "Найден покупатель: " << buyer.lastName << " " << buyer.firstName << " " << buyer.middleName << endl;
    }

    // Пример удаления данных
    int carIndexToDelete = 0;
    DeleteCar(carIndexToDelete);

    int managerIndexToDelete = 0;
    DeleteManager(managerIndexToDelete);

    int buyerIndexToDelete = 0;
    DeleteBuyer(buyerIndexToDelete);

    // Пример сохранения и загрузки данных в файл
    SaveDataToBinaryFile("auto_shop_data.dat");
    LoadDataFromBinaryFile("auto_shop_data.dat");

    return 0;
}

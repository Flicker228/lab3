#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h> 

struct Product {
    std::string Name;
    double price;
    std::string kolvo;
};

void addProductToFile(const Product& product) {
    std::ofstream outFile1("output.txt", std::ios::app);
    std::ofstream outFile("products.txt", std::ios::app);
    std::ifstream inFile("products.txt");
    if (outFile.is_open()) {
        outFile << product.Name << ", " << product.price << ", " << product.kolvo << std::endl;
        outFile.close();
        std::cout << "������� ������� ��������." << std::endl;
    }
    else {
        std::cerr << "�� ������� ������� ���� ��� ������." << std::endl;
    }
    if (inFile.is_open()) {
        std::string line;
        while (std::getline(inFile, line)) {
            if (outFile1.is_open()) {
                outFile1 << line << std::endl;
            }
        }

        if (outFile1.is_open()) {
            outFile1 << std::endl;
        }
        outFile1.close();
        inFile.close(); // �������� �����
    }
    
}

void searchProductByName(const std::string& name) {
    std::ofstream outFile1("output.txt", std::ios::app);
    std::ifstream inFile("products.txt");
    if (inFile.is_open()) {
        std::string line;
        bool found = false;
        while (std::getline(inFile, line)) {
            size_t pos = line.find(',');
            std::string Name = line.substr(0, pos);
            if (Name == name) {
                std::cout << "������ �������: " << line << std::endl;
                if (outFile1.is_open()) {
                    outFile1 << "������ �������: " << line << std::endl << std::endl;
                    outFile1.close();
                found = true;
                break;
                }
            }
        }
        inFile.close();
        if (!found) {
            std::cout << "������� � ����� ������ �� ������." << std::endl << std::endl;
            if (outFile1.is_open()) {
                outFile1 << "������� � ����� ������ �� ������." << std::endl << std::endl;
                outFile1.close();
            }
        }
    }
    else {
        std::cerr << "�� ������� ������� ���� ��� ������." << std::endl << std::endl;
        if (outFile1.is_open()) {
            outFile1 << "�� ������� ������� ���� ��� ������." << std::endl << std::endl;
            outFile1.close();
        }
    }
}

void outputBelowPrice(const double price) {
    std::ofstream outFile1("output.txt", std::ios::app);
    std::ifstream inFile("products.txt");
    if (inFile.is_open()) {
        int count = 0;
        std::string line;
        while (std::getline(inFile, line)) {
            size_t pos = line.find_first_of(',');
            double price1 = std::stod(line.substr(pos + 1));
            if (price1 <= price) {
                std::cout << line << std::endl;
                if (outFile1.is_open()) {
                    outFile1 << line << std::endl;
                }
            }
        }
        if (outFile1.is_open()) {
            outFile1 << std::endl;
        }
        outFile1.close();
        inFile.close();
    }
    else {
        std::cerr << "�� ������� ������� ���� ��� ������." << std::endl << std::endl;
        if (outFile1.is_open()) {
            outFile1 << "�� ������� ������� ���� ��� ������." << std::endl << std::endl;
            outFile1.close();
        }
    }
}

void sortProductsByPrice() {
    std::ofstream outFile1("output.txt", std::ios::app);
    std::ifstream inFile("products.txt");
    if (inFile.is_open()) {
        // ������ ������ � ���������� (����������� ����������)
        std::string lines[100]; // ������������, ��� �� ����� 100 ���������
        int count = 0;
        std::string line;
        while (std::getline(inFile, line)) {
            lines[count] = line;
            count++;
        }
        inFile.close();
        for (int i = 0; i < count - 1; i++) {
            for (int j = 0; j < count - i - 1; j++) {
                size_t pos1 = lines[j].find_first_of(',');
                size_t pos2 = lines[j + 1].find_first_of(',');
                double price1 = std::stod(lines[j].substr(pos1 + 1));
                double price2 = std::stod(lines[j + 1].substr(pos2 + 1));
                if (price1 < price2) {
                    std::swap(lines[j], lines[j + 1]);
                }
            }
        }
        // ������ ��������������� ������ ������� � ����
        std::ofstream outFile("products.txt");

        if (outFile.is_open()) {
            for (int i = 0; i < count; i++) {
                outFile << lines[i] << std::endl;
            }
            outFile.close();
            std::cout << "�������� ������������� �� ����." << std::endl;
        }
        else {
            std::cerr << "�� ������� ������� ���� ��� ������." << std::endl;
        }

        if (outFile1.is_open()) {
            for (int i = 0; i < count; i++) {
                outFile1 << lines[i] << std::endl;
            }
            outFile1 << std::endl;
            outFile1.close();
        }
        else {
            outFile1 << "�� ������� ������� ���� ��� ������." << std::endl << std::endl;
            outFile1.close();
        }
    }
    else {
        std::cerr << "�� ������� ������� ���� ��� ������." << std::endl << std::endl;
        if (outFile1.is_open()) {
            outFile1 << "�� ������� ������� ���� ��� ������." << std::endl << std::endl;
            outFile1.close();
        }
    }
}

void sortProductsByKolvo() {
    std::ifstream inFile("products.txt");
    std::ofstream outFile1("output.txt", std::ios::app);
    if (inFile.is_open()) {
        // ������ ������ � ���������� (����������� ����������)
        std::string lines[100]; // ������������, ��� �� ����� 100 ���������
        int count = 0;
        std::string line;
        while (std::getline(inFile, line)) {
            lines[count] = line;
            count++;
        }
        inFile.close();
        for (int i = 0; i < count - 1; i++) {
            for (int j = 0; j < count - i - 1; j++) {
                size_t pos1 = lines[j].find_last_of(', ');
                size_t pos2 = lines[j + 1].find_last_of(', ');
                int kolvo1 = std::stod(lines[j].substr(pos1 + 1));
                int kolvo2 = std::stod(lines[j + 1].substr(pos2 + 1));
                if (kolvo1 < kolvo2) {
                    std::swap(lines[j], lines[j + 1]);
                }
            }
        }
        // ������ ��������������� ������ ������� � ����
        std::ofstream outFile("products.txt");
        if (outFile.is_open()) {
            for (int i = 0; i < count; i++) {
                outFile << lines[i] << std::endl;
            }
            outFile.close();
            std::cout << "�������� ������������� �� ����������." << std::endl;
        }
        else {
            std::cerr << "�� ������� ������� ���� ��� ������." << std::endl;
        }

        if (outFile1.is_open()) {
            for (int i = 0; i < count; i++) {
                outFile1 << lines[i] << std::endl;
            }
            outFile1 << std::endl;
            outFile1.close();
        }
        else {
            outFile1 << "�� ������� ������� ���� ��� ������." << std::endl << std::endl;
            outFile1.close();
        }
        
    }
    else {
        std::cerr << "�� ������� ������� ���� ��� ������." << std::endl << std::endl;
        if (outFile1.is_open()) {
            outFile1 << "�������� ������������� �� ����������." << std::endl << std::endl;
            outFile1.close();
        }
    }
}

void output() {
    std::ofstream outFile1("output.txt", std::ios::app);
    std::ifstream inFile("products.txt");
    if (inFile.is_open()) {
        std::string line;
        while (std::getline(inFile, line)) {
            std::cout << line << std::endl;
            if (outFile1.is_open()) {
                outFile1 << line << std::endl;
            }
        }
        if (outFile1.is_open()) {
            outFile1 << std::endl;
        }
        outFile1.close();
        inFile.close(); // �������� �����
    }
}


int main() {
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int choice;
    double pr;
    std::string name;

    do {
        std::cout << "����:" << std::endl;
        std::cout << "1. �������� �������" << std::endl;
        std::cout << "2. ����� �������� �� ��������" << std::endl;
        std::cout << "3. ����������� �������� �� ����" << std::endl;
        std::cout << "4. ����������� �������� �� ����������" << std::endl;
        std::cout << "5. ������� ���������� � ���������" << std::endl;
        std::cout << "6. ������� ���������� � ��������� �� ����� ������ ����" << std::endl;
        std::cout << "0. �����" << std::endl;
        std::cout << "�������� ��������: ";
        std::cin >> choice;

        switch (choice) {
        case 1: {
            std::cin.ignore();
            std::string Name, kolvo;
            double price;
            std::cout << "������� �������� ��������: ";
            std::getline(std::cin, Name);
            if (Name.empty()) {
                std::cout << "���� �������." << std::endl;
                break;
            }
            std::cout << "������� ���� ��������: ";
            std::cin >> price;
            std::cin.ignore();
            std::cout << "������� ���������� ��������: ";
            std::getline(std::cin, kolvo);
            Product newProduct = { Name, price, kolvo };
            addProductToFile(newProduct);
            break;
        }
        case 2: {
            std::cin.ignore();
            std::cout << "������� �������� �������� ��� ������: ";
            std::getline(std::cin, name);
            searchProductByName(name);
            break;
        }
        case 3: {
            sortProductsByPrice();
            break;
        }
        case 4: {
            sortProductsByKolvo();
            break;
        }
        case 5: {
            output();
            break;
        }
        case 6: {
            std::cin.ignore();
            std::cout << "������� ����: ";
            std::cin >> pr;
            outputBelowPrice(pr);
            break;
        }
        case 0: {
            std::cout << "��������� ���������." << std::endl;
            break;
        }
        default: {
            std::cout << "�������� �����. ���������� �����." << std::endl;
            break;
        }
        }
    } while (choice != 0);

    return 0;
}
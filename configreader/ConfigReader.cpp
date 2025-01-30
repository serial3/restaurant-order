#include "ConfigReader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <string>
#include <stdexcept>
#include <functional>

MenuItem ConfigReader::parseMenuItem(const std::string& line) const {
    std::istringstream iss(line);
    std::string idStr, name, priceStr;
    
    if (std::getline(iss, idStr, ',') && 
        std::getline(iss, name, ',') && 
        std::getline(iss, priceStr, ',')) {
        return {std::stoi(idStr), name, std::stod(priceStr)};
    }
    throw std::runtime_error("formato de menu inválido");
}

InventoryItem ConfigReader::parseInventoryItem(const std::string& line) const {
    std::istringstream iss(line);
    std::string ingredient, quantityStr;
    
    if (std::getline(iss, ingredient, ',') && 
        std::getline(iss, quantityStr, ',')) {
        return {ingredient, std::stoi(quantityStr)};
    }
    throw std::runtime_error("formato de inventário inválido");
}

template<typename T>
std::vector<T> ConfigReader::loadFromFile(const std::string& filename, std::function<T(const std::string&)> parseLine) const {
    std::ifstream file(filename);
    std::vector<T> result;
    
    if (!file.is_open()) {
        throw std::runtime_error("ficheiro falhou a abrir: " + filename);
    }

    std::string line;
    std::getline(file, line); // Ignore header

    while (std::getline(file, line)) {
        try {
            result.push_back(parseLine(line));
        } catch (const std::exception& e) {
            std::cerr << "erro ao parsar linha: " << line << ". Erro: " << e.what() << std::endl;
        }
    }

    file.close();
    return result;
}

std::vector<MenuItem> ConfigReader::loadMenuFromFile(const std::string& filename) const {
    return loadFromFile<MenuItem>(
        filename, 
        [this](const std::string& line) { return parseMenuItem(line); }
    );
}

std::map<std::string, int> ConfigReader::loadInventoryFromFile(const std::string& filename) const {
    std::vector<InventoryItem> inventoryItems = loadFromFile<InventoryItem>(
        filename, 
        [this](const std::string& line) { return parseInventoryItem(line); }
    );
    std::map<std::string, int> inventory;
    for (const auto& item : inventoryItems) {
        inventory[item.ingredient] = item.quantity;
    }
    return inventory;
}
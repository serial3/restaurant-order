#ifndef CONFIGREADER_H
#define CONFIGREADER_H

#include <vector>
#include <map>
#include <string>
#include <functional>

struct MenuItem {
    int id;
    std::string name;
    double price;
};

struct InventoryItem {
    std::string ingredient;
    int quantity;
};

class ConfigReader {
public:
    std::vector<MenuItem> loadMenuFromFile(const std::string& filename) const;
    std::map<std::string, int> loadInventoryFromFile(const std::string& filename) const;
private:
    MenuItem parseMenuItem(const std::string& line) const;
    InventoryItem parseInventoryItem(const std::string& line) const;

    template<typename T>
    std::vector<T> loadFromFile(const std::string& filename, std::function<T(const std::string&)> parseLine) const;
};

#endif // CONFIGREADER_H
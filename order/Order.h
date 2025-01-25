#ifndef ORDER_H
#define ORDER_H

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include "ConfigReader.h"
#include "Sales.h"

class ConfigReader;

using namespace std;

class Order {
private:
    int orderId;
    vector<int> itemIds;
    string customization;
    string status;
    static vector<MenuItem> menu;
    static map<string, int> inventory;

    int placeOrder();
    void processOrders() const;
    void manageInventory();
    void notifyKitchen() const;

public:
    Order();
    Order(int orderId, const vector<int>& itemIds, const string& customization, const string& status);
    void displayMenu() const;
    int run();
};

#endif // ORDER_H

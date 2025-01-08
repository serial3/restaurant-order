#ifndef ORDER_H
#define ORDER_H

#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <fstream>
#include <sstream>
#include <thread>
#include <chrono>
#include <string>
#include "ConfigReader.h"
#include "Sales.h"  // Adicionar inclusão do header de Sales

using namespace std;

class Order {
private:
    int orderId;
    vector<int> itemIds;
    string customization;
    string status;

    int placeOrder();
    void processOrders() const;
    void generateBill() const;
    void manageInventory();
    void notifyKitchen() const;

public:
    Order();
    Order(int orderId, const vector<int>& itemIds, const string& customization, const string& status);
    void displayMenu() const;
    int run();
};

#endif // ORDER_H
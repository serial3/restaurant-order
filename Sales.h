#ifndef SALES_H 
#define SALES_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector> // Para usar o vetor de MenuItem
#include "ConfigReader.h"

using namespace std;

class Sales {
public:
    void generateSalesReport() const;
    void saveSalesLog(double amount) const;
    void generateBill(int orderId, const vector<int>& itemIds, const vector<MenuItem>& menu) const; // Nova função

private:
    void writeToFile(double amount) const;
    void readFile() const;
};

#endif // SALES_H
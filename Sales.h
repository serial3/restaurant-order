#ifndef SALES_H
#define SALES_H

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Sales {
public:
    void generateSalesReport() const;
    void saveSalesLog(double amount) const;

private:
    void writeToFile(double amount) const;
    void readFile() const;
};

#endif // SALES_H
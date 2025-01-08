#include "Sales.h"
#include <iostream>
#include <fstream>

using namespace std;

void Sales::generateSalesReport() const {
    readFile();

    double totalSales = 0.0;
    double amount;
    ifstream logFile("sales.log");

    while (logFile >> amount) {
        totalSales += amount;
    }
    logFile.close();

    cout << "\n--- Relatório de Vendas ---\n";
    cout << "Total de Vendas: €" << totalSales << endl;
}

void Sales::saveSalesLog(double amount) const {
    writeToFile(amount);
}

void Sales::writeToFile(double amount) const {
    ofstream logFile("sales.log", ios::app);
    if (logFile.is_open()) {
        logFile << amount << endl;
        logFile.close();
    }
}

void Sales::readFile() const {
    ifstream logFile("sales.log");
    if (!logFile.is_open()) {
        cout << "Não foram encontrados dados de vendas." << endl;
        return;
    }

    double amount;
    cout << "\n--- Log de Vendas ---\n";
    while (logFile >> amount) {
        cout << "Venda: €" << amount << endl;
    }
    logFile.close();
}
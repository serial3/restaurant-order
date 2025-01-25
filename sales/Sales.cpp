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

void Sales::generateBill(int orderId, const vector<int>& itemIds, const vector<MenuItem>& menu) const {
    double total = 0.0;
    double taxRate = 0.08; // 8% de IVA
    cout << "\n--- Fatura para encomenda ID: " << orderId << " ---\n";

    for (int id : itemIds) {
        cout << menu[id - 1].name << " - €" << menu[id - 1].price << "\n";
        total += menu[id - 1].price;
    }

    total += total * taxRate;
    cout << "IVA (8%): €" << total * taxRate << "\n";
    cout << "Total: €" << total << "\n";

    saveSalesLog(total);  // Chama a função para salvar o log de vendas
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
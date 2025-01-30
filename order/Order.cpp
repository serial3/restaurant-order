#include "Order.h"
#include <fstream>
#include <sstream>
#include <thread>
#include <chrono>
#include <queue>

ConfigReader configReader;
Sales sales;

vector<MenuItem> Order::menu = configReader.loadMenuFromFile("menu.txt");
map<string, int> Order::inventory = configReader.loadInventoryFromFile("inventory.txt");

Order::Order() : orderId(0), customization(""), status("") {}

Order::Order(int orderId, const std::vector<int>& itemIds, const std::string& customization, const std::string& status)
    : orderId(orderId), itemIds(itemIds), customization(customization), status(status) {}

void Order::displayMenu() const {
    std::cout << "\n--- Menu ---\n";

    for (const auto& item : menu) {
        std::cout << "Item - ID: " << item.id << ", Name: " << item.name 
                  << ", Price: " << item.price << "$\n";
    }

    if (menu.empty()) {
        std::cout << "Menu está vazio!\n";
    }
}

int Order::placeOrder() {
    std::vector<int> itemIds;
    int itemId;
    std::string customization;

    std::cout << "Introduza os IDs dos artigos a encomendar (insira -1 para parar): ";
    while (true) {
        std::cin >> itemId;
        if (itemId == -1) break;
        itemIds.push_back(itemId);
    }
    std::cin.ignore();

    std::cout << "Alguma personalização? ";
    std::getline(std::cin, customization);

    // Validate customization
    if (inventory.find(customization) == inventory.end()) {
        std::cout << "Customização inválida! Apenas os seguintes ingredientes são permitidos: ";
        for (const auto& item : inventory) {
            std::cout << item.first << " ";
        }
        std::cout << std::endl;
        return -1; // Indicate failure due to invalid customization
    }

    this->orderId++;
    this->itemIds = itemIds;
    this->customization = customization;
    this->status = "Pendente";

    std::cout << "Encomenda colocada com sucesso! ID da encomenda: " << this->orderId << "\n";
    return this->orderId;
}

void Order::processOrders() const {
    std::queue<Order> orderQueue;

    while (!orderQueue.empty()) {
        Order currentOrder = orderQueue.front();
        orderQueue.pop();

        std::cout << "A processar encomenda ID: " << currentOrder.orderId << "\n";
        currentOrder.status = "A preparar";
        std::this_thread::sleep_for(std::chrono::seconds(2));

        currentOrder.status = "Concluída";
        std::cout << "Encomenda ID: " << currentOrder.orderId << " está pronta!\n";
    }
}

void Order::manageInventory() {
    std::cout << "\n--- Inventário ---\n";
    for (const auto& item : inventory) {
        std::cout << item.first << ": " << item.second << "\n";
    }

    std::string ingredient;
    int quantity;
    std::cout << "Introduza o ingrediente para repor stock (ou -1 para parar): ";
    while (true) {
        std::cin >> ingredient;
        if (ingredient == "1") break;
        std::cout << "Introduza a quantidade: ";
        std::cin >> quantity;
        inventory[ingredient] += quantity;
    }
}

void Order::notifyKitchen() const {
    std::queue<Order> orderQueue;
    while (!orderQueue.empty()) {
        std::this_thread::sleep_for(std::chrono::seconds(5));
        std::cout << "Nova encomenda pronta para ser processada.\n";
    }
}

int Order::run() {
    int choice;
    queue<Order> orderQueue;
    while (true) {
        cout << "\n=== Sistema de Gestão de Pedidos de Restaurante ===\n";
        cout << "1. Mostrar Menu\n";
        cout << "2. Efetuar Pedido\n";
        cout << "3. Ver Fila de Pedidos\n";
        cout << "4. Processar Pedidos\n";
        cout << "5. Gerir Inventário\n";
        cout << "6. Gerar Relatório de Vendas\n";
        cout << "7. Sair\n";
        cout << "Escolha uma opção: ";
        cin >> choice;

        switch (choice) {
        case 1:
            displayMenu();
            break;
        case 2:
            placeOrder();
            break;
        case 3:
            cout << "A fila de pedidos contém " << orderQueue.size() << " pedidos.\n";
            break;
        case 4:
            processOrders();
            break;
        case 5:
            manageInventory();
            break;
        case 6:
            sales.generateSalesReport();
            break;
        case 7:
            cout << "Saindo do sistema. Adeus!\n";
            return 0;
        default:
            cout << "Opção inválida. Tente novamente.\n";
        }
    }
}
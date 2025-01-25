#include "Order.h"
#include "Sales.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <gmock/gmock-matchers.h>
#include "ConfigReader.h"

class OrderTest : public ::testing::Test {
public:
    std::string mockFile = "menu.txt"; // Use the expected file name
    Sales sales;
    ConfigReader configReader;
    void SetUp() override {
        // Limpa o arquivo de log antes de cada teste
        std::ofstream logFile("sales.log", std::ios::trunc);
        logFile.close();
    }

    void TearDown() override {
        // Limpa o arquivo de log após cada teste
        std::ofstream logFile("sales.log", std::ios::trunc);
        logFile.close();
    }

    // Método auxiliar para verificar o conteúdo da saída padrão
    std::string captureStdout(std::function<void()> func) {
        std::streambuf* orig_buf = std::cout.rdbuf();
        std::ostringstream captured;
        std::cout.rdbuf(captured.rdbuf());
        
        func();
        
        std::cout.rdbuf(orig_buf);
        return captured.str();
    }
};

TEST_F(OrderTest, DisplayMenuWithExistingFile) {
    std::string expectedOutput = "\n--- Menu ---\n"
                                 "Item - ID: 1, Name: Burger, Price: 5.99$\n"
                                 "Item - ID: 2, Name: Pizza, Price: 8.99$\n"
                                 "Item - ID: 3, Name: Pasta, Price: 7.49$\n"
                                 "Item - ID: 4, Name: Salad, Price: 4.99$\n";

    Order order;
    std::ostringstream oss;
    std::streambuf *oldbuf = std::cout.rdbuf(oss.rdbuf());

    order.displayMenu(); // Call with the hardcoded "menu.txt"

    std::cout.rdbuf(oldbuf);
    ASSERT_EQ(expectedOutput, oss.str());

}

// Testa se o log de vendas é salvo corretamente
TEST_F(OrderTest, SaveSalesLog_SingleEntry) {
    sales.saveSalesLog(100.0);

    // Verifica se o arquivo "sales.log" foi criado e contém o valor esperado
    std::ifstream logFile("sales.log");
    double amount;
    logFile >> amount;

    ASSERT_EQ(amount, 100.0);
    logFile.close();
}

// Testa se o relatório de vendas é gerado corretamente
TEST_F(OrderTest, GenerateSalesReport_SingleEntry) {
    sales.saveSalesLog(150.0);

    // Captura a saída do console
    testing::internal::CaptureStdout();
    sales.generateSalesReport();
    std::string output = testing::internal::GetCapturedStdout();

    // Verifica se o total de vendas no relatório está correto
    ASSERT_NE(output.find("Total de Vendas: €150"), std::string::npos);
}

// Testa a leitura do arquivo quando está vazio
TEST_F(OrderTest, ReadFile_EmptyLog) {

    // Captura a saída do console
    std::remove("sales.log");
    testing::internal::CaptureStdout();
    sales.generateSalesReport();
    std::string output = testing::internal::GetCapturedStdout();

    // Verifica se a mensagem de dados não encontrados é exibida
    ASSERT_NE(output.find("Não foram encontrados dados de vendas."), std::string::npos);
}

// Testa o relatório com múltiplas entradas
TEST_F(OrderTest, GenerateSalesReport_MultipleEntries) {
    sales.saveSalesLog(100.0);
    sales.saveSalesLog(200.0);
    sales.saveSalesLog(300.0);

    // Captura a saída do console
    testing::internal::CaptureStdout();
    sales.generateSalesReport();
    std::string output = testing::internal::GetCapturedStdout();

    // Verifica se o total de vendas no relatório está correto
    ASSERT_NE(output.find("Total de Vendas: €600"), std::string::npos);
}

// Testa a leitura de um arquivo que contém entradas
TEST_F(OrderTest, ReadFile_WithEntries) {
    sales.saveSalesLog(50.0);
    sales.saveSalesLog(75.0);

    // Captura a saída do console
    testing::internal::CaptureStdout();
    sales.generateSalesReport();
    std::string output = testing::internal::GetCapturedStdout();

    // Verifica se as vendas estão sendo exibidas no log
    ASSERT_NE(output.find("Venda: €50"), std::string::npos);
    ASSERT_NE(output.find("Venda: €75"), std::string::npos);
}

TEST_F(OrderTest, LoadMenuFromFile_ValidFile) {
    std::vector<MenuItem> menu = configReader.loadMenuFromFile("menu.txt");
    
    ASSERT_EQ(menu.size(), 4);
    EXPECT_EQ(menu[0].id, 1);
    EXPECT_EQ(menu[0].name, "Burger");
    EXPECT_NEAR(menu[0].price, 5.99, 0.01);

    EXPECT_EQ(menu[1].id, 2);
    EXPECT_EQ(menu[1].name, "Pizza");
    EXPECT_NEAR(menu[1].price, 8.99, 0.01);

    EXPECT_EQ(menu[2].id, 3);
    EXPECT_EQ(menu[2].name, "Pasta");
    EXPECT_NEAR(menu[2].price, 7.49, 0.01);

    EXPECT_EQ(menu[3].id, 4);
    EXPECT_EQ(menu[3].name, "Salad");
    EXPECT_NEAR(menu[3].price, 4.99, 0.01);
}

TEST_F(OrderTest, LoadInventoryFromFile_ValidFile) {
    std::map<std::string, int> inventory = configReader.loadInventoryFromFile("inventory.txt");
    
    ASSERT_EQ(inventory.size(), 4);
    EXPECT_EQ(inventory["Burger Patty"], 20);
    EXPECT_EQ(inventory["Pizza Dough"], 15);
    EXPECT_EQ(inventory["Pasta"], 25);
    EXPECT_EQ(inventory["Salad Greens"], 30);
}

TEST_F(OrderTest, LoadMenuFromFile_InvalidFile) {
    ASSERT_THROW(configReader.loadMenuFromFile("non_existent_file.txt"), std::runtime_error);
}

TEST_F(OrderTest, LoadInventoryFromFile_InvalidFile) {
    ASSERT_THROW(configReader.loadInventoryFromFile("non_existent_file.txt"), std::runtime_error);
}

TEST_F(OrderTest, LoadMenuFromFile_InvalidLineFormat) {
    std::vector<MenuItem> menu = configReader.loadMenuFromFile("invalid_menu.txt");
    
    ASSERT_EQ(menu.size(), 0);
}

TEST_F(OrderTest, LoadInventoryFromFile_InvalidLineFormat) {
    std::map<std::string, int> inventory = configReader.loadInventoryFromFile("invalid_inventory.txt");
    
    ASSERT_EQ(inventory.size(), 3);
}
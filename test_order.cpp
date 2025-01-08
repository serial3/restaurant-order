#include "Order.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

class OrderTest : public ::testing::Test {
public:
    std::string mockFile = "menu.txt"; // Use the expected file name

    void SetUp() override {
    }

    void TearDown() override {

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
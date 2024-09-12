#include <iostream>
#include <string>
#include <vector>
#include <iomanip> // For formatting output

// Forward declaration of Order class
class Order;

// Product class
class Product {
private:
    std::string productID;
    std::string name;
    int price;

public:
    // Constructor
    Product(std::string id, std::string n, int p) : productID(id), name(n), price(p) {}

    // Getters
    std::string getProductID() const { return productID; }
    std::string getName() const { return name; }
    int getPrice() const { return price; }
};

// Order class
class Order {
private:
    std::vector<std::pair<Product, int>> orders;

public:
    Order() = default;
    ~Order() = default;

    void addOrder(const std::vector<std::pair<Product, int>>& cartItems) {
        // Add the cart items to orders
        for (const auto& item : cartItems) {
            orders.push_back(item);
        }
    }

    void viewOrders() const {
        if (orders.empty()) {
            std::cout << "No orders placed yet." << std::endl;
        } else {
            std::cout << "Order Summary:" << std::endl;
            std::cout << std::left << std::setw(10) << "Product ID"
                      << std::setw(20) << "Name"
                      << std::setw(10) << "Price"
                      << std::setw(10) << "Quantity" << std::endl;
            std::cout << "------------------------------------------------" << std::endl;

            for (const auto& item : orders) {
                std::cout << std::left << std::setw(10) << item.first.getProductID()
                          << std::setw(20) << item.first.getName()
                          << std::setw(10) << item.first.getPrice()
                          << std::setw(10) << item.second << std::endl;
            }
        }
    }
};

// ShoppingCart class
class ShoppingCart {
private:
    std::vector<std::pair<Product, int>> cart;

public:
    ShoppingCart() = default;
    ~ShoppingCart() = default;

    void addProduct(const Product& product, int quantity = 1) {
        bool productFound = false;
        for (auto& item : cart) {
            if (item.first.getProductID() == product.getProductID()) {
                item.second += quantity;
                productFound = true;
                break;
            }
        }
        if (!productFound) {
            cart.push_back(std::make_pair(product, quantity));
        }
        std::cout << "Product added successfully!" << std::endl;
    }

    void viewCart(Order& order) {
        if (cart.empty()) {
            std::cout << "Shopping cart is empty." << std::endl;
        } else {
            std::cout << "Shopping Cart:" << std::endl;
            std::cout << std::left << std::setw(10) << "Product ID"
                      << std::setw(20) << "Name"
                      << std::setw(10) << "Price"
                      << std::setw(10) << "Quantity" << std::endl;
            std::cout << "------------------------------------------------" << std::endl;

            for (const auto& item : cart) {
                std::cout << std::left << std::setw(10) << item.first.getProductID()
                          << std::setw(20) << item.first.getName()
                          << std::setw(10) << item.first.getPrice()
                          << std::setw(10) << item.second << std::endl;
            }

            char choice;
            std::cout << "Do you want to check out all the products? (Y/N): ";
            std::cin >> choice;

            if (choice == 'Y' || choice == 'y') {
                // Pass the cart items to checkout and move them to the Order class
                checkout(order);
            }
        }
    }

    void checkout(Order& order) {
        // Move products from the cart to an order
        if (cart.empty()) {
            std::cout << "Your cart is empty, nothing to checkout." << std::endl;
        } else {
            order.addOrder(cart);
            std::cout << "Checkout completed. Your order has been placed!" << std::endl;
            cart.clear(); // Clear the cart after checkout
        }
    }

    bool isEmpty() const {
        return cart.empty();
    }

    const std::vector<std::pair<Product, int>>& getCartItems() const {
        return cart;
    }

    void clearCart() {
        cart.clear();
    }
};

// Function to display a predefined list of products
void displayProductList(const std::vector<Product>& productList) {
    if (productList.empty()) {
        std::cout << "There are no products available." << std::endl;
    } else {
        std::cout << "Product List:" << std::endl;
        std::cout << std::left << std::setw(10) << "Product ID"
                  << std::setw(20) << "Name"
                  << std::setw(10) << "Price" << std::endl;
        std::cout << "------------------------------------------" << std::endl;

        for (const Product& product : productList) {
            std::cout << std::left << std::setw(10) << product.getProductID()
                      << std::setw(20) << product.getName()
                      << std::setw(10) << product.getPrice() << std::endl;
        }
    }
}

// Menu function
void menu(std::vector<Product>& productList, ShoppingCart& cart, Order& order) {
    int choice;
    bool condition = true;

    while (condition) {
        std::cout << "\nMenu" << std::endl;
        std::cout << "1 - View Products" << std::endl;
        std::cout << "2 - View Shopping Cart" << std::endl;
        std::cout << "3 - View Orders" << std::endl;
        std::cout << "4 - Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1: {
            displayProductList(productList);
            std::string productID;
            std::cout << "Enter the Product ID to add to the cart: ";
            std::cin >> productID;

            for (const auto& product : productList) {
                if (product.getProductID() == productID) {
                    cart.addProduct(product);
                    break;
                }
            }
            break;
        }
        case 2:
            cart.viewCart(order);
            break;
        case 3:
            order.viewOrders();
            break;
        case 4:
            std::cout << "Exiting the program." << std::endl;
            condition = false;
            break;
        default:
            std::cout << "Invalid selection. Please try again." << std::endl;
        }
    }
}

int main() {
    //Product LIST
    std::vector<Product> productList = {
        Product("ABC", "Pencil", 20),
        Product("DEF", "Notebook", 50),
        Product("GHI", "Eraser", 15),
        Product("JKL", "Ruler", 30),
        Product("MNO", "Pen", 25)
    };

    ShoppingCart cart;
    Order order;

    // Run the menu
    menu(productList, cart, order);

    return 0;
}

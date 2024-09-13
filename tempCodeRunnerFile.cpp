#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

// Product class
class Product
{
private:
    std::string productID;
    std::string name;
    int price;
    int stock;

public:
    // Constructor
    Product(std::string id, std::string n, int p, int s) : productID(id), name(n), price(p), stock(s) {}

    // Getters
    std::string getProductID() const { return productID; }
    std::string getName() const { return name; }
    int getPrice() const { return price; }
    int getStock() const { return stock; }

    // Update stock of products
    void updateStock(int quantity)
    {
        stock += quantity;
        if (stock < 0)
        {
            stock = 0;
            std::cout << "Product ID: " << productID << ", Name: " << name << " is out of stock!" << std::endl;
        }
    }

    // Display product info
    void productDetails() const
    {
        std::cout << "Product ID: " << productID << ", Name: " << name << ", Price: " << price << ", Stock: " << stock << "\n";
    }
};

// ProductManager class to handle product list
class ProductManager
{
private:
    std::vector<Product> productList;

public:
    ProductManager()
    {
        // Predefined products
        productList = {
            Product("ABC", "Notebook", 20, 99),
            Product("DEF", "Ball Pens Pack", 50, 99),
            Product("GHI", "Pencil Pack", 15, 99),
            Product("JKL", "Ruler", 35, 99),
            Product("MNO", "Eraser", 25, 99),
            Product("PQR", "Highlighter", 90, 99),
            Product("STU", "School Bag", 800, 99),
            Product("VYX", "Binder (A4)", 120, 99),
            Product("XZ1", "Colored Pen Set", 100, 99),
            Product("234", "Glue Stick", 40, 99)};
    }

    const std::vector<Product> &getProductList() const { return productList; }

    void displayProductList() const
    {
        if (productList.empty())
        {
            std::cout << "There are no products available." << std::endl;
        }
        else
        {
            std::cout << "Product List:" << std::endl;
            std::cout << "+--------------------+--------------------+----------+-----------+" << std::endl;
            std::cout << "| " << std::left << std::setw(18) << "Product ID"
                      << "| " << std::setw(18) << "Name"
                      << "| " << std::setw(10) << "Price"
                      << "| " << std::setw(8) << "Stock" << "   |" << std::endl;
            std::cout << "+--------------------+--------------------+----------+-----------+" << std::endl;
            for (const Product &product : productList)
            {
                std::cout << "| " << std::left << std::setw(18) << product.getProductID()
                          << "| " << std::setw(18) << product.getName()
                          << "| PHP " << std::setw(6) << product.getPrice()
                          << "| " << std::setw(10) << product.getStock() << " |" << std::endl;
            }

            std::cout << "+--------------------+--------------------+----------+-----------+" << std::endl;
        }
    }

    // Update stock of a product
    void updateStock(const std::string &productID, int quantity)
    {
        for (auto &product : productList)
        {
            if (product.getProductID() == productID)
            {
                product.updateStock(-quantity);
                return;
            }
        }
        std::cout << "Product ID not found." << std::endl;
    }
};

// Order class
class Order
{
private:
    std::vector<std::vector<std::pair<Product, int>>> allOrders;

public:
    Order() = default;
    ~Order() = default;

    void addOrder(const std::vector<std::pair<Product, int>> &cartItems)
    {
        allOrders.push_back(cartItems); // Add new order to the list
    }

    void viewOrders() const
    {
        if (allOrders.empty())
        {
            std::cout << "No orders placed yet." << std::endl;
        }
        else
        {
            int orderNumber = 1;
            for (const auto &orders : allOrders)
            {
                double totalPrice = 0.0; // Calculate total price for this order

                std::cout << "Order " << orderNumber << ":" << std::endl;
                std::cout << std::left << std::setw(20) << "Product ID"
                          << std::setw(15) << "Name"
                          << std::right << std::setw(15) << "Price"
                          << std::setw(10) << "Quantity"
                          << std::setw(15) << "Subtotal" << std::endl;

                for (const auto &item : orders)
                {
                    double subtotal = item.first.getPrice() * item.second;
                    totalPrice += subtotal;

                    std::cout << std::left << std::setw(20) << item.first.getProductID()
                              << std::setw(15) << item.first.getName()
                              << std::right << std::setw(12) << std::fixed << std::setprecision(2) << item.first.getPrice()
                              << std::setw(6) << item.second
                              << std::setw(19) << std::fixed << std::setprecision(2) << subtotal << std::endl;
                }

                std::cout << std::left << std::setw(75) << std::setfill('-') << "" << std::endl;
                std::cout << std::setfill(' ');
                std::cout << "Total Amount: PHP " << std::fixed << std::setprecision(2) << totalPrice << std::endl;
                std::cout << std::left << std::setw(75) << std::setfill('-') << "" << std::endl;
                std::cout << std::setfill(' ');
                std::cout << std::endl;
                ++orderNumber;
            }
        }
    }
};

// ShoppingCart class
class ShoppingCart
{
private:
    std::vector<std::pair<Product, int>> cart;
    double totalPrice;
    ProductManager &productManager; // Reference to ProductManager

public:
    ShoppingCart(ProductManager &pm) : totalPrice(0.0), productManager(pm) {}

    void addItem(const Product &product, int quantity = 1)
    {
        // Check if the product has enough stock
        if (product.getStock() < quantity)
        {
            std::cout << "Insufficient stock for product ID: " << product.getProductID() << std::endl;
            return;
        }

        bool productFound = false;
        for (auto &item : cart)
        {
            if (item.first.getProductID() == product.getProductID())
            {
                item.second += quantity;
                productFound = true;
                break;
            }
        }

        if (!productFound)
        {
            cart.push_back(std::make_pair(product, quantity));
        }

        productManager.updateStock(product.getProductID(), -quantity); // Update stock in ProductManager
        updateTotalPrice();
        std::cout << "Product added successfully!" << std::endl;
        system("pause");
        system("cls");
    }
   void removeItem(const std::string &productID, int quantity) {
    bool productFound = false;
    for (auto it = cart.begin(); it != cart.end(); ++it) {
        if (it->first.getProductID() == productID) {
            productFound = true;
            it->second -= quantity;

            if (it->second <= 0) {
                productManager.updateStock(productID, it->second); // Add back stock to ProductManager
                cart.erase(it);
                std::cout << "Product removed from cart." << std::endl;
            } else {
                std::cout << "Updated quantity for " << it->first.getName() << ": " << it->second << std::endl;
            }
            break;
        }
    }

    if (!productFound) {
        std::cout << "Product ID not found in cart." << std::endl;
    }
    updateTotalPrice();
}

    void viewCart(Order &order)
    {
        if (cart.empty())
        {
            std::cout << "Shopping cart is empty." << std::endl;
        }
        else
        {
            std::cout << "Shopping Cart:" << std::endl;
            std::cout << "Total Amount: PHP " << std::fixed << std::setprecision(2) << totalPrice << std::endl;
            std::cout << std::left << std::setw(20) << "Product ID"
                      << std::setw(20) << "Name"
                      << std::setw(10) << "Price"
                      << std::setw(10) << "Quantity" << std::endl;
            std::cout << "-----------------------------------------------------------" << std::endl;

            for (const auto &item : cart)
            {
                std::cout << std::left << std::setw(20) << item.first.getProductID()
                          << std::setw(20) << item.first.getName()
                          << std::setw(10) << item.first.getPrice()
                          << std::setw(10) << item.second << std::endl;
            }

            std::cout << "-----------------------------------------------------------" << std::endl;
            std::cout << "Total Amount: PHP " << std::fixed << std::setprecision(2) << totalPrice << std::endl;
            std::cout << "1 - Checkout" << std::endl;
            std::cout << "2 - Remove Item" << std::endl;
            std::cout << "3 - Return to Menu" << std::endl;

            int choice;
            std::cin >> choice;
            switch (choice)
            {
            case 1:
                order.addOrder(cart);
                cart.clear();
                totalPrice = 0.0;
                std::cout << "Order placed successfully!" << std::endl;
                break;

            case 2:
            {
                std::string productID;
                int quantity;
                std::cout << "Enter Product ID to remove: ";
                std::cin >> productID;
                std::cout << "Enter quantity to remove: ";
                std::cin >> quantity;
                removeItem(productID, quantity);
            }
            break;

            case 3:
                return; // Return to the menu
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
                break;
            }
        }
        system("pause");
        system("cls");
    }

private:
    void updateTotalPrice()
    {
        totalPrice = 0.0;
        for (const auto &item : cart)
        {
            totalPrice += item.first.getPrice() * item.second;
        }
    }
};

// Main function
int main()
{
    ProductManager productManager;
    ShoppingCart cart(productManager);
    Order order;
    int choice;
    bool running = true;

    while (running)
    {
        std::cout << "Menu:" << std::endl;
        std::cout << "1 - View Products" << std::endl;
        std::cout << "2 - View Cart" << std::endl;
        std::cout << "3 - View Orders" << std::endl;
        std::cout << "4 - Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            system("cls");
            productManager.displayProductList();
            {
                std::string productID;
                int quantity;
                std::cout << "Enter Product ID to add to cart: ";
                std::cin >> productID;
                std::cout << "Enter quantity: ";
                std::cin >> quantity;

                bool found = false;
                for (const auto &product : productManager.getProductList())
                {
                    if (product.getProductID() == productID)
                    {
                        cart.addItem(product, quantity);
                        found = true;
                        break;
                    }
                }

                if (!found)
                {
                    std::cout << "Product ID not found." << std::endl;
                }
            }
            break;
        case 2:
            cart.viewCart(order);
            break;
        case 3:
            order.viewOrders();
            break;
        case 4:
            std::cout << "Exiting program." << std::endl;
            running = false;
            break;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }

    return 0;
}

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <unistd.h>

int main() {
	std::cout << "Hello C++ World!\n";

	auto s = "I am a string 🤓";
	std::cout << "What is s?\t" << s << "\n";
	auto v = 2.09;
	std::cout << "What is v?\t" << v << "\n";

	std::string customerName;
	std::string customerOrder = "";
	std::cout << "What is your name?\n";
	std::cin >> customerName;
	std::cout << "What is your order?\n";
	std::cin >> customerOrder;
	sleep(2);
	std::cout << customerName << "... Your " << customerOrder << " is ready!\n";

	// // store an array of order numbers
	std::vector<int> orders = { 1, 2, 7, 8, 12, 16 };
	// add another order
	orders.push_back(23);
    std::cout << "Orders issued: ";
    for (int n : orders) {
        std::cout << n << ", ";
    }
    std::cout << "\n";
	// free a table
	orders.pop_back();
}
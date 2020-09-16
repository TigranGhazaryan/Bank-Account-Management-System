#pragma once
#include <iostream>
#include <string>

class Address
{
protected:
	std::string streetAddress{};
	std::string city{};
	std::string state{};
	std::string country{};
	std::string postal_Code{};

	//INTPUT ADDRESS INFORMATION
	void InputAddressInfo()
	{
		std::cout << "\n     ADDRESS INFORMATION\n";
		std::cout << "Street Address: ";
		std::cin.ignore();
		std::getline(std::cin, streetAddress);
		std::cout << "City: ";
		//std::cin.ignore();
		std::getline(std::cin, city);
		std::cout << "State: ";
		//std::cin.ignore();
		std::getline(std::cin, state);
		std::cout << "Country: ";
		//std::cin.ignore();
		std::getline(std::cin, country);
		std::cout << "Postal Code: ";
		std::cin >> postal_Code;
		std::cout << "\n";
	}
};

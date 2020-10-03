#pragma once
#include <iostream>
#include <string>

class Personal
{
protected:
	std::string firstName{};
	std::string lastName{};
	int birthYear{};
	int birthMonth{};
	int birthDay{};

	//INPUT PERSONAL INFORMATION
	void InputPersonalInfo()
	{
		std::cout << "\n     PERSONAL INFORMATION\n";
		std::cout << "\nFirst Name: ";
		std::cin >> firstName;
		std::cout << "Last Name: ";
		std::cin >> lastName;
		std::cout << "Birth Date (year, month, day): ";
		while (std::cin >> birthYear >> birthMonth >> birthDay)
		{
			if (birthYear <= 1900 || birthYear >= 2002 || birthDay <= 0 
				|| birthDay > 31 || birthMonth < 1 || birthMonth > 12)
				std::cout << "\nWrong Input (Invalid year, month or day).\nTry again: ";
			else
				break;
		}	
		std::cout << "\n";
	}
};

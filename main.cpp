#include <iostream>
#include <fstream>
#include "Json.hpp"
#include "Customer_Accounts.h"

using json = nlohmann::json;

int main()
{
    json j;
    json k;
    Customer_Accounts C;
    C.Main_Page();
    std::string Input{};
    while (std::cin >> Input)
    {
        if (Input == "1")
            C.Create_Account(k, j);
        else if (Input == "2")
            C.Update_Existing_Account(k);
        else if (Input == "3")
            C.For_Transactions(k);
        else if (Input == "4")
            C.Check_Existing_Account(k);
        else  if (Input == "5")
            C.Remove_Existing_Account(k);
        else  if (Input == "6")
            C.Print_Customer_List(k);
        else if (Input == "7")
            break;
        else
            std::cout << "Wrong Input, Try again\n";
    }
}

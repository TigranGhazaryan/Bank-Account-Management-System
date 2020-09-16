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
    int Input{};
    while (std::cin >> Input)
    {
        if (Input > 7 || Input < 1)
            std::cout << "Wrong Input, Try again\n";
        if (Input == 1)
            C.Create_Account(k, j);
        if (Input == 2)
            C.Update_Existing_Account(k);
        if (Input == 3)
            C.For_Transactions(k);
        if (Input == 4)
            C.Check_Existing_Account(k);
        if (Input == 5)
            C.Remove_Existing_Account(k);
        if (Input == 6)
            C.Print_Customer_List(k);
        if (Input == 7)
            break;
    }
}

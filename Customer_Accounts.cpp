#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <sstream>
#include "Json.hpp"
#include "Customer_Accounts.h"

using json = nlohmann::json;

//Default Constructor
Customer_Accounts::Customer_Accounts() {};

//Adding to Json File
void Customer_Accounts::Add_Json(json k)
{
    std::ofstream Banking_account_output_file("BankingInfo.json", std::ios::out);
    if (Banking_account_output_file.is_open())
    {
        Banking_account_output_file << std::setw(4) << k;
        Banking_account_output_file.close();
    }
    else
        std::cout << "Unable to open the file\n";
}

//Reading from Json File
void Customer_Accounts::Read_Json(json& k)
{
    std::ifstream Banking_account_input_file("BankingInfo.json");
    if (Banking_account_input_file.is_open())
    {
        Banking_account_input_file >> k;
        Banking_account_input_file.close();
    }
    else
        std::cout << "Unable to open Json\n";
}

//Clear Screen (OS independent)
void Customer_Accounts::Clear_screen()
{
  #ifdef WINDOWS
    std::system("cls");
  #else
    std::system ("clear");
  #endif
}

//Account Verification (name, surname, password)
void Customer_Accounts::Account_Verification()
{
    std::cout << "\nFirst Name: ";
    std::cin >> firstName;
    std::cout << "Last Name: ";
    std::cin >> lastName;
    std::cout << "Password: ";
    std::cin >> accountPassword;
}

//Check for Account Existence
bool Customer_Accounts::Account_Exists(json k, int& i)
{
    for (i = 0; i < k["Customer_Accounts"].size(); ++i)
        if (k["Customer_Accounts"][i]["firstName"] == firstName &&
            k["Customer_Accounts"][i]["lastName"] == lastName &&
            k["Customer_Accounts"][i]["accountPassword"] == accountPassword)
            return true;
    return false;
}

//TRANSFER Information Check
bool Customer_Accounts::Transfer_Info_Check(json k, int& i)
{
    if (k["Customer_Accounts"][i]["CardInfo"]["CardType"] == Card_Type &&
        k["Customer_Accounts"][i]["CardInfo"]["CardNumber"] == Card_Number &&
        k["Customer_Accounts"][i]["CardInfo"]["Valid_Month"] == Valid_Date_Month &&
        k["Customer_Accounts"][i]["CardInfo"]["Valid_Year"] == Valid_Date_Year)
        return true;
    return false;
}

//INPUT ACCOUNT INFORMATION
void Customer_Accounts::InputAccountInfo()
{
    std::cout << "\n     ACCOUNT INFORMATION\n";
    std::cout << "Card Type (Visa or Mastercard): ";
    while (std::cin >> Card_Type)
    {
        if (Card_Type == "Visa" || Card_Type == "Mastercard")
            break;
        else
            std::cout << "Invalid Card Type.\nTry Again: ";
    }
    std::cout << "Card Number: ";
    std::cin.ignore();
    std::getline(std::cin, Card_Number);
    std::cout << "Card Valid Date (Month): ";
    while (std::cin >> Valid_Date_Month)
    {
        if (Valid_Date_Month < 1 || Valid_Date_Month > 12)
            std::cout << "Invalid month \n";
        else
            break;
    }
    std::cout << "Card Valid Date (Year): ";
    while (std::cin >> Valid_Date_Year)
    {
        if (Valid_Date_Year < 2020 || Valid_Date_Year > 2030)
            std::cout << "Invalid year\n";
        else
            break;
    }
    std::cout << "Account Password: ";
    std::cin >> accountPassword;
}

//Turn CUSTOMER INFORMATION to Json format
void Customer_Accounts::Customer_Information(json& j)
{
    j = {
           {"firstName", firstName}, {"lastName", lastName},
           {"birthYear", birthYear}, {"birthMonth", birthMonth},
           {"birthDay", birthDay},
           {"address", {
               {"streetAdress", streetAddress},
               {"city", city},
               {"state", state},
               {"country", country},
               {"postalCode", postal_Code}
                }},
           {"accountBalance", accountBallance},
           {"CardInfo", {
               {"CardType", Card_Type}, {"CardNumber", Card_Number},
               { "Valid_Month", Valid_Date_Month}, {"Valid_Year", Valid_Date_Year}
               }},
              {"accountPassword", accountPassword} };
}

//0. Main Page
void Customer_Accounts::Main_Page()
{
    Customer_Accounts::Clear_screen();
    std::cout << "                      CUSTOMER ACCOUNT BANKING MANAGEMENT SYSTEM                   \n";
    std::cout << "                                WELCOME TO THE MAIN MENU	                         \n";
    std::cout << "\n";
    std::cout << "1. Create new Account\n";
    std::cout << "2. Update information of existing account\n";
    std::cout << "3. For transactions\n";
    std::cout << "4. Check the details of existing account\n";
    std::cout << "5. Removing existing account\n";
    std::cout << "6. View customer's list\n";
    std::cout << "7. Exit\n";
    std::cout << "\n \n \n \n";
    std::cout << "Enter your choice: ";
}

//0.1 Return to the Main Page
void Customer_Accounts::Return_to_Page()
{
    std::cout << "\nInput 'Y' to return to the Main Menu\n";
    char Input{};
    while (std::cin >> Input)
    {
        if (Input == 'Y')
        {
            Customer_Accounts::Main_Page();
            break;
        }
        else
            std::cout << "\nWrong Input, try again\n";
    }
}

//1.CREATE NEW ACCOUNT
void Customer_Accounts::Create_Account(json k, json j)
{
    Customer_Accounts::Clear_screen();
    std::cout << "                                CREATE NEW ACCOUNT	                         \n";
    std::cout << "\nFill in the relevant fields\n";

    Customer_Accounts::InputPersonalInfo();
    Customer_Accounts::InputAddressInfo();
    Customer_Accounts::InputAccountInfo();

    //Set Initial Deposit Amount
    std::cout << "Initial Deposit Amount (AMD): ";
    std::cin >> accountBallance;

    //Put the Input files into Json Format
    Customer_Accounts::Customer_Information(j["Customer_Information"]);

    //Read a file into json format
    Customer_Accounts::Read_Json(k);

    k["Customer_Accounts"].push_back(j["Customer_Information"]);

    //Add the modified json to the file
    Customer_Accounts::Add_Json(k);

    std::cout << "\nAccount SUCCESSFULLY CREATED";
    Customer_Accounts::Return_to_Page();
}

//2.UPDATE EXISTING ACCOUNT
void Customer_Accounts::Update_Existing_Account(json k)
{
    Customer_Accounts::Clear_screen();
    std::cout << "                                UPDATE EXISTING ACCOUNT	                         \n";
    std::cout << "\nFill in Login Details:";
    Customer_Accounts::Account_Verification();
    Customer_Accounts::Read_Json(k);
    int i{};
    if (Customer_Accounts::Account_Exists(k, i))
    {
        std::cout << "\n      Account UPDATE For '"
            << this->firstName << "' '" << this->lastName << "' \n";

        Customer_Accounts::InputPersonalInfo();
        Customer_Accounts::InputAddressInfo();
        Customer_Accounts::InputAccountInfo();

        std::cout << "Update Account Balance\n";
        std::cin >> accountBallance;
        Customer_Accounts::Customer_Information(k["Customer_Accounts"][i]);

        std::cout << "\nAccount UPDATED SUCCESSFULLY";
    }
    else
        std::cout << "Account doesn't exist";
    Customer_Accounts::Add_Json(k);
    Customer_Accounts::Return_to_Page();
}

//3. FOR TRANSACTIONS
void Customer_Accounts::For_Transactions(json k)
{
    Customer_Accounts::Clear_screen();
    std::cout << "                                FOR TRANSACTIONS	                         \n";
    std::cout << "\nFill in Login Details:";
    Customer_Accounts::Account_Verification();
    Customer_Accounts::Read_Json(k);
    int i{};
    if (Customer_Accounts::Account_Exists(k, i))
    {
        std::cout << "\nChoose an Account to Transfer Money to:";
        std::cout << "\nFirst Name: ";
        std::cin >> firstName;
        std::cout << "Last Name: ";
        std::cin >> lastName;
        int j{};
        if (Customer_Accounts::Account_Exists(k, j))
        {
            Customer_Accounts::InputAccountInfo();
            if (!Customer_Accounts::Transfer_Info_Check(k, i))
                std::cout << "\nAccount Data Doesn't Match";

            if (Customer_Accounts::Transfer_Info_Check(k, i))
            {
                int Transfer{};
                //Transfer Money to Your Account
                if (k["Customer_Accounts"][i] == k["Customer_Accounts"][j])
                {
                    std::cout << "     UPDATE ACCOUNT BALANCE\n";
                    std::cin >> Transfer;
                    k["Customer_Accounts"][i]["accountBalance"] = Transfer;
                    std::cout << "ACCOUNT BALANCE UPDATED SUCCESSFULLY\n";
                }

                //Transfer to Another Account
                else
                {
                    std::cout << "Choose Amount for Transfer:\n ";

                    while (std::cin >> Transfer)
                    {
                        if (k["Customer_Accounts"][i]["accountBalance"] >= Transfer)
                        {
                            int originalAmount{};
                            int changedAmount{};

                            originalAmount = k["Customer_Accounts"][i]["accountBalance"];
                            changedAmount = originalAmount - Transfer;
                            k["Customer_Accounts"][i]["accountBalance"] = changedAmount;

                            originalAmount = k["Customer_Accounts"][j]["accountBalance"];
                            changedAmount = originalAmount + Transfer;
                            k["Customer_Accounts"][j]["accountBalance"] = changedAmount;
                            std::cout << "\nTRANSFER COMPLETED SUCCESSFULLY\n";
                            break;
                        }
                        else
                            std::cout << "Not Enought Funds, your current Balance is "
                            << k["Customer_Accounts"][i]["accountBalance"] << "\n"
                            << "Try Again: \n";
                    }
                }
            }

        }
        else
            std::cout << "\nAccount doesn't exist";
    }
    else
        std::cout << "\nAccount doesn't exist";

    Customer_Accounts::Add_Json(k);
    Customer_Accounts::Return_to_Page();
}

//4. CHECK ACCOUNT DETAILS
void Customer_Accounts::Check_Existing_Account(json k)
{
    Customer_Accounts::Clear_screen();
    std::cout << "                                CHECK ACCOUNT DETAILS	                         \n";
    std::cout << "\nFill in Login Details:";
    Customer_Accounts::Account_Verification();
    Customer_Accounts::Read_Json(k);
    int i{};
    if (Customer_Accounts::Account_Exists(k, i))
    {
        std::cout << "      The Account Details For '"
            << this->firstName << "' '" << this->lastName << "' Are\n";
        std::cout << std::setw(4) << k["Customer_Accounts"][i];
    }
    else
        std::cout << "Account doesn't exist";

    Customer_Accounts::Return_to_Page();
}

//5. REMOVE EXISTING ACCOUNT
void Customer_Accounts::Remove_Existing_Account(json k)
{
    Customer_Accounts::Clear_screen();
    std::cout << "                                REMOVE EXISTING ACCOUNT	                         \n";
    std::cout << "\nFill in Login Details:";
    Customer_Accounts::Account_Verification();
    Customer_Accounts::Read_Json(k);
    int i{};
    if (Customer_Accounts::Account_Exists(k, i))
    {
        k["Customer_Accounts"].erase(i);
        Customer_Accounts::Add_Json(k);
        std::cout << "\nAccount SUCCESSFULLY REMOVED";
    }
    else
        std::cout << "Account doesn't exist";

    Customer_Accounts::Return_to_Page();
}

//6.PRINT CUSTOMER LIST
void Customer_Accounts::Print_Customer_List(json k)
{
    Customer_Accounts::Clear_screen();
    std::cout << "                                  CUSTOMER LIST	                         \n";
    Customer_Accounts::Read_Json(k);
    for (int i = 0; i < k["Customer_Accounts"].size(); ++i)
    {
        std::cout << i + 1 << ".";
        std::cout << k["Customer_Accounts"][i]["firstName"] << " ";
        std::cout << k["Customer_Accounts"][i]["lastName"] << " \n";
    }

    Customer_Accounts::Return_to_Page();
}

#pragma once
#include <string>
#include "Json.hpp"
#include "Personal.h"
#include "Address.h"

using json = nlohmann::json;

class Customer_Accounts : protected Personal, protected Address
{
private:
	int accountBallance{};
	std::string Card_Type{};
	std::string Card_Number{};
	int Valid_Date_Month{};
	int Valid_Date_Year{};
	std::string accountPassword{};	
	void InputAccountInfo();
	void Customer_Information(json &j);
	void Account_Verification();
	bool Account_Exists(json k, int& i);
	bool Transfer_Info_Check(json k, int& i);
	void Return_to_Page();
	void Add_Json(json k);
	void Read_Json(json& k);
public:
	Customer_Accounts();
	void Main_Page();
	void Create_Account(json k, json j);
	void Update_Existing_Account(json k);
	void For_Transactions(json k);
	void Check_Existing_Account(json k);
	void Remove_Existing_Account(json k);
	void Print_Customer_List(json k);
};

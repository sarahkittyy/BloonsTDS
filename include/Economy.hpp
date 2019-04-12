#pragma once

#include <string>
#include <unordered_map>

/**
 * @brief Manages a shop-like structure, with different purchases
 * and methods to determine if there is enough money to purchase
 * certain items.
 * 
 */
class Economy
{
public:
	Economy();

	void deposit(int count);
	void withdraw(int count);

	void setBalance(int count);
	int getBalance();

	void addPurchase(std::string name, int cost);
	void removePurchase(std::string name);
	bool canPurchase(std::string name);
	bool purchase(std::string name, bool force = false);

private:
	int mBalance;

	std::unordered_map<std::string, int> mPurchaseable;
};
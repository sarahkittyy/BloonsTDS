#include "Economy.hpp"

Economy::Economy()
{
	mBalance = 0;
}

void Economy::deposit(int count)
{
	mBalance += count;
}

void Economy::withdraw(int count)
{
	mBalance -= count;
}

void Economy::setBalance(int count)
{
	mBalance = count;
}

int Economy::getBalance()
{
	return mBalance;
}

void Economy::addPurchase(std::string name, int cost)
{
	mPurchaseable[name] = cost;
}

void Economy::removePurchase(std::string name)
{
	mPurchaseable.erase(name);
}

bool Economy::canPurchase(std::string name)
{
	return mBalance >= mPurchaseable[name];
}

bool Economy::purchase(std::string name, bool force)
{
	if (force)
	{
		mBalance -= mPurchaseable[name];
		return true;
	}
	else if (canPurchase(name))
	{
		mBalance -= mPurchaseable[name];
		return true;
	}
	else
	{
		return false;
	}
}
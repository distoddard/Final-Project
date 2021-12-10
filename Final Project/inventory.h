#pragma once

#include <iostream>
#include <string>
using namespace std;

#ifndef Inventory_h
#define Inventory_h

class Inventory {
private:
	double invSize;
	double invPrice;
	double invRate;
	string invName;
	string invPub;
	string invDev;
	string invGenre;
	string invGenre2;
	string invGenre3;
	string invFullG;
	double newSize;
	double newPrice;
	double newRate;
	string newName;
	string newPub;
	string newDev;
	string newGenre;
	string newGenre2;
	string newGenre3;
	string newFullG;

	

public:
	Inventory() {
		invSize = 0;
		invPrice = 0.0;
		invRate = 0.0;
		invName = "";
		invPub = "";
		invDev = "";
		invGenre = "";
		invGenre2 = "";
		invGenre3 = "";
		invFullG = "";
		newSize = 0;
		newPrice = 0.0;
		newRate = 0.0;
		newName = "";
		newPub = "";
		newDev = "";
		newGenre = "";
		newGenre2 = "";
		newGenre3 = "";
		newFullG = "";
	}
	
	void storeInvItem(string name, double price, string pub, string dev, string genre1, string genre2, string genre3, string fullG, double size, double rating);
	void setNewInvItem(string name, double price, string pub, string dev, string genre1, string genre2, string genre3, string fullG, double size, double rating);
	void displayInv();
	void displayNewGame();
	string getInvName();
	string getInvGenre();
	string getInvGenre2();
	string getInvGenre3();
	string getFullG();
	double getInvSize();
	double getInvPrice();
	double getInvRate();
	string getInvPub();
	string getInvDev();

	
};

#endif // !Inventory_h

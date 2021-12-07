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
	double newSize;
	double newPrice;
	double newRate;
	string newName;
	string newPub;
	string newDev;
	string newGenre;

	

public:
	Inventory() {
		invSize = 0;
		invPrice = 0.0;
		invRate = 0.0;
		invName = "";
		invPub = "";
		invDev = "";
		invGenre = "";
		newSize = 0;
		newPrice = 0.0;
		newRate = 0.0;
		newName = "";
		newPub = "";
		newDev = "";
		newGenre = "";
	}
	
	void storeInvItem(string name, double price, string pub, string dev, string genre, double size, double rating);
	void setNewInvItem(string name, double price, string pub, string dev, string genre, double size, double rating);
	void displayInv();
	void displayNewGame();
	string getInvName();
	string getInvGenre();
	double getInvSize();
	double getInvPrice();
	double getInvRate();
	string getInvPub();
	string getInvDev();

	void setInvAll(string name, double price, string publisher, string developer, string genre, double size, double rating) {
		invName = name;
		invPrice = price;
		invPub = publisher;
		invDev = developer;
		invGenre = genre;
		invSize = size;
		invRate = rating;
	}
	void setAllNew(string name, double price, string publisher, string developer, string genre, double size, double rating) {
		newName = name;
		newPrice = price;
		newPub = publisher;
		newDev = developer;
		newGenre = genre;
		newSize = size;
		newRate = rating;
	}
};

#endif // !Inventory_h

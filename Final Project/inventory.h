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
	

public:
	Inventory() {
		invSize = 0;
		invPrice = 0.0;
		invRate = 0.0;
		invName = "";
		invPub = "";
		invDev = "";
		invGenre = "";
	}
	
	void storeInvItem(string name, double price, string pub, string dev, string genre, double size, double rating);
	void displayInv();
	string getInvName();
	string getInvGenre();
	double getInvSize();
	double getInvPrice();
	double getInvRate();
	string getInvPub();
	string getInvDev();

	void setInvSize(double size) {
		invSize = size;
	}
	void setInvPrice(double price) {
		invPrice = price;
	}
	void setInvRate(double rating) {
		invRate = rating;
	}
	void setInvName(string name) {
		invName = name;
	}
	void setInvPub(string publisher) {
		invPub = publisher;
	}
	void setInvDev(string developer) {
		invDev = developer;
	}
	void setInvCat(string genre) {
		invGenre = genre;
	}
	void setInvAll(string name, double price, string publisher, string developer, string genre, double size, double rating) {
		invName = name;
		invPrice = price;
		invPub = publisher;
		invDev = developer;
		invGenre = genre;
		invSize = size;
		invRate = rating;
	}
};

#endif // !Inventory_h

#pragma once

#include <iostream>
#include <string>
using namespace std;

#ifndef Inventory_h
#define Inventory_h

class Inventory {
private:
	int invNum;
	double invPrice;
	double invHrs;
	string invName;
	string invCat;
	

public:
	Inventory() {
		invNum = 0;
		invPrice = 0.0;
		invHrs = 0.0;
		invName = "";
		invCat = "";
	}

	int getInvNum() {
		return invNum;
	}
	double getInvPrice() {
		return invPrice;
	}
	double getInvHrs() {
		return invHrs;
	}
	string getInvName() {
		return invName;
	}
	string getInvCat() {
		return invCat;
	}

	void setInvNum(int num) {
		invNum = num;
	}
	void setInvPrice(double price) {
		invPrice = price;
	}
	void setInvHrs(double hrsPlayed) {
		invHrs = hrsPlayed;
	}
	void setInvName(string name) {
		invName = name;
	}
	void setInvCat(string category) {
		invCat = category;
	}
	void setInvAll(int num, double price, string name, string category) {
		invNum = num;
		invPrice = price;
		invName = name;
		invCat = category;
	}
	void displayInv() {
		cout << "Name: " << invName << endl;
		cout << "Inventory #: " << invNum << endl;
		cout << "Price: $" << invPrice << endl;
		cout << "Category: " << invCat << endl;
	}
};

#endif // !Inventory_h

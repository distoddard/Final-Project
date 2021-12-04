#pragma once

#include <iostream>
#include<string>
using namespace std;

#ifndef NewGame_h
#define NewGame_h

class NewGame {
private:
	int newNum;
	double newPrice;
	double newHrs;
	string newName;
	string newCat;

public:
	NewGame() {
		newNum = 0;
		newPrice = 0.0;
		newHrs = 0.0;
		newName = "";
		newCat = "";
	}

	int getNewNum() {
		return newNum;
	}
	double getNewPrice() {
		return newPrice;
	}
	string getNewName() {
		return newName;
	}
	string getNewCat() {
		return newCat;
	}

	void setNewNum(int num) {
		newNum = num;
	}
	void setNewPrice(double price) {
		newPrice = price;
	}
	void setNewHrs(double hrsPlayed) {
		newHrs = hrsPlayed;
	}
	void setNewCat(string category) {
		newCat = category;
	}
	void setNewName(string name) {
		newName = name;
	}
	void setAllNew(int num, double price, double hrsPlayed, string category, string name) {
		newNum = num;
		newPrice = price;
		newHrs = hrsPlayed;
		newCat = category;
		newName = name;
	}

	void displayNewGame() {
		cout << "Inventory #: " << newNum << endl;
		cout << "Game: " << newName << endl;
		cout << "Price: $" << newPrice << endl;
		cout << "Category: " << newCat << endl;
		cout << "Hours played: " << newHrs << endl;
	}
	
};

#endif // !NewGame_h

#pragma once

#include <iostream>
#include<string>
using namespace std;

#ifndef NewGame_h
#define NewGame_h

class NewGame {
private:
	double newSize;
	double newPrice;
	double newRate;
	string newName;
	string newPub;
	string newDev;
	string newGenre;

public:
	NewGame() {
		newSize = 0;
		newPrice = 0.0;
		newRate = 0.0;
		newName = "";
		newPub = "";
		newDev = "";
		newGenre = "";
	}

	double getNewSize() {
		return newSize;
	}
	double getNewPrice() {
		return newPrice;
	}
	double getNewRate() {
		return newRate;
	}
	string getNewName() {
		return newName;
	}
	string getNewGenre() {
		return newGenre;
	}

	void setNewSize(double size) {
		newSize = size;
	}
	void setNewPrice(double price) {
		newPrice = price;
	}
	void setNewRate(double rating) {
		newRate = rating;
	}
	void setNewCat(string genre) {
		newGenre = genre;
	}
	void setNewName(string name) {
		newName = name;
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

	void displayNewGame() {
		cout << "Name: " << newName << endl;
		cout << "Price: $" << newPrice << endl;
		cout << "Publisher: " << newPub << endl;
		cout << "Developer: " << newDev << endl;
		cout << "Genre: " << newGenre << endl;
		cout << "Size: " << newSize << endl;
		cout << "Rating: " << newRate << endl;
	}
	
};

#endif // !NewGame_h

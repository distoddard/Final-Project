#include <iostream>
#include<iomanip>
#include "inventory.h"
using namespace std;

void Inventory::storeInvItem(string name, double price, string pub, string dev, string genre, double size, double rating) {
	invName = name;
	invPrice = price;
	invPub = pub;
	invDev = dev;
	invGenre = genre;
	invSize = size;
	invRate = rating;
}

void Inventory::displayInv() {
	cout << "*****************************************" << endl;
	cout << "Name: " << invName << endl;
	cout << "-----------------------------------------" << endl;
	cout << "Price: $" << fixed << setprecision(2) << invPrice << endl;
	cout << "Publisher: " << invPub << endl;
	cout << "Developer: " << invDev << endl;
	cout << "Genre: " << invGenre << endl;
	if (invSize > 32)
		cout << "Size: " << invSize << " MB" << endl;
	else
		cout << "Size: " << invSize << " GB" << endl;
	cout << "Rating (out of 5): " << invRate << endl << endl;
	
}

string Inventory::getInvName() {
	return invName;
}
string Inventory::getInvGenre() {
	return invGenre;
}
string Inventory::getInvPub() {
	return invPub;
}
string Inventory::getInvDev() {
	return invDev;
}
double Inventory::getInvSize() {
	return invSize;
}
double Inventory::getInvPrice() {
	return invPrice;
}
double Inventory::getInvRate() {
	return invRate;
}
#include <iostream>
#include<iomanip>
#include "inventory.h"
using namespace std;


void Inventory::setInvItem(string name, double price, string pub, string dev, string genre1, string genre2, string genre3, string fullG, double size, double rating) {
	invName = name;
	invPrice = price;
	invPub = pub;
	invDev = dev;
	invGenre = genre1;
	invGenre2 = genre2;
	invGenre3 = genre3;
	invFullG = fullG;
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
	cout << "Genre: " << invFullG << endl;
	if (invSize > 32)
		cout << "Size: " << invSize << " MB" << endl;
	else
		cout << "Size: " << invSize << " GB" << endl;
	cout << "Rating (out of 5): " << invRate << endl << endl;
	
}
void Inventory::displayNewGame() {
	cout << "Name: " << newName << endl;
	cout << "Price: $" << newPrice << endl;
	cout << "Publisher: " << newPub << endl;
	cout << "Developer: " << newDev << endl;
	cout << "Genre: " << newFullG << endl;
	if (newSize > 32)
		cout << "Size: " << newSize << " MB" << endl;
	else
		cout << "Size: " << newSize << " GB" << endl;
	cout << "Rating: " << newRate << endl;
}

string Inventory::getInvName() {
	return invName;
}
string Inventory::getInvGenre() {
	return invGenre;
}
string Inventory::getInvGenre2() {
	return invGenre2;
}
string Inventory::getInvGenre3() {
	return invGenre3;
}
string Inventory::getFullG() {
	return invFullG;
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
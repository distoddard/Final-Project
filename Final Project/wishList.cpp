#include <iostream>
#include <iomanip>
#include "wishList.h"
using namespace std;

void WishList::storeWLitem(string name, double price, string pub, string dev, string genre, double size, string available) {
	nameWL = name;
	priceWL = price;
	pubWL = pub;
	devWL = dev;
	genreWL = genre;
	sizeWL = size;
	avail = available;
}
void WishList::displayWL() {
	cout << "*****************************************" << endl;
	cout << "Name: " << nameWL << endl;
	cout << "-----------------------------------------" << endl;
	cout << "Price: $" << fixed << setprecision(2) << priceWL << endl;
	cout << "Publisher: " << pubWL << endl;
	cout << "Developer: " << devWL << endl;
	cout << "Genre: " << genreWL << endl;
	if (sizeWL > 32)
		cout << "Size: " << sizeWL << " MB" << endl;
	else
		cout << "Size: " << sizeWL << " GB" << endl;
	cout << "Avaialble now?? ";
	if (avail == "Y")
		cout << "YES" << endl;
	else 
		cout << "NO, this game releases on "<< avail << endl;
		
}
string WishList::getWLitemName() {
	return nameWL;
}
double WishList::getWLitemPrice() {
	return priceWL;
}
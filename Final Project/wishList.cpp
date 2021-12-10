#include <iostream>
#include <iomanip>
#include "wishList.h"
using namespace std;

void Wishlist::storeWLitem(string name, double price, string pub, string dev, string genre, string genre2, string genre3, double size, string available) {
	nameWL = name;
	priceWL = price;
	pubWL = pub;
	devWL = dev;
	genreWL = genre;
	genreWL2 = genre2;
	genreWL3 = genre3;
	sizeWL = size;
	avail = available;
}
void Wishlist::displayWL() {
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
	if (avail == "YES")
		cout << "YES" << endl << endl;
	else 
		cout << "NO, this game releases on "<< avail << endl << endl;
		
}
string Wishlist::getWLName() {
	return nameWL;
}
double Wishlist::getWLPrice() {
	return priceWL;
}
string Wishlist::getWLPub() {
	return pubWL;
}
string Wishlist::getWLDev() {
	return devWL;
}
string Wishlist::getWLGenre() {
	return genreWL;
}
string Wishlist::getWLGenre2() {
	return genreWL2;
}
string Wishlist::getWLGenre3() {
	return genreWL3;
}
double Wishlist::getWLSize() {
	return sizeWL;
}
string Wishlist::getWLAvail() {
	return avail;
}
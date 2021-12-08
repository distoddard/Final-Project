#pragma once

#include <iostream>
#include <string>
using namespace std;

#ifndef Wishlist_h
#define Wishlist_h

class Wishlist {
private:
	string nameWL;
	double priceWL;
	string pubWL;
	string devWL;
	string genreWL;
	double sizeWL;
	string avail;

public:
	Wishlist() {
		nameWL = "";
		priceWL = 0.0;
		pubWL = "";
		devWL = "";
		genreWL = "";
		sizeWL = 0.0;
		avail = 'Y';
	}

	void storeWLitem(string name, double price, string pub, string dev, string genre, double size, string available);
	void displayWL();
	string getWLitemName();
	double getWLitemPrice();
};



#endif // !WishList_h

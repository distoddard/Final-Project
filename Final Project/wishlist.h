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
	string genreWL2;
	string genreWL3;
	double sizeWL;
	string avail;

public:
	Wishlist() {
		nameWL = "";
		priceWL = 0.0;
		pubWL = "";
		devWL = "";
		genreWL = "";
		genreWL2 = "";
		genreWL3 = "";
		sizeWL = 0.0;
		avail = "";
	}

	void storeWLitem(string name, double price, string pub, string dev, string genre1, string genre2, string genre3, double size, string available);
	void displayWL();
	string getWLName();
	double getWLPrice();
	string getWLPub();
	string getWLDev();
	string getWLGenre();
	string getWLGenre2();
	string getWLGenre3();
	double getWLSize();
	string getWLAvail();
};



#endif // !WishList_h

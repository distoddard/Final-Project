//Daniel Stoddard
//CIS 1202 - 800
//December 2, 2021

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
#include "inventory.h"
#include "newGame.h"
using namespace std;

int showMenu();
void getFullInventory(vector<Inventory> &, vector<string> &, vector<string> &, vector<string> &, int &);
void showFullInventory(vector<Inventory>);
void showNamesOnly(vector<Inventory>);
int searchName(vector<Inventory>, string);
void searchGenres(vector<Inventory>, vector<string>, vector<string>, vector<string>, string);
void showBacklog(vector<Inventory>);
void showTopRated(vector<Inventory>);
void searchPublisher(vector<Inventory>, string);

template<class S>
double getTotalSizeNeeded(S inventory) {
	double totalSize = 0.0, tempSize = 0.0;
	for (int i = 0; i < inventory.size(); i++) {
		tempSize = inventory.at(i).getInvSize();
		if (tempSize > 32)
			tempSize = tempSize / 1000;
		totalSize += tempSize;
	}
	return ceil(totalSize);
}
template<class V>
double getTotalValue(V inventory) {
	double totalValue = 0.0;
	for (int i = 0; i < inventory.size(); i++) {
		totalValue += inventory.at(i).getInvPrice();
	}
	return totalValue;
}

int main() {

	int totalNumGames = 0, choice = 0, foundNameLocation;
	double totalSize, totalValue;
	string nameSearch, genreSearch, pubSearch, devSearch;
	vector<Inventory> inventory;
	vector<string> genres1; vector<string> genres2; vector<string> genres3;
	
	getFullInventory(inventory, genres1, genres2, genres3, totalNumGames);
	

	cout << "************************************************" << endl;
	cout << "* NINTENDO SWITCH INDIE GAME INVENTORY MANAGER *" << endl;
	cout << "************************************************" << endl << endl;
	cout << "Welcome to you 'NINDIE' game inventory manager!" << endl << endl;
	choice = showMenu();
	switch (choice) {
	case 1:
		showFullInventory(inventory);
		break;
	case 2:
		showNamesOnly(inventory);
		break;
	case 3:
		cout << "Please enter the name of the game you wnat to search for (case-sensitive):" << endl;
		cin.ignore(50, '\n');
		getline(cin, nameSearch);
		foundNameLocation = searchName(inventory, nameSearch);
		if (foundNameLocation > -1)
			inventory[foundNameLocation].displayInv();
		else
			cout << "Game not found! Check your spelling or get on the eShop and buy it!" << endl;
		break;
	case 4:
		cout << "Please enter the genre you would like to search for (case-sensitive):" << endl;
		cin.ignore(50, '\n');
		getline(cin, genreSearch);
		searchGenres(inventory, genres1, genres2, genres3, genreSearch);
		break;
	case 5:
		totalSize = getTotalSizeNeeded(inventory);
		cout << "You will need about " << totalSize << " GBs of storage space to install all your games at once!" << endl;
		break;
	case 6:
		totalValue = getTotalValue(inventory);
		cout << "The total value of you full library of games is $" << setprecision(2) << fixed << totalValue << endl;
		cout << "**SPOUSAL DISCLAIMER** Most of these games were purchased while on sale, love you! :)" << endl;
		break;
	case 7:
		showBacklog(inventory);
		break;
	case 8:
		showTopRated(inventory);
		break;
	case 9:
		cout << "Please enter the publisher you would like to search for (case-sensitive):" << endl;
		cin.ignore(50, '\n');
		getline(cin, pubSearch);
		searchPublisher(inventory, pubSearch);
		break;
	case 10:
		break;
	case 11:
		break;
	case 0:
		return 0;
	default:
		break;
	}
	
}

int showMenu() {
	int choice = 0;
	
	cout << "What would you like to do today?" << endl;
	cout << "1. Show the full inventory of games with all details" << endl;
	cout << "2. Show the game names only" << endl;
	cout << "3. Search for a specific game" << endl;
	cout << "4. Show all the games of a particular genre" << endl;
	cout << "5. Calculate the total storage space needed to have all games installed" << endl;
	cout << "6. Calculate the value of the entire library" << endl;
	cout << "7. Show your backlog of games you haven't played enough yet" << endl;
	cout << "8. Show the top rated games only" << endl;
	cout << "9. Search by publisher" << endl;
	cout << "10. Search by developer" << endl;
	cout << "11. Add a new game to your inventory" << endl;
	cout << "0. Exit the program" << endl;
	cout << "Enter your choice now: ";
	cin >> choice;
	while (choice > 11 || choice < 0) {
		cout << "Please enter a valid choice (0 - 11): ";
		cin >> choice;
	}
	cout << "\n";
	return choice;
}
void getFullInventory(vector<Inventory> &inventory, vector<string> &genres1, vector<string> &genres2, vector<string> &genres3, int &count) {
	
	double price, size, rating;
	string name, pub, dev, genre1, genre2, genre3, fullGenre;
	fstream readNames, readPrices, readPubs, readDevs, readGenre1, readGenre2, readGenre3, readSizes, readRatings;

	readNames.open("names.txt", ios::in); readPrices.open("prices.txt", ios::in); readPubs.open("pubs.txt", ios::in); 
	readDevs.open("devs.txt", ios::in);readGenre1.open("genre1.txt", ios::in); readGenre2.open("genre2.txt", ios::in); 
	readGenre3.open("genre3.txt", ios::in); readSizes.open("sizes.txt", ios::in); readRatings.open("ratings.txt", ios::in);

	while (getline(readNames, name)) {
		Inventory tempSlot;
		readPrices >> price;
		getline(readPubs, pub);
		getline(readDevs, dev);
		getline(readGenre1, genre1);
		genres1.push_back(genre1);
		getline(readGenre2, genre2);
		genres2.push_back(genre2);
		getline(readGenre3, genre3);
		genres3.push_back(genre3);
		fullGenre = genre1 + " " + genre2 + " " + genre3;
		readSizes >> size;
		readRatings >> rating;
		tempSlot.storeInvItem(name, price, pub, dev, fullGenre, size, rating);
		inventory.push_back(tempSlot);
		count++;
	}
	readNames.close(); readPrices.close(); readPubs.close(); readDevs.close();
	readGenre1.close(); readGenre2.close(); readGenre3.close(); readSizes.close(); readRatings.close();
}
void showFullInventory(vector<Inventory> inventory) {
	for (int i = 0; i < inventory.size(); i++) {
		inventory[i].displayInv();
	}
	cout << "\n";
}
void showNamesOnly(vector<Inventory> inventory) {
	for (int i = 0; i < inventory.size(); i++) {
		cout << inventory[i].getInvName() << endl;
	}
	cout << "\n";
}
int searchName(vector<Inventory> inventory, string nameSearch) {
	for (int i = 0; i < inventory.size(); i++) {
		inventory[i].getInvName();
		if (nameSearch == inventory[i].getInvName())
			return i;
	}
	return -1;
}
void searchGenres(vector<Inventory> inventory, vector<string> genres1, vector<string> genres2, vector<string> genres3, string genreSearch) {
	bool found = false;
	cout << "Showing all owned games with the genre containing '" << genreSearch << "'..." << endl;
	cout << "----------------------------------------------------------------------" << endl;
	for (int i = 0; i < inventory.size(); i++) {
		if (genres1[i] == genreSearch || genres2[i] == genreSearch || genres3[i] == genreSearch) {
			cout << setw(40) << right << inventory[i].getInvName() << " - " << setw(40) << left << inventory[i].getInvGenre() << endl;
			found = true;
		}
	}
	if (found != true)
		cout << "No games found with '" << genreSearch << "' in the genre. Please check the spelling.." << endl;
}
void showBacklog(vector<Inventory> inventory) {
	double select = 1;
	cout << "These are all the games in your backlog (games you havent played enough to provide a rating)" << endl;
	cout << "--------------------------------------------------------------------------------------------" << endl;
	for (int i = 0; i < inventory.size(); i++) {
		select = inventory[i].getInvRate();
		if (select == 0.0)
			cout << inventory[i].getInvName() << endl;
	}
}
void showTopRated(vector<Inventory> inventory) {
	double select = 0.0;
	cout << "These are all your games that have a (self-declared) rating of at least 4.7 out of 5 along with their publishers" << endl;
	cout << "----------------------------------------------------------------------------------------------------------------" << endl;
	for (int i = 0; i < inventory.size(); i++) {
		select = inventory[i].getInvRate();
		if (select >= 4.7)
			cout << setw(40) << right << inventory[i].getInvName() << " - " << setw(3) << setprecision(1) << fixed << left << inventory[i].getInvRate() << " - " << setw(40) << left << inventory[i].getInvPub() << endl;
	}
}
void searchPublisher(vector<Inventory> inventory, string pubSearch) {
	bool found = false;
	cout << "Showing all owned games published by '" << pubSearch << "' and their developers" << endl;
	cout << "----------------------------------------------------------------------------" << endl;
	for (int i = 0; i < inventory.size(); i++) {
		if (inventory[i].getInvPub() == pubSearch) {
			cout << setw(40) << right << inventory[i].getInvName() << " - " << setw(40) << left << inventory[i].getInvDev() << endl;
			found = true;
		}
	}
	if (found != true)
		cout << "No games found published by '" << pubSearch << "'. Please check the spelling, or get some!" << endl;
}



/*while (getline(readNames, name)) {
	names.push_back(name);
	readPrices >> price;
	prices.push_back(price);
	getline(readPubs, pub);
	pubs.push_back(pub);
	getline(readDevs, dev);
	devs.push_back(dev);
	getline(readGenre1, genre1);
	genres1.push_back(genre1);
	getline(readGenre2, genre2);
	genres2.push_back(genre2);
	getline(readGenre3, genre3);
	genres3.push_back(genre3);
	readSizes >> size;
	sizes.push_back(size);
	readRatings >> rating;
	ratings.push_back(rating);
	count++;
}*/

//vector<string> names; vector<double> prices; vector<string> pubs; vector<string> devs; vector<string> genres1; vector<string> genres2; vector<string> genres3; vector<double> sizes; vector<double> ratings;

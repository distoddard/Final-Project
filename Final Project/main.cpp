//Daniel Stoddard
//CIS 1202 - 800
//December 2, 2021
//Nintendo Switch Indie Game Inventory Manager
//description goes here

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
#include "inventory.h"
#include "wishList.h"

using namespace std;
int mainMenu();

int invMenu();
void getFullInventory(vector<Inventory> &, vector<string> &, vector<string> &, vector<string> &);
void showFullInventory(vector<Inventory>);
void showNamesOnly(vector<Inventory>);
int searchName(vector<Inventory>, string);
void searchGenres(vector<Inventory>, vector<string>, vector<string>, vector<string>, string);
void showBacklog(vector<Inventory>);
void showTopRated(vector<Inventory>);
void searchPublisher(vector<Inventory>, string);
void searchByDeveloper(vector<Inventory>, string);
void addNewGame(vector<Inventory> &, vector<string> &, vector<string> &, vector<string> &);
void writeInvToFiles(vector<Inventory>, vector<string>, vector<string>, vector<string>);
void editInvItem(vector<Inventory>&, vector<string>&, vector<string>&, vector<string>&);
void removeInvItem(vector<Inventory>&, vector<string>&, vector<string>&, vector<string>&);

int wlMenu();
void getFullWishlist(vector<Wishlist>&, vector <string>&, vector<string>&, vector<string>&);
void showFullWishlist(vector<Wishlist>);
void showWishlistNames(vector<Wishlist>);
void searchWishlist();
void addWLitem();

enum Menu {
	EXIT,
	INVENTORY,
	WISHLIST
};
enum Search {
	CANCEL,
	NAME,
	PUB,
	DEV,
	GENRE
};
enum Manage {
	CANCEL,
	ADD,
	EDIT,
	REMOVE,
	MOVE
};

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
template<class W>
double getTotalNeeded(W wishList) {
	double totalNeeded = 0.0;
	for (int i = 0; i < wishList.size(); i++) {
		totalNeeded += wishList.at(i).getWLitemPrice();
	}
	return totalNeeded;
}

int main() {
	Menu menuEnum;
	Search searchEnum;
	Manage manageEnum;
	int totalNumGames = 0, choice = 0, mainChoice = 0, searchChoice = 0, manageChoice = 0, foundNameLocation;
	double totalSize, totalValue;
	string nameSearch, genreSearch, pubSearch, devSearch;
	vector<Inventory> inventory;
	vector<string> genres1; vector<string> genres2; vector<string> genres3;
	
	getFullInventory(inventory, genres1, genres2, genres3);
	

	cout << "***********************************************************" << endl;
	cout << "* NINTENDO SWITCH INDIE GAME INVENTORY & WISHLIST MANAGER *" << endl;
	cout << "***********************************************************" << endl << endl;
	cout << "Welcome to you 'NINDIE' game inventory & wish list manager!" << endl << endl;
	menuEnum = static_cast<Menu>(mainMenu());
	while (menuEnum != EXIT) {
		switch (menuEnum)
		{
		case EXIT: return(0);
			break;
		case INVENTORY:
			choice = invMenu();
			while (choice != 0) {
				switch (choice) 
				{
				case 0:
					cout << "Returning to main menu..." << endl << endl;
					break;
				case 1:
					showFullInventory(inventory);
					break;
				case 2:
					showNamesOnly(inventory);
					break;
				case 3:
					cout << "What would you like to search by?" << endl;
					cout << "1. NAME	|2.	PUBLISHER |3. DEVELOPER |4. GENRE	|0. CANCEL SEARCH" << endl;
					cin >> searchChoice;
					while (searchChoice < 0 || searchChoice > 4) {
						cout << "Please enter a valid choice (1 - 4): " << endl;
						cin >> searchChoice;
					}
					searchEnum = static_cast<Search>(searchChoice);
					switch (searchEnum)
					{
					case NAME:
						cout << "Please enter the name of the game you want to search for (case-sensitive):" << endl;
						cin.ignore(50, '\n');
						getline(cin, nameSearch);
						foundNameLocation = searchName(inventory, nameSearch);
						if (foundNameLocation > -1)
							inventory[foundNameLocation].displayInv();
						else
							cout << "Game not found! Check your spelling or get on the eShop and buy it!" << endl;
						break;
					case PUB:
						cout << "Please enter the publisher you would like to search for (case-sensitive):" << endl;
						cin.ignore(50, '\n');
						getline(cin, pubSearch);
						searchPublisher(inventory, pubSearch);
						break;
					case DEV:
						cout << "Please enter the developer you would like to search for (case-sensitive):" << endl;
						cin.ignore(50, '\n');
						getline(cin, devSearch);
						searchPublisher(inventory, devSearch);
						break;
					case GENRE:
						cout << "Please enter the genre you would like to search for (case-sensitive):" << endl;
						cin.ignore(50, '\n');
						getline(cin, genreSearch);
						searchGenres(inventory, genres1, genres2, genres3, genreSearch);
						break;
					case CANCEL:
						cout << "Returning to previous menu.." << endl << endl;
						break;
					default:
						break;
					}
					break;
				case 4:
					totalSize = getTotalSizeNeeded(inventory);
					cout << "You will need about " << totalSize << " GBs of storage space to install all your games at once!" << endl;
					break;
				case 5:
					totalValue = getTotalValue(inventory);
					cout << "The total value of you full library of games is $" << setprecision(2) << fixed << totalValue << endl;
					cout << "**SPOUSAL DISCLAIMER** Most of these games were purchased while on sale, love you! :)" << endl;
					break;
				case 6:
					showBacklog(inventory);
					break;
				case 7:
					showTopRated(inventory);
					break;
				case 8:
					cout << "What would you like to do?" << endl;
					cout << "1. ADD		|2. EDIT	|3. REMOVE	|0. CANCEL " << endl;
					cin >> manageChoice;
					while (manageChoice > 3 || manageChoice < 0) {
						cout << "Please enter a valid choice (0 - 3): ";
						cin >> manageChoice;
					}
					manageEnum = static_cast<Manage>(manageChoice);
					switch (manageEnum)
					{
					case CANCEL:
						cout << "Returning to previous menu.." << endl << endl;
						break;
					case ADD:
						addNewGame(inventory, genres1, genres2, genres3);
						break;
					case EDIT:
						editInvItem(inventory, genres1, genres2, genres3);
						break;
					case REMOVE:
						removeInvItem(inventory, genres1, genres2, genres3);
						break;
					case MOVE:
						break;
					default:
						break;
					}
					break;
				default:
					break;
				}
				choice = invMenu();
			}
			break;
		case WISHLIST:
			choice = wlMenu();
			while (choice != 0) {
				switch (choice)
				{
				case 0:
					cout << "Returning to the main menu..." << endl << endl;
					break;
				case 1:
					break;
				case 2:
					break;
				case 3:
					break;
				case 4:
					break;
				case 5:
					break;
				case 6:
					break;
				case 7:
					break;
				default:
					break;
				}
				choice = wlMenu();
			}
			break;
		default:
			break;
		}
		menuEnum = static_cast<Menu>(mainMenu());
	}
}
int mainMenu() {
	int choice;
	cout << "Which library would you like to manage?" << endl;
	cout << "Enter '1' for INVENTORY | '2' for WISHLIST | '3' to EXIT: ";
	cin >> choice;
	while (choice < 0 || choice > 2) {
		cout << "Invalid option enetered..." << endl;
		cout << "(better have been a fat finger because it's pretty simple...)" << endl;
		cout << "Enter '1' for INVENTORY or '2' for WISHLIST | '3' to EXIT: ";
		cin >> choice;
	}
	return choice;
}
int invMenu() {
	int choice = 0;
	cout << "***********************************" << endl;
	cout << "****---- INVENTORY MANAGER ----****" << endl;
	cout << "***********************************" << endl << endl;
	cout << "What would you like to do?" << endl;
	cout << "0. Return to the main menu" << endl;
	cout << "1. Show the full inventory of games with all details" << endl;
	cout << "2. Show the game names only" << endl;
	cout << "3. Search for a specific game" << endl;
	cout << "4. Calculate the total storage space needed to have all games installed" << endl;
	cout << "5. Calculate the value of the entire library" << endl;
	cout << "6. Show your backlog of games you haven't played enough yet" << endl;
	cout << "7. Show the top rated games only" << endl;
	cout << "8. Manage a single entry in your inventory" << endl;
	cout << "Enter your choice now: ";
	cin >> choice;
	while (choice > 8 || choice < 0) {
		cout << "Please enter a valid choice (0 - 8): ";
		cin >> choice;
	}
	cout << "\n";
	return choice;
}
void getFullInventory(vector<Inventory> &inventory, vector<string> &genres1, vector<string> &genres2, vector<string> &genres3) {
	
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
	}
	readNames.close(); readPrices.close(); readPubs.close(); readDevs.close();
	readGenre1.close(); readGenre2.close(); readGenre3.close(); readSizes.close(); readRatings.close();
}
void showFullInventory(vector<Inventory> inventory) {
	for (int i = 0; i < inventory.size(); i++) {
		inventory.at(i).displayInv();
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
void searchDeveloper(vector<Inventory> inventory, string devSearch) {
	bool found = false;
	cout << "Showing all owned games published by '" << devSearch << "' and their publishers" << endl;
	cout << "----------------------------------------------------------------------------" << endl;
	for (int i = 0; i < inventory.size(); i++) {
		if (inventory[i].getInvDev() == devSearch) {
			cout << setw(40) << right << inventory[i].getInvName() << " - " << setw(40) << left << inventory[i].getInvPub() << endl;
			found = true;
		}
	}
	if (found != true)
		cout << "No games found developed by '" << devSearch << "'. Please check the spelling, or get some!" << endl;
}
void addNewGame(vector<Inventory> &inventory, vector<string> &genres1, vector<string> &genres2, vector<string> &genres3) {
	Inventory tempSlot, tempSlot2;
	char error;
	string name, pub, dev, fullGenre;
	double price, size, rating;
	cout << "Name of the game you would like to add:" << endl;
	cin.ignore(50, '\n');
	getline(cin, name);
	cout << "\nPrice of the game (not the sale price):" << endl;
	cin >> price;
	cin.ignore(100, '\n');
	cout << "\nPublisher:" << endl;
	getline(cin, pub);
	cout << "\nDeveloper:" << endl;
	getline(cin, dev);
	fullGenre = genreSelection(genres1, genres2, genres3);
	cout << "\nSize of the game:" << endl;
	cin >> size;
	cout << "\nPersonal rating out of 5 (use 0 if not played enough to rate):" << endl;
	cin >> rating;
	tempSlot.storeInvItem(name, price, pub, dev, fullGenre, size, rating);
	inventory.push_back(tempSlot);
	tempSlot2.setNewInvItem(name, price, pub, dev, fullGenre, size, rating);
	cout << "\nThis is what you entered:" << endl;
	cout << "------------------------------------------" << endl;
	tempSlot2.displayNewGame();
	cout << "\nAny errors? (Y/N) ";
	cin >> error;
	toupper(error);
	if (error == 'Y') {
		cout << "We will need to delete the entry and start again" << endl;
		removeInvItem(inventory, genres1, genres2, genres3);
		cout << "The entry has been deleted! Choose the option '11' from the main menu if you want to try again" << endl;
	}
	else {
		cout << "Well done! Writing the new info to your files now.." << endl;
		writeInvToFiles(inventory, genres1, genres2, genres3);
	}
}
void writeInvToFiles(vector<Inventory> inventory, vector<string> genres1, vector<string> genres2, vector<string> genres3) {
	fstream writeNames, writePrices, writePubs, writeDevs, writeGenre1, writeGenre2, writeGenre3, writeSizes, writeRatings;

	writeNames.open("names.txt", ios::out); writePrices.open("prices.txt", ios::out); writePubs.open("pubs.txt", ios::out);
	writeDevs.open("devs.txt", ios::out); writeGenre1.open("genre1.txt", ios::out); writeGenre2.open("genre2.txt", ios::out);
	writeGenre3.open("genre3.txt", ios::out); writeSizes.open("sizes.dat", ios::out | ios::binary); writeRatings.open("ratings.dat", ios::out || ios::binary);

	for (int i = 0; i < inventory.size(); i++) {
		writeNames << inventory[i].getInvName() << "\n";
		writePrices << inventory[i].getInvPrice() << "\n";
		writePubs << inventory[i].getInvPub() << "\n";
		writeDevs << inventory[i].getInvDev() << "\n";
		writeGenre1 << genres1[i] << "\n";
		writeGenre2 << genres2[i] << "\n";
		writeGenre3 << genres3[i] << "\n";
		writeSizes << inventory[i].getInvSize() << "\n";
		writeRatings << inventory[i].getInvRate() << "\n";
	}
	cout << "Your inventory files have been updated!" << endl << endl;

	writeNames.close(); writePrices.close(); writePubs.close(); writeDevs.close(); writeGenre1.close();
	writeGenre2.close(); writeGenre3.close(); writeSizes.close(); writeRatings.close();
}
void editInvItem(vector<Inventory>& inventory, vector<string>& genres1, vector<string>& genres2, vector<string>& genres3) {
	Inventory tempSlot;
	string search, name, pub, dev, fullGenre;
	double price, size, rating;
	int found;
	char yn;
	do {
		cout << "Enter the name of the game you would like to edit the information for:" << endl;
		cin.ignore(100, '\n');
		getline(cin, search);
		found = searchName(inventory, search);
		if (found > -1) {
			cout << "FOUND:" << endl;
			inventory[found].displayInv();
			do {
				cout << "\nEnter the new information for this game:" << endl;
				cout << "Name: ";
				getline(cin, name);
				cout << "Price: ";
				cin >> price;
				cout << "Publisher: ";
				cin.ignore(50, '\n');
				getline(cin, pub);
				cout << "Developer: ";
				getline(cin, dev);
				fullGenre = genreEdit(genres1, genres2, genres3, found);
				cout << "\nSize of the game:" << endl;
				cin >> size;
				cout << "\nPersonal rating out of 5 (use 0 if not played enough to rate):" << endl;
				cin >> rating;
				tempSlot.storeInvItem(name, price, pub, dev, fullGenre, size, rating);
				cout << "\nIs everything correct?" << endl;
				tempSlot.displayInv();
				cout << "\nY/N : ";
				cin >> yn;
				toupper(yn);
				while (yn != 'Y' || yn != 'N') {
					cout << "Inavild input! Enter 'Y' or 'N' only!" << endl;
					cin >> yn;
					toupper(yn);
				}
				if (yn == 'Y')
					inventory[found] = tempSlot;
				else
					cout << "Starting over.." << endl << endl;
			} while (yn == 'N');
			cout << "The new information is now stored!" << endl << endl;
		}
		else {
			cout << "The game you are trying to edit could not be found.." << endl;
			cout << "Would you like to try again? (Y/N):";
			cin >> yn;
		}
	} while (yn == 'Y');

}
void removeInvItem(vector<Inventory> &inventory, vector<string>& genres1, vector<string>& genres2, vector<string>& genres3) {
	int x = 0;
	string nameSearch;
	cout << "Please enter the name of the game you want to remove" << endl;
	cin.ignore(100, '\n');
	getline(cin, nameSearch);
	for (int i = 0; i < inventory.size(); i++) {
		inventory[i].getInvName();
		if (nameSearch == inventory[i].getInvName())
			x = i;
	}
	inventory.erase(inventory.begin() + x);
	genres1.erase(genres1.begin() + x);
	genres2.erase(genres2.begin() + x);
	genres3.erase(genres3.begin() + x);
}


int wlMenu() {
	int choice = 0;
	cout << "***********************************" << endl;
	cout << "****---- WISHLIST  MANAGER ----****" << endl;
	cout << "***********************************" << endl << endl;
	cout << "What would you like to do?" << endl;
	cout << "0. Return to the main menu" << endl;
	cout << "1. Show the full wishlist" << endl;
	cout << "2. Show the game names only" << endl;
	cout << "3. Search for a specific game" << endl;
	cout << "4. Show release dates for upcoming games" << endl;
	cout << "5. Add a game" << endl;
	cout << "6. Move a game from the wishlist to your inventory" << endl;
	cout << "7. Remove a game" << endl;
	cout << "Enter your choice now: " << endl;
	cin >> choice;
	while (choice > 7 || choice < 0) {
		cout << "Please enter a valid choice (0 - 7): ";
		cin >> choice;
	}
	cout << "\n";
	return choice;
}
void getFullWishlist(vector<Wishlist>& wishlist, vector<string>& genres1, vector<string>& genres2, vector<string>& genres3) {
	double price, size;
	string name, pub, dev, genre1, genre2, genre3, fullGenre, release;
	fstream readNames, readPrices, readPubs, readDevs, readGenre1, readGenre2, readGenre3, readSizes, readDates;

	readNames.open("namesWL.txt", ios::in); readPrices.open("pricesWL.txt", ios::in); readPubs.open("pubsWL.txt", ios::in);
	readDevs.open("devsWL.txt", ios::in); readGenre1.open("genre1WL.txt", ios::in); readGenre2.open("genre2WL.txt", ios::in);
	readGenre3.open("genre3WL.txt", ios::in); readSizes.open("sizesWL.txt", ios::in); readDates.open("datesWL.txt", ios::in);

	while (getline(readNames, name)) {
		Wishlist tempSlot;
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
		readDates >> release;
		tempSlot.storeWLitem(name, price, pub, dev, fullGenre, size, release);
		wishlist.push_back(tempSlot);
	}
	readNames.close(); readPrices.close(); readPubs.close(); readDevs.close();
	readGenre1.close(); readGenre2.close(); readGenre3.close(); readSizes.close(); readDates.close();
}
void showFullWishlist(vector<Wishlist> wishlist) {
	for (int i = 0; i < wishlist.size(); i++) {
		wishlist.at(i).displayWL();
	}
	cout << "\n";
}
void showWishlistNames(vector<Wishlist> wishlist) {

}
void searchWishlist(vector<Wishlist> wishlist) {

}


string genreSelection(vector<string> &genres1, vector<string> &genres2, vector<string> &genres3) {
	string genre1c, genre2c, genre3c, fullGenre;
	string genre1[] = { "Action", "Strategy", "Turn - Based", "Simulation" };
	string genre2[] = { "Adventure", "Platformer", "Arcade", "Deck-Builder", "Puzzle" };
	string genre3[] = { "Roguelike", "Fighting", "RPG", "Platformer", "Survival", "Exploration", "Lifestyle" };
	int genre1m, genre2m, genre3m;
	cout << "\nEnter the number that corresponds with your choice for each genre category" << endl;
	cout << "1st genre category (of 3)" << endl;
	cout << "1.Action |2. Strategy |3. Turn-Based |4. Simulation" << endl;
	cin >> genre1m;
	while (genre1m > 4 || genre1m < 1) {
		cout << "Invalid number entered! Try again.." << endl;
		cin >> genre1m;
	}
	genre1c = genre1[genre1m - 1];
	cout << "\n2nd genre category (of 3)" << endl;
	cout << "1.Adventure |2. Platformer |3. Arcade |4. Deck-Builder |5. Puzzle" << endl;
	cin >> genre2m;
	while (genre2m > 5 || genre2m < 1) {
		cout << "Invalid number entered! Try again.." << endl;
		cin >> genre2m;
	}
	genre2c = genre2[genre2m - 1];
	cout << "\n3rd genre category (last)" << endl;
	cout << "1. Roguelike |2. Fighting |3. RPG |4. Platformer |5. Survival |6. Exploration |7. Lifestyle" << endl;
	cin >> genre3m;
	while (genre3m > 7 || genre3m < 1) {
		cout << "Invalid number entered! Try again.." << endl;
		cin >> genre3m;
	}
	genre3c = genre3[genre3m - 1];
	fullGenre = genre1c + " " + genre2c + " " + genre3c;

	genres1.push_back(genre1c);
	genres2.push_back(genre2c);
	genres3.push_back(genre3c);

	return fullGenre;
}
string genreEdit(vector<string>& genres1, vector<string>& genres2, vector<string>& genres3, int location) {
	string genre1c, genre2c, genre3c, fullGenre;
	string genre1[] = { "Action", "Strategy", "Turn - Based", "Simulation" };
	string genre2[] = { "Adventure", "Platformer", "Arcade", "Deck-Builder", "Puzzle" };
	string genre3[] = { "Roguelike", "Fighting", "RPG", "Platformer", "Survival", "Exploration", "Lifestyle" };
	int genre1m, genre2m, genre3m;
	cout << "\nEnter the number that corresponds with your choice for each genre category" << endl;
	cout << "1st genre category (of 3)" << endl;
	cout << "1.Action |2. Strategy |3. Turn-Based |4. Simulation" << endl;
	cin >> genre1m;
	while (genre1m > 4 || genre1m < 1) {
		cout << "Invalid number entered! Try again.." << endl;
		cin >> genre1m;
	}
	genre1c = genre1[genre1m - 1];
	cout << "\n2nd genre category (of 3)" << endl;
	cout << "1.Adventure |2. Platformer |3. Arcade |4. Deck-Builder |5. Puzzle" << endl;
	cin >> genre2m;
	while (genre2m > 5 || genre2m < 1) {
		cout << "Invalid number entered! Try again.." << endl;
		cin >> genre2m;
	}
	genre2c = genre2[genre2m - 1];
	cout << "\n3rd genre category (last)" << endl;
	cout << "1. Roguelike |2. Fighting |3. RPG |4. Platformer |5. Survival |6. Exploration |7. Lifestyle" << endl;
	cin >> genre3m;
	while (genre3m > 7 || genre3m < 1) {
		cout << "Invalid number entered! Try again.." << endl;
		cin >> genre3m;
	}
	genre3c = genre3[genre3m - 1];
	fullGenre = genre1c + " " + genre2c + " " + genre3c;

	genres1[location] = genre1c;
	genres2[location] = genre2c;
	genres3[location] = genre3c;

	return fullGenre;
}

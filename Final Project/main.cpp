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
//main menu prototype
int mainMenu();
//inventory prototypes
int invMenu();
void getFullInventory(vector<Inventory> &);
void showFullInventory(vector<Inventory>);
void showNamesOnly(vector<Inventory>);
int searchName(vector<Inventory>, string);
void searchGenres(vector<Inventory>, string);
void showBacklog(vector<Inventory>);
void showTopRated(vector<Inventory>);
void searchPublisher(vector<Inventory>, string);
void searchDeveloper(vector<Inventory>, string);
void addNewGame(vector<Inventory> &);
void writeInvToFiles(vector<Inventory>);
void editInvItem(vector<Inventory>&);
void removeInvItem(vector<Inventory>&, string);

//wishlist prototypes
int wlMenu();
void getFullWishlist(vector<Wishlist>&);
void showFullWishlist(vector<Wishlist>);
void showWishlistNames(vector<Wishlist>);
int searchWLNames(vector<Wishlist>, string);
void searchWLPub(vector<Wishlist>, string);
void searchWLDev(vector<Wishlist>, string);
void searchWLGenres(vector<Wishlist>, string);
void showUpcomingGames(vector<Wishlist>);
void addGameToWL(vector<Wishlist>&);
void editWLitem(vector<Wishlist>&);
void removeWLitem(vector<Wishlist>&);
void moveToInv(vector<Inventory>&, vector<Wishlist>&);
void writeWLToFiles(vector<Wishlist>);

//used for both prototypes
string genre1select();
string genre2select();
string genre3select();
string fullGenreMaker(string, string, string);
//enumerators for menu options
enum Menu {//main menu
	EXIT,
	INVENTORY,
	WISHLIST
};
enum Search {//search menu
	RETURN,
	NAME,
	PUB,
	DEV,
	GENRE
};
enum Manage {//single game management menu
	CANCEL,
	ADD,
	EDIT,
	REMOVE
};
//templates for calculating values
template<class S>
double getTotalSizeNeeded(S inventory) {
	double totalSize = 0.0, tempSize = 0.0;
	for (int i = 0; i < inventory.size(); i++) {
		tempSize = inventory.at(i).getInvSize();
		if (tempSize > 32)
			tempSize = tempSize / 1000;
		totalSize += tempSize;
	}
	return ceil(totalSize);//return the total amount of storage space needed, rounded up (math function!)
}
template<class V>
double getTotalValue(V inventory) {
	double totalValue = 0.0;
	for (int i = 0; i < inventory.size(); i++) {
		totalValue += inventory.at(i).getInvPrice();
	}
	return totalValue;//return the total value of all the games in the inventory
}

int main() 
{
	//declaring variables, enums and vectors needed in the main function
	Menu menuEnum;
	Search searchEnum;
	Manage manageEnum;
	int totalNumGames = 0, choice = 0, mainChoice = 0, searchChoice = 0, manageChoice = 0, foundNameLoc;
	double totalSize, totalValue;
	string nameSearch, genreSearch, pubSearch, devSearch;
	char yn;
	vector<Inventory> inventory;
	vector<Wishlist> wishlist;
	//retrieves the data from the files and stores in vectors
	getFullInventory(inventory);
	getFullWishlist(wishlist);
	//intro display on startup
	cout << "***********************************************************" << endl;
	cout << "* NINTENDO SWITCH INDIE GAME INVENTORY & WISHLIST MANAGER *" << endl;
	cout << "***********************************************************" << endl << endl;
	cout << "Welcome to you 'NINDIE' game inventory & wish list manager!" << endl << endl;
	menuEnum = static_cast<Menu>(mainMenu());//display the main menu and convert input to enum
	while (menuEnum != EXIT) {
		switch (menuEnum)//switch for main menu
		{
		case EXIT: return(0);
			break;
		case INVENTORY://takes the user to the menu for the inventory
			choice = invMenu();
			while (choice != 0) {
				switch (choice)//switch for inventory menu
				{
				case 0://send user back to previous menu
					cout << "Returning to main menu..." << endl << endl;
					break;
				case 1://display the full inventory
					showFullInventory(inventory);
					break;
				case 2://show game names only
					showNamesOnly(inventory);
					break;
				case 3://search options
					searchChoice = searchMenu();
					searchEnum = static_cast<Search>(searchChoice);
					switch (searchEnum)//switch for search options menu
					{
					case NAME://searching by name
						cout << "Please enter the name of the game you want to search for (case-sensitive):" << endl;
						cin.ignore(50, '\n');
						getline(cin, nameSearch);
						foundNameLoc = searchName(inventory, nameSearch);
						if (foundNameLoc > -1)
							inventory[foundNameLoc].displayInv();
						else
							cout << "Game not found! Check your spelling or get on the eShop and buy it!" << endl;
						break;
					case PUB://searching by publisher
						searchPublisher(inventory);
						break;
					case DEV://searching by developer
						searchDeveloper(inventory);
						break;
					case GENRE://searching by genre
						searchGenres(inventory);
						break;
					case RETURN://send user back to previous menu
						cout << "Returning to previous menu.." << endl << endl;
						break;
					default:
						break;
					}
					break;
				case 4://calculate total size needed to install all games
					totalSize = getTotalSizeNeeded(inventory);
					cout << "You will need about " << totalSize << " GBs of storage space to install all your games at once!" << endl;
					break;
				case 5://calculate total value of all the owned games
					totalValue = getTotalValue(inventory);
					cout << "The total value of you full library of games is $" << setprecision(2) << fixed << totalValue << endl;
					cout << "**SPOUSAL DISCLAIMER** 90% of these games were purchased while on sale, love you! :)" << endl;
					break;
				case 6://shows games with a '0' rating (games in the 'backlog')
					showBacklog(inventory);
					break;
				case 7://shows games with a rating of '4.7' or better
					showTopRated(inventory);
					break;
				case 8://manage a single entry
					manageChoice = manageMenu();
					manageEnum = static_cast<Manage>(manageChoice);
					switch (manageEnum)//switch for game management menu
					{
					case CANCEL://send user to previous menu
						cout << "Returning to previous menu.." << endl << endl;
						break;
					case ADD://add a new game
						addNewGame(inventory);
						break;
					case EDIT://edit a game's info
						editInvItem(inventory);
						break;
					case REMOVE://delete a game
						cout << "Please enter the name of the game you want to remove" << endl;
						cin.ignore(100, '\n');
						getline(cin, nameSearch);
						removeInvItem(inventory, nameSearch);
						break;
					default:
						break;
					}
					break;
				default:
					break;
				}
				choice = invMenu();//displays inventory menu again
			}
			break;
		case WISHLIST://takes the user to the menu for the wishlist
			choice = wlMenu();//display the wishlist menu
			while (choice != 0) {
				switch (choice)//switch for the wishlist menu options
				{
				case 0://send user back to previous menu
					cout << "Returning to the main menu..." << endl << endl;
					break;
				case 1://show full wishlist
					showFullWishlist(wishlist);
					break;
				case 2://show the game names only
					showWishlistNames(wishlist);
					break;
				case 3://search options menu
					searchChoice = searchMenu();
					searchEnum = static_cast<Search>(searchChoice);
					switch (searchEnum)//switch for the search options
					{
					case NAME://search by name
						cout << "Please enter the name of the game you want to search for (case-sensitive):" << endl;
						cin.ignore(50, '\n');
						getline(cin, nameSearch);
						foundNameLoc = searchWLNames(wishlist, nameSearch);
						if (foundNameLoc > -1)
							wishlist[foundNameLoc].displayWL();
						else
							cout << "Game not found! Check your spelling or get on the eShop and buy it!" << endl;
						break;
					case PUB://search by publisher
						cout << "Please enter the publisher you would like to search for (case-sensitive):" << endl;
						cin.ignore(50, '\n');
						getline(cin, pubSearch);
						searchWLPub(wishlist, pubSearch);
						break;
					case DEV://search by developer
						cout << "Please enter the developer you would like to search for (case-sensitive):" << endl;
						cin.ignore(50, '\n');
						getline(cin, devSearch);
						searchWLDev(wishlist, devSearch);
						break;
					case GENRE://search by genre
						cout << "Please enter the genre you would like to search for (case-sensitive):" << endl;
						cin.ignore(50, '\n');
						getline(cin, genreSearch);
						searchWLGenres(wishlist, genreSearch);
						break;
					case RETURN://send user to previous menu
						cout << "Returning to previous menu.." << endl << endl;
						break;
					default:
						break;
					}
					break;
				case 4://show only games that have not been released yet
					showUpcomingGames(wishlist);
					break;
				case 5://manage a single entry
					manageChoice = manageMenu();
					manageEnum = static_cast<Manage>(manageChoice);
					switch (manageEnum)//switch for game management menu
					{
					case CANCEL://send user to previous menu
						cout << "Returning to previous menu.." << endl << endl;
						break;
					case ADD://add a new game
						addGameToWL(wishlist);
						break;
					case EDIT://edit a game's info
						editWLitem(wishlist);
						break;
					case REMOVE://delete a game or move it to the inventory
						cout << "Would you like to move the game to your inventory? (Y/N)" << endl;
						yn = yesNo(yn);//validates the input char and returns an uppercase 'Y' or 'N'
						if (yn == 'Y')
							moveToInv(inventory, wishlist);//move the game from the wishlist to the inventory
						else
							removeWLitem(wishlist);//delete the entry form the wishlist
						break;
					default:
						break;
					}
					break;
				default:
					break;
				}
				choice = wlMenu();//display the WL menu again
			}
			break;
		default:
			break;
		}
		menuEnum = static_cast<Menu>(mainMenu());//display the main menu again and convert input to enum
	}
}
int mainMenu() {//main menu for choosing inventory or wishlist
	int choice;
	cout << "Which library would you like to manage?" << endl;
	cout << "Enter '1' for INVENTORY | '2' for WISHLIST | '0' to EXIT: ";
	choice = validate(0, 2);
	return choice;
}
int invMenu() {//inventory menu
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
	choice = validate(0, 8);
	cout << "\n";
	return choice;
}
int searchMenu() {//function for the search menu
	int choice = 0;
	cout << "What would you like to search by?" << endl;
	cout << "1. NAME	|2.	PUBLISHER |3. DEVELOPER |4. GENRE	|0. CANCEL SEARCH" << endl;
	choice = validate(0, 4);
	return choice;
}
int manageMenu() {//item management menu
	int choice = 0;
	cout << "What would you like to do?" << endl;
	cout << "1. ADD		|2. EDIT	|3. REMOVE	|0. CANCEL " << endl;
	choice = validate(0, 3);
	return choice;
}
void getFullInventory(vector<Inventory> &inventory) {//function to read the inventory files and store the info in a vector of Inventory class objects	
	double price, size, rating;
	string name, pub, dev, genre1, genre2, genre3, fullG;
	fstream readNames, readPrices, readPubs, readDevs, readGenre1, readGenre2, readGenre3, readSizes, readRatings;

	readNames.open("names.txt", ios::in); readPrices.open("prices.txt", ios::in); readPubs.open("pubs.txt", ios::in); 
	readDevs.open("devs.txt", ios::in);readGenre1.open("genre1.txt", ios::in); readGenre2.open("genre2.txt", ios::in); 
	readGenre3.open("genre3.txt", ios::in); readSizes.open("sizes.dat", ios::in | ios::binary); readRatings.open("ratings.txt", ios::in);

	while (getline(readNames, name)) {//loops while there is a game name to pull
		Inventory tempSlot;
		readPrices >> price;
		getline(readPubs, pub);
		getline(readDevs, dev);
		getline(readGenre1, genre1);
		getline(readGenre2, genre2);
		getline(readGenre3, genre3);
		fullG = fullGenreMaker(genre1, genre2, genre3);//combines the 3 genres into 1 for ease of displaying later
		readSizes >> size;
		readRatings >> rating;
		tempSlot.storeInvItem(name, price, pub, dev, genre1, genre2, genre3, fullG, size, rating);//stores the read info in an Inventory variable
		inventory.push_back(tempSlot);//puts the info in the inventory vector
	}
	readNames.close(); readPrices.close(); readPubs.close(); readDevs.close();
	readGenre1.close(); readGenre2.close(); readGenre3.close(); readSizes.close(); readRatings.close();
}
void showFullInventory(vector<Inventory> inventory) {//shows the full ionventory
	for (int i = 0; i < inventory.size(); i++) {
		inventory.at(i).displayInv();
	}
	cout << "\n";
}
void showNamesOnly(vector<Inventory> inventory) {//shows only the names for the full inventory
	for (int i = 0; i < inventory.size(); i++) {
		cout << inventory[i].getInvName() << endl;
	}
	cout << "\n";
}
int searchName(vector<Inventory> inventory, string nameSearch) {//searches the inventory and returns an int indicating vector location
	for (int i = 0; i < inventory.size(); i++) {
		inventory[i].getInvName();
		if (nameSearch == inventory[i].getInvName())
			return i;
	}
	return -1;
}
void searchGenres(vector<Inventory> inventory) {//searched through the inventory for a specific genre and displays all instances
	bool found = false;
	string genreSearch;
	cout << "Please enter the genre you would like to search for (case-sensitive):" << endl;
	cin.ignore(50, '\n');
	getline(cin, genreSearch);
	cout << "Showing all owned games with the genre containing '" << genreSearch << "'..." << endl;
	cout << "----------------------------------------------------------------------" << endl;
	for (int i = 0; i < inventory.size(); i++) {
		if (inventory[i].getInvGenre() == genreSearch || inventory[i].getInvGenre2() == genreSearch || inventory[i].getInvGenre3() == genreSearch) {
			cout << setw(40) << right << inventory[i].getInvName() << " - " << setw(40) << left << inventory[i].getFullG() << endl;
			found = true;
		}
	}
	if (found != true)
		cout << "No games found with '" << genreSearch << "' in the genre. Please check the spelling.." << endl;
}
void showBacklog(vector<Inventory> inventory) {//displays all games with a rating of '0'
	double select = 1;
	cout << "These are all the games in your backlog (games you havent played enough to provide a rating)" << endl;
	cout << "--------------------------------------------------------------------------------------------" << endl;
	for (int i = 0; i < inventory.size(); i++) {
		select = inventory[i].getInvRate();
		if (select == 0.0)
			cout << inventory[i].getInvName() << endl;
	}
}
void showTopRated(vector<Inventory> inventory) {//shows only the games rated '4.7' or higher
	double select = 0.0;
	cout << "These are all your games that have a (self-declared) rating of at least 4.7 out of 5 along with their publishers" << endl;
	cout << "----------------------------------------------------------------------------------------------------------------" << endl;
	for (int i = 0; i < inventory.size(); i++) {
		select = inventory[i].getInvRate();
		if (select >= 4.7)
			cout << setw(40) << right << inventory[i].getInvName() << " - " << setw(3) << setprecision(1) << fixed << left << inventory[i].getInvRate() << " - " << setw(40) << left << inventory[i].getInvPub() << endl;
	}
}
void searchPublisher(vector<Inventory> inventory) {//searchs the inventory for a specific publisher
	string pubSearch;
	bool found = false;
	cout << "Please enter the publisher you would like to search for (case-sensitive):" << endl;
	cin.ignore(50, '\n');
	getline(cin, pubSearch);
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
void searchDeveloper(vector<Inventory> inventory) {//searches the inventory for a specific developer
	string devSearch;
	bool found = false;
	cout << "Please enter the developer you would like to search for (case-sensitive):" << endl;
	cin.ignore(50, '\n');
	getline(cin, devSearch);
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
void addNewGame(vector<Inventory> &inventory) {//adds a new game to the inventory
	Inventory tempSlot, tempSlot2;
	char error;
	string name, pub, dev, genre1, genre2, genre3, fullG;
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
	genre1 = genre1select();
	genre2 = genre2select();
	genre3 = genre3select();
	fullG = fullGenreMaker(genre1, genre2, genre3);
	cout << "\nSize of the game:" << endl;
	cin >> size;
	cout << "\nPersonal rating out of 5 (use 0 if not played enough to rate):" << endl;
	cin >> rating;
	tempSlot.setNewInvItem(name, price, pub, dev, genre1, genre2, genre3, fullG, size, rating);
	cout << "\nThis is what you entered:" << endl;
	cout << "------------------------------------------" << endl;
	tempSlot.displayNewGame();
	cout << "\nIs everything correct? (Y/N) ";
	error = yesNo(error);
	if (error == 'N') {
		cout << "The info has not been stored. Choose option '11' from the main menu if you want to try again" << endl;
	}
	else {
		inventory.push_back(tempSlot);
		cout << "Well done! Writing the new info to your files now.." << endl;
		writeInvToFiles(inventory);
	}
}
void writeInvToFiles(vector<Inventory> inventory) {//writes the information in the inventory vector to each respective file
	fstream writeNames, writePrices, writePubs, writeDevs, writeGenre1, writeGenre2, writeGenre3, writeSizes, writeRatings;

	writeNames.open("names.txt", ios::out); writePrices.open("prices.txt", ios::out); writePubs.open("pubs.txt", ios::out);
	writeDevs.open("devs.txt", ios::out); writeGenre1.open("genre1.txt", ios::out); writeGenre2.open("genre2.txt", ios::out);
	writeGenre3.open("genre3.txt", ios::out); writeSizes.open("sizes.dat", ios::out | ios::binary); writeRatings.open("ratings.txt", ios::out);

	for (int i = 0; i < inventory.size(); i++) {
		writeNames << inventory[i].getInvName() << "\n";
		writePrices << inventory[i].getInvPrice() << "\n";
		writePubs << inventory[i].getInvPub() << "\n";
		writeDevs << inventory[i].getInvDev() << "\n";
		writeGenre1 << inventory[i].getInvGenre() << "\n";
		writeGenre2 << inventory[i].getInvGenre2() << "\n";
		writeGenre3 << inventory[i].getInvGenre3() << "\n";
		writeSizes << inventory[i].getInvSize() << "\n";
		writeRatings << inventory[i].getInvRate() << "\n";
	}
	cout << "Your inventory files have been updated!" << endl << endl;

	writeNames.close(); writePrices.close(); writePubs.close(); writeDevs.close(); writeGenre1.close();
	writeGenre2.close(); writeGenre3.close(); writeSizes.close(); writeRatings.close();
}
void editInvItem(vector<Inventory>& inventory) {//edits the information of a signle game
	Inventory tempSlot;
	string search, name, pub, dev, genre1, genre2, genre3, fullG;
	double price, size, rating;
	int found;
	char yn, again;
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
				genre1 = genre1select();
				genre2 = genre2select();
				genre3 = genre3select();
				fullG = fullGenreMaker(genre1, genre2, genre3);
				cout << "\nSize of the game:" << endl;
				cin >> size;
				cout << "\nPersonal rating out of 5 (use 0 if not played enough to rate):" << endl;
				cin >> rating;
				tempSlot.storeInvItem(name, price, pub, dev, genre1, genre2, genre3, fullG, size, rating);
				cout << "\nIs everything correct?" << endl;
				tempSlot.displayInv();
				cout << "\nY/N : ";
				yn = yesNo(yn);
				if (yn == 'Y') {
					inventory[found] = tempSlot;
				}
				else
					cout << "Starting over.." << endl << endl;
			} while (yn == 'N');
			writeInvToFiles(inventory);
			cout << "The new information is now stored!" << endl << endl;
		}
		else {
			cout << "The game you are trying to edit could not be found.." << endl;
			cout << "Would you like to try again? (Y/N):";
			again = yesNo(again);
		}
	} while (again == 'Y');

}
void removeInvItem(vector<Inventory> &inventory, string nameSearch) {//removes a single game from the inventory
	int x = -1;
	x = searchName(inventory, nameSearch);
	if (x > -1) {
		inventory.erase(inventory.begin() + x);
		cout << "The game " << inventory[x].getInvName() << " has been removed from your inventory.." << endl;
		writeInvToFiles(inventory);
		cout << "..And your files have been updated" << endl;
	}
	else {
		cout << "Game not found.." << endl;
	}
}


int wlMenu() {//displays the wishlist menu and return an int
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
	cout << "5. Manage a single entry" << endl;
	cout << "Enter your choice now: " << endl;
	choice = validate(0, 5);
	cout << "\n";
	return choice;
}
void getFullWishlist(vector<Wishlist>& wishlist) {//gets the full wishlist from the files and stores the info in a vector
	double price, size;
	string name, pub, dev, genre1, genre2, genre3, fullG, release;
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
		getline(readGenre2, genre2);
		getline(readGenre3, genre3);
		fullG = fullGenreMaker(genre1, genre2, genre3);
		readSizes >> size;
		readDates >> release;
		tempSlot.storeWLitem(name, price, pub, dev, genre1, genre2, genre3, fullG, size, release);
		wishlist.push_back(tempSlot);
	}
	readNames.close(); readPrices.close(); readPubs.close(); readDevs.close();
	readGenre1.close(); readGenre2.close(); readGenre3.close(); readSizes.close(); readDates.close();
}
void showFullWishlist(vector<Wishlist> wishlist) {//displays the full wishlist
	for (int i = 0; i < wishlist.size(); i++) {
		wishlist.at(i).displayWL();
	}
	cout << "\n";
}
void showWishlistNames(vector<Wishlist> wishlist) {//shows only the names of the games in the wishlist
	for (int i = 0; i < wishlist.size(); i++) {
		cout << wishlist[i].getWLName() << endl;
	}
	cout << "\n";
}
int searchWLNames(vector<Wishlist> wishlist, string nameSearch) {//searches the wishlist for a specific name and returns an int 
	for (int i = 0; i < wishlist.size(); i++) {
		wishlist[i].getWLName();
		if (nameSearch == wishlist[i].getWLName())
			return i;
	}
	return -1;
}
void searchWLPub(vector<Wishlist> wishlist, string pubSearch) {//searches the wishlist for a specific publisher
	bool found = false;
	cout << "Showing all owned games published by '" << pubSearch << "' and their developers" << endl;
	cout << "----------------------------------------------------------------------------" << endl;
	for (int i = 0; i < wishlist.size(); i++) {
		if (wishlist[i].getWLPub() == pubSearch) {
			cout << setw(40) << right << wishlist[i].getWLName() << " - " << setw(40) << left << wishlist[i].getWLDev() << endl;
			found = true;
		}
	}
	if (found != true)
		cout << "No games found published by '" << pubSearch << "'. Please check the spelling, or get some!" << endl;
}
void searchWLDev(vector<Wishlist> wishlist, string devSearch) {//searches the wishlist for a specific developer
	bool found = false;
	cout << "Showing all owned games published by '" << devSearch << "' and their publishers" << endl;
	cout << "----------------------------------------------------------------------------" << endl;
	for (int i = 0; i < wishlist.size(); i++) {
		if (wishlist[i].getWLDev() == devSearch) {
			cout << setw(40) << right << wishlist[i].getWLName() << " - " << setw(40) << left << wishlist[i].getWLDev() << endl;
			found = true;
		}
	}
	if (found != true)
		cout << "No games found developed by '" << devSearch << "'. Please check the spelling, or get some!" << endl;
}
void searchWLGenres(vector<Wishlist>wishlist, string genreSearch) {//searches the wishlist for a specific genre
	bool found = false;
	cout << "Showing all owned games with the genre containing '" << genreSearch << "'..." << endl;
	cout << "----------------------------------------------------------------------" << endl;
	for (int i = 0; i < wishlist.size(); i++) {
		if (wishlist[i].getWLGenre() == genreSearch || wishlist[i].getWLGenre2() == genreSearch || wishlist[i].getWLGenre3() == genreSearch) {
			cout << setw(40) << right << wishlist[i].getWLName() << " - " << setw(40) << left << wishlist[i].getWLFullG() << endl;
			found = true;
		}
	}
	if (found != true)
		cout << "No games found with '" << genreSearch << "' in the genre. Please check the spelling.." << endl;
}
void showUpcomingGames(vector<Wishlist> wishlist) {//shows only the games that are not currently available
	string found;
	for (int i = 0; i < wishlist.size(); i++) {
		found = wishlist[i].getWLAvail();
		if (found != "YES") {
			cout << wishlist[i].getWLName() << " Releasing: " << wishlist[i].getWLAvail();
		}
	}
	cout << "\n";
}
void addGameToWL(vector<Wishlist>& wishlist) {//adds a game to the wishlist
	Wishlist tempSlot, tempSlot2;
	char error;
	string name, pub, dev, genre1, genre2, genre3, fullG, avail;
	double price, size;
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
	genre1 = genre1select();
	genre2 = genre2select();
	genre3 = genre3select();
	fullG = fullGenreMaker(genre1, genre2, genre3);
	cout << "\nSize of the game:" << endl;
	cin >> size;
	cout << "\nAvailabilty (enter the date as 'mm/dd/yy', or 'YES' if already released" << endl;
	cin.ignore(100, '\n');
	getline(cin, avail);
	tempSlot.storeWLitem(name, price, pub, dev, genre1, genre2, genre3, fullG, size, avail);
	cout << "\nThis is what you entered:" << endl;
	cout << "------------------------------------------" << endl;
	tempSlot.displayWL();
	cout << "\nIs everything correct? (Y/N) ";
	error = yesNo(error);
	if (error == 'N') {
		cout << "The info has not been stored. Choose option '11' from the main menu if you want to try again" << endl;
	}
	else {
		wishlist.push_back(tempSlot);
		cout << "Well done! Writing the new info to your files now.." << endl;
		writeWLToFiles(wishlist);
	}
}
void editWLitem(vector<Wishlist>& wishlist) {//edits a game's info in the wishlist
	Wishlist tempSlot;
	string search, name, pub, dev, genre1, genre2, genre3, fullG, avail;
	double price, size;
	int found;
	char yn, again;
	do {
		cout << "Enter the name of the game you would like to edit the information for:" << endl;
		cin.ignore(100, '\n');
		getline(cin, search);
		found = searchWLNames(wishlist, search);
		if (found > -1) {
			cout << "FOUND:" << endl;
			wishlist[found].displayWL();
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
				genre1 = genre1select();
				genre2 = genre2select();
				genre3 = genre3select();
				fullG = fullGenreMaker(genre1, genre2, genre3);
				cout << "\nSize of the game:" << endl;
				cin >> size;
				cout << "\nIs this games avaialble now? Enter 'YES' or the date it will be available in this format: mm/dd/yy" << endl;
				cin.ignore(100, '\n');
				getline(cin, avail);
				tempSlot.storeWLitem(name, price, pub, dev, genre1, genre2, genre3, fullG, size, avail);
				cout << "\nIs everything correct?" << endl;
				tempSlot.displayWL();
				cout << "\nY/N : ";
				yn = yesNo(yn);
				if (yn == 'Y') {
					wishlist[found] = tempSlot;
				}
				else
					cout << "Starting over.." << endl << endl;
			} while (yn == 'N');
			writeWLToFiles(wishlist);
			cout << "The new information is now stored!" << endl << endl;
		}
		else {
			cout << "The game you are trying to edit could not be found.." << endl;
			cout << "Would you like to try again? (Y/N):";
			again = yesNo(again);
		}
	} while (again == 'Y');
}
void moveToInv(vector<Inventory>& inventory, vector<Wishlist>& wishlist) {//moves a game from the inventory to the wishlist
	Inventory tempInvSlot;
	int found;
	string nameSearch, name, pub, dev, genre1, genre2, genre3, fullG;
	string nameWL, pubWL, devWL;
	double price, size, rating = 0;
	char yn;

	cout << "Enter the name of the game you would like to move from your wishlist to your inventory:" << endl;
	cin.ignore(100, '\n');
	getline(cin, nameSearch);
	found = searchWLNames(wishlist, nameSearch);
	if (found > -1) {
		cout << "FOUND!" << endl;
		wishlist[found].displayWL();
		cout << "\nPlease confirm this game was purchased and should be moved to your inventory. (Y/N)" << endl;
		yn = yesNo(yn);
		name = wishlist[found].getWLName();
		price = wishlist[found].getWLPrice();
		pub = wishlist[found].getWLPub();
		dev = wishlist[found].getWLDev();
		genre1 = wishlist[found].getWLGenre();
		genre2 = wishlist[found].getWLGenre2();
		genre3 = wishlist[found].getWLGenre3();
		fullG = fullGenreMaker(genre1, genre2, genre3);
		size = wishlist[found].getWLSize();
		tempInvSlot.storeInvItem(name, price, pub, dev, genre1, genre2, genre3, fullG, size, rating);
		inventory.push_back(tempInvSlot);
		cout << "The game has been added to your inventory.." << endl;
		wishlist.erase(wishlist.begin() + found);
		cout << "..And removed from your wishlist" << endl << endl;
		writeInvToFiles(inventory);
		writeWLToFiles(wishlist);
		cout << "Your inventory and wishlist files have been updated" << endl;
	}
	else {
		cout << "The game was not found in your inventory" << endl;
	}
	

}
void removeWLitem(vector<Wishlist>& wishlist, string nameSearch) {//removes a game form the wishlist
	int x = -1;
	x = searchWLNames(wishlist, nameSearch);
	if (x > -1) {
		wishlist.erase(wishlist.begin() + x);
		cout << "The game "<< wishlist[x].getWLName() << "has been removed from your wishlist.." << endl;
		writeWLToFiles(wishlist);
		cout << "..And your files have been updated" << endl;
	}
	else {
		cout << "Game not found.." << endl;
	}
	
}
void writeWLToFiles(vector<Wishlist> wishlist) {//writes the information in the wishlist vector to each respective file
	fstream writeNames, writePrices, writePubs, writeDevs, writeGenre1, writeGenre2, writeGenre3, writeSizes, writeRatings;

	writeNames.open("namesWL.txt", ios::out); writePrices.open("pricesWL.txt", ios::out); writePubs.open("pubsWL.txt", ios::out);
	writeDevs.open("devsWL.txt", ios::out); writeGenre1.open("genre1WL.txt", ios::out); writeGenre2.open("genre2WL.txt", ios::out);
	writeGenre3.open("genre3WL.txt", ios::out); writeSizes.open("sizesWL.dat", ios::out | ios::binary); writeRatings.open("datesWL.txt", ios::out || ios::binary);

	for (int i = 0; i < wishlist.size(); i++) {
		writeNames << wishlist[i].getWLName() << "\n";
		writePrices << wishlist[i].getWLPrice() << "\n";
		writePubs << wishlist[i].getWLPub() << "\n";
		writeDevs << wishlist[i].getWLDev() << "\n";
		writeGenre1 << wishlist[i].getWLGenre() << "\n";
		writeGenre2 << wishlist[i].getWLGenre2() << "\n";
		writeGenre3 << wishlist[i].getWLGenre3() << "\n";
		writeSizes << wishlist[i].getWLSize() << "\n";
		writeRatings << wishlist[i].getWLAvail() << "\n";
	}
	cout << "Your wishlist files have been updated!" << endl << endl;

	writeNames.close(); writePrices.close(); writePubs.close(); writeDevs.close(); writeGenre1.close();
	writeGenre2.close(); writeGenre3.close(); writeSizes.close(); writeRatings.close();
}


string genre1select() {//returns a string containing the first genre of a game based on user input
	string genre1c;
	string genre1[] = { "Action", "Strategy", "Turn - Based", "Simulation" };
	int choice;
	cout << "\nEnter the number that corresponds with your choice for each genre category" << endl;
	cout << "1st genre category (of 3)" << endl;
	cout << "1.Action |2. Strategy |3. Turn-Based |4. Simulation" << endl;
	choice = validate(1, 4);
	genre1c = genre1[choice - 1];
	return genre1c;
}
string genre2select() {//returns a string containing the second genre of a game based on user input
	string genre2c;
	string genre2[] = { "Adventure", "Platformer", "Arcade", "Deck-Builder", "Puzzle" };
	int choice;
	cout << "\n2nd genre category (of 3)" << endl;
	cout << "1.Adventure |2. Platformer |3. Arcade |4. Deck-Builder |5. Puzzle" << endl;
	choice = validate(1, 5);
	genre2c = genre2[choice - 1];
	return genre2c;
}
string genre3select() {//returns a string containing the third genre of a game based on user input
	string genre3c;
	string genre3[] = { "Roguelike", "Fighting", "RPG", "Platformer", "Survival", "Exploration", "Lifestyle" };
	int choice;
	cout << "\n3rd genre category (last)" << endl;
	cout << "1. Roguelike |2. Fighting |3. RPG |4. Platformer |5. Survival |6. Exploration |7. Lifestyle" << endl;
	choice = validate(1, 7);
	genre3c = genre3[choice - 1];
	return genre3c;
}
string fullGenreMaker(string genre1, string genre2, string genre3) {//combines the 3 genres of a game into 1 string and returns it
	string fullGenre;
	fullGenre = genre1 + " " + genre2 + " " + genre3;
	return fullGenre;
}
char yesNo(char yn) {//converts a user input char to uppercase and confirms it is 'Y' or 'N'
	cin >> yn;
	yn = toupper(yn);
	while (yn != 'Y' && yn != 'N') {
		cout << "Invalid input! Please eneter 'Y' or 'N': ";
		cin >> yn;
	}
	return yn;
}
int validate(int bottom, int top) {//takes and validates user input for menus
	int choice;
	cin >> choice;
	while (choice < bottom || choice > top) {
		cout << "Invalid input! Please enter a number between " << bottom << " and " << top << endl;
		cin >> choice;
	}
	return choice;
}

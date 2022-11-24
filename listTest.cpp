#ifndef LISTTEST_CPP
#define LISTTEST_CPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include "PlayerList.h"
#include "stack.cpp"
#include "hashtable.h"
using namespace std;

void mainMenu();
void addToList();
void deleteFromList();
void createList();
void selectedRosterMenu();
void searchList();
void searchHash();

//Declaring global PlayerList instead of needing to pass one
//back and forth between functions.
PlayerList* list2 = new PlayerList;

//Declaring a global stack to be used throughout the program.
Stack teamStack;    

//Declared global ofstream object. Used to write
//the contents of the stack to a file. Line 134.
ofstream stackContents;     

//Declared global hash table for use by all functions.
HashTable testTable(10); 

//Other global variables used in multiple funcitons.
string selectedTeamFilename;


void listTest() {
    system("cls");
    int teamSelect;
    string nameLine, filenameLine;
    string teamNameArr[32];         //Array of team names in a human readable format
    string teamFilenameArr[32];     //Array of teamnames in teamname.txt format

    /*The following two loops create arrays to hold team names.
    The first array will read team names from a file in a 
    human readable format.
    The second loop reads from a file that contains the 
    filenames of the rosters for each team.*/
    ifstream teamNames("text_files/teamNames.txt");
    int i = 0;
    while (getline(teamNames, nameLine)) {
        teamNameArr[i] = nameLine;
        i++;
    }
    teamNames.close();

    ifstream teamFilenames("text_files/teamFilenames.txt");
    int j = 0;
    while (getline(teamFilenames, filenameLine)) {
        teamFilenameArr[j] = filenameLine;
        j++;
    }
    teamFilenames.close();

    //Printing the contents of the teamNameArr
    //Changes to team names are not common, so
    //the .txt file containing them is not 
    //edited by the user.
    cout << "What team would you like to view?" << endl;
    for (int i = 0; i < 32; i++) {
        cout << i+1 << ".) " << teamNameArr[i] << endl;     
    }

    //The user selects a team using the numbers provided on screen.
    //The function then decrements that selection and provides the
    //appropriate array indexes to add to the stack.
    cin >> teamSelect;
    if (teamSelect > 0 or teamSelect < 33) {
        teamSelect--;

        selectedTeamFilename = "team_filenames/" + teamFilenameArr[teamSelect];
        teamStack.push(teamNameArr[teamSelect]);
    }
    else {
        cout << "Invalid Choice" << endl;
        listTest();
    }

    createList();
    testTable.displayHash();
    selectedRosterMenu();
    // PlayerList* list1 = new PlayerList;
    // list1 = createList(list1, selectedTeamFilename);
    // selectedRosterMenu(list1, selectedTeamFilename);
}

void selectedRosterMenu(){
    int menuSelect;
    cout << "What do you want to do?" << endl;
    cout << "1.) Print Roster" << endl;
    cout << "2.) Add Player" << endl;
    cout << "3.) Remove Player" << endl;
    cout << "4.) Search Roster" << endl;
    cout << "5.) Select Another Team" << endl;
    cout << "6.) Return to Main Menu" << endl;
    cout << "7.) View Recently viewed teams" << endl;
    cout << "8.) Display hash table contents" << endl;
    cin >> menuSelect;
    cin.ignore();

    switch(menuSelect){
        case 1:
            system("cls");
            list2->displayList();
            selectedRosterMenu();
            break;

        case 2:
            addToList();
            selectedRosterMenu();
            break;
        
        case 3:
            deleteFromList();
            selectedRosterMenu();
            break;

        case 4:
            searchList();
            searchHash();
            selectedRosterMenu();
            break;

        case 5:
            //delete list;
            listTest();
            break;

        case 6:
            //delete list;
            mainMenu();
            break;

        case 7:
            system("cls");
            cout << "---Recently Viewed Teams---" << endl;
            stackContents.open("stackContents.txt", ios::out | ios::trunc);
            while (!teamStack.isEmpty())
            {
                string teamOutput;
                teamStack.pop(teamOutput);
                cout << teamOutput << endl;
                stackContents << teamOutput << endl;
            }
            system("pause");
            selectedRosterMenu();
            break;

        case 8:
            testTable.displayHash();
            break;

        default:
            cout << "Invalid Choice\n Please select again." << endl;
            selectedRosterMenu();
            break;

    }
}

/*****************************************************************************/
/*****************************************************************************/
void createList(){
    fstream file(selectedTeamFilename);
    string playerNumber, playerName, playerAge, playerPOS, tempData;
    string line;

    file.close();
    file.open(selectedTeamFilename);

    int number, age;
    while (getline(file, line)) {

        stringstream ss(line);
        getline(ss, playerNumber, ',');
        getline(ss, playerName, ',');
        getline(ss, playerAge, ',');
        getline(ss, playerPOS, ',');
        getline(ss, tempData, ',');

        if (playerNumber == "") {
            number = 0;
        }
        else {
            number = stoi(playerNumber);
        }

        if (playerAge == "") {
            age = 0;
        }
        else {
            age = stoi(playerAge);
        }

        list2->insertNode(number, playerName, age, playerPOS);
        testTable.insertItem(number, playerName, age, playerPOS);
    }  

    list2->displayList();
}

void addToList() {
    bool validInput = true;
    string playerName, playerPOS;
    int playerNum, playerAge;
    cout << "In addToList() Function" << endl;
    cout << "What is the player's name?" << endl;
    getline(cin, playerName);
    cin.ignore();

    do{
    validInput = true;
    cout << "What is the player's number?" << endl;
    cin >> playerNum;
        if(playerNum < 0 or playerNum > 99){
            cout << "Please enter a valid number (0-99)" << endl;
            validInput = false;
        }
    } while(validInput == false);

    do{
    validInput = true;
    cout << "What is the player's age?" << endl;
    cin >> playerAge;
        if(playerAge < 0 or playerAge > 99){
            cout << "Please enter a valid number (0-99)" << endl;
            validInput = false;
        }
    } while (validInput == false);
    
    cout << "What is the player's position?" << endl;
    cin >> playerPOS;

    list2->insertNode(playerNum, playerName, playerAge, playerPOS);
    list2->displayList();
    list2->writeListToFile(selectedTeamFilename);
}

void deleteFromList() {
    int numToDelete;

    cout << "Typer the number of the player to delete." << endl;
    cin >> numToDelete;

    list2->deleteNode(numToDelete);

    cout << "New list will now be displayed." << endl;
    system("pause");
    list2->displayList();
    list2->writeListToFile(selectedTeamFilename);
}

void searchList(){
    cout << "In searchList()" << endl;
    int numToSearch;
    cout << "What player number would you like to search for?" << endl;
    cin >> numToSearch;

    auto start = chrono::steady_clock::now();
    list2->searchList(numToSearch);
    auto end = chrono::steady_clock::now();
    double elapsedTime = double(::chrono::duration_cast < ::chrono::microseconds> 
        (end - start).count());
    cout << "Elapsed Time: " << elapsedTime << " microseconds." << endl;
}

void searchHash(){
    cout << "In searchHash()" << endl;
    int numToSearch;
    cout << "Enter a number to search for." << endl;
    cin >> numToSearch;
    auto start = chrono::steady_clock::now();
    testTable.searchForItem(numToSearch);
    auto end = chrono::steady_clock::now();
    double elapsedTime = double(::chrono::duration_cast < ::chrono::microseconds> 
        (end - start).count());
    cout << "Elapsed Time: " << elapsedTime << " microseconds." << endl;}

#endif

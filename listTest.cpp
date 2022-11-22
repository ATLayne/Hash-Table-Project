#ifndef LISTTEST_CPP
#define LISTTEST_CPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include "PlayerList.h"
#include "stack.cpp"
//#include "main.cpp"         //comment out for windows.
//#include "mainmenu.cpp"     //comment out for windows.
using namespace std;

void mainMenu();
PlayerList* createList(PlayerList* list, string teamName);
PlayerList* addToList(PlayerList* list, string teamName);
PlayerList* deleteFromList(PlayerList* list, string teamName);
void selectedRosterMenu(PlayerList* list, string teamName);
void searchList(PlayerList* list);

Stack teamStack;    //Declaring a global stack to be used throughout the program.
ofstream stackContents;     //Declared global ofstream object. Used to write
                            //the contents of the stack to a file. Line 134.

void listTest() {
    system("cls");
    int teamSelect;
    string selectedTeamFilename;
    string nameLine, filenameLine;
    string teamNameArr[32];         //Array of team names in a human readable format
    string teamFilenameArr[32];     //Array of teamnames in teamname.txt format

    /*The following two loops create arrays to hold team names.
    The first array will read team names from a file in a 
    human readable format.
    The second loop reads from a file that contains the 
    filenames of the rosters for each team.*/
    ifstream teamNames("teamNames.txt");
    int i = 0;
    while (getline(teamNames, nameLine)) {
        teamNameArr[i] = nameLine;
        i++;
    }
    teamNames.close();

    ifstream teamFilenames("teamFilenames.txt");
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

        selectedTeamFilename = teamFilenameArr[teamSelect];
        teamStack.push(teamNameArr[teamSelect]);
    }
    else {
        cout << "Invalid Choice" << endl;
        listTest();
    }


    PlayerList* list1 = new PlayerList;
    list1 = createList(list1, selectedTeamFilename);
    selectedRosterMenu(list1, selectedTeamFilename);
}

void selectedRosterMenu(PlayerList* list, string teamName){
    int menuSelect;
    cout << "What do you want to do?" << endl;
    cout << "1.) Print Roster" << endl;
    cout << "2.) Add Player" << endl;
    cout << "3.) Remove Player" << endl;
    cout << "4.) Search Roster" << endl;
    cout << "5.) Select Another Team" << endl;
    cout << "6.) Return to Main Menu" << endl;
    cout << "7.) View Recently viewed teams" << endl;
    cin >> menuSelect;
    cin.ignore();

    switch(menuSelect){
        case 1:
            system("cls");
            list->displayList();
            selectedRosterMenu(list, teamName);
            break;

        case 2:
            list = addToList(list, teamName);
            selectedRosterMenu(list, teamName);
            break;
        
        case 3:
            list = deleteFromList(list, teamName);
            selectedRosterMenu(list, teamName);
            break;

        case 4:
            searchList(list);
            selectedRosterMenu(list, teamName);
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
            selectedRosterMenu(list, teamName);
            break;

    }
}



/*****************************************************************************/
/*****************************************************************************/
PlayerList* createList(PlayerList* list, string teamName) {
    //declaring integer counter for number of lines in input file
    int size = 0;

    fstream file(teamName);
    string playerNumber, playerName, playerAge, playerPOS, tempData;
    string line;

    file.close();
    file.open(teamName);

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

        list->insertNode(number, playerName, age, playerPOS);
    }

    return list;
}

PlayerList* addToList(PlayerList* list, string teamName) {
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

    list->insertNode(playerNum, playerName, playerAge, playerPOS);
    list->displayList();
    list->writeListToFile(teamName);

    return list;
}

PlayerList* deleteFromList(PlayerList* list, string teamName) {
    int numToDelete;

    cout << "Typer the number of the player to delete." << endl;
    cin >> numToDelete;

    list->deleteNode(numToDelete);

    cout << "New list will now be displayed." << endl;
    system("pause");
    list->displayList();
    list->writeListToFile(teamName);

    return list;
}

void searchList(PlayerList* list){
    int numToSearch;
    cout << "What player number would you like to search for?" << endl;
    cin >> numToSearch;

    auto start = chrono::steady_clock::now();
    list->searchList(numToSearch);
    auto end = chrono::steady_clock::now();
    double elapsedTime = double(::chrono::duration_cast < ::chrono::microseconds> 
        (end - start).count());
    cout << "Elapsed Time: " << elapsedTime << " microseconds." << endl;
}

#endif

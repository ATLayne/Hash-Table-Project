//Austin Layne
//Nathaniel Moreno


#ifndef MAINMENU_CPP
#define MAINMENU_CPP
#include <stdlib.h>
#include <iostream>
#include "listTest.cpp"     //comment out for windows
using namespace std;

//Serves as a starting point for users of the program.
//simple switch statement used to call other functions 
//included in the program.
void listTest();
//void teamRecordMenu();
//void QBstatsMenu();

void mainMenu() {
    system("cls");
    cin.clear();
    int selection = 0;

        cout << "*****MAIN MENU*****\n\n";
        cout << "What do you want to do?" << endl;
        cout << "1.) Open Roster Menu" << endl;
        cout << "2.) Open Team Record Menu" << endl;
        cout << "3.) Open QB Stats Menu" << endl;
        cout << "4.) ---Quit Program---" << endl;
        cin >> selection;
        cin.ignore();

        switch (selection) {

            //This selection will take you to the menu that deals with everything
            //relating to team roster management.
            case 1:
                system("cls");
                listTest();
                break;

            //This selection will allow you to view the win/loss records of each team
            //and edit as needed.
            // case 2:
            //     system("cls");
            //     teamRecordMenu();
            //     break;
            
            //This selection allows you to view QB related stats.
            // case 3:
            //     system("cls");
            //     QBstatsMenu();
            //     break;

            //Terminates the program.
            case 4:
                system("cls");
                exit(1);
                break;

            //Default choice if the user selects the wrong menu item.
            default:
                cout << "Invalid Choice" << endl;
                system("pause");
                mainMenu();
                break;
        }
}
#endif

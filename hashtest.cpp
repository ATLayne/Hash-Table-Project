#include "hashtable.h"
#include <sstream>
#include <string>

void hashTest(){
    cout << "In hastTest()" << endl;
    fstream file("ArizonaCardinals.txt");
    string playerNumber, playerName, playerAge, playerPOS, tempData;
    string line;
    HashTable map(10);

    file.close();
    file.open("ArizonaCardinals.txt");

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
        
        map.insertItem(number, playerName, age, playerPOS);
    }

    map.displayHash();
}

#include <iostream>
#include "PlayerList.h"

class HashTable{
    //integer for the number of buckets in the map
    int BUCKET;
    //Declaring a pointer to what will become an array
    //of PlayerList linked lists
    PlayerList* table;

public:
    //Constructor
    HashTable(int num);

    //Insert item into hash table. The key will be the 
    //players number
    void insertItem(int number, string playerName, 
                    int age, string playerPOS);
    
    void deleteItem(int key);

    void searchForItem(int key);

    //Determines the hash funciton. Created based on number
    //of buckets
    int hashFunction(int x){
        return (x % BUCKET);
    }

    void displayHash();
};

HashTable::HashTable(int num){
    this->BUCKET = num;
    table = new PlayerList[BUCKET];
}

void HashTable::insertItem(int number, string playerName, 
                           int age, string playerPOS)
{
    int index = hashFunction(number);
    table[index].insertNode(number, playerName, age, playerPOS);
}

void HashTable::searchForItem(int key){
    int index = hashFunction(key);
    table[index].searchList(key);
}

void HashTable::displayHash(){
    for (int i = 0; i < BUCKET; i++) {
	cout << "Bucket: " << i;
	table[i].displayList();
}
}

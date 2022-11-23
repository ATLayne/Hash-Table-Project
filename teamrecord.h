// File that creates a struct for TeamRecord.
//Austin Layne
//Nathaniel Moreno

// TeamRecord holds win/loss/tie data on each
// team.

#ifndef TEAMRECORD_H
#define TEAMRECORD_H
#include <iostream>
#include <string>
using namespace std;

struct TeamRecord
{
    string teamName;
    double win = 0, loss = 0, tie = 0;
    double percentage = 0;
};


#endif

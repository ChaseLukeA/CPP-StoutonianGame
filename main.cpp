// ---------------------------------------------------------------------------
//
//                   University of Wisconsin-Stout
//            Mathematics, Statistics & Computer Science
//                 CS-244 Data Structures - Fall 2016
//
// This software is student work for CSS-244 Data Structures and may not
// be copied except by the original author and instructor.
// Copyright 2016
//
// <filename>
//
// <class description>
//
// Instructor: Jocelyn Richardt
// Assignment: StoutonianGame
// Author: Luke A Chase
// Date: 03/01/2017
//
// ---------------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>
#include <random>
#include "LinkedList.h"
#include "Stoutonian.h"
#include "Player.h"

using namespace std;


// forward declarations --------------------------------------------------- //
//NameList generateNameList(string filename);
// end forward declarations ----------------------------------------------- //


int main()
{
    // set random seed for this program's instance
    srand(time(NULL));

    LinkedList<Stoutonian> stoutonians;

    for (int j = 0; j < 10; j++)
    {
        Stoutonian st;
        stoutonians.addLast(st);
    }

    int stoutonianNumber = 0;
    for (LinkedList<Stoutonian>::Iterator itr = stoutonians.begin();
        itr != stoutonians.end(); itr++)
    {
        stoutonianNumber++;
        cout << endl << "Stoutonian " << stoutonianNumber << ":" << endl;
        (*itr).speak();
    }

    return 0;
}

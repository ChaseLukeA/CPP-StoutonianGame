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
// main.cpp
//
// The main program
//
// Instructor: Jocelyn Richardt
// Assignment: StoutonianGame
// Author: Luke A Chase
// Date: 03/01/2017
//
// ---------------------------------------------------------------------------

#include <iostream>
#include <random>
#include <time.h>
#include "Game.h"


using namespace std;

int main()
{
    // set random seed for this program's instance
    srand(time(NULL));

    Game game;

    game.getPlayer();
    game.start();


    return 0;
}

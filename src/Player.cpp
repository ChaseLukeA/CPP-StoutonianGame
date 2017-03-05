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

#include <stdio.h>
#include "Player.h"

Player::Player()
{
    //ctor
}

Player::~Player()
{
    //dtor
}

bool Player::hasSavedFile()
{
    struct stat buffer;
    return (stat ((m_Name + ".sav").c_str(), &buffer) == 0);
}

void Player::getSavedFile()
{

}

bool Player::saveFile()
{
    int i;
    if (hasSavedFile())
    {
        i = rename((m_Name + ".sav").c_str(), (m_Name + ".old").c_str());
    }
    if (i == 0)
    {
        cout << "Successfully renamed!" << endl;
        return true;
    }
    else
    {
        cout << "NOT renamed!" << endl;
        return false;
    }
}

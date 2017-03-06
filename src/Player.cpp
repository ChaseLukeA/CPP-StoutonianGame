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
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "Player.h"


template<typename T>
std::string ToString(const T& v)
{
    std::ostringstream ss;
    ss << v;
    return ss.str();
}

template<typename T>
T FromString(const std::string& str)
{
    std::istringstream ss(str);
    T ret;
    ss >> ret;
    return ret;
}


Player::Player()
{
    //ctor
}

Player::~Player()
{
    //dtor
}

void Player::generateInitialStoutonians()
{
    Stoutonian first(GameDesigner);
    addStoutonian(first);

    Stoutonian second(MathGenius);
    addStoutonian(second);

    Stoutonian third(InfoTechGuru);
    addStoutonian(third);
}

bool Player::hasSavedFile()
{
    struct stat buffer;
    return (stat((m_Name + ".sav").c_str(), &buffer) == 0);
}

void Player::getSavedFile()
{
    // if no saved file, generate 3 Stoutonians
    if (!hasSavedFile())
    {
        generateInitialStoutonians();
        return;
    }

    // get saved file with <player name>.sav
    ifstream file((m_Name + ".sav").c_str());

    while (file)
    {
        // read each line
        string line;
        if (!getline(file, line)) break;

        istringstream iss(line);
        vector<string> stats;

        // parse line into individual Stoutonian stats
        while (iss)
        {
            string stat;
            if (!getline(iss, stat, '|')) break;
            stats.push_back(stat);
        }

        // recreate saved Stoutonian and add
        Stoutonian stoutonian(
            Stoutonian::typeFromInt(FromString<int>(stats[0])),
            stats[1],
            FromString<int>(stats[2]),
            FromString<int>(stats[3]),
            FromString<int>(stats[4])
        );
        m_Stoutonians.addLast(stoutonian);
    }
}

bool Player::saveFile()
{
    // if save file already exists, temporarily rename to keep as backup
    if (hasSavedFile()) rename((m_Name + ".sav").c_str(), (m_Name + ".old").c_str());

    // save the Stoutonians to file
    ofstream file;
    string filename = (m_Name + ".sav").c_str();
    file.open((m_Name + ".sav").c_str(), ios_base::out);

    for (LinkedList<Stoutonian>::Iterator itr = m_Stoutonians.begin(); itr != m_Stoutonians.end(); itr++)
    {
        file << (*itr).getType() << "|";
        file << (*itr).getName() << "|";
        file << (*itr).getInitialMentalSharpness() << "|";
        file << (*itr).getChallengeStrength() << "|";
        file << (*itr).getSpeed() << endl;
    }

    file.close();

    // if backup saved file exists, delete it
    if (hasSavedFile()) remove((m_Name + ".old").c_str());
}

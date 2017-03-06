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

bool Player::hasSavedFile()
{
    struct stat buffer;
    return (stat ((m_Name + ".sav").c_str(), &buffer) == 0);
}

void Player::getSavedFile()
{
    if (!hasSavedFile()) return;

    //vector<vector<string>> data;
    ifstream file(m_SaveFileName);

    while (file)
    {
        string s;
        if (!getline( file, s )) break;

        istringstream iss(s);
        vector<string> stats;

        while (iss)
        {
            string stat;
            if (!getline(iss, stat, '|')) break;
            cout << stat << endl;
            stats.push_back(stat);
        }

        Stoutonian stoutonian;
        stoutonian.setType(FromString<int>(stats[0]));
        stoutonian.setName(stats[1]);
        //stoutonian.setInitialMentalSharpness(FromString<int>(stats[2]));
        //stoutonian.setChallengeStrength(FromString<int>(stats[3]));
        //stoutonian.setSpeed(FromString<int>(stats[4]));
        m_Stoutonians.addLast(stoutonian);

        //data.push_back(stoutonian);
    }

    if (!file.eof())
    {
        cerr << "Fooey!\n";
    }

}

bool Player::saveFile()
{
    // if save file already exists, temporarily rename to keep as backup
    if (hasSavedFile()) rename((m_Name + ".sav").c_str(), (m_Name + ".old").c_str());

    ofstream file;
    string filename = (m_Name + ".sav").c_str();
    file.open((m_Name + ".sav").c_str(), ios_base::out);

    for (LinkedList<Stoutonian>::Iterator itr = m_Stoutonians.begin(); itr != m_Stoutonians.end(); itr++)
    {
        file << (*itr).getType() << "|" << (*itr).getName() << "|" << (*itr).getInitialMentalSharpness() << "|" << (*itr).getChallengeStrength() << "|" << (*itr).getSpeed() << endl;
    }

    file << "second file";
    file.close();

    // if saved file exists, delete any existing .old file
    if (hasSavedFile()) remove((m_Name + ".old").c_str());
}

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
// NameList.h
//
// A class to hold list of names and provide functions to add a name to the
// list (if its not already here), to  get a random name from the list,
// or to check for the existence of a name in the list
//
// Instructor: Jocelyn Richardt
// Assignment: StoutonianGame
// Author: Luke A Chase
// Date: 03/01/2017
//
// ---------------------------------------------------------------------------

#ifndef NAMELIST_H
#define NAMELIST_H

#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include <iostream>

using namespace std;

class NameList
{
    public:
        NameList() {};
        virtual ~NameList() {};

        // add a name to the list if its not already there
        void add(string name) { if (!this->contains(name)) m_Names.push_back(name); }

        // get a random name from the list
        string randomName() { return m_Names[rand() % m_Names.size()]; }

        // see if a name is in the list
        bool contains(string name) { return find(m_Names.begin(), m_Names.end(), name) != m_Names.end(); }

    private:
        vector<string> m_Names;
};

#endif // NAMELIST_H

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
// Names.h
//
// A singleton class to hold a list of first names and a list of surnames;
// provides a function to return a random name with a first name and surname
//
// I made this a singleton because both the main program and the Stoutonian
// class will be randomly generating names and I only wanted to create the
// random name lists once from the "firstnames.dat" and "surnames.dat" files
//
// Instructor: Jocelyn Richardt
// Assignment: StoutonianGame
// Author: Luke A Chase
// Date: 03/01/2017
//
// ---------------------------------------------------------------------------

#ifndef NAMES_H
#define NAMES_H

#include "NameList.h"

using namespace std;

class Names
{
    private:
        Names();
        static bool instance;
        static Names* m_Names;
        NameList m_FirstNames;
        NameList m_SurNames;
        NameList generateNameList(string filename);

    public:
        virtual ~Names();
        static Names* getInstance();
        string randomName();
};

#endif // NAMES_H

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
// Names.cpp
//
// A singleton class to hold a list of first names and a list of surnames;
// provides a function to return a random name with a first name and surname
//
// I made this a singleton because both the main program and the Stoutonian
// class will be randomly generating names and I only wanted to create the
// random name lists once (from the "firstnames.dat" and "surnames.dat" files)
// and be able to use both lists from this one instance
//
// Instructor: Jocelyn Richardt
// Assignment: StoutonianGame
// Author: Luke A Chase
// Date: 03/01/2017
//
// ---------------------------------------------------------------------------

#ifndef null
#define null 0
#endif

#include <fstream>
#include "Names.h"

// default constructor
Names::Names()
{
    m_FirstNames = generateNameList("firstnames.dat");
    m_SurNames = generateNameList("surnames.dat");
}

// deconstructor
Names::~Names()
{
    instance = false;
}

// flag to see if an instance of Names already exists
bool Names::instance = false;

// m_Names should be null if Names has not been instantiated yet
Names* Names::m_Names = null;

// gets (or creates) the instance of Names
Names* Names::getInstance()
{
    if (!instance)
    {
        m_Names = new Names();
        instance = true;
        return m_Names;
    }
    else
    {
        return m_Names;
    }
}

// returns a name randomly created from the first names and surnames lists
string Names::randomName()
{
    return m_FirstNames.randomName() + " " + m_SurNames.randomName();
}

// generates a list of names from a *.dat file
NameList Names::generateNameList(string filename)
{
    NameList names;
    ifstream file;
    file.open(filename);

    while (!file.eof())
    {
        string name;
        file >> name;
        names.add(name);
    }

    file.close();
    return names;
}

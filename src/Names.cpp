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

#ifndef null
#define null 0
#endif

#include <fstream>
#include "Names.h"

Names::Names()
{
    m_FirstNames = generateNameList("firstnames.dat");
    m_SurNames = generateNameList("surnames.dat");
}

Names::~Names()
{
    instance = false;
}


bool Names::instance = false;

Names* Names::m_Names = null;

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

string Names::randomName()
{
    return m_FirstNames.randomName() + " " + m_SurNames.randomName();
}

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

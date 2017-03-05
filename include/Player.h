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

#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <sys/stat.h>
#include "LinkedList.h"
#include "Stoutonian.h"

using namespace std;

// I liked the sound of "Player" over "User", this is a game after all
class Player
{
    public:
        Player();
        virtual ~Player();

        string getName() { return m_Name; }
        void setName(string val) { m_Name = val; }
        string Name() { return m_Name; }
        void Name(string val) { m_Name = val; }
        string getPassword() { return m_Password; }
        void setPassword(string val) { m_Password = val; }
        LinkedList<Stoutonian> getStoutonians() { return m_Stoutonians; }
        void addStoutonian(Stoutonian stoutonian) { m_Stoutonians.addLast(stoutonian); }

        bool hasSavedFile()
        {
            struct stat buffer;
            return (stat ((m_Name + ".sav").c_str(), &buffer) == 0);
        }
        void getSavedFile();
        void generateInitialStoutonians();
        bool saveFile();

    protected:

    private:
        string m_Name;
        string m_Password;
        LinkedList<Stoutonian> m_Stoutonians;
};

#endif // PLAYER_H

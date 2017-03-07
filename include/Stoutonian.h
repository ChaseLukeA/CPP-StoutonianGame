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
// Stoutonian.h
//
// The Stoutonian class for creating a Stoutonian object; names are randomly-
// generated by the Names.h class
//
// Instructor: Jocelyn Richardt
// Assignment: StoutonianGame
// Author: Luke A Chase
// Date: 03/01/2017
//
// ---------------------------------------------------------------------------

#ifndef STOUTONIAN_H
#define STOUTONIAN_H

#include "StoutonianType.h"

using namespace std;

class Stoutonian
{
    public:
        Stoutonian();
        Stoutonian(StoutonianType type);
        Stoutonian(StoutonianType type, string name, int sharpness, int strength, int speed);
        virtual ~Stoutonian();

        StoutonianType getType() { return m_Type; }
        void setType(StoutonianType type) { m_Type = type; }
        string getName() { return m_Name; }
        void setName(string val) { m_Name = val; }
        int getInitialMentalSharpness() { return m_InitialMentalSharpness; }
        void setInitialMentalSharpness(int val) { m_InitialMentalSharpness = val; }
        int getActualMentalSharpness() { return m_ActualMentalSharpness; }
        void setActualMentalSharpness(int val) { m_ActualMentalSharpness = val; }
        int getChallengeStrength() { return m_ChallengeStrength; }
        void setChallengeStrength(int val) { m_ChallengeStrength = val; }
        int getSpeed() { return m_Speed; }
        void setSpeed(int val) { m_Speed = val; }

        static StoutonianType randomType();
        static StoutonianType typeFromInt(int type);
        static string randomAction();
        static string randomAdjective();
        static string getTypeName(StoutonianType type);


        void speak();
        string stats();
        void rest();
        bool runAway();
        void challenge(Stoutonian& opponent);
        bool recruit(Stoutonian& opponent);

    private:
        StoutonianType m_Type;
        string m_Name;
        int m_InitialMentalSharpness;
        int m_ActualMentalSharpness;
        int m_ChallengeStrength;
        int m_Speed;

        void spawn(StoutonianType type);
        static int random(int low, int high);
};

#endif // STOUTONIAN_H

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
// Game.h
//
// The actual game with methods to get player, get opponents, get input, and
// run the actual game scenarios
//
// Instructor: Jocelyn Richardt
// Assignment: StoutonianGame
// Author: Luke A Chase
// Date: 03/01/2017
//
// ---------------------------------------------------------------------------

#ifndef GAME_H
#define GAME_H

#include "Player.h"

class Game
{
    public:
        Game() {}
        virtual ~Game() {}

        void getPlayer();

        void start();

    protected:

    private:
        Player m_Player;
        Stoutonian m_ChosenOne;
        Stoutonian m_Opponent;
        int m_SelectedStoutonian;

        int getChoice(int numberOfChoices);
        void getOpponent();
        void listStoutonians();
        void chooseStoutonian();
        void playGame();
        bool wantToPlay();
};

#endif // GAME_H

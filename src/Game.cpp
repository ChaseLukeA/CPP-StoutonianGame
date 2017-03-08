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
// Game.cpp
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

#include "Game.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include "LinkedList.h"
#include "Stoutonian.h"
#include "Player.h"


// forward declarations
void printSeparator();


void Game::getPlayer()
{
    string name;

    cout << "   ___________________________" << endl;
    cout << "  /  _______________________  \\" << endl;
    cout << " /  /                       \\  \\" << endl;
    cout << "|  |  -= STOUTONIAN GAME =-  |  |" << endl;
    cout << " \\  \\_______________________/  /" << endl;
    cout << "  \\___________________________/" << endl;

    cout << endl << "\nEnter your desired player name: ";
    cin >> name;

    m_Player.setName(name);

    if (m_Player.hasSavedFile())
    {
        cout << endl << "Loading " << name << "'s saved Stoutonians from file..." << endl;
        m_Player.getSavedFile();

        // if player lost players last session and has less than 3, generate new ones up to three
        while (m_Player.getStoutonians().getSize() < 3)
        {
            cout << endl << "You have less than 3 Stoutonian's saved. Recruiting a new Stoutonian to your team..." << endl;
            Stoutonian st(Stoutonian::randomType());
            m_Player.addStoutonian(st);
        }
    }
    else
    {
        cout << endl << "No save file found for " << name << ", finding three willing Stoutonians..." << endl;
        m_Player.generateInitialStoutonians();
    }

    cout << endl << "Let the games begin!" << endl;
    printSeparator();
}

void Game::start()
{
    bool play = true;

    while (play)
    {
        getOpponent();

        listStoutonians();

        chooseStoutonian();

        playGame();

        play = wantToPlay();
    }

    cout << endl << "Saving " << m_Player.getName() << "'s Stoutonians to disk..." << endl;
    m_Player.saveFile();

    cout << endl << "Goodbye!" << endl;
}

int Game::getChoice(int numberOfChoices)
{
    int choice;

    while (choice < 1 || choice > numberOfChoices)
    {
        cin >> choice;
        if (choice < 1 || choice > numberOfChoices) cout << endl << "Invalid choice. Please choose again: ";
    }

    return choice;
}

void Game::getOpponent()
{
    Stoutonian opponent(Stoutonian::randomType());
    m_Opponent = opponent;

    cout << endl << "A " << Stoutonian::randomAdjective() << " figure steps from the shadows..." << endl;
    cout << endl << "OPPONENT:" << endl;
    opponent.speak();
    printSeparator();
}

void Game::listStoutonians()
{
    int number = 0;
    string nameTabs;
    string typeTabs;

    cout << endl << "Here are your Stoutonians: " << endl;
    cout << "\t\t\t\t\t\t  Mental     Challenge" << endl;
    cout << "   Name:\t\t\tType:\t\tSharpness:   Strength:" << endl;

    while (number < m_Player.getStoutonians().getSize())
    {
        Stoutonian st = m_Player.getStoutonians().getElementAt(number);
        // set number of tabs after name for proper alignment
        if (st.getName().length() < 21)
            nameTabs = "\t\t";
        else
            nameTabs = "\t";
        // set number of tabs after type for proper alignment
        if (st.getType() == Unknown)
            typeTabs = "\t\t";
        else
            typeTabs = "\t";
        cout << ++number << ") " << st.getName() << nameTabs << Stoutonian::getTypeName(st.getType()) << typeTabs << "    " << st.getActualMentalSharpness() << "\t\t" << st.getChallengeStrength() << endl;
    }
}

void Game::chooseStoutonian()
{
    int numberOfStoutonians = m_Player.getStoutonians().getSize();
    int choice = 0;

    cout << endl << "Enter the number of the Stoutonian you want to use: ";

    choice = getChoice(numberOfStoutonians) - 1;
    m_SelectedStoutonian = choice;

    m_ChosenOne = m_Player.getStoutonians().getElementAt(choice);

    cout << endl << "Lets go " << m_ChosenOne.getName() << "!" << endl;
    printSeparator();
}

void Game::playGame()
{
    int choice;
    int hitTotal;
    bool gameOver = false;
    string yourDefeatMessage = "Your Stoutonian, " + m_ChosenOne.getName() + ", has been defeated. Game over.";
    string opponentsDefeatMessage = "You have defeated " + m_Opponent.getName() + ". You win!!!";

    cout << endl << "YOU:" << endl;
    m_ChosenOne.speak();

    while (!gameOver)
    {
        printSeparator();
        cout << endl << m_Opponent.getName() << " stands opposing you, " << m_ChosenOne.getName() << ". What would you like to do?" << endl;
        cout << "1) Challenge Them" << endl;
        cout << "2) Recruit Them" << endl;
        cout << "3) Run Away!" << endl;
        cout << endl << "Enter your choice: ";
        choice = getChoice(3);
        printSeparator();

        // 10% of the time choose something else
        if (rand() % 10 < 1) choice = 4;

        if (m_Opponent.getSpeed() > m_ChosenOne.getSpeed())
        {
            cout << endl << "Opponent " << m_Opponent.getName() << " gets in an early jab." << endl;
            hitTotal = m_Opponent.challenge(m_ChosenOne);
            cout << endl << "Your Stoutonian " << m_ChosenOne.getName() << "'s mental sharpness is dulled by " << hitTotal << " points!" << endl;

            if (m_ChosenOne.defeated())
            {
                cout << endl << yourDefeatMessage << endl;
                gameOver = true;
            }
        }

        if (!gameOver)
        {
            switch (choice)
            {
            case 1: // challenge
                hitTotal = m_ChosenOne.challenge(m_Opponent); // hit the opponent
                cout << endl << "You dull " << m_Opponent.getName() << "'s mental sharpness by " << hitTotal << " points! Groovy!" << endl;

                if (m_Opponent.defeated()) // you defeat opponent
                {
                    cout << endl << opponentsDefeatMessage << endl;
                    gameOver = true;
                }
                else // you do NOT defeat opponent
                {
                    if (m_Opponent.getSpeed() < m_ChosenOne.getSpeed()) // is slower speed
                    {
                        hitTotal = m_Opponent.challenge(m_ChosenOne);
                        cout << endl << m_Opponent.getName() << " counter-attacks! Your Stoutonian loses " << hitTotal << " mental sharpness points!" << endl;

                        if (m_ChosenOne.defeated()) // you are defeated
                        {
                            cout << endl << yourDefeatMessage << endl;
                            gameOver = true;
                        }
                    }
                }
                break;
            case 2: // recruit
                if (m_ChosenOne.recruit(m_Opponent)) // recruit successful
                {
                    cout << endl << "Opponent " << m_Opponent.getName() << " has be successfully recruited into your party!" << endl;
                    m_Opponent.rest();
                    m_ChosenOne.rest();
                    m_Player.addStoutonian(m_Opponent);
                    gameOver = true;
                }
                else // recruit unsuccessful
                {
                    cout << endl << "Recruit unsuccessful! You've just made " << m_Opponent.getName() << " angry..." << endl;
                }
                break;
            case 3: // run away
                if (m_ChosenOne.runAway()) // run away successful
                {
                    cout << endl << "You ran away! Better luck next time I guess. Game over!" << endl;
                    gameOver = true;
                }
                else // run away unsuccessful
                {
                    cout << endl << "You were not able to run away! " << m_Opponent.getName() << " gets in a solid hit." << endl;
                    hitTotal = m_Opponent.challenge(m_ChosenOne);
                    cout << endl << "Your Stoutonian " << m_ChosenOne.getName() << "'s mental sharpness is dulled by " << hitTotal << " points!" << endl;

                    if (m_ChosenOne.defeated()) // you are defeated
                    {
                        cout << endl << yourDefeatMessage << endl;
                        gameOver = true;
                    }
                }
                break;
            default:
                hitTotal = rand() % 8 + 2; // 2-10 points
                cout << endl << "Both Stoutonians stand there looking confounded. Both lose " << hitTotal << " points for being stupid!" << endl;
                m_ChosenOne.setActualMentalSharpness(m_ChosenOne.getActualMentalSharpness() - hitTotal);
                m_Opponent.setActualMentalSharpness(m_Opponent.getActualMentalSharpness() - hitTotal);

                if (m_ChosenOne.defeated() || m_Opponent.defeated())
                {
                    cout << endl << "Well that was just sad. Game over!" << endl;
                    gameOver = true;
                }
            }
        }
    }

    if (m_ChosenOne.defeated())
    {
        m_Player.removeStoutonian(m_SelectedStoutonian);
    }
}

bool Game::wantToPlay()
{
    char choice;

    printSeparator();
    cout << endl << "Would you like to keep playing? (y/n) ";
    cin >> choice;
    printSeparator();
    return choice == 'Y' || choice == 'y';
}

void printSeparator()
{
    cout << endl << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
}

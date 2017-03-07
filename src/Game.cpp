#include "Game.h"
#include <iostream>
#include <fstream>
#include <vector>


#include "LinkedList.h"
#include "Stoutonian.h"
#include "Player.h"



Game::Game()
{
    //ctor
}

Game::~Game()
{
    //dtor
}

void Game::getPlayer()
{
    string name;

    cout << "   ___________________________" << endl;
    cout << "  /  _______________________  \\" << endl;
    cout << " /  /                       \\  \\" << endl;
    cout << "|  |  -= STOUTONIAN GAME =-  |  |" << endl;
    cout << " \\  \\_______________________/  /" << endl;
    cout << "  \\___________________________/" << endl;

    cout << "\nEnter your desired player name: " << endl;
    cin >> name;

    m_Player.setName(name);

    if (m_Player.hasSavedFile())
    {
        cout << endl << "Loading " << name << "'s saved Stoutonians from file..." << endl;
        m_Player.getSavedFile();
    }
    else
    {
        cout << endl << "No save file found for " << name << ", finding three willing Stoutonians..." << endl;
        m_Player.generateInitialStoutonians();
    }

    cout << endl << "Done. Let the games begin!" << endl << endl;

    /*
    Stoutonian st1(Stoutonian::randomType());
    m_Player.addStoutonian(st1);

    for (LinkedList<Stoutonian>::Iterator itr = m_Player.getStoutonians().begin(); itr != m_Player.getStoutonians().end(); itr++)
    {
        (*itr).speak();
        cout << endl << endl;
    }

    m_Player.saveFile();
    */
}

void Game::getOpponent()
{
    Stoutonian opponent(Stoutonian::randomType());
    m_Opponent = opponent;

    cout << "A " << Stoutonian::randomAdjective() << " figure steps from the shadows..." << endl << endl;
    opponent.speak();
    cout << endl;
}

void Game::listStoutonians()
{
    int number = 0;

    cout << endl << "Pick your Stoutonian to challenge with!" << endl;
    cout << "\t\t\t\t\t  Mental     Challenge" << endl;
    cout << "   Name:\t\tType:\t\tSharpness:   Strength:" << endl;

    for (LinkedList<Stoutonian>::Iterator itr = m_Player.getStoutonians().begin(); itr != m_Player.getStoutonians().end(); itr++)
    {
        number++;
        cout << number << ") " << (*itr).stats() << endl;
    }
}

Stoutonian Game::getChoice()
{
    int numberOfStoutonians = m_Player.getStoutonians().getSize();
    int number = -1;
    int choice = -1;

    cout << "Enter the number of the Stoutonian you want to use: ";

    while (choice < 0 || choice > numberOfStoutonians)
    {
        cin >> choice;
        if (choice < 0 || choice > numberOfStoutonians) cout << endl << "Invalid choice. Please choose again: ";
    }

    for (LinkedList<Stoutonian>::Iterator itr = m_Player.getStoutonians().begin(); itr != m_Player.getStoutonians().end(); itr++)
    {
        number++;
        if (number == choice) return (*itr);
    }
}

void Game::play()
{
    bool playGame = true;

    while (playGame)
    {
        getOpponent();

        listStoutonians();

        getChoice();

        playGame = wantToPlay();
    }
}

bool Game::wantToPlay()
{
    char choice;
    cout << endl << "Would you like to keep playing? (y/n)" << endl;
    cin >> choice;

    return choice == 'Y' || choice == 'y';
}

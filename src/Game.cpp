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
        cout << endl << "Loading " << name << "'s saved Stoutonians from file...";
        m_Player.getSavedFile();
        cout << " Done." << endl;
    }
    else
    {
        cout << endl << "No save file found for " << name << ", finding three willing Stoutonians..." << endl;
        m_Player.generateInitialStoutonians();
    }

    cout << endl << endl;
    //cout << endl << "Adding one random Stoutonian...";
    //Stoutonian st1(Stoutonian::randomType());
    //m_Player.addStoutonian(st1);

    for (LinkedList<Stoutonian>::Iterator itr = m_Player.getStoutonians().begin(); itr != m_Player.getStoutonians().end(); itr++)
    {
        (*itr).speak();
        cout << endl << endl;
    }

    m_Player.saveFile();
    //player.saveFile();
}

#ifndef GAME_H
#define GAME_H

#include "Player.h"


class Game
{
    public:
        Game();
        virtual ~Game();

        void getPlayer();

        void play();

    protected:

    private:
        Player m_Player;
        Stoutonian m_Opponent;

        void getOpponent();
        void listStoutonians();
        Stoutonian getChoice();
        bool wantToPlay();
};

#endif // GAME_H

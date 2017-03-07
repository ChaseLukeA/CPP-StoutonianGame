#ifndef GAME_H
#define GAME_H

#include "Player.h"


class Game
{
    public:
        Game();
        virtual ~Game();

        void getPlayer();
        void getOpponent();

        void play();
        void choose();

    protected:

    private:
        Player m_Player;

};

#endif // GAME_H

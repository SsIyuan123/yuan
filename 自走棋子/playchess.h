#ifndef PLAY_CHESS_H
#define PLAY_CHESS_H
#include"player.h"

class playchess
{
    public:
    playchess();
    // void showPlayer();
    std::vector<player> A;
    private:
    int playtime;
    int palyernum;
    int circule;
    int money_growth;
};

#endif
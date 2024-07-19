#ifndef PLAY_CHESS_H
#define PLAY_CHESS_H
#include"player.h"
#include"war.h"

class playchess
{
    public:
    playchess();
    void createAccount();
    void determinePeopleAmount();
    int loadin();
    void home();
    void WriteA();
    void running();
    std::string makePassword();
    std::vector<war> makewar();
    void winnerDetermine();
    void determineMoneyGrowth();
    // void showPlayer();
    std::vector<player> alivePlayer;
    std::vector<player> allPlayer;
    private:
    int aliveNum;
    int playtime;
    int playernum;
    int circule;
    int money_growth;
};

#endif
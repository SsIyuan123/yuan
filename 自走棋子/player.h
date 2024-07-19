#ifndef PLAYER_H
#define PLAYER_H
#include"chessbase.h"
#include"troop.h"
#include <utility>
#include<string>

class player
{
    public:
    player();
    player(std::string name, std::string password, int WinAmount, int One, int Total, int Winrate);
    player(const player &);
    player(int test,std::string name);
    void Save();
    void reFresh();
    void changeFrontline();
    void Hpdecrease(int x);
    void troopMenu();
    void Upgrade();
    void showDetail();
    void changeRecord(int Win, int One);
    void IncreaseMoney(int x);
    void gainExperience(int delta);
    std::pair<std::vector<std::string>,int*> Getinfo();
    troop* MyTroop(){return &Atroop;}
    void showPersonalInfo();
    private:
    std::string name;
    std::string password;
    troop Atroop;
    int Hp = 100;
    int Money;
    int level;
    int experience;
    int Maxexperience = 100;
    int MaxHp = 100;
    int WinAmount;//进入前一半记为赢,奇数玩家赢者偏少
    int One;
    int Total;
    float Winrate;
};


#endif
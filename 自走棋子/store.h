#ifndef STORE_H
#define STORE_H
#include"player.h"
#include"chessbase.h"

class store
{
    public:
    store(player& a);
    store(store& a);
    void generateSoldier();
    void menu();
    void showGoods();
    void showPlayerInfo();
    void hiresoldier();
    void reGenerate();
    void lookinto();
    void sellSoldier();
    void clean(int x);//x属于[0,WindowNum)
    void buy(int x);
    private:
    player* A;
    int WindowNum;
    std::vector<std::pair<int,soldier*>> goods;
};

#endif
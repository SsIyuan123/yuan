#ifndef STORE_H
#define STORE_H
#include"player.h"

class store
{
    public:
    store(player& a);
    void generateSoldier();
    void clean(int x);//x属于[0,WindowNum)
    void buy(int x);
    private:
    player A;
    int WindowNum;
    std::vector<std::pair<int,soldier*>> goods;
};

#endif
#ifndef WAR_H
#define WAR_H
#include "player.h"
#include<array>

class war
{
    public:
    war(std::vector<player*> enemy,int);
    void show();
    int getFirst();
    int MakeDistance(int a[10][5], int zhenying, int x, int y);
    int *pickAttackingEnemy(int x); 
    int *pickLeastHpEnemy(int x);
    int bleed(int zhenying);
    void deadout();
    std::pair<std::vector<std::array<int,3>>,std::vector<std::array<int,3>>> drawDistanceMap(int a[10][5], int k, int zhenying, int xFront, int yFront);
    void moveOrAttack(int zhenying, int x, int y);
    void chaos_moveOrAttack(int zhenying, int x, int y);
    void effects(int number, int x, int y);
    void running();
    std::vector<player*> A;
    SoldierCondition WarPosition[10][5];
    private:
    int special;
};

#endif
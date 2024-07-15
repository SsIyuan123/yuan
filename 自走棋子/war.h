#ifndef WAR_H
#define WAR_H
#include "player.h"
#include<array>

class war
{
    public:
    war(std::vector<player> enemy);
    void show();
    int getFirst();
    int MakeDistance(int a[10][5], int zhenying, int x, int y);
    int *pickAttackingEnemy(int x);   //x为目前正在出手的己方阵营
    int *pickLeastHpEnemy(int x);
    void deadout();
    std::pair<std::vector<std::array<int,3>>,std::vector<std::array<int,3>>> drawDistanceMap(int a[10][5], int k, int zhenying, int xFront, int yFront);
    void moveOrAttack(int zhenying, int x, int y);
    void effects(int number, int x, int y);//x,y为核验的对象为位置，number为所在的玩家阵营序号
    void running();
    std::vector<player> A;
    SoldierCondition WarPosition[10][5];
};

#endif
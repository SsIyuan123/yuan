#ifndef TROOP_H
#define TROOP_H

#include"chessbase.h"
#include<string>

class SoldierCondition
{
    public:
    SoldierCondition():vacancyindex(0),type((soldiers)0),zhenying(10),xFront(10),yFront(10),xWar(100),yWar(100){a=nullptr;}
    SoldierCondition input(SoldierCondition &tem, int zhenying, int x=10, int y=10);
    void lay(soldier * ,int, int);
    void go();
    SoldierCondition(const SoldierCondition &p);
    void dying();
    void relive(int x=0);
    std::pair<int*,soldier*> getInfo();
    private:
    int vacancyindex;
    soldiers type;
    soldier *a;
    int zhenying,xFront,yFront,xWar,yWar;
};

class troop
{
    public:
    troop():
        Warehouse_Amount(0),OnFrontline_Amount(0),
        AliveAmount(0),OnFrontline_limit(2),
        Warehouse_limit(6),levelOne_Amount(0),
        levelThree_Amount(0),levelTwo_Amount(0){}
    troop(const troop&);
    void changeAmount(int deltaWareAmount = 0, int deltaFrontAmount = 0, int deltaWareLimit = 0, int deltaFrontLimit = 0);
    void testOnFront(soldier*,int,int);
    void gota(soldier *newsoldier);
    std::pair<std::vector<std::pair<int,soldier*>>,int*> GetInfo();
    int getAlive();

    void showFrontline();
    void getdown();
    void turnOnFrontline();
    void sell(int x);
    void showAllSoldiers(int x=100);
    // void MakeBack(int x, int y);
    SoldierCondition** MyCondition();
    private:
    SoldierCondition FrontDistribution[2][5];//There are 2 lines and 5 rows for the war field of a troop 
    std::vector<std::pair<int,soldier*>> MySoldier;
    int levelOne_Amount;
    int levelTwo_Amount;
    int levelThree_Amount;
    int AliveAmount;
    int Warehouse_Amount;
    int OnFrontline_Amount;
    int OnFrontline_limit;
    int Warehouse_limit;
};

#endif
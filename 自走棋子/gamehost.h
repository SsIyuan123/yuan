#ifndef GAMEHOST_H
#define GAMEHOST_H
#include"chesstype.h"
#include <utility>
#include<string>
class player;
class troop;
class SoldierCondition;

class SoldierCondition
{
    public:
    SoldierCondition():vacancyindex(0),type((soldiers)0),zhenying(10),x(10),y(10){a=nullptr;}
    SoldierCondition input(SoldierCondition &tem, int x, int y, int zhenying);//用于从troop模式到war模式的输入，并非完全相等
    void lay(soldier *);
    void go();
    SoldierCondition(SoldierCondition &p);
    void dying();
    void relive(int x=0);//如果x=0默认回满血，要不回复x滴血
    std::pair<int*,soldier*> getInfo();
    private:
    int vacancyindex;
    soldiers type;
    soldier *a;
    int zhenying,x,y;
};

class troop
{
    public:
    troop():Warehouse_Amount(0),OnFrontline_Amount(0),AliveAmount(0),OnFrontline_limit(1),Warehouse_limit(3){}
    void changeAmount(int deltaWareAmount = 0, int deltaFrontAmount = 0, int deltaWareLimit = 0, int deltaFrontLimit = 0);
    void gota(soldier *newsoldier);
    std::pair<std::vector<soldier*>,int*> GetInfo();
    int getAlive();
    void TurnOnFronter(soldier *a, int x, int y);
    void MakeBack(int x, int y);
    SoldierCondition** MyCondition();
    private:
    SoldierCondition FrontDistribution[2][5];//There are 2 lines and 5 rows for the war field of a troop 
    std::vector<soldier*> WarehouseSoldier;
    int AliveAmount;
    int Warehouse_Amount;
    int OnFrontline_Amount;
    int OnFrontline_limit;
    int Warehouse_limit;
};

class player
{
    public:
    player();
    player(char* name);
    // void buy();//purchase a new soldier from the store
    void gainExperience(int delta);
    std::pair<std::string,int*> Getinfo();
    troop MyTroop(){return Atroop;}
    private:
    std::string name;
    troop Atroop;
    int Money;
    int level;
    int experience;
};

class playchess
{
    public:
    playchess();
    player *A;
    private:
    int playtime;
    int palyernum;
    int circule;
    int money_growth;
};

class war
{
    public:
    war(player enemy[2]);
    int getFirst();
    int MakeDistance(int a[10][5], int zhenying, int x, int y);
    int *pickAttackingEnemy(int x);   //x为目前正在出手的己方阵营
    int *pickLeastHpEnemy(int x);
    void moveOrAttack(int zhenying, int x, int y);
    void effects(int number, int x, int y);//x,y为核验的对象为位置，number为所在的玩家阵营序号
    void running();
    player A[2];
    SoldierCondition WarPosition[10][5];
};

// class store
// {
//     public:
//     store(){}
//     void generateSoldier();
//     void reGenerat();
//     private:
//     int WindowNum;
//     std::pair<int,soldier> *goods;
// };

#endif
#ifndef CHESS_BASE_H
#define CHESS_BASE_H
#include<vector>

enum soldiers
{
    Dead=0,
    particlewarrior=1,
    laserarcher=2,
    particleengineer=3,
    dimensionassassin=4,
    swordman=5,
    hypnotist=6
};

enum soldierState
{
    Common=0,
    DefenseOff=1,
    harmsharp=2,
    missrateup=3,
    shield=4,
    Onfire=5,
    dizzied=6,
    wounded=7,
    rageup=8,
    chaos=9,
    Hpup=10,
    rebound=11
};

class State
{
    public:
    State();
    State(const State &a);
    void show();
    std::pair<std::vector<soldierState>,std::vector<std::vector<int>>> getInfo();
    void SthHappen(soldierState a, int strength, int duration, int zhenying, int x, int y);
    void settlement(int x = 10, int y = 10, int num = 0);
    void clear();
    void erase(int x = 10, int y = 10, int num = 0);
    private:
    std::vector<soldierState> a;
    std::vector<int> strength;
    std::vector<int> duration;
    std::vector<int>Totalduration;
    std::vector<int> YouOrMe;//对敌方为1对我方为0
    std::vector<int> position[2];//如果是自己的话默认为10，10
};

class soldier
{
    public:
    soldier(int Hp=0,int rage=0, int missrate=0, int harm=5, int defense=1, int shield=0, int level=0, int freedom=0, int MaxHp=1, int speed=1, int range=0,int type=0, int Maxdefense=0, int reBound=0, int rageUp = 0):
        Hp(Hp),harm(harm),defense(defense),
        missrate(missrate),level(level),type((soldiers)type),
        rage(rage),shield(shield),freedom(freedom),reBound(reBound),
        MaxHp(MaxHp),speed(speed),range(range),
        Maxdefense(Maxdefense),rageUp(rageUp){}
    virtual void done(std::vector<std::vector<int>> position) = 0;//number,line,row,camp
    virtual void levelUp() = 0;
    void checkState(int x = 10, int y = 10, int num = 0);//x,y是目前正结算的单位位置，num是相对阵营，无参数使用时默认操作MyState
    void addindex(int Hp = 0, int rage = 0, int missrate = 0, int harm = 0, int defense = 0, int shield = 0, int level = 0, int MaxHp = 0, int speed = 0, int range = 0, int reBound = 0, int Maxdefense = 0, int rageUp = 0);
    void makerecord(int zhenying, int x, int y, soldierState a, int strength, int duration);
    State recordRun();
    void changeMyState(int a, int strength, int duration, int x = 10, int y = 10, int zhenying = 0);
    int* getInfo();
    virtual void show();
    private:
    State record;//用来记录自己对别人干了什么
    State MyState;
    State BearState;//在别人回合结算的
    int Hp;
    int rage;
    int missrate;
    int harm;
    int defense;
    int shield;
    int level;
    int freedom;
    int MaxHp;
    int speed;
    int range;
    soldiers type;
    int Maxdefense;
    int reBound;
    int rageUp;
};

#endif
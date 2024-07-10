#ifndef CHESS_TYPE_H
#define CHESS_TYPE_H
#include<vector>

enum soldiers
{
    Dead=0,
    particlewarrior=1,
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
    chaos=9
};

class State
{
    public:
    State();
    State(const State &a);
    std::pair<std::vector<soldierState>,std::vector<std::vector<int>>> getInfo();
    void SthHappen(soldierState a, int strength, int duration, int zhenying, int x, int y);
    void settlement(int x = 10, int y = 10, int num = 0);
    void clear();
    void erase(int x = 10, int y = 10, int num = 0);
    private:
    std::vector<soldierState> a;
    std::vector<int> strength;
    std::vector<int> duration;
    std::vector<int> YouOrMe;//对敌方为1对我方为0
    std::vector<int> position[2];//如果是自己的话默认为10，10
};

class soldier
{
    public:
    soldier(int Hp=0,int rage=0, int missrate=0, int harm=5, int defense=1, int shield=0, int level=0, int freedom=0, int MaxHp=1, int speed=1, int range=0,int type=0):
        Hp(Hp),harm(harm),defense(defense),
        missrate(missrate),level(level),type((soldiers)type),
        rage(rage),shield(shield),freedom(freedom),
        MaxHp(MaxHp),speed(speed),range(range){}
    virtual void done(int* position[3]) = 0;//number,line,row,camp
    void checkState(int x = 10, int y = 10, int num = 0);//x,y是目前正结算的单位位置，num是相对阵营，无参数使用时默认操作MyState
    void addindex(int Hp = 0, int rage = 0, int missrate = 0, int harm = 0, int defense = 0, int shield = 0, int level = 0, int MaxHp = 0, int speed = 0, int range = 0);
    void makerecord(int zhenying, int x, int y, soldierState a, int strength, int duration);
    State recordRun();
    void changeMyState(int a, int strength, int duration, int x = 10, int y = 10, int zhenying = 0);
    int* getInfo();
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
};

//角色分为四个阵营，分别为粒子（particle），Reiki（灵气），元素（element）和野蛮（wild）各有特色

//particle来自未来，通过粒子科技进行打击，特点是防御很高
class particle 
{
    public:
    particle(int energyamount = 0):energyamount(energyamount),state(0){}
    int changeparticle(int delta);
    void switchstate();
    int showstate();
    private:
    int energyamount;
    int state;
};

//Reiki属于修仙世界，身手敏捷，特点是躲避能力强、近战伤害很高
class Reiki
{
    public:
    Reiki(int Reikiamount = 0):Reikiamount(0),state(0){}
    int changeReiki(int delta);
    int switchstate();
    private:
    int Reikiamount;
    int state;
};

class element
{
    public:
    element(int fireflag = 0, int electricityflag = 0){}
    void changeflag(int fire, int elctricity){}
    private:
    int fireflag;
    int electricityflag;
};

class wild
{
    public:
    wild(int wildness = 0){}
    void changewildness(int delta){}
    private:
    int wildness;
};

class warrior:public soldier
{
    public:
    warrior(int type= 0, int Hp=50, int harm=4, int defense=2, int missrate=10, int level=1, int rage=0, int shield = 0, int freedom = 1, int speed = 2, int range = 1):soldier(Hp,rage,missrate,harm,defense,shield,level,freedom,Hp,speed,range,type){}
};

class archer:public soldier
{
    public:
    archer(int Hp=30,int harm=6, int defense=1, int missrate=5, int level=1, int rage=0, int shield = 0, int freedom = 1, int speed = 1, int range = 4, int type=0):soldier(Hp,rage,missrate,harm,defense,shield,level,freedom,Hp,speed,range,type){}
};

class magician:public soldier
{
    public:
    magician(int Hp=25,int harm=5, int defense=0, int missrate=5, int level=1, int rage=0, int shield = 0, int freedom = 1, int speed = 1, int range = 3, int type=0):soldier(Hp,rage,missrate,harm,defense,shield,level,freedom,Hp,speed,range,type){}
};

class assassin:public soldier
{
    assassin(int Hp=30,int harm=8, int defense=1, int missrate=20, int level=1, int rage=0, int shield = 0, int freedom = 1, int speed = 3, int range = 2,int type=0):soldier(Hp,rage,missrate,harm,defense,shield,level,freedom,Hp,speed,type){}
};

class Mecha:public soldier, public particle
{
    public:
    Mecha(int Hp=70, int harm=8, int defense=4, int missrate=0, int level=0, int rage=0, int shield = 0, int energyamount=0, int freedom = 1, int speed = 2, int range = 2, int type=0):soldier(Hp,rage,missrate,harm,defense,shield,level,freedom,Hp,speed,type),particle(energyamount){}
};

class JadeEmperor:public soldier, public Reiki
{
    JadeEmperor(int Hp=30, int harm=12, int defense=8, int missrate=30, int level=0, int rage=0, int shield = 0, int Reikiamount=0, int freedom = 1, int speed = 1, int range =5, int type =0):soldier(Hp,rage,missrate,harm,defense,shield,level,freedom,Hp,speed,type),Reiki(Reikiamount){}
};

class Dragon:public soldier, public element
{
    Dragon(int Hp=40, int harm=6, int defense=5, int missrate=15, int level=0, int rage=0, int shield = 0, int freedom = 1, int speed = 2, int fire=1, int electricity=1, int range =4, int type =0):soldier(Hp,rage,missrate,harm,defense,shield,level,freedom,Hp,speed,type),element(fire,electricity){}
};

class werewolf:public soldier, public wild
{
    werewolf(int Hp=100, int harm=8, int defense=2, int missrate=20, int level=0, int rage=0, int shield = 0, int freedom = 1, int speed = 5, int wildness=0, int range =1, int type =0):soldier(Hp,rage,missrate,harm,defense,shield,level,freedom,Hp,speed,type),wild(wildness){}
};

class ParticleWarrior:public warrior, public particle
{
    public:
    ParticleWarrior():warrior(1),particle(){}
    virtual void done(int* position[3]);
};

#endif
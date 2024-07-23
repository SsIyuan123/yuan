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
    hypnotist=6,
    fulu_drawer=7,
    sorcerer=8,
    firewarrior=9,
    electriarcher=10,
    icemagician=11,
    vortexsailer=12,
    werewolf=13,
    dragon=14,
    wildpriest=15,
    dryads=16
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
    rebound=11,
    vine=12,
    nodefenseharm=13,
    ice=14,
    iceshield=15,
    AnotherWorld=16,
    bleeding=17
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
    soldier(int Hp=0,int rage=0, int missrate=0, int harm=5, int defense=1, int shield=0, int level=0, int freedom=0, int MaxHp=1, int speed=1, int range=0,int type=0, int Maxdefense=0, int reBound=0, int rageUp = 0, int chaos = 0, int vine = 0, int ice = 0, int iceshield = 0, int world = 0, int buff=0):
        Hp(Hp),harm(harm),defense(defense),
        missrate(missrate),level(level),type((soldiers)type),
        rage(rage),shield(shield),freedom(freedom),reBound(reBound),
        MaxHp(MaxHp),speed(speed),range(range),
        Maxdefense(Maxdefense),rageUp(rageUp),chaos(chaos),
        vine(vine), ice(ice),iceshield(iceshield),
        world(world),buffrate(buff){}
    virtual void done(std::vector<std::vector<int>> position) = 0;//number,line,row,camp
    virtual void levelUp() = 0;
    virtual void makebaseBuff(int index) = 0;
    void checkState(int x = 10, int y = 10, int num = 0);//x,y是目前正结算的单位位置，num是相对阵营，无参数使用时默认操作MyState
    void addindex(int Hp = 0, int rage = 0, int missrate = 0, int harm = 0, int defense = 0, int shield = 0, int level = 0, int MaxHp = 0, int speed = 0, int range = 0, int reBound = 0, int Maxdefense = 0, int rageUp = 0,int vine = 0, int ice = 0, int iceshield = 0, int world = 0);
    void makerecord(int zhenying, int x, int y, soldierState a, int strength, int duration);
    State recordRun();
    void changeMyState(int a, int strength, int duration, int x = 10, int y = 10, int zhenying = 0);
    int* getInfo();
    virtual void show();
    virtual void relive();
    void makeit(int index);
    int getbuffNum();
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
    int chaos;
    int vine;
    int ice;
    int iceshield;
    int world;
    int buffrate;
};

//角色分为四个阵营，分别为粒子（particle），Reiki（灵气），元素（element）和野蛮（wild）各有特色

//particle来自未来，通过粒子科技进行打击，特点是防御很高
class base
{
    public:
    void makebase(int index);
    int getbaseBuff();
    private:
    int buffindex;
};

class particle:public base
{
    public:
    particle(int energyamount = 0):energyamount(energyamount),state(0),particleUp(34){}
    int changeparticle(int delta, int particleUp = 0);
    int getDelta();
    void switchstate();
    int showstate();
    void buff();
    private:
    int energyamount;
    int state;
    int particleUp;
};

//Reiki属于修仙世界，身手敏捷，特点是躲避能力强、近战伤害很高
class Reiki:public base
{
    public:
    Reiki(int Reikiamount = 0):Reikiamount(0),state(0),ReikiUp(34){}
    void changeReiki(int ReikiAmount, int ReikiUp=0);
    int switchstate();
    std::vector<int> ReikiInfo();
    void buff();
    private:
    int Reikiamount;
    int state;
    int ReikiUp;
};

class element:public base
{
    public:
    element(){}
    //element的buff增益分给个体了
    private:
};

class wild:public base
{
    public:
    wild(int wildness = 0):prorate(30),wildness(wildness){}
    void Makewildness(double Hp, double MaxHp);
    int getWildness();
    void levelUp(int x);
    void buff();
    void show();
    private:
    int wildness;
    int prorate;
};

class warrior:public soldier
{
    public:
    warrior(int type= 0, int Hp=100, int harm=4, int defense=3, int missrate=10, int level=1, int rage=0, int shield = 0, int freedom = 1, int speed = 2, int range = 1, int rageUp = 20):soldier(Hp,rage,missrate,harm,defense,shield,level,freedom,Hp,speed,range,type,defense,0,rageUp){}
    virtual void levelUp();
    virtual void relive();
    void buff();
};

class archer:public soldier
{
    public:
    archer(int type = 0, int Hp=60,int harm=6, int defense=1, int missrate=5, int level=1, int rage=0, int shield = 0, int freedom = 1, int speed = 1, int range = 3, int rageUp = 20):soldier(Hp,rage,missrate,harm,defense,shield,level,freedom,Hp,speed,range,type,defense,0,rageUp){}
    virtual void levelUp();
    virtual void relive();
    void buff();
};

class magician:public soldier
{
    public:
    magician(int type = 0, int Hp=50,int harm=5, int defense=2, int missrate=5, int level=1, int rage=0, int shield = 0, int freedom = 1, int speed = 1, int range = 3, int rageUp = 20):soldier(Hp,rage,missrate,harm,defense,shield,level,freedom,Hp,speed,range,type,defense,0,rageUp){}
    virtual void levelUp();
    virtual void relive();
    void buff();
};

class assassin:public soldier
{
    public:
    assassin(int type = 0, int Hp=70,int harm=7, int defense=1, int missrate=20, int level=1, int rage=0, int shield = 0, int freedom = 1, int speed = 3, int range = 2, int rageUp = 20):soldier(Hp,rage,missrate,harm,defense,shield,level,freedom,Hp,speed,range,type,defense,0,rageUp){}
    virtual void levelUp();
    virtual void relive();
    void buff();
};


#endif
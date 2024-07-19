#ifndef CHESS_TYPE_H
#define CHESS_TYPE_H
#include "chessbase.h"

//角色分为四个阵营，分别为粒子（particle），Reiki（灵气），元素（element）和野蛮（wild）各有特色

//particle来自未来，通过粒子科技进行打击，特点是防御很高
class particle 
{
    public:
    particle(int energyamount = 0):energyamount(energyamount),state(0),particleUp(34){}
    int changeparticle(int delta, int particleUp = 0);
    int getDelta();
    void switchstate();
    int showstate();
    private:
    int energyamount;
    int state;
    int particleUp;
};

//Reiki属于修仙世界，身手敏捷，特点是躲避能力强、近战伤害很高
class Reiki
{
    public:
    Reiki(int Reikiamount = 0):Reikiamount(0),state(0),ReikiUp(34){}
    void changeReiki(int ReikiAmount, int ReikiUp=0);
    int switchstate();
    std::vector<int> ReikiInfo();
    private:
    int Reikiamount;
    int state;
    int ReikiUp;
};

class element
{
    public:
    element(int fireflag = 0, int electricityflag = 0){}
    // void changeflag(int fire, int elctricity);
    private:
    int fireflag;
    int electricityflag;
};

class wild
{
    public:
    wild(int wildness = 0){}
    // void changewildness(int delta);
    private:
    int wildness;
};

class warrior:public soldier
{
    public:
    warrior(int type= 0, int Hp=50, int harm=4, int defense=3, int missrate=10, int level=1, int rage=0, int shield = 0, int freedom = 1, int speed = 2, int range = 1, int rageUp = 20):soldier(Hp,rage,missrate,harm,defense,shield,level,freedom,Hp,speed,range,type,defense,0,rageUp){}
    virtual void levelUp();
};

class archer:public soldier
{
    public:
    archer(int type = 0, int Hp=30,int harm=6, int defense=1, int missrate=5, int level=1, int rage=0, int shield = 0, int freedom = 1, int speed = 1, int range = 3, int rageUp = 20):soldier(Hp,rage,missrate,harm,defense,shield,level,freedom,Hp,speed,range,type,defense,0,rageUp){}
    virtual void levelUp();
};

class magician:public soldier
{
    public:
    magician(int type = 0, int Hp=25,int harm=5, int defense=2, int missrate=5, int level=1, int rage=0, int shield = 0, int freedom = 1, int speed = 1, int range = 3, int rageUp = 20):soldier(Hp,rage,missrate,harm,defense,shield,level,freedom,Hp,speed,range,type,defense,0,rageUp){}
    virtual void levelUp();
};

class assassin:public soldier
{
    public:
    assassin(int type = 0, int Hp=35,int harm=7, int defense=1, int missrate=20, int level=1, int rage=0, int shield = 0, int freedom = 1, int speed = 3, int range = 2, int rageUp = 20):soldier(Hp,rage,missrate,harm,defense,shield,level,freedom,Hp,speed,range,type,defense,0,rageUp){}
    virtual void levelUp();
};

class Mecha:public soldier, public particle
{
    public:
    Mecha(int Hp=70, int harm=8, int defense=4, int missrate=0, int level=0, int rage=0, int shield = 0, int energyamount=0, int freedom = 1, int speed = 2, int range = 2, int type=0):soldier(Hp,rage,missrate,harm,defense,shield,level,freedom,Hp,speed,range,type,defense),particle(energyamount){}
};

class JadeEmperor:public soldier, public Reiki
{
    JadeEmperor(int Hp=30, int harm=12, int defense=8, int missrate=30, int level=0, int rage=0, int shield = 0, int Reikiamount=0, int freedom = 1, int speed = 1, int range =5, int type =0):soldier(Hp,rage,missrate,harm,defense,shield,level,freedom,Hp,speed,range,type,defense),Reiki(Reikiamount){}
};

class Dragon:public soldier, public element
{
    Dragon(int Hp=40, int harm=6, int defense=5, int missrate=15, int level=0, int rage=0, int shield = 0, int freedom = 1, int speed = 2, int fire=1, int electricity=1, int range =4, int type =0):soldier(Hp,rage,missrate,harm,defense,shield,level,freedom,Hp,speed,range,type,defense),element(fire,electricity){}
};

class werewolf:public soldier, public wild
{
    werewolf(int Hp=100, int harm=8, int defense=2, int missrate=20, int level=0, int rage=0, int shield = 0, int freedom = 1, int speed = 5, int wildness=0, int range =1, int type =0):soldier(Hp,rage,missrate,harm,defense,shield,level,freedom,Hp,speed,range,type,defense),wild(wildness){}
};

class ParticleWarrior:public warrior, public particle
{
    public:
    ParticleWarrior():warrior(1),particle(){}
    virtual void done(std::vector<std::vector<int>> position);
    virtual void show();
    virtual void levelUp();
};

class LaserArcher:public archer, public particle
{
    public:
    LaserArcher():archer(2),particle(){}
    virtual void done(std::vector<std::vector<int>> position);
    virtual void show();
    virtual void levelUp();
};

class ParticleEngineer:public magician, public particle
{
    public:
    ParticleEngineer():magician(3,25,0,2,5,1,20,0,1,0,20),particle(){}
    virtual void done(std::vector<std::vector<int>> position);
    virtual void show();
    virtual void levelUp();
};

class DimensionAssassin:public assassin, public particle
{
    public:
    DimensionAssassin():assassin(4),particle(){}
    virtual void done(std::vector<std::vector<int>> position);
    virtual void show();
    virtual void levelUp();
};

class Swordman:public warrior, public Reiki
{
    public:
    Swordman():warrior(5),Reiki(){}
    virtual void done(std::vector<std::vector<int>> position);
    virtual void show();
    virtual void levelUp();
};

class Hypnotist:public archer, public Reiki
{
    public:
    Hypnotist():archer(6),Reiki(){}
    virtual void done(std::vector<std::vector<int>> position);
    virtual void show();
    virtual void levelUp();
};

#endif
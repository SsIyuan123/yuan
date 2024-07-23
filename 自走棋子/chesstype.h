#ifndef CHESS_TYPE_H
#define CHESS_TYPE_H
#include "chessbase.h"

class ParticleWarrior:public warrior, public particle
{
    public:
    ParticleWarrior():warrior(1),particle(){}
    virtual void done(std::vector<std::vector<int>> position);
    virtual void show();
    virtual void levelUp();
    virtual void relive();
    virtual void makebaseBuff(int index);
};

class LaserArcher:public archer, public particle
{
    public:
    LaserArcher():archer(2),particle(){}
    virtual void done(std::vector<std::vector<int>> position);
    virtual void show();
    virtual void levelUp();
    virtual void relive();
    virtual void makebaseBuff(int index);
};

class ParticleEngineer:public magician, public particle
{
    public:
    ParticleEngineer():magician(3,25,0,2,5,1,20,0,1,0,20),particle(){}
    virtual void done(std::vector<std::vector<int>> position);
    virtual void show();
    virtual void levelUp();
    virtual void relive();
    virtual void makebaseBuff(int index);
};

class DimensionAssassin:public assassin, public particle
{
    public:
    DimensionAssassin():assassin(4),particle(){}
    virtual void done(std::vector<std::vector<int>> position);
    virtual void show();
    virtual void levelUp();
    virtual void relive();
    virtual void makebaseBuff(int index);
};

class Swordman:public warrior, public Reiki
{
    public:
    Swordman():warrior(5),Reiki(){}
    virtual void done(std::vector<std::vector<int>> position);
    virtual void show();
    virtual void levelUp();
    virtual void relive();
    virtual void makebaseBuff(int index);
};

class Hypnotist:public archer, public Reiki
{
    public:
    Hypnotist():archer(6),Reiki(){}
    virtual void done(std::vector<std::vector<int>> position);
    virtual void show();
    virtual void levelUp();
    virtual void relive();
    virtual void makebaseBuff(int index);
};

class Fulu_Painter:public magician,public Reiki
{
    public:
    Fulu_Painter():magician(7),Reiki(){}
    virtual void done(std::vector<std::vector<int>> position);
    virtual void show();
    virtual void levelUp();
    virtual void relive();
    virtual void makebaseBuff(int index);
    void thumder_Fu(std::vector<std::vector<int>> position);
    void wind_Fu(std::vector<std::vector<int>> position);
    void quake_Fu(std::vector<std::vector<int>> position);
    void fire_Fu(std::vector<std::vector<int>> position);
    void vine_Fu(std::vector<std::vector<int>> position);
    void Rage_Fu(std::vector<std::vector<int>> position);
};

class Sorcerer:public assassin, public Reiki
{
    public:
    Sorcerer():assassin(8),Reiki(){}
    virtual void done(std::vector<std::vector<int>> position);
    virtual void show();
    virtual void levelUp();
    virtual void relive();
    virtual void makebaseBuff(int index);
};

class fire_Warrior:public warrior, public element
{
    public:
    fire_Warrior():warrior(9),element(),fireAmount(0),fireharm(1),rate(3),firestrengthTime(0){}
    virtual void done(std::vector<std::vector<int>> position);
    virtual void show();
    virtual void levelUp();
    virtual void relive();
    virtual void makebaseBuff(int index);
    void buff();
    private:
    int fireAmount;
    int fireharm;
    int rate;
    int firestrengthTime;
};

class electri_Archer:public archer, public element
{
    public:
    electri_Archer():archer(10),element(){}
    virtual void done(std::vector<std::vector<int>> position);
    virtual void show();
    virtual void levelUp();
    virtual void relive();
    virtual void makebaseBuff(int index);
    void chain_electricity(std::vector<std::vector<int>> position);
    void buff();
};

class ice_Magician:public magician, public element
{
    public:
    ice_Magician():magician(11),element(){}
    virtual void done(std::vector<std::vector<int>> position);
    virtual void show();
    virtual void levelUp();
    virtual void relive();
    virtual void makebaseBuff(int index);
    void buff();
}; 

class vortexSailer:public assassin, public element
{
    public:
    vortexSailer();
    virtual void done(std::vector<std::vector<int>> position);
    virtual void show();
    virtual void levelUp();  
    virtual void relive(); 
    virtual void makebaseBuff(int index);
    void buff();
    private:
    int worldnum;
    static std::vector<int> allWorld;
};

class wereWolf:public warrior, public wild
{
    public:
    wereWolf():warrior(13),wild(),bloody(0),bloodstate(0),bloodstatetime(0){}
    virtual void done(std::vector<std::vector<int>> position);
    virtual void show();
    virtual void levelUp();
    virtual void relive();
    virtual void makebaseBuff(int index);
    private:
    int bloody;
    int bloodstate;
    int bloodstatetime;

};

class Dragon:public archer, public wild
{
    public:
    Dragon():archer(14,40),wild(){}
    virtual void done(std::vector<std::vector<int>> position);
    virtual void show();
    virtual void levelUp();
    virtual void relive();
    virtual void makebaseBuff(int index);
};

class wild_Priest:public magician, public wild
{
    public:
    wild_Priest():magician(15),wild(){}
    virtual void done(std::vector<std::vector<int>> position);
    virtual void show();
    virtual void relive();
    virtual void levelUp();
    virtual void makebaseBuff(int index);
};

class Dryads:public assassin, public wild
{
    public:
    Dryads():assassin(16),wild(),usedblood(0),blood(0){}
    virtual void done(std::vector<std::vector<int>> position);
    virtual void show();
    virtual void relive();
    virtual void levelUp();
    virtual void makebaseBuff(int index);
    int usedblood;
    int blood;
};

#endif
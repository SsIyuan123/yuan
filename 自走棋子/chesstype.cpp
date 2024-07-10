#include"chesstype.h"
#include"tools.h"
#include<iostream>

void soldier::checkState(int x, int y, int num)
{
    if(x==10&&y==10)
    {
        for(int i=0;i<MyState.getInfo().first.size();i++)
            if(MyState.getInfo().second[1][i]==0)
                switch((int)MyState.getInfo().first[i])
                {
                    case 1:addindex(0,0,0,0,MyState.getInfo().second[0][i]);break;
                    case 2:addindex(0,0,0,-MyState.getInfo().second[0][i]);break;
                    case 3:addindex(0,0,-MyState.getInfo().second[0][i]);break;
                    case 4:addindex(0,0,0,0,0,-MyState.getInfo().second[0][i]);break;
                    case 6:switching(&freedom);
                    default:break;
                }
        MyState.erase();
        for(int i=0;i<MyState.getInfo().first.size();i++)
            switch((int)MyState.getInfo().first[i])
            {
                case 1:addindex(0,0,0,0,-MyState.getInfo().second[0][i]);break;
                case 2:addindex(0,0,0,+MyState.getInfo().second[0][i]);break;
                case 3:addindex(0,0,-MyState.getInfo().second[0][i]);break;
                case 4:addindex(0,0,0,0,0,+MyState.getInfo().second[0][i]);break;
                case 5:addindex(-MyState.getInfo().second[0][i]);break;
                case 7:addindex(-MyState.getInfo().second[0][i]);break;
                case 6:switching(&freedom);break;
                default:break;
            }  
        MyState.settlement();  
    }
    else
    {
        for(int i=0;i<BearState.getInfo().first.size();i++)
        {
            if(BearState.getInfo().second[3][i]==x&&BearState.getInfo().second[4][i]==y&&BearState.getInfo().second[2][i]==num)
                if(BearState.getInfo().second[1][i]==0)
                    switch((int)BearState.getInfo().first[i])
                    {
                        case 1:addindex(0,0,0,0,BearState.getInfo().second[0][i]);break;
                        case 2:addindex(0,0,0,-BearState.getInfo().second[0][i]);break;
                        case 3:addindex(0,0,-BearState.getInfo().second[0][i]);break;
                        case 4:addindex(0,0,0,0,0,-BearState.getInfo().second[0][i]);break;
                        case 6:switching(&freedom);
                        default:break;
                    }
            BearState.erase(x,y,num);
        }
        for(int i=0;i<BearState.getInfo().first.size();i++)
        {
            if(BearState.getInfo().second[3][i]==x&&BearState.getInfo().second[4][i]==y&&BearState.getInfo().second[2][i]==num)
                switch((int)BearState.getInfo().first[i])
                {
                    case 1:addindex(0,0,0,0,-BearState.getInfo().second[0][i]);break;
                    case 2:addindex(0,0,0,+BearState.getInfo().second[0][i]);break;
                    case 3:addindex(0,0,-BearState.getInfo().second[0][i]);break;
                    case 4:addindex(0,0,0,0,0,+BearState.getInfo().second[0][i]);break;
                    case 5:addindex(-BearState.getInfo().second[0][i]);break;
                    case 7:addindex(-BearState.getInfo().second[0][i]);break;
                    case 6:switching(&freedom);break;
                    default:break;
                }  
            BearState.settlement(x,y,num);  
        }
    }
}

void soldier::addindex(int Hp, int rage, int missrate, int harm, int defense, int shield, int level, int MaxHp, int speed, int range)
{
    this->Hp=edge(this->Hp+Hp,0,MaxHp);
    this->shield=edgeleft(this->shield+shield,0);
    this->level+=level;
    this->harm=edgeleft(this->harm+harm,0);
    this->defense=edgeleft(this->defense+defense,0);
    this->missrate=edge(this->missrate+missrate,0,100);
    this->rage=edge(this->rage+rage,0,100);
    this->MaxHp=edgeleft(this->MaxHp+MaxHp,0);
    this->speed=edgeleft(this->speed+speed,0);
    this->range=edgeleft(this->range+range,0);
}

void soldier::makerecord(int zhenying, int x, int y, soldierState a, int strength, int duration)
{
    record.SthHappen(a,strength,duration,zhenying,x,y);
}

State soldier::recordRun()//meixiewan
{
    State tem=record;
    record.clear();
    return tem;
}

void soldier::changeMyState(int a, int strength, int duration, int x, int y, int zhenying)
{
    if( zhenying == 0 && x == 10 && y == 10 )
        MyState.SthHappen((soldierState)a,strength,duration,zhenying,x,y);
    else 
        BearState.SthHappen((soldierState)a,strength,duration,zhenying,x,y);
}

int* soldier::getInfo()
{
    int* Info = new int[12];
    Info[0]=Hp,
    Info[1]=rage,
    Info[2]=missrate,
    Info[3]=harm,
    Info[4]=defense,
    Info[5]=shield,
    Info[6]=level,
    Info[7]=freedom,
    Info[8]=MaxHp,
    Info[9]=speed;
    Info[10]=range;
    Info[11]=(int)type;
    return Info;
}

State::State()
{
    a.push_back((soldierState)0);
    strength.push_back(999);
    duration.push_back(999);
    YouOrMe.push_back(0);
    position[0].push_back(0),position[1].push_back(0);
}

State::State(const State&tem)
{
    a=tem.a;
    duration=tem.duration;
    strength=tem.strength;
    YouOrMe=tem.YouOrMe;
    position[0]=tem.position[0],position[1]=tem.position[1];
}

std::pair<std::vector<soldierState>,std::vector<std::vector<int>>> State::getInfo()
{
    std::pair<std::vector<soldierState>,std::vector<std::vector<int>>> tem;
    tem.first=a;
    std::vector<std::vector<int>> tem1;
    tem1.push_back(strength),tem1.push_back(duration),tem1.push_back(YouOrMe),tem1.push_back(position[0]),tem1.push_back(position[1]);
    tem.second=tem1;
    return tem;
}

void State::SthHappen(soldierState a, int strength, int duration, int zhenying, int x, int y)
{
    if(this->a.size()!=0)
        if(this->a.front()==(soldierState)0)
        {
            this->a.clear();
            this->strength.clear();
            this->duration.clear();
            YouOrMe.clear();
            position[0].clear(),position[1].clear();
        }
    this->a.push_back(a);
    this->strength.push_back(strength);
    this->duration.push_back(duration);
    YouOrMe.push_back(zhenying);
    position[0].push_back(x), position[1].push_back(y);
}

void State::settlement(int x, int y, int num)
{
    int length=a.size();
    if(x==0&&y==0)
    {
        for(int i=0;i<length;i++)
        duration[i]--;
    }
    else
    {
        for(int i=0;i<length;i++)
            if(position[0][i]==x&&position[1][i]==y&&YouOrMe[i]==num)
                duration[i]--;
    }
}

void State::clear()
{
    while(a[0]!=(soldierState)0)
        settlement(),erase();
}

void State::erase(int x, int y, int num)
{
    int length=a.size();
    if(x==0&&y==0)
    {
        for(int i=length-1;i>=0;i--)
            if(duration[i]==0)
            {
                a.erase(a.begin()+i);
                strength.erase(strength.begin()+i);
                duration.erase(duration.begin()+i);
                YouOrMe.erase(YouOrMe.begin()+i);
                position[0].erase(position[0].begin()+i);
                position[1].erase(position[1].begin()+i);
            }
    }
    else
        for(int i=0;i<length;i++)
            if(position[0][i]==x&&position[1][i]==y&&duration[i]==0&&YouOrMe[i]==num)
            {
                a.erase(a.begin()+i);
                strength.erase(strength.begin()+i);
                duration.erase(duration.begin()+i);
                YouOrMe.erase(YouOrMe.begin()+i);
                position[0].erase(position[0].begin()+i);
                position[1].erase(position[1].begin()+i);
            }
    if(a.size()==0)
        SthHappen((soldierState)0,999,999,0,0,0);
}


int particle::changeparticle(int delta)
{
    energyamount=edge(energyamount+delta,0,100);
    return energyamount;
}

void particle::switchstate()
{
    switching(&state);
}

int particle::showstate()
{
    return state;
}

int Reiki::changeReiki(int delta)
{
    Reikiamount=edge(Reikiamount+delta,0,100);
    return Reikiamount;
}

int Reiki::switchstate()
{
    if(state==0)
        state=1;
    else
        state=0;
        return state;
}

void ParticleWarrior::done(int *position[3])
{
    if(getInfo()[7]==0) return;
    if(getInfo()[1]!=100)
    {
        if(showstate()==0)
                makerecord(1,position[0][0],position[0][0],(soldierState)2,getInfo()[3],1),changeparticle(34);
        else
        {
            changeMyState(4,3+getInfo()[5]*2,1);
            changeMyState(2,getInfo()[3]*((double)getInfo()[6]/2.0+0.5),1);
            switchstate();
        }
        if(changeparticle(0)==100)
            switchstate();
        addindex(0,20);
    }
    else
    {
        addindex(getInfo()[8]/3);
        changeMyState(2,2,2);
    }
}

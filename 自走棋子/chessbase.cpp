#include"chessbase.h"
#include"tools.h"
#include<iostream>
#include<iomanip>

void soldier::checkState(int x, int y, int num)
{
    if(x==10&&y==10)
    {
        for(int i=0;i<MyState.getInfo().first.size();i++)
            if(MyState.getInfo().second[1][i]==0)
            {
                switch((int)MyState.getInfo().first[i])
                {
                    case 1:
                    {
                        if(MyState.getInfo().second[0][i]>=100)
                            addindex(0,0,0,0,Up_quzheng(Maxdefense*(double)BearState.getInfo().second[0][i]/10000));
                        else
                            addindex(0,0,0,0,MyState.getInfo().second[0][i]);
                        break;
                    }
                    case 2:addindex(0,0,0,-MyState.getInfo().second[0][i]);break;
                    case 3:addindex(0,0,-MyState.getInfo().second[0][i]);break;
                    case 4:
                    {
                        if(MyState.getInfo().second[0][i]>=100)
                            addindex(0,0,0,0,0,-MaxHp*(double)MyState.getInfo().second[0][i]/10000.0);
                        else
                            addindex(0,0,0,0,0,-MyState.getInfo().second[0][i]);
                        break;
                    }
                    case 6:switching(&freedom);break;
                    case 9:switching(&chaos);break;
                    case 11:addindex(0,0,0,0,0,0,0,0,0,0,-MyState.getInfo().second[0][i]);break;
                    default:break;
                }
            }
        MyState.erase();
        for(int i=0;i<MyState.getInfo().first.size();i++)
            switch((int)MyState.getInfo().first[i])
            {
                case 1:
                {
                    if(MyState.getInfo().second[1][i]==MyState.getInfo().second[5][i])
                    {
                        if(MyState.getInfo().second[0][i]>=100)
                            addindex(0,0,0,0,-Up_quzheng(Maxdefense*(double)BearState.getInfo().second[0][i]/10000.0));
                        else
                            addindex(0,0,0,0,-MyState.getInfo().second[0][i]);
                    }
                    break;
                }
                case 2:
                {
                    if(MyState.getInfo().second[1][i]==MyState.getInfo().second[5][i])
                        addindex(0,0,0,+MyState.getInfo().second[0][i]);
                    break;
                }
                case 3:
                {
                    if(MyState.getInfo().second[1][i]==MyState.getInfo().second[5][i])
                        addindex(0,0,MyState.getInfo().second[0][i]);
                    break;
                }
                case 4:
                {
                    if(MyState.getInfo().second[1][i]==MyState.getInfo().second[5][i])
                    {
                        if(MyState.getInfo().second[0][i]>=100)
                            addindex(0,0,0,0,0,MaxHp*(double)MyState.getInfo().second[0][i]/10000.0);
                        else
                            addindex(0,0,0,0,0,+MyState.getInfo().second[0][i]);
                    }
                    break;
                }
                case 5:
                {
                    if(MyState.getInfo().second[0][i]>=100)
                        addindex(-MyState.getInfo().second[0][i]*MaxHp/10000.0);
                    else
                        addindex(-MyState.getInfo().second[0][i]);
                    break;
                }
                case 7:
                {
                    if(random()<missrate)
                        {std::cout<<"miss!"<<std::endl;break;}
                    if(shield>=MyState.getInfo().second[0][i])
                        addindex(0,0,0,0,0,-MyState.getInfo().second[0][i]);
                    else
                    {
                        int harming=MyState.getInfo().second[0][i]-shield;
                        // std::cout<<"Rebound "<<Up_quzheng(harming*cifang(0.75,defense))<<std::endl;
                        addindex(-Up_quzheng(harming*cifang(0.75,defense)));
                        shield=0;
                    }
                    break;
                }
                case 6:
                {
                    if(MyState.getInfo().second[1][i]==MyState.getInfo().second[5][i])
                        switching(&freedom);
                    break;
                }
                case 9:
                {
                    if(MyState.getInfo().second[1][i]==MyState.getInfo().second[5][i])
                        switching(&chaos);
                    break;
                }
                case 11:
                {
                    if(MyState.getInfo().second[1][i]==MyState.getInfo().second[5][i])
                        addindex(0,0,0,0,0,0,0,0,0,0,MyState.getInfo().second[0][i]);
                    break;
                }
                case 12:
                {
                    if(MyState.getInfo().second[1][i]==MyState.getInfo().second[5][i])
                        addindex(0,0,0,0,0,0,0,0,0,0,0,0,0,MyState.getInfo().second[0][i]);
                    break;
                }
                default:break;
            }  
        MyState.settlement();  
    }
    else
    {
        for(int i=0;i<BearState.getInfo().first.size();i++)
            if(BearState.getInfo().second[3][i]==x&&BearState.getInfo().second[4][i]==y&&BearState.getInfo().second[2][i]==num)
                if(BearState.getInfo().second[1][i]==0)
                {
                    switch((int)BearState.getInfo().first[i])
                    {
                        case 1:
                        {
                            if(BearState.getInfo().second[0][i]>=100)
                                addindex(0,0,0,0,Up_quzheng(Maxdefense*(double)BearState.getInfo().second[0][i]/10000.0));
                            else
                                addindex(0,0,0,0,BearState.getInfo().second[0][i]);
                            break;
                        }
                        case 2:addindex(0,0,0,-BearState.getInfo().second[0][i]);break;
                        case 3:addindex(0,0,-BearState.getInfo().second[0][i]);break;
                        case 4:
                        {                       
                            if(BearState.getInfo().second[0][i]>=100)
                                addindex(0,0,0,0,0,-MaxHp*(double)BearState.getInfo().second[0][i]/10000.0);
                            else
                                addindex(0,0,0,0,0,-BearState.getInfo().second[0][i]);
                            break;
                        }
                        case 5:
                        {
                            if(BearState.getInfo().second[0][i]>=100)
                                makerecord(BearState.getInfo().second[2][i],BearState.getInfo().second[3][i],BearState.getInfo().second[4][i],(soldierState)10,BearState.getInfo().second[0][i]*MaxHp/10000.0,1);
                        }
                        case 6:switching(&freedom);break;
                        case 9:switching(&chaos);break;
                        case 11:addindex(0,0,0,0,0,0,0,0,0,0,-BearState.getInfo().second[0][i]);break;
                        default:break;
                    }
                }
        BearState.erase(x,y,num);
        for(int i=0;i<BearState.getInfo().first.size();i++)
            if(BearState.getInfo().second[3][i]==x&&BearState.getInfo().second[4][i]==y&&BearState.getInfo().second[2][i]==num)
            {
                switch((int)BearState.getInfo().first[i])
                {
                    case 1:
                    {
                        if(BearState.getInfo().second[1][i]==BearState.getInfo().second[5][i])
                        {
                            if(BearState.getInfo().second[0][i]>=100)
                                addindex(0,0,0,0,-Up_quzheng(Maxdefense*(double)BearState.getInfo().second[0][i]/10000.0));
                            else
                                addindex(0,0,0,0,-BearState.getInfo().second[0][i]);
                        }
                        break;
                    }
                    case 2:
                    {
                        if(BearState.getInfo().second[1][i]==BearState.getInfo().second[5][i])
                            addindex(0,0,0,+BearState.getInfo().second[0][i]);
                        break;
                    }
                    case 3:
                    {
                        if(BearState.getInfo().second[1][i]==BearState.getInfo().second[5][i])
                            addindex(0,0,BearState.getInfo().second[0][i]);
                        break;
                    }
                    case 4:
                    {
                        if(BearState.getInfo().second[1][i]==BearState.getInfo().second[5][i])
                        {
                            if(BearState.getInfo().second[0][i]>=100)
                                addindex(0,0,0,0,0,MaxHp*(double)BearState.getInfo().second[0][i]/10000.0);
                            else
                                addindex(0,0,0,0,0,+BearState.getInfo().second[0][i]);
                        }
                        break;
                    }
                    case 5:
                    {
                        if(BearState.getInfo().second[0][i]>=100)
                            addindex(-BearState.getInfo().second[0][i]*MaxHp/10000.0);
                        else
                            addindex(-BearState.getInfo().second[0][i]);
                        break;
                    }
                    case 7:
                    {
                        if(random()<missrate)
                            {std::cout<<"miss!"<<std::endl;break;}
                        if(shield>=BearState.getInfo().second[0][i])
                            addindex(0,0,0,0,0,-BearState.getInfo().second[0][i]);
                        else
                        {
                            int harming=BearState.getInfo().second[0][i]-shield;
                            addindex(-Up_quzheng(harming*cifang(0.75,defense)));
                            shield=0;
                        }
                        break;
                    }
                    case 6:
                    {
                        if(BearState.getInfo().second[1][i]==BearState.getInfo().second[5][i])
                            switching(&freedom);
                        break;
                    }
                    case 10:
                    {
                        if(BearState.getInfo().second[0][i]>=100)
                            addindex(MaxHp*(double)BearState.getInfo().second[0][i]/10000.0);
                        else
                            addindex(BearState.getInfo().second[0][i]);
                        break;
                    }
                    case 8:addindex(0,BearState.getInfo().second[0][i]);break;
                    case 9:
                    {
                        if(BearState.getInfo().second[1][i]==BearState.getInfo().second[5][i])
                            switching(&chaos);
                        break;
                    }
                    case 11:
                    {
                        if(BearState.getInfo().second[1][i]==BearState.getInfo().second[5][i])
                            addindex(0,0,0,0,0,0,0,0,0,0,BearState.getInfo().second[0][i]);
                        break;
                    }
                    case 12:
                    {
                        if(BearState.getInfo().second[1][i]==BearState.getInfo().second[5][i])
                            addindex(0,0,0,0,0,0,0,0,0,0,0,0,0,BearState.getInfo().second[0][i]);
                    }
                    default:break;
                    
                } 
        } 
        BearState.settlement(x,y,num);  
    }   
}

void soldier::addindex(int Hp, int rage, int missrate, int harm, int defense, int shield, int level, int MaxHp, int speed, int range, int reBound, int Maxdefense, int rageUp, int vine)
{
    this->Hp=edge(this->Hp+Hp,0,this->MaxHp);
    this->shield=edgeleft(this->shield+shield,0);
    this->level+=level;
    this->harm=edgeleft(this->harm+harm,0);
    this->defense=edgeleft(this->defense+defense,0);
    this->missrate=edge(this->missrate+missrate,0,100);
    this->rage=edge(this->rage+rage,0,100);
    this->MaxHp=edgeleft(this->MaxHp+MaxHp,0);
    this->speed=edgeleft(this->speed+speed,0);
    this->range=edgeleft(this->range+range,0);
    this->reBound=edgeleft(this->reBound+reBound,0);
    this->Maxdefense=edgeleft(this->Maxdefense+Maxdefense,0);
    this->rageUp+=rageUp;
    this->vine=edgeleft(this->vine+vine,0);
}

void soldier::makerecord(int zhenying, int x, int y, soldierState a, int strength, int duration)
{
    record.SthHappen(a,strength,duration,zhenying,x,y);
}

State soldier::recordRun()//meixiewan
{
    // std::cout<<"recordRun!"<<std::endl;
    State tem=record;
    record.clear();
    // std::cout<<"recordRun ends!"<<std::endl;
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
    int* Info = new int[17];
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
    Info[12]=Maxdefense;
    Info[13]=reBound;
    Info[14]=rageUp;
    Info[15]=chaos;
    Info[16]=vine;
    return Info;
}

void soldier::show()
{
    std::cout<<"Hp: "<<Hp<<"/"<<MaxHp<<std::right<<std::setw(20)<<"rage: "<<rage<<std::right<<std::setw(20)<<"missrate: "<<missrate<<std::right<<std::setw(20)<<"harm: "<<harm;toEnter(2);
    std::cout<<"defense :"<<defense<<std::right<<std::setw(20)<<"shield: "<<shield<<std::right<<std::setw(20)<<"level: "<<level<<std::right<<std::setw(20)<<"freedom: "<<freedom;toEnter(2);
    std::cout<<"speed: "<<speed<<std::right<<std::setw(20)<<"range: "<<range<<std::right<<std::setw(20)<<"warname: "<<type<<std::right<<std::setw(20)<<"reBound:"<<reBound;toEnter(2);
    std::cout<<"chaos: "<<chaos;toEnter(2);
    MyState.show();
}

State::State()
{
    a.push_back((soldierState)0);
    strength.push_back(999);
    duration.push_back(999);
    Totalduration.push_back(999);
    YouOrMe.push_back(0);
    position[0].push_back(0),position[1].push_back(0);
}

State::State(const State&tem)
{
    a=tem.a;
    Totalduration=tem.Totalduration;
    duration=tem.duration;
    strength=tem.strength;
    YouOrMe=tem.YouOrMe;
    position[0]=tem.position[0],position[1]=tem.position[1];
}

void State::show()
{
    // std::cout<<"amount:"<<a.size()<<std::endl;
    for(int i=0;i<a.size();i++)
    {std::cout<<"Type:"<<a[i]<<std::setw(10)<<"Strength:"<<strength[i]<<std::setw(10)<<"Duration:"<<duration[i]<<"/"<<Totalduration[i]<<std::setw(10)<<"zhenying:"<<YouOrMe[i]<<std::setw(10)<<"FrontlinePosition:("<<position[0][i]<<","<<position[1][i]<<")";toEnter(2);}
}

std::pair<std::vector<soldierState>,std::vector<std::vector<int>>> State::getInfo()
{
    std::pair<std::vector<soldierState>,std::vector<std::vector<int>>> tem;
    tem.first=a;
    std::vector<std::vector<int>> tem1;
    tem1.push_back(strength),tem1.push_back(duration),tem1.push_back(YouOrMe),tem1.push_back(position[0]),tem1.push_back(position[1]);
    tem1.push_back(Totalduration);
    tem.second=tem1;
    return tem;
}

void State::SthHappen(soldierState a, int strength, int duration, int zhenying, int x, int y)
{
    if(this->a.size()!=0)
        if(this->a.front()==(soldierState)0)
        {
            Totalduration.clear();
            this->a.clear();
            this->strength.clear();
            this->duration.clear();
            YouOrMe.clear();
            position[0].clear(),position[1].clear();
        }
    this->a.push_back(a);
    this->strength.push_back(strength);
    this->duration.push_back(duration);
    Totalduration.push_back(duration);
    YouOrMe.push_back(zhenying);
    position[0].push_back(x), position[1].push_back(y);
}

void State::settlement(int x, int y, int num)
{
    int length=a.size();
    if(x==10&&y==10)
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
    if(x==10&&y==10)
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
                Totalduration.erase(Totalduration.begin()+i);
            }
    }
    else
        for(int i=length-1;i>=0;i--)
            if(position[0][i]==x&&position[1][i]==y&&duration[i]==0&&YouOrMe[i]==num)
            {
                a.erase(a.begin()+i);
                strength.erase(strength.begin()+i);
                duration.erase(duration.begin()+i);
                YouOrMe.erase(YouOrMe.begin()+i);
                position[0].erase(position[0].begin()+i);
                position[1].erase(position[1].begin()+i);
                Totalduration.erase(Totalduration.begin()+i);
            }
    if(a.size()==0)
        SthHappen((soldierState)0,999,999,0,0,0);
}


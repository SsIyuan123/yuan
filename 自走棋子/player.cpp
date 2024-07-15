#include"player.h"
#include"tools.h"
#include<iostream>
#include<array>
#include<iomanip>
#include<chrono>
#include<thread>

player::player()
{
    std::cout<<"Please name your role (less than 20 characters):"<<std::endl;
    std::string a;
    std::getline(std::cin,a);
    while(a.length()>20)
    {
        std::cout<<"The length of your name is longer than 20. Please name your role again(less than 20 characters):"<<std::endl;
        std::getline(std::cin,a);
    }
    Money=3,level=1,experience=0,name=a;
}

player::player(char *name)
{
    this->name=name,Money=3,level=1,experience=0;
}

player::player(const player &tem)
{
    name=tem.name,
    Atroop=tem.Atroop;
    Money=tem.Money;
    level=tem.level;
    experience=tem.experience;
}

void player::IncreaseMoney(int x)
{
    Money+=x;
}

void player::gainExperience(int delta)
{
    int limit=400+level*100;
    if(experience+delta<limit)
        experience+=delta;
    else//每升3级，上场士兵+1；每升4级，仓库储存容量+1
    {
        level++,experience=experience+delta-limit;
        if(level%3==0)
            Atroop.changeAmount(0,0,0,1);
        if(level%4==0)
            Atroop.changeAmount(0,0,1,0);
    }
}

std::pair<std::string,int*> player::Getinfo()
{
    std::pair<std::string,int*> tem;
    tem.first=name;
    int* a = new int[3];
    a[0]=Money,a[1]=level,a[2]=experience;
    tem.second=a;
    return tem;
} 


troop::troop(const troop &tem)
{
    for(int i=0;i<2;i++)
        for(int j=0;j<5;j++)
            FrontDistribution[i][j]=tem.FrontDistribution[i][j];
    WarehouseSoldier=tem.WarehouseSoldier;
    AliveAmount=tem.AliveAmount;
    Warehouse_Amount=tem.Warehouse_Amount;
    OnFrontline_Amount=tem.OnFrontline_Amount;
    OnFrontline_limit=tem.OnFrontline_limit;
    Warehouse_limit=tem.OnFrontline_limit;
}

void troop::changeAmount(int deltaWareAmount, int deltaFrontAmount, int deltaWareLimit, int deltaFrontLimit)
{
    Warehouse_Amount+=deltaWareAmount;
    OnFrontline_Amount+=deltaFrontAmount;
    Warehouse_limit+=deltaWareLimit;
    OnFrontline_limit+=deltaFrontLimit;
    AliveAmount=OnFrontline_Amount;
}

void troop::gota(soldier *newsoldier)
{
    if(Warehouse_Amount==Warehouse_limit)
    {std::cout<<"Your warehouse is full so you cannot got it"<<std::endl;return;}
    WarehouseSoldier.push_back(newsoldier);
    Warehouse_Amount++;
}

int troop::getAlive()
{
    AliveAmount=0;
    for(int i=0;i<2;i++)
        for(int j=0;j<5;j++)
            if(FrontDistribution[i][j].getInfo().first[0]==1)
            {
                if(FrontDistribution[i][j].getInfo().second->getInfo()[0]==0&&FrontDistribution[i][j].getInfo().first[1]!=(soldiers)0)
                {
                    FrontDistribution[i][j].dying();
                }
            }
    for(int i=0;i<2;i++)
        for(int j=0;j<5;j++)
            if(FrontDistribution[i][j].getInfo().first[0]==1)
                if(FrontDistribution[i][j].getInfo().second->getInfo()[0]>0)
                    AliveAmount++;
    std::cout<<AliveAmount<<std::endl;
    return AliveAmount;
}

void troop::TurnOnFronter(soldier *a, int x, int y)
{
    if(OnFrontline_Amount==OnFrontline_limit)
    {std::cout<<"Your cannot afford the soldier to go on the frontline. Please make a personal change"<<std::endl;return;}
    if(FrontDistribution[x][y].getInfo().first[0]==1)
    {std::cout<<"The position has been occupied"<<std::endl;return;}
    int flag=0;
    for(int i=0;i<WarehouseSoldier.size();i++)
        if(a==WarehouseSoldier[i])
            flag=1;
    if(flag==0)
    {std::cout<<"There is no such hero in your warehouse."<<std::endl;return;}
    Warehouse_Amount--,OnFrontline_Amount++;
    for(int i=0;i<WarehouseSoldier.size();i++)
        if(WarehouseSoldier[i]==a)
            WarehouseSoldier.erase(WarehouseSoldier.begin()+i);
    FrontDistribution[x][y].lay(a,x,y);
}

void troop::showFrontline()
{
    std::cout<<"Your Frontline:"<<std::endl;
    for(int i=0;i<2;i++)
    {
        for(int j=0;j<5;j++)
        {
            if(FrontDistribution[i][j].getInfo().first[0]==0)
                std::cout<<std::setw(10)<<"0";
            else
                std::cout<<std::setw(10)<<FrontDistribution[i][j].getInfo().first[1]; 
        }
        std::cout<<std::endl;  
    }
    std::system("pause");
}

// void troop::levelUp(){}
void troop::MakeBack(int x, int y)
{
    if(MyCondition()[x][y].getInfo().first[0]==0)
    {std::cout<<"The position is empty"<<std::endl;return;}
    if(Warehouse_Amount==Warehouse_limit)
    {std::cout<<"The warehouse is full!"<<std::endl;return;}
    WarehouseSoldier.push_back(FrontDistribution[x][y].getInfo().second);
    FrontDistribution[x][y].go();
    Warehouse_Amount++,OnFrontline_Amount--;
}

std::pair<std::vector<soldier*>, int*> troop::GetInfo()
{
    std::pair<std::vector<soldier*>, int*> tem;
    tem.first = WarehouseSoldier;
    int* a = new int[4];
    a[0] = Warehouse_Amount;
    a[1] = OnFrontline_Amount;
    a[2] = Warehouse_limit;
    a[3] = OnFrontline_limit;
    a[4]=levelOne_Amount;
    a[5]=levelTwo_Amount;
    a[6]=levelThree_Amount;
    tem.second = a;
    return tem;
}

SoldierCondition** troop::MyCondition()
{
    SoldierCondition **tem = new SoldierCondition*[2];
    tem[0]=FrontDistribution[0],tem[1]=FrontDistribution[1];
    return tem;
}

SoldierCondition::SoldierCondition(const SoldierCondition &p) : vacancyindex(p.vacancyindex), type(p.type), a(p.a){}

std::pair<int*,soldier*> SoldierCondition::getInfo()
{
    std::pair<int*,soldier*> tt;
    int *tem = new int[7];
    tem[0]=vacancyindex,tem[1]=(int)type;
    tem[2]=zhenying,tem[3]=xFront,tem[4]=yFront,
    tem[5]=xWar,tem[6]=yWar;
    tt.first=tem;
    tt.second=a;
    return tt;
}

SoldierCondition SoldierCondition::input(SoldierCondition &tem, int zhenying, int x, int y)
{
    a=tem.a;
    type=tem.type;
    vacancyindex=tem.vacancyindex;
    this->zhenying=zhenying;
    xFront=tem.xFront,yFront=tem.yFront;
    if(x==10&&y==10)
    {
        yWar=tem.yFront;
        if(zhenying==0)
            xWar=getSwitchNum(tem.xFront);
        else 
            xWar=tem.xFront+8;
    }
    else
        xWar=x,yWar=y;
    // std::cout<<zhenying<<std::setw(10)<<"xWar:"<<xWar<<std::setw(10)<<"yWar:"<<yWar<<std::endl;
    return *this;
}

void SoldierCondition::lay(soldier * aa, int x, int y)
{
    a=aa,vacancyindex=1;
    type=(soldiers)aa->getInfo()[11];
    xFront=x,yFront=y;
}

void SoldierCondition::relive(int x)
{
    if(x==0)
        getInfo().second->addindex(getInfo().second->getInfo()[8]);
    else
        getInfo().second->addindex(x);
        type=(soldiers)getInfo().second->getInfo()[11];
}

void SoldierCondition::go()
{
    vacancyindex=0,type=(soldiers)0,zhenying=10,xFront=10,yFront=10,a=nullptr,xWar=100,yWar=100;
}

void SoldierCondition::dying()
{
    type=(soldiers)0;
}

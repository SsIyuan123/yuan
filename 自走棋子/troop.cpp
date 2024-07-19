#include "troop.h"
#include "tools.h"
#include <iostream>
#include <iomanip>
#include <array>

troop::troop(const troop &tem)
{
    for(int i=0;i<2;i++)
        for(int j=0;j<5;j++)
            FrontDistribution[i][j]=tem.FrontDistribution[i][j];
    MySoldier=tem.MySoldier;
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
    OnFrontline_limit=edgeright(OnFrontline_limit+deltaFrontLimit,4);
    AliveAmount=OnFrontline_Amount;
}

void troop::testOnFront(soldier* a, int x, int y)
{
    FrontDistribution[x][y].lay(a,x,y);
}

void troop::gota(soldier *newsoldier)
{
    if(Warehouse_Amount==Warehouse_limit)
    {std::cout<<"Your warehouse is full so you cannot got it"<<std::endl;return;}
    std::pair<int,soldier*>tem={0,newsoldier};
    MySoldier.push_back(tem);
    Warehouse_Amount++;
    std::cout<<Warehouse_Amount;
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

void troop::getdown()
{
    system("cls");
    std::cout<<std::setw(75)<<" "<<"MY TROOP";
    fengexian(0,160,2,4);
    std::cout<<std::setw(68)<<" "<<"To Change the Frontline";
    toEnter(3);
    showFrontline();
    fengexian(0,160,2,3);
    showAllSoldiers();
    toEnter(1);
    if(Warehouse_Amount==Warehouse_limit)
    {std::cout<<"Your Warehouse has been full. We can sell some of soldiers in store.";system("pause");return;}
    std::cout<<"Please input the position of the soldier you'd like to make it down the frontline:(row,column)";
    std::string input;
    std::cin>>input;toEnter(1);
    std::vector<char> number={'0','1','2','3','4','5','6','7','8','9'};
    int position[2],num=0;
    for(int i=0;i<input.size();i++)
        if(Include(input[i],number)==1)
            position[num]=(int)(input[i]-48)-1,num++;
    int* Info=FrontDistribution[position[0]][position[1]].getInfo().first;
    if(Info[0]==0)
    {std::cout<<"The position ("<<position[0]<<","<<position[1]<<") is empty. Check your intention.";system("pause");return;}
    delete[] Info;
    for(int i=0;i<MySoldier.size();i++)
        if(FrontDistribution[position[0]][position[1]].getInfo().second==MySoldier[i].second)
        {switching(&MySoldier[i].first);break;}
    FrontDistribution[position[0]][position[1]].go();
    Warehouse_Amount++,OnFrontline_Amount--;
    return;    
}

void troop::turnOnFrontline()
{
    system("cls");
    std::cout<<std::setw(75)<<" "<<"MY TROOP";
    fengexian(0,160,2,4);
    std::cout<<std::setw(68)<<" "<<"To Change the Frontline";
    toEnter(3);
    showFrontline();
    fengexian(0,160,2,3);
    showAllSoldiers();
    toEnter(1);
    if(OnFrontline_Amount==OnFrontline_limit)
    {std::cout<<"Your cannot afford the soldier to go on the frontline. Please make a personal change";system("pause");return;}
    std::cout<<"Please input the number of the soldier you'd like to make it on the frontline of all the soldiers:";
    int input;
    std::cin>>input;toEnter(1);
    input--;
    if(MySoldier[input].first==1)
    {std::cout<<"The soldier has been on the frontline. Check your intention";system("pause");return;}
    std::cout<<"Please input the position it will be:(row,column)";
    std::string inpu;
    std::cin>>inpu;toEnter(1);
    std::vector<char> number={'0','1','2','3','4','5','6','7','8','9'};
    int position[2],num=0;
    for(int i=0;i<inpu.size();i++)
        if(Include(inpu[i],number)==1)
            std::cout<<position[i]<<std::endl,position[num]=(int)(inpu[i]-48)-1,num++;
    std::cout<<position[0]<<position[1]<<std::endl;
    if(FrontDistribution[position[0]][position[1]].getInfo().first[0]==1)
    {std::cout<<"The position has been occupied";system("pause");return;}
    switching(&MySoldier[input].first);
    FrontDistribution[position[0]][position[1]].lay(MySoldier[input].second,position[0],position[1]);
    OnFrontline_Amount++,Warehouse_Amount--;
    return;
}

void troop::showFrontline()
{
    std::cout<<std::setw(72)<<" "<<"Your Frontline:";
    toEnter(3);
    std::cout<<std::setw(26)<<" ";
    for(int i=0;i<5;i++)
    {
        std::string tem="Column "+std::to_string(i+1);
        std::cout<<std::setw(11)<<" "<<tem;
    }
    toEnter(2);
    for(int i=0;i<2;i++)
    {
        std::cout<<std::right<<std::setw(20)<<"Row "<<i+1;
        for(int j=0;j<5;j++)
        {
            if(FrontDistribution[i][j].getInfo().first[0]==0)
                std::cout<<std::setw(20)<<"0";
            else
            {
                std::cout<<std::setw(20)<<FrontDistribution[i][j].getInfo().first[1]; 
            }
        }
        toEnter(3);
    }
    std::cout<<std::setw(30)<<" "<<"Soldiers on Frontline: "<<OnFrontline_Amount<<"/"<<OnFrontline_limit;
    std::cout<<std::setw(30)<<" "<<"Soldiers on Warehouse: "<<Warehouse_Amount<<"/"<<Warehouse_limit;
    toEnter(2);
}

void troop::sell(int x)
{
    if(MySoldier[x].first==1)
    {
        for(int i=0;i<2;i++)
            for(int j=0;j<5;j++)
                if(FrontDistribution[i][j].getInfo().second==MySoldier[x].second)
                {
                    FrontDistribution[i][j].go();
                    changeAmount(0,-1);
                }
    }
    if(MySoldier[x].first==0)
        changeAmount(-1);
    soldier* tem=MySoldier[x].second;
    MySoldier.erase(MySoldier.begin()+x);
    delete tem;
}

void troop::showAllSoldiers(int x)
{
    std::string tmp,name,type;
    if(x==100)
    {
        std::cout<<"These are all your soldiers:";
        toEnter(3);
        if(MySoldier.size()==0)
        {std::cout<<std::setw(40)<<" "<<"OMG!You don't have any soldiers :(";fengexian(0,160,2,2);return;}
        int times=Up_quzheng(MySoldier.size()/4.0);
        for(int j=0;j<times;j++)
        {
            for(int i=0;i+j*4<MySoldier.size()&&i<4;i++)
                std::cout<<std::setw(15)<<" "<<std::left<<std::setw(25)<<i+j*4+1;
            toEnter(2);
            for(int i=0;i+j*4<MySoldier.size()&&i<4;i++)
            {
                std::string level;
                level=std::to_string(MySoldier[i+j*4].second->getInfo()[6]);
                tmp="level: "+level;
                std::cout<<std::left<<std::setw(40)<<tmp;
            }
            toEnter(2);
            for(int i=0;i+j*4<MySoldier.size()&&i<4;i++)
            {
                switch(MySoldier[i+j*4].second->getInfo()[11])
                {
                    case 1:name="Particle Warrior";break;
                    case 2:name="Laser Archer";break;
                    case 3:name="Particle Engineer";break;
                    case 4:name="Dimension Assassin";break;            
                }
                tmp="name: "+name;
                std::cout<<std::left<<std::setw(40)<<tmp;
            }
            toEnter(2);
            for(int i=0;i+j*4<MySoldier.size()&&i<4;i++)
            {
                switch(MySoldier[i+j*4].second->getInfo()[11])
                {
                    case 1:type="Particle World, Warrior";break;
                    case 2:type="Particle World, Archer";break;
                    case 3:type="Particle World, Magician";break;
                    case 4:type="Particle World, Assassin";break;            
                }
                tmp="type: "+type;
                std::cout<<std::left<<std::setw(40)<<tmp;
            }
            toEnter(2);
            for(int i=0;i+j*4<MySoldier.size()&&i<4;i++)
            {
                std::string Position;
                switch(MySoldier[i+j*4].first)
                {
                    case 0:Position="Warehouse";break;
                    case 1:Position="Frontline";break;
                }
                tmp="Where: "+Position;
                std::cout<<std::left<<std::setw(40)<<tmp;
            }
            toEnter(2);
            for(int i=0;i+j*4<MySoldier.size()&&i<4;i++)
            {
                int* Info=MySoldier[i+j*4].second->getInfo();
                std::string warname=std::to_string(Info[11]);
                delete[] Info;
                tmp="Warname: "+warname;
                std::cout<<std::left<<std::setw(40)<<tmp;
            }
            toEnter(2);
            for(int i=0;i+j*4<MySoldier.size()&&i<4;i++)
            {
                std::string Detail;
                if(MySoldier[i+j*4].first==0)
                    Detail="Warehouse";
                else
                {
                    for(int x=0; x<2;x++)
                        for(int y=0;y<5;y++)
                            if(MySoldier[i].second==FrontDistribution[x][y].getInfo().second)
                            {
                                int* Info=FrontDistribution[x][y].getInfo().first;
                                Detail="("+std::to_string(Info[3]+1)+","+std::to_string(Info[4]+1)+")";
                            }
                }
                tmp="Detailed Position: "+Detail;
                std::cout<<std::left<<std::setw(40)<<tmp;
            }
            toEnter(3);
        }
    }
    else
    {
        int* Info=MySoldier[x].second->getInfo();
        std::cout<<std::setw(79)<<" "<<x+1;toEnter(2);
        tmp="level: "+std::to_string(Info[6]);
        std::cout<<std::left<<std::setw(65)<<" "<<tmp;toEnter(2);
        switch(Info[11])
        {
            case 1:name="Particle Warrior";break;
            case 2:name="Laser Archer";break;
            case 3:name="Particle Engineer";break;
            case 4:name="Dimension Assassin";break;            
        }
        tmp="name: "+name;
        std::cout<<std::left<<std::setw(65)<<" "<<tmp;toEnter(2);
        switch(Info[11])
        {
            case 1:type="Particle World, Warrior";break;
            case 2:type="Particle World, Archer";break;
            case 3:type="Particle World, Magician";break;
            case 4:type="Particle World, Assassin";break;            
        }
        tmp="type: "+type;
        std::cout<<std::left<<std::setw(65)<<" "<<tmp;toEnter(2);
        std::string Position;
        switch(MySoldier[x].first)
        {
            case 0:Position="Warehouse";break;
            case 1:Position="Frontline";break;
        }
        tmp="Where: "+Position;
        std::cout<<std::left<<std::setw(65)<<" "<<tmp;toEnter(2);
        std::string warname=std::to_string(Info[11]);
        tmp="Warname: "+warname;
        std::cout<<std::left<<std::setw(65)<<" "<<tmp;toEnter(2);
        std::string Detail;
        if(MySoldier[x].first==0)
            Detail="Warehouse";
        else
        {
            for(int i=0; i<2;i++)
                for(int j=0;j<5;j++)
                    if(MySoldier[x].second==FrontDistribution[i][j].getInfo().second)
                    {
                        int* Info=FrontDistribution[i][j].getInfo().first;
                        Detail="("+std::to_string(Info[3]+1)+","+std::to_string(Info[4]+1)+")";
                    }
        }
        tmp="Detailed Position: "+Detail;
        std::cout<<std::left<<std::setw(65)<<" "<<tmp;toEnter(2);
        delete[] Info;
    }
    fengexian(0,160,2,2);
}

// void troop::MakeBack(int x, int y)
// {
//     if(MyCondition()[x][y].getInfo().first[0]==0)
//     {std::cout<<"The position is empty"<<std::endl;return;}
//     if(Warehouse_Amount==Warehouse_limit)
//     {std::cout<<"The warehouse is full!"<<std::endl;return;}
//     for(int i=0;i<MySoldier.size();i++)
//         if(FrontDistribution[x][y].getInfo().second==MySoldier[i].second)
//             switching(&MySoldier[i].first);
//     FrontDistribution[x][y].go();
//     Warehouse_Amount++,OnFrontline_Amount--;
// }

std::pair<std::vector<std::pair<int,soldier*>>, int*> troop::GetInfo()
{
    std::pair<std::vector<std::pair<int,soldier*>>, int*> tem;
    tem.first = MySoldier;
    int* a = new int[7];
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

SoldierCondition::SoldierCondition(const SoldierCondition &p) : 
    vacancyindex(p.vacancyindex), type(p.type), a(p.a),
    zhenying(p.zhenying),xFront(p.xFront),yFront(p.yFront),
    xWar(p.xWar),yWar(p.yWar){}

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
    int *Info=getInfo().second->getInfo();
    if(x==0)
        getInfo().second->addindex(Info[8]);
    else
        getInfo().second->addindex(x);
    type=(soldiers)Info[11];
    delete[] Info;
}

void SoldierCondition::go()
{
    vacancyindex=0,type=(soldiers)0,zhenying=10,xFront=10,yFront=10,a=nullptr,xWar=100,yWar=100;
}

void SoldierCondition::dying()
{
    type=(soldiers)0;
}

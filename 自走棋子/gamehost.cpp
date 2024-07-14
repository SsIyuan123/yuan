#include"gamehost.h"
#include"tools.h"
#include<iostream>
#include<array>
#include<iomanip>
#include<chrono>
#include<thread>

playchess::playchess()
{
    playtime=0;
    palyernum=2;
    player m,n;
    A.push_back(m),A.push_back(n);
    circule=0;
    money_growth=3;
}


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

war::war(std::vector<player> enemy)
{
    if(enemy.size()!=2)
    {std::cout<<"The paticipants of the war are not 2"<<std::endl;return;}
    A=enemy;
    for(int i=0;i<2;i++)
        for(int j=0;j<5;j++)
        {
            if(A[0].MyTroop()->MyCondition()[i][j].getInfo().first[0]==1)
                WarPosition[getSwitchNum(i)][j].input(A[0].MyTroop()->MyCondition()[i][j],0);
            if(A[1].MyTroop()->MyCondition()[i][j].getInfo().first[0]==1)
                WarPosition[i+8][j].input(A[1].MyTroop()->MyCondition()[i][j],1);
        }
}

void war::show()
{
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<5;j++)
        {
            if(WarPosition[i][j].getInfo().first[0]==0)
                std::cout<<std::setw(10)<<"0";
            else
                std::cout<<std::setw(10)<<WarPosition[i][j].getInfo().first[1]; 
        }
        std::cout<<std::endl;  
    }
    for(int k=0;k<2;k++)
    {
        std::cout<<A[k].Getinfo().first<<":"<<std::endl;
        for(int i=0;i<2;i++)
            for(int j=0;j<5;j++)
                if(A[k].MyTroop()->MyCondition()[i][j].getInfo().first[0]==1)
                    A[k].MyTroop()->MyCondition()[i][j].getInfo().second->show();
    }
            
}

int* war::pickAttackingEnemy(int x)
{
    int temp=x;
    int enemy=switching(&temp);
    int *tem=new int[2];
    for(int j=0;j<2;j++)
        for(int i=0;i<5;i++)
        {
            if(A[enemy].MyTroop()->MyCondition()[j][i].getInfo().first[0]==1)
            {tem[0]=j,tem[1]=i;return tem;}
        }
    return nullptr;
}

int* war::pickLeastHpEnemy(int x)
{
    int temp=x;
    int enemy=switching(&temp);
    int HP[2][5]={0},min=1000;
    for(int i=0;i<2;i++)
        for(int j=0;j<5;j++)
            if(A[enemy].MyTroop()->MyCondition()[j][i].getInfo().first[0]==1)
                HP[i][j]=A[enemy].MyTroop()->MyCondition()[i][j].getInfo().second->getInfo()[0];
    static int tem[2]={FindMinPosition(HP)[0],FindMinPosition(HP)[1]};
    return tem;
}

int war::getFirst()
{
    if(random()<50)
        return 0;
    else return 1;
}

void war::effects(int number, int x, int y)
{
    std::cout<<"Effects!"<<std::endl;
    State Zhongzhuan=A[number].MyTroop()->MyCondition()[x][y].getInfo().second->recordRun();
    Zhongzhuan.show();
    if(Zhongzhuan.getInfo().first[0]!=(soldierState)0)
        for(int i=0;i<Zhongzhuan.getInfo().second[0].size();i++)
            A[Zhongzhuan.getInfo().second[2][i]].MyTroop()->MyCondition()[Zhongzhuan.getInfo().second[3][i]][Zhongzhuan.getInfo().second[4][i]].getInfo().second->changeMyState(Zhongzhuan.getInfo().first[i],Zhongzhuan.getInfo().second[0][i],Zhongzhuan.getInfo().second[1][i],x,y,number);
    std::cout<<"effects end"<<std::endl;
}

int war::MakeDistance(int a[10][5], int zhenying, int x, int y)
{
    // std::cout<<"make distance"<<std::endl;
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 5; j++)
            a[i][j] = 100;  // 先找到一个充分大的数
    // std::cout<<x<<y<<std::endl;
    a[x][y]=0;
    int aa = 1,k=0;             // 距离目标格子距离为k的格子有aa个
    while (aa != 0)
    {
        k++;
        aa = 0;
        for (int i = 0; i < 10; i++)
            for (int j = 0; j < 5; j++)
                if (a[i][j] == k - 1)
                {
                    if (i > 0)
                        if (a[i - 1][j] >= k)
                                a[i - 1][j] = k, aa++;
                    if (i < 9)
                        if (a[i + 1][j] >= k)
                                a[i + 1][j] = k, aa++;
                    if (j < 4)
                        if (a[i][j + 1] >= k)
                                a[i][j + 1] = k, aa++;
                    if (j > 0)
                        if (a[i][j - 1] >= k)
                                a[i][j - 1] = k, aa++;
                }
        // for(int i=0;i<10;i++)
        // {
        //     for(int j=0;j<5;j++)
        //         std::cout<<std::setw(10)<<a[i][j];
        //     std::cout<<std::endl;
        // }
        // std::cout<<k<<std::endl;
    }
    // std::cout<<"make distance out"<<k-1<<std::endl;
    // for(int i=0;i<10;i++)
    // {
    //     for(int j=0;j<5;j++)
    //         std::cout<<std::setw(10)<<a[i][j];
    //     std::cout<<std::endl;
    // }
    return k-1;
}

void war::deadout()
{
    for(int i=0;i<10;i++)
        for(int j=0;j<5;j++)
            if(WarPosition[i][j].getInfo().first[0]==1)
                if(WarPosition[i][j].getInfo().second->getInfo()[0]==0)
                    WarPosition[i][j].go();
}

void war::moveOrAttack(int zhenying, int xFront, int yFront)
{
    int a[10][5],k,xWar,yWar;
    for(int i=0;i<10;i++)
        for(int j=0;j<5;j++)
            if(WarPosition[i][j].getInfo().first[2]==zhenying&&WarPosition[i][j].getInfo().first[3]==xFront&&WarPosition[i][j].getInfo().first[4]==yFront)
                k=MakeDistance(a,zhenying,WarPosition[i][j].getInfo().first[5],WarPosition[i][j].getInfo().first[6]),xWar=WarPosition[i][j].getInfo().first[5],yWar=WarPosition[i][j].getInfo().first[6];
    std::vector<std::array<int,3>> distance;
    distance.clear();
    for(int i=1;i<k;i++)
        for(int row=0;row<10;row++)
            for(int column=0;column<5;column++)
                if(WarPosition[row][column].getInfo().first[0]==1&&WarPosition[row][column].getInfo().first[2]==getSwitchNum(zhenying)&&a[row][column]==i)
                {
                    std::array<int,3> tem={a[row][column],row,column};
                    distance.push_back(tem);
                }
    if(distance[0][0]<=A[zhenying].MyTroop()->MyCondition()[xFront][yFront].getInfo().second->getInfo()[10])
    {
        std::vector<int> xx,yy,zz;
        switch(A[zhenying].MyTroop()->MyCondition()[xFront][yFront].getInfo().first[1])
        {
            case 1:
            {
                xx.push_back(WarPosition[distance[0][1]][distance[0][2]].getInfo().first[3]),yy.push_back(WarPosition[distance[0][1]][distance[0][2]].getInfo().first[4]),zz.push_back(WarPosition[distance[0][1]][distance[0][2]].getInfo().first[2]);
                break;
            }
            case 2:
            {
                xx.push_back(WarPosition[distance[0][1]][distance[0][2]].getInfo().first[3]),yy.push_back(WarPosition[distance[0][1]][distance[0][2]].getInfo().first[4]),zz.push_back(WarPosition[distance[0][1]][distance[0][2]].getInfo().first[2]);
                for(int i=0;i<distance.size();i++)
                    if(i>0&&(yWar-distance[i][2])*(xWar-distance[0][1])==(xWar-distance[i][1])*(yWar-distance[0][2]))
                        xx.push_back(WarPosition[distance[i][1]][distance[i][2]].getInfo().first[3]),yy.push_back(WarPosition[distance[i][1]][distance[i][2]].getInfo().first[4]),zz.push_back(WarPosition[distance[i][1]][distance[i][2]].getInfo().first[2]);
                break;
            }
        }
        std::vector<std::vector<int>> tem;
        tem.push_back(xx),tem.push_back(yy),tem.push_back(zz);
        A[zhenying].MyTroop()->MyCondition()[xFront][yFront].getInfo().second->done(tem);
        effects(zhenying,xFront,yFront);
    }
    else
    {
        std::cout<<"Type "<<A[zhenying].MyTroop()->MyCondition()[xFront][yFront].getInfo().first[1]<<" soldier owned by "<<A[zhenying].Getinfo().first<<" move from ("<<xWar<<","<<yWar<<") to";
        int b[10][5];
        MakeDistance(b,WarPosition[distance[0][1]][distance[0][2]].getInfo().first[2],WarPosition[distance[0][1]][distance[0][2]].getInfo().first[5],WarPosition[distance[0][1]][distance[0][2]].getInfo().first[6]);
        for(int i=0;i<10;i++)
            for(int j=0;j<5;j++)
                if(a[i][j]==0)
                {WarPosition[i][j].go();break;}
        if(distance[0][0]>A[zhenying].MyTroop()->MyCondition()[xFront][yFront].getInfo().second->getInfo()[9])
        {
            for(int i=0;i<10;i++)
                for(int j=0;j<5;j++)
                    if(b[i][j]==distance[0][0]-A[zhenying].MyTroop()->MyCondition()[xFront][yFront].getInfo().second->getInfo()[9]&&a[i][j]==A[zhenying].MyTroop()->MyCondition()[xFront][yFront].getInfo().second->getInfo()[9]&&WarPosition[i][j].getInfo().first[0]==0)
                    {
                        WarPosition[i][j].input(A[zhenying].MyTroop()->MyCondition()[xFront][yFront],zhenying,i,j);
                        std::cout<<" ("<<i<<","<<j<<")"<<std::endl;
                        return;
                    }
        }
        else
            for(int i=0;i<10;i++)
                for(int j=0;j<5;j++)
                    if(b[i][j]==1&&WarPosition[i][j].getInfo().first[0]==0&&a[i][j]<A[zhenying].MyTroop()->MyCondition()[xFront][yFront].getInfo().second->getInfo()[9])
                    {
                        WarPosition[i][j].input(A[zhenying].MyTroop()->MyCondition()[xFront][yFront],zhenying,i,j);
                        std::cout<<" ("<<i<<","<<j<<")"<<std::endl;
                        return;
                    }

    }
}

void war::running()
{
    int Order=getFirst();
    std::cout<<"Through the draw lots, "<<A[Order].Getinfo().first<<" get the first  to strike."<<std::endl;
    show();
    while(true)
    {
        std::cout<<"this is "<<A[Order].Getinfo().first<<"'s turn"<<std::endl;
        for(int row=0;row<2;row++)
            for(int column=0;column<5;column++)
                if(A[Order].MyTroop()->MyCondition()[row][column].getInfo().first[0]==1&&A[Order].MyTroop()->MyCondition()[row][column].getInfo().second->getInfo()[0]!=0)
                {
                    moveOrAttack(Order,row,column);
                    for(int i=0;i<2;i++)
                        for(int j=0;j<5;j++)
                        {
                            if(A[Order].MyTroop()->MyCondition()[i][j].getInfo().first[0]==1&&A[Order].MyTroop()->MyCondition()[i][j].getInfo().second->getInfo()[0]!=0)
                                A[Order].MyTroop()->MyCondition()[i][j].getInfo().second->checkState(row,column,Order);
                            if(A[getSwitchNum(Order)].MyTroop()->MyCondition()[i][j].getInfo().first[0]==1&&A[getSwitchNum(Order)].MyTroop()->MyCondition()[i][j].getInfo().second->getInfo()[0]!=0)
                                A[getSwitchNum(Order)].MyTroop()->MyCondition()[i][j].getInfo().second->checkState(row,column,Order);
                        }
                    A[Order].MyTroop()->MyCondition()[row][column].getInfo().second->checkState();
                }
        deadout();
        show();
        switching(&Order);
        std::this_thread::sleep_for(std::chrono::seconds(1));
        if(A[Order].MyTroop()->getAlive()==0)
            break;
    }
    switching(&Order);
    std::cout<<A[Order].Getinfo().first<<" win!"<<std::endl;
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

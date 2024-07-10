#include"gamehost.h"
#include"tools.h"
#include<iostream>
#include<array>

playchess::playchess()
{
    playtime=0;
    palyernum=2;
    static player m[2];
    A=m;
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

war::war(player enemy[2])
{
    for(int i=0;i<2;i++)
        A[i]=enemy[i];
    for(int i=0;i<2;i++)
        for(int j=0;j<5;j++)
            WarPosition[i][j].input(A[0].MyTroop().MyCondition()[i][j],i,j,0),
            WarPosition[9-getSwitchNum(i)][j].input(A[0].MyTroop().MyCondition()[i][j],i,j,1);
}

int* war::pickAttackingEnemy(int x)
{
    int temp=x;
    int enemy=switching(&temp);
    int *tem=new int[2];
    for(int j=0;j<2;j++)
        for(int i=0;i<5;i++)
        {
            if(A[enemy].MyTroop().MyCondition()[j][i].getInfo().first[0]==1)
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
            if(A[enemy].MyTroop().MyCondition()[j][i].getInfo().first[0]==1)
                HP[i][j]=A[enemy].MyTroop().MyCondition()[i][j].getInfo().second->getInfo()[0];
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
    State Zhongzhuan=A[number].MyTroop().MyCondition()[x][y].getInfo().second->recordRun();
    for(int i=0;i<Zhongzhuan.getInfo().second[0].size();i++)
    {
        int zhenying=Zhongzhuan.getInfo().second[2][i],num;
        if(zhenying==0)
            num=number;
        else
            int tem=number,num=switching(&tem);
        A[num].MyTroop().MyCondition()[Zhongzhuan.getInfo().second[3][i]][Zhongzhuan.getInfo().second[4][i]].getInfo().second->changeMyState(Zhongzhuan.getInfo().first[i],Zhongzhuan.getInfo().second[0][i],Zhongzhuan.getInfo().second[1][i],x,y,Zhongzhuan.getInfo().second[2][i]);
    }
    
}

int war::MakeDistance(int a[10][5], int zhenying, int x, int y)
{
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 5; j++)
            a[i][j] = 50;  // 先找到一个充分大的数
    for(int i=0; i<10;i++)
        for(int j=0;j<5;j++)
            if(zhenying==WarPosition[i][j].getInfo().first[2]&&x==WarPosition[i][j].getInfo().first[3]&&y==WarPosition[i][j].getInfo().first[4])
                a[i][j]=0;
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
                    if (j < 9)
                        if (a[i][j + 1] >= k)
                                a[i][j + 1] = k, aa++;
                    if (j > 0)
                        if (a[i][j - 1] >= k)
                                a[i][j - 1] = k, aa++;
                }
    }
    return k;
}

void war::moveOrAttack(int zhenying, int x, int y)
{
    int a[10][5];
    int k=MakeDistance(a,zhenying,x,y);
    std::vector<std::array<int,3>> distance;
    for(int i=1;i<=k;i++)
        for(int row=0;row<10;row++)
            for(int column=0;column<5;column++)
                if(WarPosition[row][column].getInfo().first[0]==1)
                {
                    std::array<int,3> tem={a[row][column],row,column};
                    distance.push_back(tem);
                }
    if(distance[0][0]<=A[zhenying].MyTroop().MyCondition()[x][y].getInfo().second->getInfo()[10])
    {
        switch(A[zhenying].MyTroop().MyCondition()[x][y].getInfo().first[1])
        {
            case 1:
            {
                int* xx,*yy,*zz;
                xx=new int[1],yy=new int[1],zz=new int[1];
                xx[0]=WarPosition[distance[0][1]][distance[0][2]].getInfo().first[3],yy[0]=WarPosition[distance[0][1]][distance[0][2]].getInfo().first[4],zz[0]=WarPosition[distance[0][1]][distance[0][2]].getInfo().first[2];
                int *tem[3]={xx,yy,zz};
                A[zhenying].MyTroop().MyCondition()[x][y].getInfo().second->done(tem);break;
            }
        }
    }
    else
    {
        int b[10][5];
        MakeDistance(b,WarPosition[distance[0][1]][distance[0][2]].getInfo().first[2],WarPosition[distance[0][1]][distance[0][2]].getInfo().first[3],WarPosition[distance[0][1]][distance[0][2]].getInfo().first[4]);
        for(int i=0;i<10;i++)
            for(int j=0;j<5;j++)
                if(a[i][j]==0)
                {WarPosition[i][j].go();break;}
        for(int i=0;i<10;i++)
            for(int j=0;j<5;j++)
                if(b[i][j]==distance[0][0]-A[zhenying].MyTroop().MyCondition()[x][y].getInfo().second->getInfo()[9]&&a[i][j]==A[zhenying].MyTroop().MyCondition()[x][y].getInfo().second->getInfo()[9])
                {WarPosition[i][j].input(A[zhenying].MyTroop().MyCondition()[x][y],x,y,zhenying);break;}
    }
}

void war::running()
{
    int Order=getFirst();
    std::cout<<"Through the draw lots, "<<A[Order].Getinfo().first<<" get the first  to strike."<<std::endl;
    while(true)
    {
        for(int row=0;row<2;row++)
            for(int column=0;column<5;column++)
                if(A[Order].MyTroop().MyCondition()[row][column].getInfo().first[0]==1)
                    moveOrAttack(Order,row,column);
        switching(&Order);
        if(A[Order].MyTroop().getAlive()==0)
            break;
    }
    switching(&Order);
    std::cout<<A[Order].Getinfo().first<<" win!"<<std::endl;
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
                else AliveAmount++;
            }
    return AliveAmount;
}

void troop::TurnOnFronter(soldier *a, int x, int y)
{
    if(OnFrontline_Amount==OnFrontline_limit)
    {std::cout<<"Your cannot afford the soldier to go on the frontline. Please make a personal change"<<std::endl;return;}
    if(MyCondition()[x][y].getInfo().first[0]==1)
    {std::cout<<"The position has been occupied"<<std::endl;return;}
    Warehouse_Amount--,OnFrontline_Amount++;
    for(int i=0;i<WarehouseSoldier.size();i++)
        if(WarehouseSoldier[i]==a)
            WarehouseSoldier.erase(WarehouseSoldier.begin()+i);
    MyCondition()[x][y].lay(a);
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

SoldierCondition::SoldierCondition(SoldierCondition &p) : vacancyindex(p.vacancyindex), type(p.type), a(p.a){}

std::pair<int*,soldier*> SoldierCondition::getInfo()
{
    std::pair<int*,soldier*> tt;
    int *tem = new int[5];
    tem[0]=vacancyindex,tem[1]=(int)type;
    tem[2]=zhenying,tem[3]=x,tem[4]=y;
    tt.first=tem;
    tt.second=a;
    return tt;
}

SoldierCondition SoldierCondition::input(SoldierCondition &tem, int x, int y, int zhenying)
{
    a=tem.a;
    type=tem.type;
    vacancyindex=tem.vacancyindex;
    this->x=x,this->y=y,this->zhenying=zhenying;
    return *this;
}

void SoldierCondition::lay(soldier * aa)
{
    a=aa,vacancyindex=1;
    type=(soldiers)aa->getInfo()[11];
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
    vacancyindex=0,type=(soldiers)0,zhenying=10,x=10,y=10,a=nullptr;
}

void SoldierCondition::dying()
{
    type=(soldiers)0;
}

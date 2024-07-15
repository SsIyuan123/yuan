#include"store.h"
#include"tools.h"
#include"chesstype.h"
#include<iostream>

store::store(player& a):WindowNum(4)
{
    A=a;
    for(int i=0;i<WindowNum;i++)
    {std::pair<int,soldier*> tem={0,nullptr};goods.push_back(tem);}
}

void store::generateSoldier()
{
    goods.clear();
    int ran=random(0,95);
    soldier* tmp;
    for(int i=0;i<WindowNum;i++)
    {
        int money=3;
        switch(ran%4)
        {
            case 1:tmp=new ParticleWarrior();break;
            case 2:tmp=new LaserArcher();break;
            case 3:tmp=new ParticleEngineer();break;
            case 4:tmp=new DimensionAssassin();break;
        }
        int rate=edgeleft(edgeright(A.MyTroop()->GetInfo().second[5],5)*10-5+edgeright(A.MyTroop()->GetInfo().second[6],3)*15,0);//每多一个二级士兵概率加10％，每多一个三级士兵概率加15%，第一个高级士兵少加5％的概率
        int levelran=random(1,1000);
        if(levelran<=rate*10)
            tmp->levelUp(),money=10;
        std::pair<int,soldier*> tem={money,tmp};
        goods.push_back(tem);
    }
}

void store::clean(int x)
{
    goods.erase(goods.begin()+x);
    std::pair<int,soldier*> tem={0,nullptr};
    goods.insert(goods.begin()+x,tem);
}

void store::buy(int x)
{
    if(A.Getinfo().second[0]<goods[x].first)
    {std::cout<<"Your money is not enough!"<<std::endl;return;}
    if(A.MyTroop()->GetInfo().second[0]==A.MyTroop()->GetInfo().second[2])
    {std::cout<<"Your Warehouse is full!"<<std::endl;return;}
    if(goods[x].first==0)
    {std::cout<<"The soldier has been bought"<<std::endl;return;}
    A.MyTroop()->gota(goods[x].second);
    A.IncreaseMoney(-goods[x].first);
}
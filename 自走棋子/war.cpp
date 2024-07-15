#include"war.h"
#include"tools.h"
#include<iostream>
#include<iomanip>
#include<array>
#include<chrono>
#include<thread>

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

std::pair<std::vector<std::array<int,3>>,std::vector<std::array<int,3>>> war::drawDistanceMap(int a[10][5], int k, int zhenying, int xFront, int yFront)
{
    std::vector<std::array<int,3>> distance,league;
    distance.clear();
    std::vector<int> ASSASSIN={4,8,12,16};
    std::vector<int> WARRIOR={1,5,9,13};
    if(Include(A[zhenying].MyTroop()->MyCondition()[xFront][yFront].getInfo().first[1],ASSASSIN)==0)
    {
        for(int i=1;i<k;i++)
            for(int row=0;row<10;row++)
                for(int column=0;column<5;column++)
                {
                    
                    if(WarPosition[row][column].getInfo().first[0]==1&&WarPosition[row][column].getInfo().first[2]==getSwitchNum(zhenying)&&a[row][column]==i)
                    {
                        std::array<int,3> tem={a[row][column],row,column};
                        distance.push_back(tem);
                    }
                    if(WarPosition[row][column].getInfo().first[0]==1&&WarPosition[row][column].getInfo().first[2]==zhenying&&a[row][column]==i)
                    {
                        std::array<int,3> tem={a[row][column],row,column};
                        league.push_back(tem);
                    }
                }
    }
    else
    {
        for(int i=1;i<k;i++)
            for(int row=0;row<10;row++)
                for(int column=0;column<5;column++)
                {
                    if(WarPosition[row][column].getInfo().first[0]==1&&WarPosition[row][column].getInfo().first[2]==getSwitchNum(zhenying)&&a[row][column]==i&&Include(WarPosition[row][column].getInfo().first[1],ASSASSIN)==0&&Include(WarPosition[row][column].getInfo().first[1],WARRIOR)==0)
                    {
                        std::array<int,3> tem={a[row][column],row,column};
                        distance.push_back(tem);
                    }
                    if(WarPosition[row][column].getInfo().first[0]==1&&WarPosition[row][column].getInfo().first[2]==zhenying&&a[row][column]==i)
                    {
                        std::array<int,3> tem={a[row][column],row,column};
                        league.push_back(tem);
                    }
                }
        for(int i=1;i<k;i++)
            for(int row=0;row<10;row++)
                for(int column=0;column<5;column++)
                    if(WarPosition[row][column].getInfo().first[0]==1&&WarPosition[row][column].getInfo().first[2]==getSwitchNum(zhenying)&&a[row][column]==i&&(Include(WarPosition[row][column].getInfo().first[1],ASSASSIN)==1||Include(WarPosition[row][column].getInfo().first[1],WARRIOR)==1))
                    {
                        std::array<int,3> tem={a[row][column],row,column};
                        distance.push_back(tem);
                    }
    }
    std::pair<std::vector<std::array<int,3>>,std::vector<std::array<int,3>>> tem;
    tem.first=distance,tem.second=league;
    return tem;
}

void war::moveOrAttack(int zhenying, int xFront, int yFront)
{
    int a[10][5],k,xWar,yWar;
    for(int i=0;i<10;i++)
        for(int j=0;j<5;j++)
            if(WarPosition[i][j].getInfo().first[2]==zhenying&&WarPosition[i][j].getInfo().first[3]==xFront&&WarPosition[i][j].getInfo().first[4]==yFront)
                k=MakeDistance(a,zhenying,WarPosition[i][j].getInfo().first[5],WarPosition[i][j].getInfo().first[6]),xWar=WarPosition[i][j].getInfo().first[5],yWar=WarPosition[i][j].getInfo().first[6];
    std::pair<std::vector<std::array<int,3>>,std::vector<std::array<int,3>>> zhongzhuan=drawDistanceMap(a,k,zhenying,xFront,yFront);
    std::vector<std::array<int,3>> distance=zhongzhuan.first,league=zhongzhuan.second;
    if(A[zhenying].MyTroop()->MyCondition()[xFront][yFront].getInfo().first[1]==3)
    {
        std::vector<int> xx,yy,zz;
        for(int i=0;i<league.size();i++)
            xx.push_back(WarPosition[league[0][1]][league[0][2]].getInfo().first[3]),yy.push_back(WarPosition[league[0][1]][league[0][2]].getInfo().first[4]),zz.push_back(WarPosition[league[0][1]][league[0][2]].getInfo().first[2]);
        std::vector<std::vector<int>> tem;
        tem.push_back(xx),tem.push_back(yy),tem.push_back(zz);
        A[zhenying].MyTroop()->MyCondition()[xFront][yFront].getInfo().second->done(tem);
        effects(zhenying,xFront,yFront);
        return;
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
            case 4:
            {
                xx.push_back(WarPosition[distance[0][1]][distance[0][2]].getInfo().first[3]),yy.push_back(WarPosition[distance[0][1]][distance[0][2]].getInfo().first[4]),zz.push_back(WarPosition[distance[0][1]][distance[0][2]].getInfo().first[2]);
                for(int i=0;i<league.size();i++)
                    xx.push_back(WarPosition[league[0][1]][league[0][2]].getInfo().first[3]),yy.push_back(WarPosition[league[0][1]][league[0][2]].getInfo().first[4]),zz.push_back(WarPosition[league[0][1]][league[0][2]].getInfo().first[2]);
            }
        }
        std::vector<std::vector<int>> tem;
        tem.push_back(xx),tem.push_back(yy),tem.push_back(zz);
        if(WarPosition[distance[0][1]][distance[0][2]].getInfo().second->getInfo()[13]!=0)
        {
            std::vector<int> reBound(WarPosition[distance[0][1]][distance[0][2]].getInfo().second->getInfo()[13]);
            tem.push_back(reBound);
        }
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
            {
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
                else if(A[Order].MyTroop()->MyCondition()[row][column].getInfo().first[0]==1&&A[Order].MyTroop()->MyCondition()[row][column].getInfo().second->getInfo()[0]==0)
                {
                    for(int i=0;i<2;i++)
                        for(int j=0;j<5;j++)
                        {
                            if(A[Order].MyTroop()->MyCondition()[i][j].getInfo().first[0]==1&&A[Order].MyTroop()->MyCondition()[i][j].getInfo().second->getInfo()[0]!=0)
                                A[Order].MyTroop()->MyCondition()[i][j].getInfo().second->checkState(row,column,Order);
                            if(A[getSwitchNum(Order)].MyTroop()->MyCondition()[i][j].getInfo().first[0]==1&&A[getSwitchNum(Order)].MyTroop()->MyCondition()[i][j].getInfo().second->getInfo()[0]!=0)
                                A[getSwitchNum(Order)].MyTroop()->MyCondition()[i][j].getInfo().second->checkState(row,column,Order);
                        }
                }
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
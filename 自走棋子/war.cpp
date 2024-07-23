#include"war.h"
#include"tools.h"
#include<iostream>
#include<iomanip>
#include<array>
#include<chrono>
#include<thread>

std::vector<int> WARRIOR = {1,5,9,13};
std::vector<int> ARCHER = {2,6,10,14};
std::vector<int> MAGICIAN ={3,7,11,15};
std::vector<int> ASSASSIN = {4,8,12,16};
std::vector<int> PARTICLE = {1,2,3,4};
std::vector<int> REIKI = {5,6,7,8};
std::vector<int> ELEMENT = {9,10,11,12};
std::vector<int> WILD = {13,14,15,16};

war::war(std::vector<player*> enemy, int special):special(special),fireNum(0),bleeding(0)
{
    if(special==0)
        std::cout<<enemy[0]->Getinfo().first[0]<<" and "<<enemy[1]->Getinfo().first[0]<<" are chosen to make war.";toEnter(1);
    if(enemy.size()!=2)
    {std::cout<<"The paticipants of the war are not 2"<<std::endl;return;}
    A=enemy;
    for(int i=0;i<2;i++)
        for(int j=0;j<5;j++)
        {
            if(A[0]->MyTroop()->MyCondition()[i][j].getInfo().first[0]==1)
                WarPosition[getSwitchNum(i)][j].input(A[0]->MyTroop()->MyCondition()[i][j],0);
            if(A[1]->MyTroop()->MyCondition()[i][j].getInfo().first[0]==1)
                WarPosition[i+8][j].input(A[1]->MyTroop()->MyCondition()[i][j],1);
        }
}

void war::show()
{
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<5;j++)
        {
            if(WarPosition[i][j].getInfo().first[0]==0)
                std::cout<<std::setw(19)<<"\033[0m"<<"0";
            else
            {
                if(WarPosition[i][j].getInfo().first[2]==0)
                    std::cout<<std::setw(20)<<"\033[31m"<<WarPosition[i][j].getInfo().first[1]; 
                else
                    std::cout<<std::setw(20)<<"\033[34m"<<WarPosition[i][j].getInfo().first[1]; 
            }
        }
        toEnter(2);
    }
    std::cout<<"\033[0m";
    for(int k=0;k<2;k++)
    {
        if(k==0)
            std::cout<<"\033[31m"<<A[k]->Getinfo().first[0]<<":"<<"\033[0m"<<std::endl;
        else
            std::cout<<"\033[34m"<<A[k]->Getinfo().first[0]<<":"<<"\033[0m"<<std::endl;
        for(int i=0;i<2;i++)
            for(int j=0;j<5;j++)
                if(A[k]->MyTroop()->MyCondition()[i][j].getInfo().first[0]==1)
                    A[k]->MyTroop()->MyCondition()[i][j].getInfo().second->show();
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
            if(A[enemy]->MyTroop()->MyCondition()[j][i].getInfo().first[0]==1)
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
            if(A[enemy]->MyTroop()->MyCondition()[j][i].getInfo().first[0]==1)
                HP[i][j]=A[enemy]->MyTroop()->MyCondition()[i][j].getInfo().second->getInfo()[0];
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
    // std::cout<<"Effects!"<<std::endl;
    State Zhongzhuan=A[number]->MyTroop()->MyCondition()[x][y].getInfo().second->recordRun();
    Zhongzhuan.show();
    if(Zhongzhuan.getInfo().first[0]!=(soldierState)0)
        for(int i=0;i<Zhongzhuan.getInfo().second[0].size();i++)
        {
            if(Zhongzhuan.getInfo().first[i]!=(soldierState)7)
                A[Zhongzhuan.getInfo().second[2][i]]->MyTroop()->MyCondition()[Zhongzhuan.getInfo().second[3][i]][Zhongzhuan.getInfo().second[4][i]].getInfo().second->changeMyState(Zhongzhuan.getInfo().first[i],Zhongzhuan.getInfo().second[0][i],Zhongzhuan.getInfo().second[1][i],x,y,number);
            else
            {
                if(A[number]->MyTroop()->MyCondition()[x][y].getInfo().second->getInfo()[16]>0)//有藤蔓必须先打碎藤蔓
                    A[number]->MyTroop()->MyCondition()[x][y].getInfo().second->addindex(0,0,0,0,0,0,0,0,0,0,0,0,0,-Zhongzhuan.getInfo().second[0][i]);
                else
                    A[Zhongzhuan.getInfo().second[2][i]]->MyTroop()->MyCondition()[Zhongzhuan.getInfo().second[3][i]][Zhongzhuan.getInfo().second[4][i]].getInfo().second->changeMyState(Zhongzhuan.getInfo().first[i],Zhongzhuan.getInfo().second[0][i],Zhongzhuan.getInfo().second[1][i],x,y,number);
            }
            if(Zhongzhuan.getInfo().first[i]==(soldierState)5)
            {
                std::cout<<fireNum<<"+"<<Zhongzhuan.getInfo().second[0][i]<<"=";
                fireNum+=Zhongzhuan.getInfo().second[0][i];
                std::cout<<fireNum<<std::endl;
            }
            if(Zhongzhuan.getInfo().first[i]==(soldierState)17)
            {
                std::cout<<bleeding<<"+"<<Zhongzhuan.getInfo().second[0][i]<<"=";
                bleeding+=Zhongzhuan.getInfo().second[0][i];
                std::cout<<bleeding<<std::endl;
            }
        }
    // std::cout<<"effects end"<<std::endl;
}

// int war::MakeDistance(int a[10][5], int zhenying, int x, int y)
// {
//     // std::cout<<"make distance"<<std::endl;
//     for (int i = 0; i < 10; i++)
//         for (int j = 0; j < 5; j++)
//             a[i][j] = 100;  
//     // std::cout<<x<<y<<std::endl;
//     a[x][y]=0;         
//     int aa = 1,k=0;            
//     while (aa != 0)
//     {
//         k++;
//         aa = 0;
//         for (int i = 0; i < 10; i++)
//             for (int j = 0; j < 5; j++)
//                 if (a[i][j] == k - 1)
//                 {
//                     if (i > 0)
//                         if (a[i - 1][j] >= k)
//                                 a[i - 1][j] = k, aa++;
//                     if (i < 9)
//                         if (a[i + 1][j] >= k)
//                                 a[i + 1][j] = k, aa++;
//                     if (j < 4)
//                         if (a[i][j + 1] >= k)
//                                 a[i][j + 1] = k, aa++;
//                     if (j > 0)
//                         if (a[i][j - 1] >= k)
//                                 a[i][j - 1] = k, aa++;
//                 }
//     }
//     return k-1;
// }

int war::MakeDistance(int a[10][5], int zhenying, int x, int y)
{
    // std::cout<<"make distance"<<std::endl;
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 5; j++)
            a[i][j] = 100;  
    // std::cout<<x<<y<<std::endl;
    a[x][y]=0;         
    int aa = 1,k=0;            
    while (aa != 0)
    {
        k++;
        aa = 0;
        for (int i = 0; i < 10; i++)
            for (int j = 0; j < 5; j++)
                if (a[i][j] == k - 1)
                {
                    if (i > 0&&a[i - 1][j] >= k)
                    {
                        if (WarPosition[i-1][j].getInfo().first[0]==0)
                            a[i - 1][j] = k, aa++;
                        else
                            a[i - 1][j] = -1;
                    }
                    if (i < 9&&a[i + 1][j] >= k)
                    {
                        if (WarPosition[i+1][j].getInfo().first[0]==0)
                            a[i + 1][j] = k, aa++;
                        else
                            a[i + 1][j] = -1;
                    }
                    if (j < 4&&a[i][j + 1] >= k)
                    {
                        if (WarPosition[i][j+1].getInfo().first[0]==0)
                            a[i][j + 1] = k, aa++;
                        else 
                            a[i][j + 1] = -1;
                    }
                    if (j > 0&&a[i][j - 1] >= k)
                    {
                        if (WarPosition[i][j-1].getInfo().first[0]==0)
                            a[i][j - 1] = k, aa++;
                        else
                            a[i][j - 1] = -1;
                    }
                }
    }
    for(int i = 0; i < 10; i++) 
        for(int j = 0; j < 5; j++) 
            if(a[i][j] == -1) 
            {
                int minVal = 200; // 初始化为一个大于所有可能值的数
                for(int m = -1; m <= 1; m++)
                    for(int k = -1; k <= 1; k++)
                        // 仅处理四个方向：上、下、左、右
                        if((m == 0 && abs(k) == 1) || (k == 0 && abs(m) == 1)) 
                        {
                            int ni = i + m;
                            int nj = j + k;
                            if(ni >= 0 && ni < 10 && nj >= 0 && nj < 5&&a[ni][nj]!=-1) 
                                minVal=minVal>a[ni][nj]?a[ni][nj]:minVal;
                        }
                a[i][j] = minVal + 1;
            }
    return k-1;
}

int war::bleed(int zhenying)
{
    int i=0,harm=0;
    for(int i=0;i<10;i++)
        for(int j=0;j<5;j++)
        {
            int* Info=WarPosition[i][j].getInfo().first;
            if(Info[0]==1)
            {
                int* inf=WarPosition[i][j].getInfo().second->getInfo();
                harm+=inf[3];
                delete[] inf;
            }
            delete[] Info;
        }
    A[zhenying]->Hpdecrease(harm);
    return harm;
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
    if(Include(A[zhenying]->MyTroop()->MyCondition()[xFront][yFront].getInfo().first[1],ASSASSIN)==0)
    {
        for(int i=1;i<k;i++)
            for(int row=0;row<10;row++)
                for(int column=0;column<5;column++)
                {
                    if(WarPosition[row][column].getInfo().first[0]==1&&WarPosition[row][column].getInfo().first[2]==getSwitchNum(zhenying)&&a[row][column]==i&&WarPosition[row][column].getInfo().second->getInfo()[19]==A[zhenying]->MyTroop()->MyCondition()[xFront][yFront].getInfo().second->getInfo()[19])
                    {
                        std::array<int,3> tem={a[row][column],row,column};
                        distance.push_back(tem);
                    }
                    if(WarPosition[row][column].getInfo().first[0]==1&&WarPosition[row][column].getInfo().first[2]==zhenying&&a[row][column]==i&&WarPosition[row][column].getInfo().second->getInfo()[19]==A[zhenying]->MyTroop()->MyCondition()[xFront][yFront].getInfo().second->getInfo()[19])
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
                    if(WarPosition[row][column].getInfo().first[0]==1&&WarPosition[row][column].getInfo().first[2]==getSwitchNum(zhenying)&&a[row][column]==i&&Include(WarPosition[row][column].getInfo().first[1],ASSASSIN)==0&&Include(WarPosition[row][column].getInfo().first[1],WARRIOR)==0&&WarPosition[row][column].getInfo().second->getInfo()[19]==A[zhenying]->MyTroop()->MyCondition()[xFront][yFront].getInfo().second->getInfo()[19])
                    {
                        std::array<int,3> tem={a[row][column],row,column};
                        distance.push_back(tem);
                    }
                    if(WarPosition[row][column].getInfo().first[0]==1&&WarPosition[row][column].getInfo().first[2]==zhenying&&a[row][column]==i&&WarPosition[row][column].getInfo().second->getInfo()[19]==A[zhenying]->MyTroop()->MyCondition()[xFront][yFront].getInfo().second->getInfo()[19])
                    {
                        std::array<int,3> tem={a[row][column],row,column};
                        league.push_back(tem);
                    }
                }
        for(int i=1;i<k;i++)
            for(int row=0;row<10;row++)
                for(int column=0;column<5;column++)
                    if(WarPosition[row][column].getInfo().first[0]==1&&WarPosition[row][column].getInfo().first[2]==getSwitchNum(zhenying)&&a[row][column]==i&&(Include(WarPosition[row][column].getInfo().first[1],ASSASSIN)==1||Include(WarPosition[row][column].getInfo().first[1],WARRIOR)==1)&&WarPosition[row][column].getInfo().second->getInfo()[19]==A[zhenying]->MyTroop()->MyCondition()[xFront][yFront].getInfo().second->getInfo()[19])
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
    if(A[zhenying]->MyTroop()->MyCondition()[xFront][yFront].getInfo().second->getInfo()[17]>=3)
    {std::cout<<"frozen!";toEnter(2);A[zhenying]->MyTroop()->MyCondition()[xFront][yFront].getInfo().second->addindex(0,0,0,0,0,0,0,0,0,0,0,0,0,0,-3);return;}
    int a[10][5],k,xWar,yWar;
    for(int i=0;i<10;i++)
        for(int j=0;j<5;j++)
            if(WarPosition[i][j].getInfo().first[2]==zhenying&&WarPosition[i][j].getInfo().first[3]==xFront&&WarPosition[i][j].getInfo().first[4]==yFront)
                k=MakeDistance(a,zhenying,WarPosition[i][j].getInfo().first[5],WarPosition[i][j].getInfo().first[6]),xWar=WarPosition[i][j].getInfo().first[5],yWar=WarPosition[i][j].getInfo().first[6];
    std::pair<std::vector<std::array<int,3>>,std::vector<std::array<int,3>>> zhongzhuan=drawDistanceMap(a,k,zhenying,xFront,yFront);
    std::vector<std::array<int,3>> distance=zhongzhuan.first,league=zhongzhuan.second;
    if(A[zhenying]->MyTroop()->MyCondition()[xFront][yFront].getInfo().second->getInfo()[15]==1&&random()<50)
    {std::cout<<"i am crazy"<<std::endl;chaos_moveOrAttack(zhenying,xFront,yFront);return;}
    if(A[zhenying]->MyTroop()->MyCondition()[xFront][yFront].getInfo().first[1]==3)
    {
        std::vector<int> xx,yy,zz,rebound,miss;
        for(int i=0;i<league.size();i++)
            xx.push_back(WarPosition[league[i][1]][league[i][2]].getInfo().first[3]),yy.push_back(WarPosition[league[i][1]][league[i][2]].getInfo().first[4]),zz.push_back(WarPosition[league[i][1]][league[i][2]].getInfo().first[2]),rebound.push_back(WarPosition[distance[i][1]][distance[i][2]].getInfo().second->getInfo()[13]);
        std::vector<std::vector<int>> tem;
        tem.push_back(xx),tem.push_back(yy),tem.push_back(zz),tem.push_back(rebound),tem.push_back(miss);
        A[zhenying]->MyTroop()->MyCondition()[xFront][yFront].getInfo().second->done(tem);
        effects(zhenying,xFront,yFront);
        return;
    }
    if(distance.size()>0)
    {
        if(distance[0][0]<=A[zhenying]->MyTroop()->MyCondition()[xFront][yFront].getInfo().second->getInfo()[10])
        {
            std::vector<int> xx,yy,zz,rebound,dis,miss;
            switch(A[zhenying]->MyTroop()->MyCondition()[xFront][yFront].getInfo().first[1])
            {
                case 1:
                {
                    xx.push_back(WarPosition[distance[0][1]][distance[0][2]].getInfo().first[3]),yy.push_back(WarPosition[distance[0][1]][distance[0][2]].getInfo().first[4]),zz.push_back(WarPosition[distance[0][1]][distance[0][2]].getInfo().first[2]);
                    rebound.push_back(WarPosition[distance[0][1]][distance[0][2]].getInfo().second->getInfo()[13]),miss.push_back(WarPosition[distance[0][1]][distance[0][2]].getInfo().second->getInfo()[2]);
                    break;
                }
                case 2:
                {
                    xx.push_back(WarPosition[distance[0][1]][distance[0][2]].getInfo().first[3]),yy.push_back(WarPosition[distance[0][1]][distance[0][2]].getInfo().first[4]),zz.push_back(WarPosition[distance[0][1]][distance[0][2]].getInfo().first[2]);
                    rebound.push_back(WarPosition[distance[0][1]][distance[0][2]].getInfo().second->getInfo()[13]),miss.push_back(WarPosition[distance[0][1]][distance[0][2]].getInfo().second->getInfo()[2]);
                    for(int i=0;i<distance.size();i++)
                        if(i>0&&(yWar-distance[i][2])*(xWar-distance[0][1])==(xWar-distance[i][1])*(yWar-distance[0][2]))
                        {
                            xx.push_back(WarPosition[distance[i][1]][distance[i][2]].getInfo().first[3]),yy.push_back(WarPosition[distance[i][1]][distance[i][2]].getInfo().first[4]),zz.push_back(WarPosition[distance[i][1]][distance[i][2]].getInfo().first[2]);
                            rebound.push_back(WarPosition[distance[i][1]][distance[i][2]].getInfo().second->getInfo()[13]),miss.push_back(WarPosition[distance[i][1]][distance[i][2]].getInfo().second->getInfo()[2]);
                        }
                    break;
                }
                case 4:
                {
                    xx.push_back(WarPosition[distance[0][1]][distance[0][2]].getInfo().first[3]),yy.push_back(WarPosition[distance[0][1]][distance[0][2]].getInfo().first[4]),zz.push_back(WarPosition[distance[0][1]][distance[0][2]].getInfo().first[2]);
                    rebound.push_back(WarPosition[distance[0][1]][distance[0][2]].getInfo().second->getInfo()[13]),miss.push_back(WarPosition[distance[0][1]][distance[0][2]].getInfo().second->getInfo()[2]);
                    for(int i=0;i<league.size();i++)
                    {
                        xx.push_back(WarPosition[league[i][1]][league[i][2]].getInfo().first[3]),yy.push_back(WarPosition[league[i][1]][league[i][2]].getInfo().first[4]),zz.push_back(WarPosition[league[i][1]][league[i][2]].getInfo().first[2]);
                        rebound.push_back(WarPosition[league[i][1]][league[i][2]].getInfo().second->getInfo()[13]),miss.push_back(WarPosition[league[i][1]][league[i][2]].getInfo().second->getInfo()[2]);
                    }
                    break;
                }
                case 5:
                {
                    xx.push_back(WarPosition[distance[0][1]][distance[0][2]].getInfo().first[3]),yy.push_back(WarPosition[distance[0][1]][distance[0][2]].getInfo().first[4]),zz.push_back(WarPosition[distance[0][1]][distance[0][2]].getInfo().first[2]);
                    rebound.push_back(WarPosition[distance[0][1]][distance[0][2]].getInfo().second->getInfo()[13]),miss.push_back(WarPosition[distance[0][1]][distance[0][2]].getInfo().second->getInfo()[2]);
                    break;
                }
                case 6:
                {
                    int map[10][5];
                    MakeDistance(map,getSwitchNum(zhenying),distance[0][1],distance[0][2]);
                    for(int i=0;i<distance.size();i++)
                        if(map[distance[i][1]][distance[i][2]]<=1)
                        {
                            xx.push_back(WarPosition[distance[i][1]][distance[i][2]].getInfo().first[3]),yy.push_back(WarPosition[distance[i][1]][distance[i][2]].getInfo().first[4]),zz.push_back(WarPosition[distance[i][1]][distance[i][2]].getInfo().first[2]);
                            rebound.push_back(WarPosition[distance[i][1]][distance[i][2]].getInfo().second->getInfo()[13]),miss.push_back(WarPosition[distance[i][1]][distance[i][2]].getInfo().second->getInfo()[2]);
                        }
                    break;
                }
                case 7:
                {
                    for(int i=0;i<distance.size();i++)
                    {
                        xx.push_back(WarPosition[distance[i][1]][distance[i][2]].getInfo().first[3]),yy.push_back(WarPosition[distance[i][1]][distance[i][2]].getInfo().first[4]),zz.push_back(WarPosition[distance[i][1]][distance[i][2]].getInfo().first[2]);
                        rebound.push_back(WarPosition[distance[i][1]][distance[i][2]].getInfo().second->getInfo()[13]),miss.push_back(WarPosition[distance[i][1]][distance[i][2]].getInfo().second->getInfo()[2]);
                    }
                    for(int i=0;i<league.size();i++)
                    {
                        xx.push_back(WarPosition[league[i][1]][league[i][2]].getInfo().first[3]),yy.push_back(WarPosition[league[i][1]][league[i][2]].getInfo().first[4]),zz.push_back(WarPosition[league[i][1]][league[i][2]].getInfo().first[2]);
                        rebound.push_back(WarPosition[league[i][1]][league[i][2]].getInfo().second->getInfo()[13]),miss.push_back(WarPosition[league[i][1]][league[i][2]].getInfo().second->getInfo()[2]);
                    }
                    break;
                }
                case 8:
                {
                    xx.push_back(WarPosition[distance[0][1]][distance[0][2]].getInfo().first[3]),yy.push_back(WarPosition[distance[0][1]][distance[0][2]].getInfo().first[4]),zz.push_back(WarPosition[distance[0][1]][distance[0][2]].getInfo().first[2]);
                    rebound.push_back(WarPosition[distance[0][1]][distance[0][2]].getInfo().second->getInfo()[13]),miss.push_back(WarPosition[distance[0][1]][distance[0][2]].getInfo().second->getInfo()[2]);
                    break;
                }
                case 9:
                {
                    for(int i=0;i<distance.size();i++)
                    {
                        xx.push_back(WarPosition[distance[i][1]][distance[i][2]].getInfo().first[3]),yy.push_back(WarPosition[distance[i][1]][distance[i][2]].getInfo().first[4]),zz.push_back(WarPosition[distance[i][1]][distance[i][2]].getInfo().first[2]);
                        rebound.push_back(WarPosition[distance[i][1]][distance[i][2]].getInfo().second->getInfo()[13]),miss.push_back(WarPosition[distance[i][1]][distance[i][2]].getInfo().second->getInfo()[2]);
                    }
                    break;
                }
                case 10:
                {
                    for(int i=0;i<distance.size();i++)
                    {
                        xx.push_back(WarPosition[distance[i][1]][distance[i][2]].getInfo().first[3]),yy.push_back(WarPosition[distance[i][1]][distance[i][2]].getInfo().first[4]),zz.push_back(WarPosition[distance[i][1]][distance[i][2]].getInfo().first[2]);
                        rebound.push_back(WarPosition[distance[i][1]][distance[i][2]].getInfo().second->getInfo()[13]),miss.push_back(WarPosition[distance[i][1]][distance[i][2]].getInfo().second->getInfo()[2]);
                    }
                    break;
                }
                case 11:
                {
                    xx.push_back(WarPosition[distance[0][1]][distance[0][2]].getInfo().first[3]),yy.push_back(WarPosition[distance[0][1]][distance[0][2]].getInfo().first[4]),zz.push_back(WarPosition[distance[0][1]][distance[0][2]].getInfo().first[2]);
                    rebound.push_back(WarPosition[distance[0][1]][distance[0][2]].getInfo().second->getInfo()[13]),miss.push_back(WarPosition[distance[0][1]][distance[0][2]].getInfo().second->getInfo()[2]);
                    for(int i=0;i<league.size();i++)
                    {
                        xx.push_back(WarPosition[league[i][1]][league[i][2]].getInfo().first[3]),yy.push_back(WarPosition[league[i][1]][league[i][2]].getInfo().first[4]),zz.push_back(WarPosition[league[i][1]][league[i][2]].getInfo().first[2]);
                        rebound.push_back(WarPosition[league[i][1]][league[i][2]].getInfo().second->getInfo()[13]),miss.push_back(WarPosition[league[i][1]][league[i][2]].getInfo().second->getInfo()[2]);
                    }
                    break;
                }
                case 12:
                {
                    xx.push_back(WarPosition[distance[0][1]][distance[0][2]].getInfo().first[3]),yy.push_back(WarPosition[distance[0][1]][distance[0][2]].getInfo().first[4]),zz.push_back(WarPosition[distance[0][1]][distance[0][2]].getInfo().first[2]);
                    rebound.push_back(WarPosition[distance[0][1]][distance[0][2]].getInfo().second->getInfo()[13]),miss.push_back(WarPosition[distance[0][1]][distance[0][2]].getInfo().second->getInfo()[2]);
                    break;
                }
                case 13:
                {
                    xx.push_back(WarPosition[distance[0][1]][distance[0][2]].getInfo().first[3]),yy.push_back(WarPosition[distance[0][1]][distance[0][2]].getInfo().first[4]),zz.push_back(WarPosition[distance[0][1]][distance[0][2]].getInfo().first[2]);
                    rebound.push_back(WarPosition[distance[0][1]][distance[0][2]].getInfo().second->getInfo()[13]),miss.push_back(WarPosition[distance[0][1]][distance[0][2]].getInfo().second->getInfo()[2]);
                    break;
                }
                case 14:
                {
                    int map[10][5];
                    MakeDistance(map,getSwitchNum(zhenying),distance[0][1],distance[0][2]);
                    for(int i=0;i<distance.size();i++)
                        if(map[distance[i][1]][distance[i][2]]<=1)
                        {
                            xx.push_back(WarPosition[distance[i][1]][distance[i][2]].getInfo().first[3]),yy.push_back(WarPosition[distance[i][1]][distance[i][2]].getInfo().first[4]),zz.push_back(WarPosition[distance[i][1]][distance[i][2]].getInfo().first[2]);
                            rebound.push_back(WarPosition[distance[i][1]][distance[i][2]].getInfo().second->getInfo()[13]),miss.push_back(WarPosition[distance[i][1]][distance[i][2]].getInfo().second->getInfo()[2]);
                        }
                    break;
                }
                case 15:
                {
                    for(int i=0;i<distance.size();i++)
                    {
                        xx.push_back(WarPosition[distance[i][1]][distance[i][2]].getInfo().first[3]),yy.push_back(WarPosition[distance[i][1]][distance[i][2]].getInfo().first[4]),zz.push_back(WarPosition[distance[i][1]][distance[i][2]].getInfo().first[2]);
                        rebound.push_back(WarPosition[distance[i][1]][distance[i][2]].getInfo().second->getInfo()[13]),miss.push_back(WarPosition[distance[i][1]][distance[i][2]].getInfo().second->getInfo()[2]);
                    }
                    for(int i=0;i<league.size();i++)
                    {
                        xx.push_back(WarPosition[league[i][1]][league[i][2]].getInfo().first[3]),yy.push_back(WarPosition[league[i][1]][league[i][2]].getInfo().first[4]),zz.push_back(WarPosition[league[i][1]][league[i][2]].getInfo().first[2]);
                        rebound.push_back(WarPosition[league[i][1]][league[i][2]].getInfo().second->getInfo()[13]),miss.push_back(WarPosition[league[i][1]][league[i][2]].getInfo().second->getInfo()[2]);
                    }
                    break;
                }
                case 16:
                {
                    for(int i=0;i<distance.size()&&i<2;i++)
                    {
                        xx.push_back(WarPosition[distance[i][1]][distance[i][2]].getInfo().first[3]),yy.push_back(WarPosition[distance[i][1]][distance[i][2]].getInfo().first[4]),zz.push_back(WarPosition[distance[i][1]][distance[i][2]].getInfo().first[2]);
                        rebound.push_back(WarPosition[distance[i][1]][distance[i][2]].getInfo().second->getInfo()[13]),miss.push_back(WarPosition[distance[i][1]][distance[i][2]].getInfo().second->getInfo()[2]);
                    }
                    break;
                }
            }
            std::vector<std::vector<int>> tem;
            tem.push_back(xx),tem.push_back(yy),tem.push_back(zz),tem.push_back(rebound),tem.push_back(miss);
            if(A[zhenying]->MyTroop()->MyCondition()[xFront][yFront].getInfo().first[1]==9)
            {
                for(int i=0;i<distance.size();i++)
                    dis.push_back(distance[i][0]);
                tem.push_back(dis);
                std::vector<int> firenum={fireNum};
                tem.push_back(firenum);
            }
            if(A[zhenying]->MyTroop()->MyCondition()[xFront][yFront].getInfo().first[1]==13)
            {
                std::vector<int> defense;
                defense.push_back(WarPosition[distance[0][1]][distance[0][2]].getInfo().second->getInfo()[4]);
                tem.push_back(defense);
            }
            if(A[zhenying]->MyTroop()->MyCondition()[xFront][yFront].getInfo().first[1]==16)
            {
                std::vector<int> blood;
                blood.push_back(bleeding);
                tem.push_back(blood);
            }
            A[zhenying]->MyTroop()->MyCondition()[xFront][yFront].getInfo().second->done(tem);
            effects(zhenying,xFront,yFront);
        }
        else
        {
            std::cout<<"Type "<<A[zhenying]->MyTroop()->MyCondition()[xFront][yFront].getInfo().first[1]<<" soldier owned by "<<A[zhenying]->Getinfo().first[0]<<" move from ("<<xWar<<","<<yWar<<") to";
            int b[10][5];
            MakeDistance(b,WarPosition[distance[0][1]][distance[0][2]].getInfo().first[2],WarPosition[distance[0][1]][distance[0][2]].getInfo().first[5],WarPosition[distance[0][1]][distance[0][2]].getInfo().first[6]);
            for(int i=0;i<10;i++)
                for(int j=0;j<5;j++)
                    if(a[i][j]==0)
                    {WarPosition[i][j].go();break;}
            if(distance[0][0]>A[zhenying]->MyTroop()->MyCondition()[xFront][yFront].getInfo().second->getInfo()[9])
            {
                for(int i=0;i<10;i++)
                    for(int j=0;j<5;j++)
                        if(b[i][j]==distance[0][0]-A[zhenying]->MyTroop()->MyCondition()[xFront][yFront].getInfo().second->getInfo()[9]&&a[i][j]==A[zhenying]->MyTroop()->MyCondition()[xFront][yFront].getInfo().second->getInfo()[9]&&WarPosition[i][j].getInfo().first[0]==0)
                        {
                            WarPosition[i][j].input(A[zhenying]->MyTroop()->MyCondition()[xFront][yFront],zhenying,i,j);
                            std::cout<<" ("<<i<<","<<j<<")"<<std::endl;
                            return;
                        }
            }
            else
                for(int i=0;i<10;i++)
                    for(int j=0;j<5;j++)
                        if(b[i][j]==1&&WarPosition[i][j].getInfo().first[0]==0&&a[i][j]<A[zhenying]->MyTroop()->MyCondition()[xFront][yFront].getInfo().second->getInfo()[9])
                        {
                            WarPosition[i][j].input(A[zhenying]->MyTroop()->MyCondition()[xFront][yFront],zhenying,i,j);
                            std::cout<<" ("<<i<<","<<j<<")"<<std::endl;
                            return;
                        }

        }
    }
}

void war::chaos_moveOrAttack(int zhenying, int xFront, int yFront)
{
    int a[10][5],k,xWar,yWar;
    for(int i=0;i<10;i++)
        for(int j=0;j<5;j++)
            if(WarPosition[i][j].getInfo().first[2]==zhenying&&WarPosition[i][j].getInfo().first[3]==xFront&&WarPosition[i][j].getInfo().first[4]==yFront)
                k=MakeDistance(a,zhenying,WarPosition[i][j].getInfo().first[5],WarPosition[i][j].getInfo().first[6]),xWar=WarPosition[i][j].getInfo().first[5],yWar=WarPosition[i][j].getInfo().first[6];
    std::pair<std::vector<std::array<int,3>>,std::vector<std::array<int,3>>> zhongzhuan=drawDistanceMap(a,k,zhenying,xFront,yFront);
    std::vector<std::array<int,3>> distance=zhongzhuan.first,league=zhongzhuan.second;
    if(A[zhenying]->MyTroop()->MyCondition()[xFront][yFront].getInfo().first[1]==3)
    {
        std::vector<int> xx,yy,zz,rebound,miss;
        for(int i=0;i<distance.size();i++)
            xx.push_back(WarPosition[distance[i][1]][distance[i][2]].getInfo().first[3]),yy.push_back(WarPosition[distance[i][1]][distance[i][2]].getInfo().first[4]),zz.push_back(WarPosition[distance[i][1]][distance[i][2]].getInfo().first[2]),rebound.push_back(WarPosition[distance[i][1]][distance[i][2]].getInfo().second->getInfo()[13]);
        std::vector<std::vector<int>> tem;
        tem.push_back(xx),tem.push_back(yy),tem.push_back(zz),tem.push_back(rebound),tem.push_back(miss);
        A[zhenying]->MyTroop()->MyCondition()[xFront][yFront].getInfo().second->done(tem);
        effects(zhenying,xFront,yFront);
        return;
    }
    if(league.size()>0)
    {
        if(league[0][0]<=A[zhenying]->MyTroop()->MyCondition()[xFront][yFront].getInfo().second->getInfo()[10])
        {
            std::vector<int> xx,yy,zz,rebound,dis,miss;
            switch(A[zhenying]->MyTroop()->MyCondition()[xFront][yFront].getInfo().first[1])
            {
                case 1:
                {
                    xx.push_back(WarPosition[league[0][1]][league[0][2]].getInfo().first[3]),yy.push_back(WarPosition[league[0][1]][league[0][2]].getInfo().first[4]),zz.push_back(WarPosition[league[0][1]][league[0][2]].getInfo().first[2]);
                    rebound.push_back(WarPosition[league[0][1]][league[0][2]].getInfo().second->getInfo()[13]),miss.push_back(WarPosition[league[0][1]][league[0][2]].getInfo().second->getInfo()[2]);
                    break;
                }
                case 2:
                {
                    xx.push_back(WarPosition[league[0][1]][league[0][2]].getInfo().first[3]),yy.push_back(WarPosition[league[0][1]][league[0][2]].getInfo().first[4]),zz.push_back(WarPosition[league[0][1]][league[0][2]].getInfo().first[2]);
                    rebound.push_back(WarPosition[league[0][1]][league[0][2]].getInfo().second->getInfo()[13]),miss.push_back(WarPosition[league[0][1]][league[0][2]].getInfo().second->getInfo()[2]);
                    for(int i=0;i<league.size();i++)
                        if(i>0&&(yWar-league[i][2])*(xWar-league[0][1])==(xWar-league[i][1])*(yWar-league[0][2]))
                        {
                            xx.push_back(WarPosition[league[i][1]][league[i][2]].getInfo().first[3]),yy.push_back(WarPosition[league[i][1]][league[i][2]].getInfo().first[4]),zz.push_back(WarPosition[league[i][1]][league[i][2]].getInfo().first[2]);
                            rebound.push_back(WarPosition[league[i][1]][league[i][2]].getInfo().second->getInfo()[13]),miss.push_back(WarPosition[league[i][1]][league[i][2]].getInfo().second->getInfo()[2]);
                        }
                    break;
                }
                case 4:
                {
                    xx.push_back(WarPosition[league[0][1]][league[0][2]].getInfo().first[3]),yy.push_back(WarPosition[league[0][1]][league[0][2]].getInfo().first[4]),zz.push_back(WarPosition[league[0][1]][league[0][2]].getInfo().first[2]);
                    rebound.push_back(WarPosition[league[0][1]][league[0][2]].getInfo().second->getInfo()[13]),miss.push_back(WarPosition[league[0][1]][league[0][2]].getInfo().second->getInfo()[2]);
                    for(int i=0;i<distance.size();i++)
                    {
                        xx.push_back(WarPosition[distance[i][1]][distance[i][2]].getInfo().first[3]),yy.push_back(WarPosition[distance[i][1]][distance[i][2]].getInfo().first[4]),zz.push_back(WarPosition[distance[i][1]][distance[i][2]].getInfo().first[2]);
                        rebound.push_back(WarPosition[distance[i][1]][distance[i][2]].getInfo().second->getInfo()[13]),miss.push_back(WarPosition[distance[i][1]][distance[i][2]].getInfo().second->getInfo()[2]);
                    }
                    break;
                }
                case 5:
                {
                    xx.push_back(WarPosition[league[0][1]][league[0][2]].getInfo().first[3]),yy.push_back(WarPosition[league[0][1]][league[0][2]].getInfo().first[4]),zz.push_back(WarPosition[league[0][1]][league[0][2]].getInfo().first[2]);
                    rebound.push_back(WarPosition[league[0][1]][league[0][2]].getInfo().second->getInfo()[13]),miss.push_back(WarPosition[league[0][1]][league[0][2]].getInfo().second->getInfo()[2]);
                    break;
                }
                case 6:
                {
                    int map[10][5];
                    MakeDistance(map,getSwitchNum(zhenying),league[0][1],league[0][2]);
                    for(int i=0;i<league.size();i++)
                        if(map[league[i][1]][league[i][2]]<=1)
                        {
                            xx.push_back(WarPosition[league[i][1]][league[i][2]].getInfo().first[3]),yy.push_back(WarPosition[league[i][1]][league[i][2]].getInfo().first[4]),zz.push_back(WarPosition[league[i][1]][league[i][2]].getInfo().first[2]);
                            rebound.push_back(WarPosition[league[i][1]][league[i][2]].getInfo().second->getInfo()[13]),miss.push_back(WarPosition[league[i][1]][league[i][2]].getInfo().second->getInfo()[2]);
                        }
                    break;
                }
                case 7:
                {
                    for(int i=0;i<league.size();i++)
                    {
                        xx.push_back(WarPosition[league[i][1]][league[i][2]].getInfo().first[3]),yy.push_back(WarPosition[league[i][1]][league[i][2]].getInfo().first[4]),zz.push_back(WarPosition[league[i][1]][league[i][2]].getInfo().first[2]);
                        rebound.push_back(WarPosition[league[i][1]][league[i][2]].getInfo().second->getInfo()[13]);
                    }
                    for(int i=0;i<distance.size();i++)
                    {
                        xx.push_back(WarPosition[distance[i][1]][distance[i][2]].getInfo().first[3]),yy.push_back(WarPosition[distance[i][1]][distance[i][2]].getInfo().first[4]),zz.push_back(WarPosition[distance[i][1]][distance[i][2]].getInfo().first[2]);
                        rebound.push_back(WarPosition[distance[i][1]][distance[i][2]].getInfo().second->getInfo()[13]),miss.push_back(WarPosition[league[i][1]][league[i][2]].getInfo().second->getInfo()[2]);
                    }
                    break;
                }
                case 8:
                {
                    xx.push_back(WarPosition[league[0][1]][league[0][2]].getInfo().first[3]),yy.push_back(WarPosition[league[0][1]][league[0][2]].getInfo().first[4]),zz.push_back(WarPosition[league[0][1]][league[0][2]].getInfo().first[2]);
                    rebound.push_back(WarPosition[league[0][1]][league[0][2]].getInfo().second->getInfo()[13]),miss.push_back(WarPosition[league[0][1]][league[0][2]].getInfo().second->getInfo()[2]);
                    break;
                }
                case 9:
                {
                    for(int i=0;i<league.size();i++)
                    {
                        xx.push_back(WarPosition[league[i][1]][league[i][2]].getInfo().first[3]),yy.push_back(WarPosition[league[i][1]][league[i][2]].getInfo().first[4]),zz.push_back(WarPosition[league[i][1]][league[i][2]].getInfo().first[2]);
                        rebound.push_back(WarPosition[league[i][1]][league[i][2]].getInfo().second->getInfo()[13]),miss.push_back(WarPosition[league[i][1]][league[i][2]].getInfo().second->getInfo()[2]);
                    }
                }
                case 10:
                {
                    for(int i=0;i<league.size();i++)
                    {
                        xx.push_back(WarPosition[league[i][1]][league[i][2]].getInfo().first[3]),yy.push_back(WarPosition[league[i][1]][league[i][2]].getInfo().first[4]),zz.push_back(WarPosition[league[i][1]][league[i][2]].getInfo().first[2]);
                        rebound.push_back(WarPosition[league[i][1]][league[i][2]].getInfo().second->getInfo()[13]),miss.push_back(WarPosition[league[i][1]][league[i][2]].getInfo().second->getInfo()[2]);
                    }
                    break;
                }
                case 11:
                {
                    xx.push_back(WarPosition[league[0][1]][league[0][2]].getInfo().first[3]),yy.push_back(WarPosition[league[0][1]][league[0][2]].getInfo().first[4]),zz.push_back(WarPosition[league[0][1]][league[0][2]].getInfo().first[2]);
                    rebound.push_back(WarPosition[league[0][1]][league[0][2]].getInfo().second->getInfo()[13]),miss.push_back(WarPosition[league[0][1]][league[0][2]].getInfo().second->getInfo()[2]);
                    for(int i=0;i<distance.size();i++)
                    {
                        xx.push_back(WarPosition[distance[i][1]][distance[i][2]].getInfo().first[3]),yy.push_back(WarPosition[distance[i][1]][distance[i][2]].getInfo().first[4]),zz.push_back(WarPosition[distance[i][1]][distance[i][2]].getInfo().first[2]);
                        rebound.push_back(WarPosition[distance[i][1]][distance[i][2]].getInfo().second->getInfo()[13]),miss.push_back(WarPosition[distance[i][1]][distance[i][2]].getInfo().second->getInfo()[2]);
                    }
                    break;
                }
                case 12:
                {
                    xx.push_back(WarPosition[league[0][1]][league[0][2]].getInfo().first[3]),yy.push_back(WarPosition[league[0][1]][league[0][2]].getInfo().first[4]),zz.push_back(WarPosition[league[0][1]][league[0][2]].getInfo().first[2]);
                    rebound.push_back(WarPosition[league[0][1]][league[0][2]].getInfo().second->getInfo()[13]),miss.push_back(WarPosition[league[0][1]][league[0][2]].getInfo().second->getInfo()[2]);
                    break;
                }
                case 13:
                {
                    xx.push_back(WarPosition[league[0][1]][league[0][2]].getInfo().first[3]),yy.push_back(WarPosition[league[0][1]][league[0][2]].getInfo().first[4]),zz.push_back(WarPosition[league[0][1]][league[0][2]].getInfo().first[2]);
                    rebound.push_back(WarPosition[league[0][1]][league[0][2]].getInfo().second->getInfo()[13]),miss.push_back(WarPosition[league[0][1]][league[0][2]].getInfo().second->getInfo()[2]);
                    break;
                }
                case 14:
                {
                    int map[10][5];
                    MakeDistance(map,getSwitchNum(zhenying),league[0][1],league[0][2]);
                    for(int i=0;i<league.size();i++)
                        if(map[league[i][1]][league[i][2]]<=1)
                        {
                            xx.push_back(WarPosition[league[i][1]][league[i][2]].getInfo().first[3]),yy.push_back(WarPosition[league[i][1]][league[i][2]].getInfo().first[4]),zz.push_back(WarPosition[league[i][1]][league[i][2]].getInfo().first[2]);
                            rebound.push_back(WarPosition[league[i][1]][league[i][2]].getInfo().second->getInfo()[13]),miss.push_back(WarPosition[league[i][1]][league[i][2]].getInfo().second->getInfo()[2]);
                        }
                    break;
                }
                case 15:
                {
                    for(int i=0;i<league.size();i++)
                    {
                        xx.push_back(WarPosition[league[i][1]][league[i][2]].getInfo().first[3]),yy.push_back(WarPosition[league[i][1]][league[i][2]].getInfo().first[4]),zz.push_back(WarPosition[league[i][1]][league[i][2]].getInfo().first[2]);
                        rebound.push_back(WarPosition[league[i][1]][league[i][2]].getInfo().second->getInfo()[13]),miss.push_back(WarPosition[league[i][1]][league[i][2]].getInfo().second->getInfo()[2]);
                    }
                    for(int i=0;i<distance.size();i++)
                    {
                        xx.push_back(WarPosition[distance[i][1]][distance[i][2]].getInfo().first[3]),yy.push_back(WarPosition[distance[i][1]][distance[i][2]].getInfo().first[4]),zz.push_back(WarPosition[distance[i][1]][distance[i][2]].getInfo().first[2]);
                        rebound.push_back(WarPosition[distance[i][1]][distance[i][2]].getInfo().second->getInfo()[13]),miss.push_back(WarPosition[distance[i][1]][distance[i][2]].getInfo().second->getInfo()[2]);
                    }
                    break;
                }
                case 16:
                {
                    for(int i=0;i<league.size()&&i<2;i++)
                    {
                        xx.push_back(WarPosition[league[i][1]][league[i][2]].getInfo().first[3]),yy.push_back(WarPosition[league[i][1]][league[i][2]].getInfo().first[4]),zz.push_back(WarPosition[league[i][1]][league[i][2]].getInfo().first[2]);
                        rebound.push_back(WarPosition[league[i][1]][league[i][2]].getInfo().second->getInfo()[13]),miss.push_back(WarPosition[league[i][1]][league[i][2]].getInfo().second->getInfo()[2]);
                    }
                    break;
                }
            }
            std::vector<std::vector<int>> tem;
            tem.push_back(xx),tem.push_back(yy),tem.push_back(zz),tem.push_back(rebound),tem.push_back(miss);
            if(A[zhenying]->MyTroop()->MyCondition()[xFront][yFront].getInfo().first[1]==9)
            {
                for(int i=0;i<league.size();i++)
                    dis.push_back(league[i][0]);
                tem.push_back(dis);
                std::vector<int> firenum={fireNum};
                tem.push_back(firenum);
            }
            if(A[zhenying]->MyTroop()->MyCondition()[xFront][yFront].getInfo().first[1]==13)
            {
                std::vector<int> defense;
                defense.push_back(WarPosition[league[0][1]][league[0][2]].getInfo().second->getInfo()[4]);
                tem.push_back(defense);
            }
            if(A[zhenying]->MyTroop()->MyCondition()[xFront][yFront].getInfo().first[1]==16)
            {
                std::vector<int> blood;
                blood.push_back(bleeding);
                tem.push_back(blood);
            }
            A[zhenying]->MyTroop()->MyCondition()[xFront][yFront].getInfo().second->done(tem);
            effects(zhenying,xFront,yFront);
        }
        else
        {
            std::cout<<"Type "<<A[zhenying]->MyTroop()->MyCondition()[xFront][yFront].getInfo().first[1]<<" soldier owned by "<<A[zhenying]->Getinfo().first[0]<<" move from ("<<xWar<<","<<yWar<<") to";
            int b[10][5];
            MakeDistance(b,WarPosition[league[0][1]][league[0][2]].getInfo().first[2],WarPosition[league[0][1]][league[0][2]].getInfo().first[5],WarPosition[league[0][1]][league[0][2]].getInfo().first[6]);
            for(int i=0;i<10;i++)
                for(int j=0;j<5;j++)
                    if(a[i][j]==0)
                    {WarPosition[i][j].go();break;}
            if(league[0][0]>A[zhenying]->MyTroop()->MyCondition()[xFront][yFront].getInfo().second->getInfo()[9])
            {
                for(int i=0;i<10;i++)
                    for(int j=0;j<5;j++)
                        if(b[i][j]==league[0][0]-A[zhenying]->MyTroop()->MyCondition()[xFront][yFront].getInfo().second->getInfo()[9]&&a[i][j]==A[zhenying]->MyTroop()->MyCondition()[xFront][yFront].getInfo().second->getInfo()[9]&&WarPosition[i][j].getInfo().first[0]==0)
                        {
                            WarPosition[i][j].input(A[zhenying]->MyTroop()->MyCondition()[xFront][yFront],zhenying,i,j);
                            std::cout<<" ("<<i<<","<<j<<")"<<std::endl;
                            return;
                        }
            }
            else
                for(int i=0;i<10;i++)
                    for(int j=0;j<5;j++)
                        if(b[i][j]==1&&WarPosition[i][j].getInfo().first[0]==0&&a[i][j]<A[zhenying]->MyTroop()->MyCondition()[xFront][yFront].getInfo().second->getInfo()[9])
                        {
                            WarPosition[i][j].input(A[zhenying]->MyTroop()->MyCondition()[xFront][yFront],zhenying,i,j);
                            std::cout<<" ("<<i<<","<<j<<")"<<std::endl;
                            return;
                        }

        }
    }
}

void war::running()
{
    int Order=getFirst();
    std::cout<<"Through the draw lots, "<<A[Order]->Getinfo().first[0]<<" get the first  to strike.";toEnter(2);
    show();
    determineBuff();
    system("pause");
    while(true)
    {
        // system("cls");
        std::cout<<std::setw(60)<<"this is "<<A[Order]->Getinfo().first[0]<<"'s turn";toEnter(2);
        for(int row=0;row<2;row++)
            for(int column=0;column<5;column++)
            {
                if(A[Order]->MyTroop()->MyCondition()[row][column].getInfo().first[0]==1&&A[Order]->MyTroop()->MyCondition()[row][column].getInfo().second->getInfo()[0]!=0)
                {
                    moveOrAttack(Order,row,column);
                    for(int i=0;i<2;i++)
                        for(int j=0;j<5;j++)
                        {
                            if(A[Order]->MyTroop()->MyCondition()[i][j].getInfo().first[0]==1&&A[Order]->MyTroop()->MyCondition()[i][j].getInfo().second->getInfo()[0]!=0)
                                A[Order]->MyTroop()->MyCondition()[i][j].getInfo().second->checkState(row,column,Order);
                            if(A[getSwitchNum(Order)]->MyTroop()->MyCondition()[i][j].getInfo().first[0]==1&&A[getSwitchNum(Order)]->MyTroop()->MyCondition()[i][j].getInfo().second->getInfo()[0]!=0)
                                A[getSwitchNum(Order)]->MyTroop()->MyCondition()[i][j].getInfo().second->checkState(row,column,Order);
                        }
                    A[Order]->MyTroop()->MyCondition()[row][column].getInfo().second->checkState();
                }
                else if(A[Order]->MyTroop()->MyCondition()[row][column].getInfo().first[0]==1&&A[Order]->MyTroop()->MyCondition()[row][column].getInfo().second->getInfo()[0]==0)
                {
                    for(int i=0;i<2;i++)
                        for(int j=0;j<5;j++)
                        {
                            if(A[Order]->MyTroop()->MyCondition()[i][j].getInfo().first[0]==1&&A[Order]->MyTroop()->MyCondition()[i][j].getInfo().second->getInfo()[0]!=0)
                                A[Order]->MyTroop()->MyCondition()[i][j].getInfo().second->checkState(row,column,Order);
                            if(A[getSwitchNum(Order)]->MyTroop()->MyCondition()[i][j].getInfo().first[0]==1&&A[getSwitchNum(Order)]->MyTroop()->MyCondition()[i][j].getInfo().second->getInfo()[0]!=0)
                                A[getSwitchNum(Order)]->MyTroop()->MyCondition()[i][j].getInfo().second->checkState(row,column,Order);
                        }
                }
            }
        deadout();
        show();
        system("pause");
        switching(&Order);
        // std::this_thread::sleep_for(std::chrono::seconds(1));
        if(A[Order]->MyTroop()->getAlive()==0)
            break;
    }
    switching(&Order);
    std::cout<<A[Order]->Getinfo().first[0]<<" wins! "<<A[getSwitchNum(Order)]->Getinfo().first[0]<<" is defeated!";toEnter(2);
    int harm=bleed(getSwitchNum(Order));
    std::cout<<A[getSwitchNum(Order)]->Getinfo().first[0]<<" bear "<<harm<<" harms and remains "<<A[getSwitchNum(Order)]->Getinfo().second[2]<<" Hp";toEnter(2);
    system("pause");
    A[Order]->gainExperience(60);
    A[getSwitchNum(Order)]->gainExperience(40);
    A[Order]->reFresh();
    A[getSwitchNum(Order)]->reFresh();
    // std::cout<<"war over!"<<std::endl;
}

void war::determineBuff()
{
    int wan=0,arn=0,mn=0,asn=0,pn=0,rn=0,en=0,win=0;
    for(int zhenying=0;zhenying<2;zhenying++)
    {
        if(special==0)
            for(int i=0;i<2;i++)
                for(int j=0;j<5;j++)
                    if(A[zhenying]->MyTroop()->MyCondition()[i][j].getInfo().first[0]==1)
                    {
                        if(Include(A[zhenying]->MyTroop()->MyCondition()[i][j].getInfo().second->getInfo()[11],WARRIOR))
                            wan++;
                        else if(Include(A[zhenying]->MyTroop()->MyCondition()[i][j].getInfo().second->getInfo()[11],ARCHER))
                            arn++;
                        else if(Include(A[zhenying]->MyTroop()->MyCondition()[i][j].getInfo().second->getInfo()[11],MAGICIAN))
                            mn++;
                        else
                            asn++;
                        if(Include(A[zhenying]->MyTroop()->MyCondition()[i][j].getInfo().second->getInfo()[11],PARTICLE))
                            pn++;
                        else if(Include(A[zhenying]->MyTroop()->MyCondition()[i][j].getInfo().second->getInfo()[11],REIKI))
                            rn++;
                        else if(Include(A[zhenying]->MyTroop()->MyCondition()[i][j].getInfo().second->getInfo()[11],ELEMENT))
                            en++;
                        else
                            win++;
                    }
        for(int i=0;i<2;i++)
            for(int j=0;j<5;j++)
                if(A[zhenying]->MyTroop()->MyCondition()[i][j].getInfo().first[0]==1)
                {
                    if(Include(A[zhenying]->MyTroop()->MyCondition()[i][j].getInfo().second->getInfo()[11],WARRIOR))
                        A[zhenying]->MyTroop()->MyCondition()[i][j].getInfo().second->makeit(wan/2);
                    else if(Include(A[zhenying]->MyTroop()->MyCondition()[i][j].getInfo().second->getInfo()[11],ARCHER))
                        A[zhenying]->MyTroop()->MyCondition()[i][j].getInfo().second->makeit(arn/2);
                    else if(Include(A[zhenying]->MyTroop()->MyCondition()[i][j].getInfo().second->getInfo()[11],MAGICIAN))
                        A[zhenying]->MyTroop()->MyCondition()[i][j].getInfo().second->makeit(mn/2);
                    else
                        A[zhenying]->MyTroop()->MyCondition()[i][j].getInfo().second->makeit(asn/2);
                    if(Include(A[zhenying]->MyTroop()->MyCondition()[i][j].getInfo().second->getInfo()[11],PARTICLE))
                        A[zhenying]->MyTroop()->MyCondition()[i][j].getInfo().second->makebaseBuff(pn/2);
                    else if(Include(A[zhenying]->MyTroop()->MyCondition()[i][j].getInfo().second->getInfo()[11],REIKI))
                        A[zhenying]->MyTroop()->MyCondition()[i][j].getInfo().second->makebaseBuff(rn/2);
                    else if(Include(A[zhenying]->MyTroop()->MyCondition()[i][j].getInfo().second->getInfo()[11],ELEMENT))
                        A[zhenying]->MyTroop()->MyCondition()[i][j].getInfo().second->makebaseBuff(en/2);
                    else
                        A[zhenying]->MyTroop()->MyCondition()[i][j].getInfo().second->makebaseBuff(win/2);
                }
    }

}
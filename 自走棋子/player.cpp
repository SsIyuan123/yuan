#include"player.h"
#include"tools.h"
#include<iostream>
#include<array>
#include<iomanip>
#include<chrono>
#include<thread>
#include<fstream>

player::player()
{
    // std::cout<<"Please name your role (less than 20 characters):"<<std::endl;
    // std::string a;
    // std::getline(std::cin,a);
    // while(a.length()>20)
    // {
    //     std::cout<<"The length of your name is longer than 20. Please name your role again(less than 20 characters):"<<std::endl;
    //     std::getline(std::cin,a);
    // }
    // Money=3,level=1,experience=0,name=a;
    Money=0,level=0,experience=0,WinAmount=0,Total=0,Winrate=0,One=0;
}

player::player(std::string name, std::string password, int WinAmount, int One, int Total, int Winrate):
    name(name),password(password),WinAmount(WinAmount),
    One(One),Total(Total),Winrate(Winrate),
    Money(5),level(1),experience(0){}

player::player(const player &tem)
{
    name=tem.name,
    password=tem.password;
    Atroop=tem.Atroop;
    Money=tem.Money;
    level=tem.level;
    experience=tem.experience;
    Maxexperience=tem.Maxexperience;
    WinAmount=tem.WinAmount;
    One=tem.One;
    Total=tem.Total;
    Winrate=tem.Winrate;
    Hp=tem.Hp;
    MaxHp=tem.MaxHp;
}

player::player(int test,std::string name):
    name(name),WinAmount(0),
    One(0),Total(0),Winrate(0),
    Money(5),level(1),experience(0)
{}

void player::Save()
{
    std::string filename="./Account/"+name+".txt";
    std::ofstream outfile;
    outfile.open(filename,std::ios::out);
    if(outfile.is_open())
    {
        outfile<<name<<" "<<password<<" "<<WinAmount<<" "<<One<<" "<<Total<<" "<<Winrate;
        outfile.close();
    }
    else std::cerr<<"cannot create the document"<<std::endl;
}

void player::reFresh()
{
    // std::cout<<"REFRESH"<<std::endl;
    for(int i=0;i<2;i++)
        for(int j=0;j<5;j++)
        {
            int *Info=Atroop.MyCondition()[i][j].getInfo().first;
            if(Info[0]==1)
                Atroop.MyCondition()[i][j].relive();
        }
}

void player::changeFrontline()
{
    system("cls");
    std::cout<<std::setw(75)<<" "<<"MY TROOP";
    fengexian(0,160,2,4);
    std::cout<<std::setw(68)<<" "<<"To Change the Frontline";
    toEnter(3);
    Atroop.showFrontline();
    fengexian(0,160,2,3);
    Atroop.showAllSoldiers();
    toEnter(1);
    std::cout<<std::setw(73)<<" "<<"Your Authority";
    toEnter(2);
    std::cout<<std::setw(64)<<" "<<"1.Get a soldier down the frontline";
    toEnter(2);
    std::cout<<std::setw(63)<<" "<<"2.Turn a soldier on the frontline";
    toEnter(2);
    std::cout<<"Please input your instruction (1/2/0)(If 0, return):";
    int ins;
    std::cin>>ins;toEnter(1);
    switch(ins)
    {
        case 0:return;
        case 1:
        {
            Atroop.getdown();
            changeFrontline();
            break;
        }
        case 2:
        {
            Atroop.turnOnFrontline();
            changeFrontline();
            break;
        }
        default:
        {std::cout<<"What do you mean?";system("pause");changeFrontline();break;}
    }
}

void player::Hpdecrease(int x)
{
    Hp=edgeleft(Hp-x,0);
}

void player::troopMenu()
{
    while(true)
    {
        system("cls");
        std::cout<<"SALUTE "<<name<<", WELCOME TO TROOP";
        toEnter(2);
        std::cout<<std::setw(75)<<" "<<"MY TROOP";
        fengexian(0,160,2,4);
        Atroop.showFrontline();
        fengexian(0,160,2,3);
        Atroop.showAllSoldiers();
        toEnter(2);
        std::cout<<std::setw(73)<<" "<<"Your Authority";
        toEnter(3);
        std::cout<<std::setw(68)<<" "<<"1.Change The Frontline";
        toEnter(2);
        std::cout<<std::setw(68)<<" "<<"2.Upgrade Your Soldier";
        toEnter(2);
        std::cout<<std::setw(66)<<" "<<"3.Look into formation buff";
        toEnter(2);
        std::cout<<std::setw(64)<<" "<<"4.Search the soldiers' details";
        toEnter(2);
        std::cout<<std::setw(73)<<" "<<"5.To the store";
        fengexian(0,160,2,3);
        std::cout<<"Please input your instruction (1/2/3/4/5/6):";
        std::cin.clear();
        int ins;
        std::cin>>ins;
        std::cout<<std::endl;
        if(ins==1)
            changeFrontline();
        else if(ins == 2)
        {
            Atroop.showAllSoldiers();
            Upgrade();
            std::cout<<"Automatically blend three of the same soldiers to get grades up";system("pause");
        }
        else if(ins == 3)
        {
            std::cout<<"The service is being exploiting";system("pause");
        }
        else if(ins == 4)
        {
            showDetail();
        }
        else if(ins==5)
        {
            return;
        }
        // else if(ins == 3)
        //     sellSoldier();
    }
}


void player::Upgrade()
{
    std::vector<std::array<int,3>> Amount;
    for(int i=0;i<Atroop.GetInfo().first.size();i++)
    {
        int flag=0;
        int* Info=Atroop.GetInfo().first[i].second->getInfo();
        for(int j=0;j<Amount.size();j++)
            if(Info[11]==Amount[j][2]&&Info[6]==Amount[j][1])
                Amount[j][0]++,flag=1;
        if(flag==0)
        {std::array<int,3> tem={1,Info[6],Info[11]};Amount.push_back(tem);}
        delete[] Info;
    }
    for(int i=0;i<Amount.size();i++)
        if(Amount[i][0]>=3)
        {
            int OnFrontline_Flag=0;
            for(int j=0;j<Atroop.GetInfo().first.size();j++)
            {
                int* Info=Atroop.GetInfo().first[j].second->getInfo();
                if(Atroop.GetInfo().first[j].first==1&&Info[6]==Amount[i][1]&&Info[11]==Amount[i][2])
                {
                    Atroop.GetInfo().first[j].second->levelUp();
                    OnFrontline_Flag=1;
                    delete[] Info;
                    break;
                }
            }
            if(OnFrontline_Flag==0)
            {
                for(int j=0;j<Atroop.GetInfo().first.size();j++)
                {
                    int* Info=Atroop.GetInfo().first[j].second->getInfo();
                    if(Info[6]==Amount[i][1]&&Info[11]==Amount[i][2])
                    {
                        Atroop.GetInfo().first[j].second->levelUp();
                        delete[] Info;
                        break;
                    }
                }
            }
            int num=0;
            int x[2];
            for(int j=Atroop.GetInfo().first.size()-1;j>=0;j--)
            {
                int* Info=Atroop.GetInfo().first[j].second->getInfo();
                if(Info[6]==Amount[i][1]&&Info[11]==Amount[i][2])
                {
                    delete[] Info;
                    Atroop.sell(j);
                    num++;
                }
                if(num==2) break;
            }
            Upgrade();
        }
    return;
}

void player::showDetail()
{
    while(true)
    {
        system("cls");
        std::cout<<std::setw(75)<<" "<<"MY TROOP";
        fengexian(0,160,2,4);
        Atroop.showAllSoldiers();
        std::cout<<"Please input the number of the soldier you'd like to search for more detailed information:(If 0, return)";
        int num;
        std::cin>>num;
        toEnter(2);
        if(num==0)
            break;
        else
        {
            system("cls");
            std::cout<<std::setw(75)<<" "<<"MY TROOP";
            fengexian(0,160,2,4);
            Atroop.showAllSoldiers(num-1);
            Atroop.GetInfo().first[num-1].second->show();
            system("pause");
        }
    }
}

void player::changeRecord(int Win, int One)
{
    WinAmount+=Win;
    this->One+=One;
    Total+=Win;
    if(Win==0&&One==0)
    Total++;
    Winrate=(float)WinAmount/(float)Total;
}

void player::IncreaseMoney(int x)
{
    Money+=x;
}

void player::gainExperience(int delta)
{
    if(experience+delta<Maxexperience)
        experience+=delta;
    else//每升3级，上场士兵+1；每升4级，仓库储存容量+1
    {
        level++,experience=experience+delta-Maxexperience;
        if(level%3==0)
            Atroop.changeAmount(0,0,0,1);
        if(level%2==0)
            Atroop.changeAmount(0,0,1,0);
    }
}

std::pair<std::vector<std::string>,int*> player::Getinfo()
{
    std::pair<std::vector<std::string>,int*> tem;
    std::vector<std::string> b={name,password};
    tem.first=b;
    int* a = new int[3];
    a[0]=Money,a[1]=level,a[2]=experience;
    a[3]=Hp;
    tem.second=a;
    return tem;
} 

void player::showPersonalInfo()
{
    system("cls");
    std::string tmp;
    std::cout<<std::setw(40-name.size()/2)<<" "<<name;
    toEnter(2);
    tmp="Hp: "+std::to_string(Hp);
    std::cout<<std::setw(20)<<" "<<std::left<<std::setw(32)<<tmp;
    tmp="Level: "+std::to_string(level);
    std::cout<<std::left<<std::setw(32)<<tmp;
    toEnter(2);
    tmp="Wins: "+std::to_string(WinAmount);
    std::cout<<std::setw(20)<<" "<<std::left<<std::setw(32)<<tmp;
    tmp="Big Winner: "+std::to_string(One);
    std::cout<<std::left<<std::setw(32)<<tmp;
    toEnter(2);
    tmp="Total playtimes: "+std::to_string(Total);
    std::cout<<std::setw(20)<<" "<<std::left<<std::setw(32)<<tmp;
    tmp="Win rate: "+std::to_string(Winrate);
    std::cout<<std::left<<std::setw(32)<<tmp;
    toEnter(2);
    system("pause");
}


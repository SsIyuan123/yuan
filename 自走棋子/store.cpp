#include"store.h"
#include"tools.h"

#include"chesstype.h"

#include<iostream>
#include<iomanip>

store::store(player& a):WindowNum(4)
{
    A=&a;
    for(int i=0;i<WindowNum;i++)
    {std::pair<int,soldier*> tem={0,nullptr};goods.push_back(tem);}
}

store::store(store& a):A(a.A),WindowNum(a.WindowNum),goods(goods){}

void store::generateSoldier()
{
    goods.clear();
    std::cout<<"generate";
    soldier** tmp=new soldier*[4];
    for(int i=0;i<WindowNum;i++)
    {
        int ran=random(0,95);
        int money=3;
        switch(ran%4)
        {
            case 0:tmp[i] = new ParticleWarrior();break;
            case 1:tmp[i] = new LaserArcher();break;
            case 2:tmp[i] = new ParticleEngineer();break;
            case 3:tmp[i] = new DimensionAssassin();break;
        }
        int* Amount = A->MyTroop()->GetInfo().second;
        int rate=edgeleft(edgeright(Amount[5],5)*10-5+edgeright(Amount[6],3)*15,0);//每多一个二级士兵概率加10％，每多一个三级士兵概率加15%，第一个高级士兵少加5％的概率
        delete[] Amount;
        int levelran=random(1,1000);
        if(levelran<=rate*10)
            tmp[i]->levelUp(), money = 10;
        std::pair<int, soldier*> tem[4];
        tem[i] = { money,tmp[i] };
        goods.push_back(tem[i]);
    }
    delete[]tmp;
    return;
}

void store::menu()
{
    while(true)
    {
        system("cls");
        std::cout<<"Hello "<<A->Getinfo().first[0]<<", welcome to fairy store!";
        toEnter(2);
        std::cout<<std::setw(75)<<" "<<"FAIRY STORE";
        fengexian(0,160,2,4);
        std::cout<<std::setw(75)<<" "<<"THE SERVICE";
        toEnter(3);
        std::cout<<std::setw(72)<<" "<<"1.Hire the soldier";
        toEnter(2);
        std::cout<<std::setw(71)<<" "<<"2.Update the goods";
        toEnter(2);
        std::cout<<std::setw(70)<<" "<<"3.Sell your soldiers";
        toEnter(2);
        std::cout<<std::setw(65)<<" "<<"4.Search the soldiers' details";
        toEnter(2);
        std::cout<<std::setw(73)<<" "<<"5.To the troop";
        toEnter(2);
        std::cout<<std::setw(67)<<" "<<"6.Ready for the next war";
        fengexian(0,160,2,3);
        std::cout<<std::setw(67)<<" "<<"THE SOLDIERS TO BE HIRED:";
        toEnter(3);
        showGoods();
        showPlayerInfo();
        std::cout<<"Please input your instruction (1/2/3/4/5/6):";
        std::cin.clear();
        int ins;
        std::cin>>ins;
        std::cout<<std::endl;
        if(ins==1)
            hiresoldier();
        else if(ins == 2)
            reGenerate();
        else if(ins == 3)
            sellSoldier();
        else if(ins == 4)
            {std::cout<<"The service is being exploiting";system("pause");}
        else if(ins == 5)
            A->troopMenu();
        else if(ins == 6)
        {
            std::cout<<"Confirm that you are ready.(y/n): (If y, you cannot make any change until next war)";
            char choose;
            std::cin.clear();
            std::cin>>choose;
            std::cin.clear();
            toEnter(1);
            if(lower(choose)=='y')
                return;
        }
    }
}

void store::hiresoldier()
{
    system("cls");
    std::cout<<std::setw(75)<<" "<<"FAIRY STORE";
    fengexian(0,160,2,4);
    std::cout<<std::setw(73)<<" "<<"HIRING SERVICE";
    toEnter(3);
    showGoods();
    showPlayerInfo();
    std::cout<<"Input the number of the soldier you'd like to hire:(If return, input 0):";
    std::cin.clear();
    int number;
    std::cin>>number;toEnter(1);
    if(number==0)
        return;
    else if(number<5&&number>0)
    {
        if(A->Getinfo().second[0]<goods[number-1].first)
        {
            std::cout<<"Your money is not enough! Choose another?";
            toEnter(2);
            system("pause");
            hiresoldier();
        }
        else
        {
            buy(number-1);
            clean(number-1);
            hiresoldier();;
        }
    }
    else
    {
        std::cout<<"Your number is out of our goods. Try it again!";
        system("pause");
        hiresoldier();;
    }
}

void store::reGenerate()
{
    system("cls");
    std::cout<<std::setw(75)<<" "<<"FAIRY STORE";
    fengexian(0,160,2,4);
    std::cout<<std::setw(73)<<" "<<"UPDATE SERVICE";
    toEnter(3);
    showGoods();
    showPlayerInfo();
    std::cout<<"You need to cost 2 dollars to update all the soldiers. Pay it?(y/n)(If n, you will be back to the menu)";
    char choose;
    std::cin.clear();
    std::cin>>choose;
    toEnter(1);
    if(lower(choose)=='y')
    {
        A->IncreaseMoney(-2);
        std::cout<<"Soldiers has been updated.";
        system("pause");
        generateSoldier();
        reGenerate();
    }
    else if(lower(choose)=='n')
        return;
    else 
    {std::cout<<"What do you mean?";reGenerate();}
}

void store::sellSoldier()
{
    system("cls");
    std::cout<<std::setw(75)<<" "<<"FAIRY STORE";
    fengexian(0,160,2,4);
    std::cout<<std::setw(73)<<" "<<"REBUY SERVICE";
    toEnter(2);
    int* Info=A->Getinfo().second;
    std::cout<<std::setw(73)<<" "<<"Yourmoney: "<<Info[0];
    toEnter(2);
    A->MyTroop()->showAllSoldiers();
    toEnter(2);
    std::cout<<std::setw(78)<<" "<<"PRICE";toEnter(3);
    std::cout<<std::setw(67)<<" "<<"LEVEL = 1 ---> 2 DOLLARS!";toEnter(2);
    std::cout<<std::setw(67)<<" "<<"LEVEL = 2 ---> 7 DOLLARS!";toEnter(2);
    std::cout<<std::setw(67)<<" "<<"LEVEL = 3 ---> 20 DOLLARS!";toEnter(3);
    std::cout<<"Input the number of the soldiers you'd like to sell:(To return, input 0)";
    int number;
    std::cin>>number;toEnter(1);
    int* Amount=A->MyTroop()->GetInfo().second;
    if(number==0) return;
    else if(number<=Amount[0]+Amount[1])
    {
        int* price=A->MyTroop()->GetInfo().first[number-1].second->getInfo();
        int Money;
        switch(price[6])
        {
            case 1:Money=3;break;
            case 2:Money=7;break;
            case 3:Money=20;break;
        }
        delete[] price;
        A->IncreaseMoney(Money);
        A->MyTroop()->sell(number-1);
    }
    else
    {
        std::cout<<"What do you mean?";
        system("pause");
        sellSoldier();
    }
    
}

void store::showGoods()
{
    std::string tmp,name,type;
    for(int i=0;i<WindowNum;i++)
        std::cout<<std::setw(15)<<" "<<std::left<<std::setw(25)<<i+1;
    toEnter(2);
    for(int i=0;i<WindowNum;i++)
    {
        std::string level;
        if(goods[i].second==nullptr)
            level=std::to_string(0);
        else
            level=std::to_string(goods[i].second->getInfo()[6]);
        tmp="level: "+level;
        std::cout<<std::left<<std::setw(40)<<tmp;

    }
    toEnter(2);
    for(int i=0;i<WindowNum;i++)
    {
        if(goods[i].second==nullptr)
            name="SOLD OUT";
        else
        {
            switch(goods[i].second->getInfo()[11])
            {
                case 1:name="Particle Warrior";break;
                case 2:name="Laser Archer";break;
                case 3:name="Particle Engineer";break;
                case 4:name="Dimension Assassin";break;            
            }
            // delete[] Info;
        }
        tmp="name: "+name;
        std::cout<<std::left<<std::setw(40)<<tmp;
    }
    toEnter(2);
    for(int i=0;i<WindowNum;i++)
    {
        if(goods[i].second==nullptr)
            type="SOLD OUT";
        else
        {
            switch(goods[i].second->getInfo()[11])
            {
                case 1:type="Particle World, Warrior";break;
                case 2:type="Particle World, Archer";break;
                case 3:type="Particle World, Magician";break;
                case 4:type="Particle World, Assassin";break;            
            }
        }
        tmp="type: "+type;
        std::cout<<std::left<<std::setw(40)<<tmp;
    }
    toEnter(2);
    for(int i=0;i<WindowNum;i++)
    {
        std::string price=std::to_string(goods[i].first);
        tmp="price: "+price;
        std::cout<<std::left<<std::setw(40)<<tmp;
    }
    fengexian(0,160,2,3);
}

void store::showPlayerInfo()
{
    std::string tmp;
    tmp="money: "+std::to_string(A->Getinfo().second[0]);
    std::cout << std::setw(40) << " " << std::left << std::setw(40) << tmp;std::cout.flush();
    // tmp="Your Warehouse: "+std::to_string(A.MyTroop()->GetInfo().second[0])+'/'+std::to_string(A.MyTroop()->GetInfo().second[2]);
    // std::cout<<std::setw(20)<<" "<<tmp;
    std::cout<<std::setw(20)<<" "<<"Your Warehouse: ";
    std::cout<<A->MyTroop()->GetInfo().second[0];
    std::cout<<'/';
    std::cout<<A->MyTroop()->GetInfo().second[2];
    toEnter(3);
    return;
}

void store::clean(int x)
{
    goods.erase(goods.begin()+x);
    std::pair<int,soldier*> tem={0,nullptr};
    goods.insert(goods.begin()+x,tem);
}

void store::buy(int x)
{
    if(A->Getinfo().second[0]<goods[x].first)
    {std::cout<<"Your money is not enough!"<<std::endl;return;}
    if(A->MyTroop()->GetInfo().second[0]==A->MyTroop()->GetInfo().second[2])
    {std::cout<<"Your Warehouse is full!"<<std::endl;return;}
    if(goods[x].first==0)
    {std::cout<<"The soldier has been bought"<<std::endl;return;}
    A->MyTroop()->gota(goods[x].second);
    A->IncreaseMoney(-goods[x].first);
}
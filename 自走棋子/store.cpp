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
    // std::cout<<"generate";
    soldier** tmp=new soldier*[4];
    for(int i=0;i<WindowNum;i++)
    {
        int ran=random(0,256);
        int money=3;
        switch(ran%16)
        {
            case 0:tmp[i] = new ParticleWarrior();break;
            case 1:tmp[i] = new LaserArcher();break;
            case 2:tmp[i] = new ParticleEngineer();break;
            case 3:tmp[i] = new DimensionAssassin();break;
            case 4:tmp[i] = new Swordman();break;
            case 5:tmp[i] = new Hypnotist();break;
            case 6:tmp[i] = new Fulu_Painter();break;
            case 7:tmp[i] = new Sorcerer();break;
            case 8:tmp[i] = new fire_Warrior();break;
            case 9:tmp[i] = new electri_Archer();break;
            case 10:tmp[i] = new ice_Magician();break;
            case 11:tmp[i] = new vortexSailer();break;
            case 12:tmp[i] = new wereWolf();break;
            case 13:tmp[i] = new Dragon();break;
            case 14:tmp[i] = new wild_Priest();break;
            case 15:tmp[i] = new Dryads();break; 
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
        std::cout<<"你好"<<A->Getinfo().first[0]<<"，欢迎来到精灵商店！";
        toEnter(2);
        std::cout<<std::setw(78)<<" "<<"精灵商店";
        fengexian(0,160,2,4);
        std::cout<<std::setw(77)<<" "<<"服务内容";
        toEnter(3);
        std::cout<<std::setw(76)<<" "<<"1.雇佣士兵";
        toEnter(2);
        std::cout<<std::setw(76)<<" "<<"2.上新士兵";
        toEnter(2);
        std::cout<<std::setw(76)<<" "<<"3.售卖士兵";
        toEnter(2);
        std::cout<<std::setw(76)<<" "<<"4.查询士兵";
        toEnter(2);
        std::cout<<std::setw(76)<<" "<<"5.去军营";
        toEnter(2);
        std::cout<<std::setw(76)<<" "<<"6.去战斗！";
        fengexian(0,160,2,3);
        std::cout<<std::setw(74)<<" "<<"可雇佣的士兵：";
        toEnter(3);
        showGoods();
        showPlayerInfo();
        std::cout<<"选择你要的服务(1/2/3/4/5/6):";
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
            lookinto();
        else if(ins == 5)
            A->troopMenu();
        else if(ins == 6)
        {
            std::cout<<"确定你准备好了吗？(y/n): (如果输入了y，到下次对战前就不能修改阵型了)";
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
    std::cout<<std::setw(78)<<" "<<"精灵商店";
    fengexian(0,160,2,4);
    std::cout<<std::setw(78)<<" "<<"雇佣服务";
    toEnter(3);
    showGoods();
    showPlayerInfo();
    std::cout<<"请输入你要雇佣的士兵序号：（如果输入0，就返回商店主页）";
    std::cin.clear();
    int number;
    std::cin>>number;toEnter(1);
    if(number==0)
        return;
    else if(number<5&&number>0)
    {
        if(A->Getinfo().second[0]<goods[number-1].first)
        {
            std::cout<<"你的钱不够啊，要不换一个?";
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
        std::cout<<"这好像不是我们的货架呢";
        system("pause");
        hiresoldier();;
    }
}

void store::reGenerate()
{
    system("cls");
    std::cout<<std::setw(78)<<" "<<"精灵商店";
    fengexian(0,160,2,4);
    std::cout<<std::setw(78)<<" "<<"上新服务";
    toEnter(3);
    showGoods();
    showPlayerInfo();
    std::cout<<"你需要花费2块钱置换所有士兵，你愿意吗？(y/n)如果为n，则返回商店主页：";
    char choose;
    std::cin.clear();
    std::cin>>choose;
    toEnter(1);
    if(lower(choose)=='y')
    {
        A->IncreaseMoney(-2);
        std::cout<<"士兵上新完成！";
        system("pause");
        generateSoldier();
        reGenerate();
    }
    else if(lower(choose)=='n')
        return;
    else 
    {std::cout<<"你在说什么？没懂";reGenerate();}
}

void store::lookinto()
{
    system("cls");
    std::cout<<std::setw(76)<<" "<<"精灵商店";
    fengexian(0,160,2,4);
    A->MyTroop()->showAllSoldiers();
    std::cout<<"请输入你想查阅更多信息的士兵编号:（如果输入0，返回菜单）";
    int num;
    std::cin>>num;
    toEnter(2);
    if(num==0)
        return;
    else
    {
        system("cls");
        std::cout<<std::setw(76)<<" "<<"精灵商店";
        fengexian(0,160,2,4);
        A->MyTroop()->allinformation(num-1);
        system("pause");
    }
}

void store::sellSoldier()
{
    system("cls");
    std::cout<<std::setw(78)<<" "<<"精灵商店";
    fengexian(0,160,2,4);
    std::cout<<std::setw(78)<<" "<<"回收服务";
    toEnter(2);
    int* Info=A->Getinfo().second;
    std::cout<<std::setw(73)<<" "<<"你的钱： "<<Info[0];
    toEnter(2);
    A->MyTroop()->showAllSoldiers();
    toEnter(2);
    std::cout<<std::setw(76)<<" "<<"我们承诺的价格：";toEnter(3);
    std::cout<<std::setw(71)<<" "<<"LEVEL = 1 ---> 2 元!";toEnter(2);
    std::cout<<std::setw(71)<<" "<<"LEVEL = 2 ---> 7 元!";toEnter(2);
    std::cout<<std::setw(71)<<" "<<"LEVEL = 3 ---> 20 元!";toEnter(3);
    std::cout<<"输入你想卖掉的英雄序号：(输入0返回商店主页)";
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
        sellSoldier();
    }
    else
    {
        std::cout<<"你没这个编号的英雄哦。";
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
        tmp="级别："+level;
        std::cout<<tmp<<std::left<<std::setw(41-(tmp.length()-1)/3*2)<<" ";

    }
    toEnter(2);
    for(int i=0;i<WindowNum;i++)
    {
        if(goods[i].second==nullptr)
            name="已出售";
        else
        {
            switch(goods[i].second->getInfo()[11])
            {
                case 1:name="量子战士";break;
                case 2:name="激光枪手";break;
                case 3:name="量子工程师";break;
                case 4:name="智子";break;      
                case 5:name="剑修";break;
                case 6:name="心修";break;
                case 7:name="箓修";break;
                case 8:name="邪修";break;
                case 9:name="野火修士";break;
                case 10:name="十万伏特";break;
                case 11:name="永冬";break;
                case 12:name="漩涡猎手";break;
                case 13:name="狼人";break;
                case 14:name="没牙仔";break;
                case 15:name="风祭";break;
                case 16:name="灵树";break;      
            }
            // delete[] Info;
        }
        tmp="名称："+name;
        std::cout<<tmp<<std::left<<std::setw(40-(tmp.length()-1)/3*2)<<" ";
    }
    toEnter(2);
    for(int i=0;i<WindowNum;i++)
    {
        if(goods[i].second==nullptr)
            type="已出售";
        else
        {
            switch(goods[i].second->getInfo()[11])
            {
                case 1:type="量子世界, 战士";break;
                case 2:type="量子世界, 弓箭手";break;
                case 3:type="量子世界, 魔法师";break;
                case 4:type="量子世界, 刺客";break; 
                case 5:type="修仙世界，战士";break;
                case 6:type="修仙世界，弓箭手";break;
                case 7:type="修仙世界，魔法师";break;
                case 8:type="修仙世界，刺客";break;
                case 9:type="元素世界，战士";break;
                case 10:type="元素世界，弓箭手";break;
                case 11:type="元素世界，魔法师";break;
                case 12:type="元素世界，刺客";break;
                case 13:type="野兽世界，战士";break;
                case 14:type="野兽世界，弓箭手";break;
                case 15:type="野兽世界，魔法师";break;
                case 16:type="野兽世界，刺客";break;

            }
        }
        tmp="类型："+type;
        std::cout<<tmp<<std::left<<std::setw(40-(tmp.length()-1)/3*2)<<" ";
    }
    toEnter(2);
    for(int i=0;i<WindowNum;i++)
    {
        std::string price=std::to_string(goods[i].first);
        tmp="价格："+price;
        std::cout<<tmp<<std::left<<std::setw(41-(tmp.length()-1)/3*2)<<" ";
    }
    fengexian(0,160,2,3);
}

void store::showPlayerInfo()
{
    std::string tmp;
    tmp="钱："+std::to_string(A->Getinfo().second[0]);
    std::cout << std::setw(40) << " " << std::left << std::setw(40) << tmp;std::cout.flush();
    // tmp="Your Warehouse: "+std::to_string(A.MyTroop()->GetInfo().second[0])+'/'+std::to_string(A.MyTroop()->GetInfo().second[2]);
    // std::cout<<std::setw(20)<<" "<<tmp;
    std::cout<<std::setw(20)<<" "<<"你的仓库：";
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
    {std::cout<<"你的钱不够！"<<std::endl;return;}
    if(A->MyTroop()->GetInfo().second[0]==A->MyTroop()->GetInfo().second[2])
    {std::cout<<"你的仓库满了!"<<std::endl;return;}
    if(goods[x].first==0)
    {std::cout<<"这个士兵已经被买走了！"<<std::endl;return;}
    A->MyTroop()->gota(goods[x].second);
    A->IncreaseMoney(-goods[x].first);
}
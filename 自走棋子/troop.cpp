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
    {std::cout<<"你的仓库满了！"<<std::endl;return;}
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
    std::cout<<std::setw(76)<<" "<<"我的军营";
    fengexian(0,160,2,4);
    std::cout<<std::setw(74)<<" "<<"变动前线人事";
    toEnter(3);
    showFrontline();
    fengexian(0,160,2,3);
    showAllSoldiers();
    toEnter(1);
    if(Warehouse_Amount==Warehouse_limit)
    {std::cout<<"你的仓库满了，可以去商店卖点士兵";system("pause");return;}
    std::cout<<"请输入你想要调下前线的士兵位置(行，列)";
    std::string input;
    std::cin>>input;toEnter(1);
    std::vector<char> number={'0','1','2','3','4','5','6','7','8','9'};
    int position[2],num=0;
    for(int i=0;i<input.size();i++)
        if(Include(input[i],number)==1)
            position[num]=(int)(input[i]-48)-1,num++;
    int* Info=FrontDistribution[position[0]][position[1]].getInfo().first;
    if(Info[0]==0)
    {std::cout<<"这个位置 ("<<position[0]<<","<<position[1]<<") 是空哒";system("pause");return;}
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
    std::cout<<std::setw(76)<<" "<<"我的军营";
    fengexian(0,160,2,4);
    std::cout<<std::setw(74)<<" "<<"变动前线人事";
    toEnter(3);
    showFrontline();
    fengexian(0,160,2,3);
    showAllSoldiers();
    toEnter(1);
    if(OnFrontline_Amount==OnFrontline_limit)
    {std::cout<<"你的前线承受不了这么多士兵！";system("pause");return;}
    std::cout<<"请输入前往前线的士兵序号：";
    int input;
    std::cin>>input;toEnter(1);
    input--;
    if(input<MySoldier.size())
    {
        if(MySoldier[input].first==1)
        {std::cout<<"这个士兵已经在前线了";system("pause");return;}
    }
    else {std::cout<<"找不到这个士兵";system("pause");return;}
    std::cout<<"请输入这个士兵上阵的位置：(行，列)";
    std::string inpu;
    std::cin>>inpu;toEnter(1);
    std::vector<char> number={'0','1','2','3','4','5','6','7','8','9'};
    int position[2],num=0;
    for(int i=0;i<inpu.size();i++)
        if(Include(inpu[i],number)==1)
            std::cout<<position[i]<<std::endl,position[num]=(int)(inpu[i]-48)-1,num++;
    std::cout<<position[0]<<position[1]<<std::endl;
    if(FrontDistribution[position[0]][position[1]].getInfo().first[0]==1)
    {std::cout<<"这个位置已经有人了";system("pause");return;}
    switching(&MySoldier[input].first);
    FrontDistribution[position[0]][position[1]].lay(MySoldier[input].second,position[0],position[1]);
    OnFrontline_Amount++,Warehouse_Amount--;
    return;
}

void troop::allinformation(int index)
{
    showAllSoldiers(index);
    GetInfo().first[index].second->show();
}

void troop::showFrontline()
{
    std::cout<<std::setw(78)<<" "<<"前线";
    toEnter(3);
    std::cout<<std::setw(26)<<" ";
    for(int i=0;i<5;i++)
    {
        std::string tem="列 "+std::to_string(i+1);
        std::cout<<std::setw(13)<<" "<<tem;
    }
    toEnter(2);
    for(int i=0;i<2;i++)
    {
        std::cout<<std::right<<std::setw(20)<<"行 "<<i+1;
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
    std::cout<<std::setw(30)<<" "<<"前线人数："<<OnFrontline_Amount<<"/"<<OnFrontline_limit;
    std::cout<<std::setw(50)<<" "<<"仓库人数："<<Warehouse_Amount<<"/"<<Warehouse_limit;
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
        std::cout<<"你的士兵：";
        toEnter(3);
        if(MySoldier.size()==0)
        {std::cout<<std::setw(40)<<" "<<"空无一人:(";fengexian(0,160,2,2);return;}
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
                tmp="级别："+level;
                std::cout<<tmp<<std::left<<std::setw(41-(tmp.length()-1)/3*2)<<" ";
            }
            toEnter(2);
            for(int i=0;i+j*4<MySoldier.size()&&i<4;i++)
            {
                switch(MySoldier[i+j*4].second->getInfo()[11])
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
                tmp="名字："+name;
                std::cout<<tmp<<std::left<<std::setw(40-(tmp.length()-1)/3*2)<<" ";
            }
            toEnter(2);
            for(int i=0;i+j*4<MySoldier.size()&&i<4;i++)
            {
                switch(MySoldier[i+j*4].second->getInfo()[11])
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
                tmp="类型："+type;
                std::cout<<tmp<<std::left<<std::setw(40-(tmp.length()-1)/3*2)<<" ";
            }
            toEnter(2);
            for(int i=0;i+j*4<MySoldier.size()&&i<4;i++)
            {
                std::string Position;
                switch(MySoldier[i+j*4].first)
                {
                    case 0:Position="仓库";break;
                    case 1:Position="前线";break;
                }
                tmp="位置："+Position;
                std::cout<<tmp<<std::left<<std::setw(40-(tmp.length()-1)/3*2)<<" ";
            }
            toEnter(2);
            for(int i=0;i+j*4<MySoldier.size()&&i<4;i++)
            {
                int* Info=MySoldier[i+j*4].second->getInfo();
                std::string warname=std::to_string(Info[11]);
                delete[] Info;
                tmp="战争编号："+warname;
                std::cout<<tmp<<std::left<<std::setw(40-(tmp.length()-1)/3*2)<<" ";
            }
            toEnter(2);
            for(int i=0;i+j*4<MySoldier.size()&&i<4;i++)
            {
                std::string Detail;
                if(MySoldier[i+j*4].first==0)
                    Detail="仓库";
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
                tmp="具体位置："+Detail;
                std::cout<<tmp<<std::left<<std::setw(40-(tmp.length()-1)/3*2)<<" ";
            }
            toEnter(3);
        }
    }
    else
    {
        int* Info=MySoldier[x].second->getInfo();
        std::cout<<std::setw(79)<<" "<<x+1;toEnter(2);
        tmp="级别："+std::to_string(Info[6]);
        std::cout<<std::left<<std::setw(65)<<" "<<tmp;toEnter(2);
        switch(Info[11])
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
        tmp="名字："+name;
        std::cout<<std::setw(65)<<" "<<tmp<<std::left<<std::setw(40-(tmp.length()-1)/3*2)<<" ";
        toEnter(2);
        switch(Info[11])
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
        tmp="类型："+type;
        std::cout<<std::setw(65)<<" "<<tmp<<std::left<<std::setw(40-(tmp.length()-1)/3*2)<<" ";
        toEnter(2);
        std::string Position;
        switch(MySoldier[x].first)
        {
            case 0:Position="仓库";break;
            case 1:Position="前线";break;
        }
        tmp="位置："+Position;
        std::cout<<std::left<<std::setw(65)<<" "<<tmp;toEnter(2);
        std::string warname=std::to_string(Info[11]);
        tmp="战争编号："+warname;
        std::cout<<std::left<<std::setw(65)<<" "<<tmp;toEnter(2);
        std::string Detail;
        if(MySoldier[x].first==0)
            Detail="仓库";
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
        tmp="具体位置"+Detail;
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

#include"playchess.h"
#include"store.h"
#include"tools.h"
#include<iostream>
#include<string>
#include<fstream>


playchess::playchess()
{
    playtime=0;
    playernum=0;
    aliveNum=0;
    circule=0;
    money_growth=3;
}

void playchess::createAccount()
{
    std::cout<<"Make a name for your account:";
    std::string name;
    std::cin>>name;
    std::cout<<std::endl;
    std::vector<char> illegal={'/','\\',':','*','?','"','<','>','|',' '};
    for(int i=0;i<name.size();i++)
        if(Include(name[i],illegal))
        {std::cout<<"There is an illegal character "<<name[i]<<" and please change a name";toEnter(2);std::getline(std::cin,name);createAccount();}
    std::ifstream infile;
    infile.open("./Account/Account.txt",std::ios::in);
    if(infile.is_open()==0)
    {std::cout<<"Cannot open the documnet Account.txt!";toEnter(2);return;}
    std::string oldname;
    while(std::getline(infile,oldname))
        if(oldname==name)
        {std::cout<<"The name has been occupied. Change a name!"<<std::endl;createAccount();}
    infile.close();
    std::ofstream outfile("./Account/Account.txt",std::ios::app);
    if(outfile.is_open()==0)
    {std::cout<<"Cannot open the documnet make an account for you!";toEnter(2);return;}
    outfile<<name<<std::endl;
    outfile.close();
    std::string filename="./Account/"+name+".txt";
    outfile.open(filename,std::ios::out);
    if(outfile.is_open()==0)
    {std::cout<<"Cannot open the documnet make an account for you!";toEnter(2);return;}   
    outfile<<name<<" "<<makePassword()<<" 0 0 0 0.0";
    outfile.close();
    std::cout<<"Your account is created";
    toEnter(2);
}

void playchess::determinePeopleAmount()
{
    std::cout<<"Choose the player number(more than one):";
    std::cin>>playernum;
    aliveNum=playernum;
}

int playchess::loadin()
{
    std::cout<<"Please input your account name:";
    std::string name,filename,line;
    std::cin>>name;
    std::cout<<std::endl;
    filename="./Account/"+name+".txt";
    std::ifstream infile(filename,std::ios::in);
    if(infile.is_open()==0)
    {std::cout<<"cannot find your account! Check your name!";toEnter(2);return 0;}
    std::cout<<"Please input your password:";
    std::string password;
    std::cin>>password;
    std::cout<<std::endl;
    std::getline(infile,line);
    std::string getname = line.substr(0,name.size());
    line=line.substr(name.size()+1);
    int num=0;
    std::string m[5];
    int k[4];
    for(int i=0;i<line.size();i++)
    {
        if(line[i]==' ')
            k[num]=i,num++;
    }
    m[0]=line.substr(0,k[0]);
    for(int i=0;i<3;i++)
        m[i+1]=line.substr(k[i]+1,k[1+i]-k[i]-1);
    m[4]=line.substr(k[3]+1);
    if(password!=m[0])
    {
        std::cout << "The password is wrong!";toEnter(2);loadin();
    }
    system("cls");
    std::cout<<"Hello!"<<name;toEnter(3);
    player tem(name,m[0],std::stoi(m[1]),std::stoi(m[2]),std::stoi(m[3]),std::stof(m[4]));
    allPlayer.push_back(tem);
    allPlayer[allPlayer.size()-1].showPersonalInfo();
    return 1;

}

void playchess::home()
{
    determinePeopleAmount();
    WriteA();
    running();
}

void playchess::WriteA()
{
    int i=0;
    while(i<playernum)
    {
        char a;
        std::cout<<"player "<<i<<", do you have an account?(y/n)";
        std::cin>>a;
        if(lower(a)=='n')
            createAccount();
        if(loadin()==1)
            i++;
        else 
        {std::cout<<"Try again!";toEnter(2);}

    }
}

std::string playchess::makePassword()
{
    std::string password,Toconfirm;
    std::cout<<"Please Input Your Password:";
    std::cin>>password;
    std::cout<<std::endl<<"Please Confirm Your Password:";
    std::cin>>Toconfirm;
    std::cout<<std::endl;
    if(Toconfirm!=password)
    {std::cout<<"The two of the passwords are different. Try again!"<<std::endl;makePassword();}
    return password;
}

std::vector<war> playchess::makewar()
{
    std::vector<player*> Tosort;
    for(int i=0;i<aliveNum;i++)
        Tosort.push_back(&alivePlayer[i]);
    std::vector<war> Myreturn;
    for(int i=0;i<aliveNum;i++)
        for(int j=aliveNum-i-2;j>=0;j--)
        {
            int* a=Tosort[i+j]->Getinfo().second,*b=Tosort[i+j+1]->Getinfo().second;
            if(a[3]<b[3])
                std::swap(Tosort[i+j],Tosort[i+j+1]);
            delete[] a,b;
        }
    if(aliveNum%2==0)
        for(int i=0;i<aliveNum;i=i+2)
        {
            std::vector<player*> tem={Tosort[i],Tosort[i+1]};
            war theGreatWar(tem,0);
            Myreturn.push_back(theGreatWar);
        }
    else 
    {
        int ran=random(0,aliveNum*10-1);
        std::cout<<Tosort[ran%aliveNum]->Getinfo().first[0]<<" is for a bye throungh drawing lots, and will battle a weaken image troop."<<std::endl;
        int num=aliveNum-ran%aliveNum-1;
        player mirror=*Tosort[random(0,num*10-1)%num+ran%aliveNum+1];
        std::vector<player*> tem={Tosort[ran%aliveNum],&mirror};
        war mirrorwar(tem,1);
        Myreturn.push_back(mirrorwar);
        Tosort.erase(Tosort.begin()+ran%aliveNum);
        for(int i=0;i<aliveNum-1;i=i+2)
        {
            std::vector<player*> tem={Tosort[i],Tosort[i+1]};
            war theGreatWar(tem,0);
            Myreturn.push_back(theGreatWar);
        }
    }
    return Myreturn;
}

void playchess::running()
{
    alivePlayer=allPlayer;
    circule=0;
    while(true)
    {
        ++circule;   
        for(int i=0;i<aliveNum;i++)
        {
            alivePlayer[i].showPersonalInfo();
            store MyStore(alivePlayer[i]);
            MyStore.generateSoldier();
            MyStore.menu();
        }
        std::vector<war> TheGreatWar=makewar();
        for(int i=0;i<TheGreatWar.size();i++)
        {
            TheGreatWar[i].running();
        }
        for(int i=0;i<aliveNum;i++)
            alivePlayer[i].gainExperience(20+10*circule),alivePlayer[i].IncreaseMoney(money_growth);
        winnerDetermine();
        determineMoneyGrowth();
        // std::cout<<"running over"<<std::endl;
        if(aliveNum==1)
            break;
    }
    for(int i=0;i<playernum;i++)
        allPlayer[i].Save();
    std::cout<<"Good game! See you next time.";
}

void playchess::winnerDetermine()
{
    for(int i=0;i<aliveNum;i++)
    {
        int* Info=alivePlayer[i].Getinfo().second;
        if(Info[3]==0)
        {
            --aliveNum;
            if(aliveNum<=Up_quzheng(playernum/2.0)&&aliveNum>1)
                for(int j=0;j<playernum;j++)
                    if(alivePlayer[i].Getinfo().first[0]==allPlayer[j].Getinfo().first[0])
                        allPlayer[j].changeRecord(1,0);
            else if(aliveNum==1)
                for(int j=0;j<playernum;j++)
                    if(alivePlayer[i].Getinfo().first[0]==allPlayer[j].Getinfo().first[0])
                        allPlayer[j].changeRecord(1,1);
            else 
                for(int j=0;j<playernum;j++)
                    if(alivePlayer[i].Getinfo().first[0]==allPlayer[j].Getinfo().first[0])
                        allPlayer[j].changeRecord(0,0);
            alivePlayer.erase(alivePlayer.begin()+i);
        }
        delete[] Info;
    }
}

void playchess::determineMoneyGrowth()
{
    if(circule%2==0)
        money_growth++;
}
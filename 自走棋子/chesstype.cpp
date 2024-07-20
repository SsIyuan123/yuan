#include"chesstype.h"
#include "tools.h"
#include<iostream>

void warrior::levelUp()
{
    addindex(0,0,0,2,0,0,1,15,0,0,0,1);
    addindex(15,0,0,0,1);
    int* Info=getInfo();
    if(Info[6]==3)
        addindex(0,0,0,0,0,0,0,0,0,0,0,0,14);
    delete[] Info;
}

void archer::levelUp()
{
    addindex(0,0,0,3,0,0,1,10,0,0,0,1);
    addindex(10,0,0,0,1);
    int* Info=getInfo();
    if(Info[6]==2)
        addindex(0,0,0,0,0,0,0,0,0,1);
    if(Info[6]==3)
        addindex(0,0,0,0,0,0,0,0,0,0,0,0,14);
    delete[] Info;
}

void magician::levelUp()
{
    addindex(0,0,5,2,0,5,1,5,0,0,0,1);
    addindex(5,0,0,0,1);
    int *Info=getInfo();
    if(Info[6]==2)
        addindex(0,0,0,0,0,0,0,0,0,0,0,0,14);
    delete[] Info;
}

void assassin::levelUp()
{
    addindex(0,0,5,2,0,0,1,10,0,0,0,1);
    addindex(10,0,0,0,1);
    int* Info=getInfo();
    if(Info[6]==3)
        addindex(0,0,0,0,0,0,0,0,0,0,0,0,14);
    delete[] Info;
}

int particle::changeparticle(int delta, int particleUp)
{
    energyamount=edge(energyamount+delta,0,100);
    this->particleUp+=particleUp;
    return energyamount;
}

int particle::getDelta()
{
    return particleUp;
}

void particle::switchstate()
{
    switching(&state);
}

int particle::showstate()
{
    return state;
}

void Reiki::changeReiki(int ReikiAmount,int ReikiUp)
{
    this->Reikiamount=edge(ReikiAmount+this->Reikiamount,0,100);
    this->ReikiUp+=ReikiUp;
}

int Reiki::switchstate()
{
    if(state==0)
        state=1;
    else
        state=0;
        return state;
}

std::vector<int> Reiki::ReikiInfo(){
    std::vector<int> tem={Reikiamount,state,ReikiUp};
    return tem;
}

void ParticleWarrior::done(std::vector<std::vector<int>> position)
{
    std::cout<<"The Particle-Warrior attacks!"<<std::endl;
    int *Info=getInfo();
    if(Info[7]==0) {std::cout<<"dizzied";toEnter(2);delete[]Info;return;}
    if(Info[1]!=100)
    {
        if(showstate()==0)
        {
            makerecord(position[2][0],position[0][0],position[1][0],(soldierState)7,Info[3],1),changeparticle(getDelta());
            changeMyState(7,Up_quzheng(Info[3]*position[3][0]/100.0),1);
        }
        else
        {
            changeMyState(4,3+Info[6]*2,1);
            changeMyState(2,Info[3]*((double)Info[6]/2.0+0.5),1);
            changeparticle(-1000);
            switchstate();
        }
        if(changeparticle(0)==100)
            switchstate();
        addindex(0,getInfo()[14]);
    }
    else
    {
        addindex(Info[8]/3);
        addindex(0,-100);
        changeMyState(2,2,2);
    }
    delete[]Info;
    return;
    // std::cout<<"attack ends."<<std::endl;
}

void ParticleWarrior::show()
{
    std::cout<<"ParticleWarrior:"<<std::endl;
    soldier::show();
    std::cout<<"Particle Amount:"<<changeparticle(0)<<std::endl<<std::endl;
}

void ParticleWarrior::levelUp()
{
    warrior::levelUp();
    int* Info=getInfo();
    if(Info[6]==3)
        changeparticle(0,16);
    delete[] Info;

}

void LaserArcher::done(std::vector<std::vector<int>> position)
{
    std::cout<<"The Laser-Archer attacks!"<<std::endl;
    int*Info=getInfo();
    if(Info[7]==0) {std::cout<<"dizzied";toEnter(2);delete[]Info;return;}
    if(Info[1]!=100)
    {
        if(showstate()==0)
        {
            makerecord(position[2][0],position[0][0],position[1][0],(soldierState)7,Info[3],1),changeparticle(getDelta());
            changeMyState(7,Up_quzheng(Info[3]*position[3][0]/100.0),1);
        }
        else
        {
            makerecord(position[2][0],position[0][0],position[1][0],(soldierState)1,4000+2000*Info[6],1);
            changeMyState(1,Up_quzheng((4000+2000*Info[6])*position[3][0]/100.0),1);
            float k;
            switch(Info[6])
            {
                case 1:k=0.5;break;
                case 2:k=0.65;break;
                case 3:k=0.8;break;
            }
            for(int i=0;i<position[0].size();i++)
            {
                makerecord(position[2][i],position[0][i],position[1][i],(soldierState)7,Up_quzheng(Info[3]*cifang(k,i)),1);
            }
            for(int i=0;i<position[3].size();i++)
                changeMyState(7,Up_quzheng(Info[3]*cifang(k,i)*position[3][i]/100.0),1);
            changeparticle(-1000);
            switchstate();
        }
        if(changeparticle(0)==100)
            switchstate();
        addindex(0,Info[14]);
    }
    else
    {
        makerecord(position[2][0],position[0][0],position[1][0],(soldierState)6,1,1);
        makerecord(position[2][0],position[0][0],position[1][0],(soldierState)7,Info[3]*2,1);
        changeMyState(7,Up_quzheng(Info[3]*2*position[3][0]/100.0),1);
        if(position[3][0]!=0)
        changeMyState(6,1,1);
        addindex(0,-100);
    }
    delete[] Info;   
    return;
}

void LaserArcher::show()
{
    std::cout<<"LaserArcher:"<<std::endl;
    soldier::show();
    std::cout<<"Particle Amount:"<<changeparticle(0)<<std::endl<<std::endl;
    
}

void LaserArcher::levelUp()
{
    archer::levelUp();
    int* Info=getInfo();
    if(Info[6]==3)
        changeparticle(0,16);
    delete[] Info;
}

void ParticleEngineer::done(std::vector<std::vector<int>> position)
{
    std::cout<<"The Particle Engineer attacks!"<<std::endl;
    int *Info=getInfo();
    if(Info[7]==0) {std::cout<<"dizzied";delete[]Info;toEnter(2);return;}
    if(position[0].size()==0) {std::cout<<"Where are my leagues?";delete[]Info;toEnter(2);return;}
    if(Info[1]!=100)
    {
        if(showstate()==0)
        {
            makerecord(position[2][0],position[0][0],position[1][0],(soldierState)4,600+Info[6]*200,5);
            makerecord(position[2][0],position[0][0],position[1][0],(soldierState)2,1+Info[6],1),changeparticle(getDelta());
        }
        else
        {
            makerecord(position[2][0],position[0][0],position[1][0],(soldierState)1,-Info[6],1);
            makerecord(position[2][0],position[0][0],position[1][0],(soldierState)2,3+Info[6],1);
            changeparticle(-1000);
            switchstate();
        }
        if(changeparticle(0)==100)
            switchstate();
        addindex(0,Info[14]);
    }
    else
    {
        for(int i=0;i<position[0].size();i++)
            makerecord(position[2][0],position[0][0],position[1][0],(soldierState)8,20,1);
        addindex(0,-100);
        addindex(0.20);
    }   
    delete[]Info;
    return;
}

void ParticleEngineer::levelUp()
{
    addindex(0,0,5,0,0,5,1,10,0,0,0,2);
    addindex(10,0,0,0,2);
    int *Info=getInfo();
    if(Info[6]==2)
        changeparticle(0,16);
    delete[] Info;
}

void ParticleEngineer::show()
{
    std::cout<<"ParticleEngineer:"<<std::endl;
    soldier::show();
    std::cout<<"Particle Amount:"<<changeparticle(0)<<std::endl<<std::endl;
}

void DimensionAssassin::levelUp()
{
    assassin::levelUp();
    int *Info=getInfo();
    if(Info[6]==3)
        changeparticle(0,16);
    delete[] Info;
}

void DimensionAssassin::done(std::vector<std::vector<int>> position)
{
    std::cout<<"The Dimension Assassin attacks!"<<std::endl;
    int* Info=getInfo();
    if(Info[7]==0) {std::cout<<"dizzied";toEnter(2);delete[]Info;return;}
    if(Info[1]!=100)
    {
        if(showstate()==0)
        {
            makerecord(position[2][0],position[0][0],position[1][0],(soldierState)7,Info[3],1),changeparticle(getDelta());
            changeMyState(7,Up_quzheng(Info[3]*position[3][0]/100.0),1);
        }
        else
        {
            changeMyState(11,50*Info[6],2);
            makerecord(position[2][0],position[0][0],position[1][0],(soldierState)7,Info[3],1);
            changeMyState(7,Up_quzheng(Info[3]*position[3][0]/100.0),1);
            changeparticle(-1000);
            switchstate();
        }
        if(changeparticle(0)==100)
            switchstate();
        addindex(0,Info[14]);
    }
    else
    {
        changeMyState(11,50*Info[6],2);
        for(int i=1;i<position[0].size();i++)
            makerecord(position[2][i],position[0][i],position[1][i],(soldierState)11,50*Info[6],2);
        addindex(0,-100);
    }  
    delete[] Info;
    return;
}

void DimensionAssassin::show()
{
    std::cout<<"DimensionAssassin:"<<std::endl;
    soldier::show();
    std::cout<<"Particle Amount:"<<changeparticle(0)<<std::endl<<std::endl;
}

void Swordman::done(std::vector<std::vector<int>> position)
{
    std::cout<<"The Swordman attacks!"<<std::endl;
    int* Info=getInfo();
    if(Info[7]==0) {delete[]Info;return;}
    if(Info[1]!=100)
    {
        makerecord(position[2][0],position[0][0],position[1][0],(soldierState)7,Info[3],1);
        changeMyState(7,Up_quzheng(Info[3]*position[3][0]/100.0),1);
        addindex(0,getInfo()[14]);
    }
    else
    {
        makerecord(position[2][0],position[0][0],position[1][0],(soldierState)7,Info[3]*2.5,1);
        makerecord(position[2][0],position[0][0],position[1][0],(soldierState)7,Info[3],2);
        changeMyState(7,Up_quzheng(Info[3]*2.5*position[3][0]/100.0),1);
        changeMyState(7,Up_quzheng(Info[3]*position[3][0]/100.0),2);
        addindex(0,-100);
    }
    if(ReikiInfo()[1]==0)
        changeReiki(ReikiInfo()[2]);
    else
    {
        changeMyState(3,5+Info[6]*5,1);
        changeMyState(2,1+Info[6],1);
        addindex(1+Info[6]);
        changeReiki(-34);
    }
    if(ReikiInfo()[0]==100||ReikiInfo()[0]==0)
        switchstate();
    delete[] Info;
    return;
}

void Swordman::show()
{
    std::cout<<"Swordman:"<<std::endl;
    soldier::show();
    std::cout<<"Reiki Amount:"<<ReikiInfo()[0]<<std::endl<<std::endl;
}

void Swordman::levelUp()
{
    warrior::levelUp();
    int* Info=getInfo();
    if(Info[6]==3)
        changeReiki(0,16);
    delete[] Info;
}

void Hypnotist::done(std::vector<std::vector<int>> position)
{
    std::cout<<"The Hypnotist attacks!"<<std::endl;
    int* Info=getInfo();
    if(Info[7]==0) {delete[]Info;return;}
    if(Info[1]!=100)
    {
        if(ReikiInfo()[1]==0)
        {
            makerecord(position[2][0],position[0][0],position[1][0],(soldierState)7,Info[3],1);
            changeMyState(7,Up_quzheng(Info[3]*position[3][0]/100.0),1);
        }
        else
            for(int i=0;i<position[0].size();i++)
            {
                makerecord(position[2][i],position[0][i],position[1][i],(soldierState)1,Info[6],1);
                makerecord(position[2][i],position[0][i],position[1][i],(soldierState)7,Info[3],1);
                changeMyState(7,Up_quzheng(Info[3]*position[3][i]/100.0),1);
                changeMyState(1,Up_quzheng(Info[6]*position[3][i]/100.0),1);
            }   
        addindex(0,Info[14]);
    }
    else
    {
        makerecord(position[2][0],position[0][0],position[1][0],(soldierState)9,1,3);
        makerecord(position[2][0],position[0][0],position[1][0],(soldierState)7,Info[3],1);
        changeMyState(7,Up_quzheng(Info[3]*position[3][0]/100.0),1);
        if(position[3][0]!=0)
            changeMyState(9,1,Up_quzheng(3*position[3][0]));
        addindex(0,-100);
    }
    if(ReikiInfo()[1]==0)
        changeReiki(ReikiInfo()[2]);
    else
        changeReiki(-34);
    if(ReikiInfo()[0]==100||ReikiInfo()[0]==0)
        switchstate();
    delete[] Info;
    return;
}

void Hypnotist::show()
{
    std::cout<<"Hypnotist:"<<std::endl;
    soldier::show();
    std::cout<<"Reiki Amount:"<<ReikiInfo()[0]<<std::endl<<std::endl;
}

void Hypnotist::levelUp()
{
    archer::levelUp();
    int* Info=getInfo();
    if(Info[6]==3)
        changeReiki(0,16);
    delete[] Info;
}

void Fulu_Painter::show()
{
    std::cout<<"Fulu_Painter:"<<std::endl;
    soldier::show();
    std::cout<<"Reiki Amount:"<<ReikiInfo()[0];toEnter(2);
}

void Fulu_Painter::levelUp()
{
    magician::levelUp();
    int* Info=getInfo();
    if(Info[6]==3)
        changeReiki(0,16);
    delete[] Info;
}

void Fulu_Painter::thumder_Fu(std::vector<std::vector<int>> position)
{
    std::cout<<"Thumder!"<<std::endl;
    int*Info=getInfo();
    makerecord(position[2][0],position[0][0],position[1][0],(soldierState)7,6+2*Info[6],1);
    changeMyState(7,Up_quzheng((6+2*Info[6])*position[3][0]/100.0),1);
    changeReiki(-34);
    delete[] Info;
}

void Fulu_Painter::wind_Fu(std::vector<std::vector<int>> position)
{
    std::cout<<"Wind!"<<std::endl;
    int* Info=getInfo();
    for(int i=position[0].size()-1;i>=0;i--)
        if(position[2][i]==position[2][position[0].size()-1])
            makerecord(position[2][i],position[0][i],position[1][i],(soldierState)3,5+Info[6]*5,1);
    changeReiki(-34);
    delete[] Info;
}

void Fulu_Painter::vine_Fu(std::vector<std::vector<int>> position)
{
    std::cout<<"vine!"<<std::endl;
    int* Info=getInfo();
    makerecord(position[2][0],position[0][0],position[1][0],(soldierState)12,3+2*Info[6],1);
    changeMyState(12,Up_quzheng((3+2*Info[6])*position[3][0]/100.0),1);
    changeReiki(-34);
    delete[] Info;
}

void Fulu_Painter::quake_Fu(std::vector<std::vector<int>> position)
{
    std::cout<<"quake!"<<std::endl;
    int* Info=getInfo();
    for(int i=0;i<position[0].size();i++)
        if(position[2][i]==position[2][0])
        {
            makerecord(position[2][i],position[0][i],position[1][i],(soldierState)7,3+Info[6],1);
            changeMyState(7,Up_quzheng((3+Info[6])*position[3][i]/100.0),1);
        }
    changeReiki(-34);
    delete[] Info;
}

void Fulu_Painter::fire_Fu(std::vector<std::vector<int>> position)
{
    std::cout<<"fire!"<<std::endl;
    int*Info=getInfo();
    makerecord(position[2][0],position[0][0],position[1][0],(soldierState)5,3+Info[6],2);
    changeMyState(5,Up_quzheng((3+Info[6])*position[3][0]/100.0),2);
    changeReiki(-34);
    delete[] Info;
}

void Fulu_Painter::Rage_Fu(std::vector<std::vector<int>> position)
{
    std::cout<<"Rage!"<<std::endl;
    int*Info=getInfo();
    for(int i=0;i<position[0].size();i++)
        if(position[2][i]==position[2][position[0].size()])
        {makerecord(position[2][i],position[0][i],position[1][i],(soldierState)8,40,1);break;}
    changeMyState(5,Up_quzheng((3+Info[6])*position[3][0]/100.0),2);
    changeReiki(-34);
    delete[] Info;
}

void Fulu_Painter::done(std::vector<std::vector<int>> position)
{
    std::cout<<"The Fulu Painter attacks!"<<std::endl;
    int* Info=getInfo();
    if(Info[7]==0) {delete[]Info;return;}
    if(Info[1]!=100)
    {
        if(ReikiInfo()[1]==0)
        {
            makerecord(position[2][0],position[0][0],position[1][0],(soldierState)7,Info[3],1);
            changeMyState(7,Up_quzheng(Info[3]*position[3][0]/100.0),1);
        }
        else
        {
            int ran=random(0,108);
            switch(ran%6)
            {
                case 0:thumder_Fu(position);break;
                case 1:wind_Fu(position);break;
                case 2:vine_Fu(position);break;
                case 3:quake_Fu(position);break;
                case 4:fire_Fu(position);break;
                case 5:Rage_Fu(position);break;
            }
        }
        addindex(0,Info[14]);
    }
    else
    {
        for(int i=0;i<3;i++)
        {
            int ran=random(0,108);
            switch(ran%6)
            {
                case 0:thumder_Fu(position);break;
                case 1:wind_Fu(position);break;
                case 2:vine_Fu(position);break;
                case 3:quake_Fu(position);break;
                case 4:fire_Fu(position);break;
                case 5:Rage_Fu(position);break;
            }
            addindex(0,-100);
        }
    }
    if(ReikiInfo()[1]==0)
        changeReiki(ReikiInfo()[2]);
    if(ReikiInfo()[0]==100&&ReikiInfo()[1]==0||(ReikiInfo()[0]==0&&ReikiInfo()[1]==1))
        switchstate();
    delete[] Info;
    return;   
}

void Sorcerer::show()
{
    std::cout<<"Sorcerer:"<<std::endl;
    soldier::show();
    std::cout<<"Reiki Amount:"<<ReikiInfo()[0];toEnter(2);
}

void Sorcerer::levelUp()
{
    assassin::levelUp();
    int* Info=getInfo();
    if(Info[6]==3)
        changeReiki(0,16);
    delete[] Info;
}

void Sorcerer::done(std::vector<std::vector<int>> position)
{
    std::cout<<"The Sorcerer attacks!"<<std::endl;
    int* Info=getInfo();
    if(Info[7]==0) {delete[]Info;return;}
    if(Info[1]!=100)
    {
        makerecord(position[2][0],position[0][0],position[1][0],(soldierState)7,Info[3],1);
        changeMyState(7,Up_quzheng(Info[3]*position[3][0]/100.0),1);
        addindex(0,getInfo()[14]);
    }
    else
    {
        addindex(-5);
        if(int ran=random()<50)
        {
            makerecord(position[2][0],position[0][0],position[1][0],(soldierState)5,5000,1);
            changeMyState(5,5000*position[3][0]/100.0,1);
            makerecord(position[2][0],position[0][0],position[1][0],(soldierState)10,Info[0]*position[3][0]/100.0,1);
            changeMyState(9,1,3);
        }
        addindex(0,-100);
    }
    if(ReikiInfo()[1]==0)
        changeReiki(ReikiInfo()[2]);
    else
    {
        makerecord(position[2][0],position[0][0],position[1][0],(soldierState)5,Info[6],2);
        changeMyState(5,Up_quzheng(Info[6]*position[3][0]/100.0),2);
        if(random()<20+10*Info[6])
        {
            makerecord(position[2][0],position[0][0],position[1][0],(soldierState)6,1,1);
            if(position[3][0]>0)
                changeMyState(6,1,1);
        }
        changeReiki(-34);
    }
    if(ReikiInfo()[0]==100||ReikiInfo()[0]==0)
        switchstate();
    delete[] Info;
    return;
}
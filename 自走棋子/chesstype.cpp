#include"chesstype.h"
#include "tools.h"
#include<iostream>

void warrior::levelUp()
{
    addindex(0,0,0,2,0,0,1,15,0,0,0,1);
    addindex(15,0,0,0,1);
    if(getInfo()[6]==3)
        addindex(0,0,0,0,0,0,0,0,0,0,0,0,14);
}

void archer::levelUp()
{
    addindex(0,0,0,3,0,0,1,10,0,0,0,1);
    addindex(10,0,0,0,1);
    if(getInfo()[6]==2)
        addindex(0,0,0,0,0,0,0,0,0,1);
    if(getInfo()[6]==3)
        addindex(0,0,0,0,0,0,0,0,0,0,0,0,14);
}

void magician::levelUp()
{
    addindex(0,0,5,2,0,5,1,5,0,0,0,1);
    addindex(5,0,0,0,1);
    if(getInfo()[6]==2)
        addindex(0,0,0,0,0,0,0,0,0,0,0,0,14);
}

void assassin::levelUp()
{
    addindex(0,0,5,2,0,0,1,10,0,0,0,1);
    addindex(10,0,0,0,1);
    if(getInfo()[6]==3)
        addindex(0,0,0,0,0,0,0,0,0,0,0,0,14);
}

int particle::changeparticle(int delta, int particleUp = 0)
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

int Reiki::changeReiki(int delta)
{
    Reikiamount=edge(Reikiamount+delta,0,100);
    return Reikiamount;
}

int Reiki::switchstate()
{
    if(state==0)
        state=1;
    else
        state=0;
        return state;
}

void ParticleWarrior::done(std::vector<std::vector<int>> position)
{
    std::cout<<"The Particle-Warrior attacks!"<<std::endl;
    if(getInfo()[7]==0) return;
    if(getInfo()[1]!=100)
    {
        if(showstate()==0)
        {
            makerecord(position[2][0],position[0][0],position[1][0],(soldierState)7,getInfo()[3],1),changeparticle(getDelta());
            if(position.size()==4)
                changeMyState(7,getInfo()[3],1);
        }
        else
        {
            changeMyState(4,3+getInfo()[5]*2,1);
            changeMyState(2,getInfo()[3]*((double)getInfo()[6]/2.0+0.5),1);
            changeparticle(-1000);
            switchstate();
        }
        if(changeparticle(0)==100)
            switchstate();
        addindex(0,getInfo()[14]);
    }
    else
    {
        addindex(getInfo()[8]/3);
        addindex(0,-100);
        changeMyState(2,2,2);
    }
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
    if(getInfo()[6]==3)
        changeparticle(0,16);

}

void LaserArcher::done(std::vector<std::vector<int>> position)
{
    std::cout<<"The Laser-Archer attacks!"<<std::endl;
    if(getInfo()[7]==0) {std::cout<<"dizzied"<<std::endl;return;}
    if(getInfo()[1]!=100)
    {
        if(showstate()==0)
        {
            makerecord(position[2][0],position[0][0],position[1][0],(soldierState)7,getInfo()[3],1),changeparticle(getDelta());
            if(position.size()==4)
                changeMyState(7,Up_quzheng(getInfo()[3]*position[3][0]/100.0),1);
        }
        else
        {
            makerecord(position[2][0],position[0][0],position[1][0],(soldierState)1,4000+2000*getInfo()[6],1);
            if(position.size()==4)
                changeMyState(1,Up_quzheng((4000+2000*getInfo()[6])*position[3][0]/100.0),1);
            float k;
            switch(getInfo()[6])
            {
                case 1:k=0.5;break;
                case 2:k=0.65;break;
                case 3:k=0.8;break;
            }
            for(int i=0;i<position[0].size();i++)
            {
                makerecord(position[2][i],position[0][i],position[1][i],(soldierState)7,Up_quzheng(getInfo()[3]*cifang(k,i)),1);
            }
            if(position.size()==4)
                changeMyState(7,Up_quzheng(getInfo()[3]*position[3][0]/100.0),1);
            changeparticle(-1000);
            switchstate();
        }
        if(changeparticle(0)==100)
            switchstate();
        addindex(0,getInfo()[14]);
    }
    else
    {
        makerecord(position[2][0],position[0][0],position[1][0],(soldierState)6,1,1);
        makerecord(position[2][0],position[0][0],position[1][0],(soldierState)7,getInfo()[3]*2,1);
        if(position.size()==4)
            changeMyState(7,Up_quzheng(getInfo()[3]*2*position[3][0]/100.0),1),changeMyState(6,1,1);
        addindex(0,-100);
    }   
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
    if(getInfo()[6]==3)
        changeparticle(0,16);
}

void ParticleEngineer::done(std::vector<std::vector<int>> position)
{
    std::cout<<"The Particle Engineer attacks!"<<std::endl;
    if(position[0].size()==0) {std::cout<<"Where are my leagues?"<<std::endl;return;}
    if(getInfo()[7]==0) {std::cout<<"dizzied"<<std::endl;return;}
    if(getInfo()[1]!=100)
    {
        if(showstate()==0)
        {
            makerecord(position[2][0],position[0][0],position[1][0],(soldierState)4,600+getInfo()[6]*200,5);
            makerecord(position[2][0],position[0][0],position[1][0],(soldierState)2,1+getInfo()[6],1),changeparticle(getDelta());
        }
        else
        {
            makerecord(position[2][0],position[0][0],position[1][0],(soldierState)1,-getInfo()[6],1);
            makerecord(position[2][0],position[0][0],position[1][0],(soldierState)2,3+getInfo()[6],1);
            changeparticle(-1000);
            switchstate();
        }
        if(changeparticle(0)==100)
            switchstate();
        addindex(0,getInfo()[14]);
    }
    else
    {
        for(int i=0;i<position[0].size();i++)
            makerecord(position[2][0],position[0][0],position[1][0],(soldierState)8,20,1);
        addindex(0,-100);
        addindex(0.20);
    }   
}

// void ParticleEngineer::levelUp(){}

void ParticleEngineer::show()
{
    std::cout<<"ParticleEngineer:"<<std::endl;
    soldier::show();
    std::cout<<"Particle Amount:"<<changeparticle(0)<<std::endl<<std::endl;
}

// void DimensionAssassin::levelUp(){}

void DimensionAssassin::done(std::vector<std::vector<int>> position)
{
    std::cout<<"The Dimension Assassin attacks!"<<std::endl;
    if(getInfo()[7]==0) {std::cout<<"dizzied"<<std::endl;return;}
    if(getInfo()[1]!=100)
    {
        if(showstate()==0)
        {
            makerecord(position[2][0],position[0][0],position[1][0],(soldierState)7,getInfo()[3],1),changeparticle(getDelta());
            if(position.size()==4)
                changeMyState(7,Up_quzheng(getInfo()[3]*position[3][0]/100.0),1);
        }
        else
        {
            changeMyState(11,50*getInfo()[6],1);
            makerecord(position[2][0],position[0][0],position[1][0],(soldierState)7,getInfo()[3],1);
            if(position.size()==4)
                changeMyState(7,Up_quzheng(getInfo()[3]*position[3][0]/100.0),1);
            changeparticle(-1000);
            switchstate();
        }
        if(changeparticle(0)==100)
            switchstate();
        addindex(0,getInfo()[14]);
    }
    else
    {
        changeMyState(11,50*getInfo()[6],1);
        for(int i=1;i<position[0].size();i++)
            makerecord(position[2][i],position[0][i],position[1][i],(soldierState)11,50*getInfo()[6],1);
        addindex(0,-100);
    }  
}

void DimensionAssassin::show()
{
    std::cout<<"DimensionAssassin:"<<std::endl;
    soldier::show();
    std::cout<<"Particle Amount:"<<changeparticle(0)<<std::endl<<std::endl;
}
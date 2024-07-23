#include"chesstype.h"
#include "tools.h"
#include<iomanip>
#include<iostream>

void ParticleWarrior::done(std::vector<std::vector<int>> position)
{
    std::cout<<"The Particle-Warrior attacks!"<<std::endl;
    int* Info=getInfo();
    if(Info[7]==0) {std::cout<<"dizzied";toEnter(2);delete[]Info;return;}
    warrior::buff();
    particle::buff();
    if(Info[1]!=100)
    {
        if(showstate()==0)
        {
            if(random()<position[4][0]){std::cout<<"miss!";toEnter(2);}
            else
            {
            makerecord(position[2][0],position[0][0],position[1][0],(soldierState)7,Info[3],1);
            }
            changeMyState(7,Up_quzheng(Info[3]*position[3][0]/100.0),1);
            changeparticle(getDelta());
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

void ParticleWarrior::relive()
{
    int* Info=getInfo();
    warrior::relive();
    changeparticle(-100,-100);
    if(Info[6]==3)
        changeparticle(0,50);
    else
        changeparticle(0,34);
    delete[] Info;
}

void LaserArcher::done(std::vector<std::vector<int>> position)
{
    std::cout<<"The Laser-Archer attacks!"<<std::endl;
    int* Info=getInfo();
    if(Info[7]==0) {std::cout<<"dizzied";toEnter(2);delete[]Info;return;}
    archer::buff();
    particle::buff();
    if(Info[1]!=100)
    {
        if(showstate()==0)
        {
            if(random()<position[4][0]){std::cout<<"miss!";toEnter(2);}
            else
            {
                makerecord(position[2][0],position[0][0],position[1][0],(soldierState)7,Info[3],1);
            }
            changeMyState(7,Up_quzheng(Info[3]*position[3][0]/100.0),1);
            changeparticle(getDelta());
        }
        else
        {
            if(random()<position[4][0]){std::cout<<"miss!";toEnter(2);}
            else
            {
                makerecord(position[2][0],position[0][0],position[1][0],(soldierState)1,4000+2000*Info[6],1);
            }
            changeMyState(1,Up_quzheng((4000+2000*Info[6])*position[3][0]/100.0),1);
            float k;
            switch((int)Info[6])
            {
                case 1:k=0.5;break;
                case 2:k=0.65;break;
                case 3:k=0.8;break;
            }
            for(int i=0;i<position[0].size();i++)
            {
                if(random()<position[4][i]){std::cout<<"miss!";toEnter(2);}
                else
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
        if(random()<position[4][0]){std::cout<<"miss!";toEnter(2);}
        else
        {
            makerecord(position[2][0],position[0][0],position[1][0],(soldierState)6,1,1);
            makerecord(position[2][0],position[0][0],position[1][0],(soldierState)7,Info[3]*2,1);
        }
        changeMyState(7,Up_quzheng(Info[3]*2*position[3][0]/100.0),1);
        changeMyState(6,1,Up_quzheng(position[3][0/100.0]));
        addindex(0,-100);
    }
    delete[] Info;   
    return;
}

void LaserArcher::relive()
{
    int* Info=getInfo();
    archer::relive();
    changeparticle(-100,-100);
    if(Info[6]==3)
        changeparticle(0,50);
    else
        changeparticle(0,34);
    delete[] Info;
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
    magician::buff();
    particle::buff();
    int* Info=getInfo();
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
    int* Info=getInfo();
    if(Info[6]==2)
        changeparticle(0,16);
    delete[] Info;
}

void ParticleEngineer::relive()
{
    int* Info=getInfo();
    addindex(0,0,-100);
    addindex(0,0,5*Info[6],0,0,5*(Info[6]-1));
    changeparticle(-100,-100);
    if(Info[6]==1)
        changeparticle(0,34);
    else
        changeparticle(0,50);
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
    int* Info=getInfo();
    if(Info[6]==3)
        changeparticle(0,16);
    delete[] Info;
}

void DimensionAssassin::relive()
{
    int* Info=getInfo();
    assassin::relive();
    changeparticle(-100,-100);
    if(Info[6]==3)
        changeparticle(0,50);
    else
        changeparticle(0,34);
    delete[] Info;
}

void DimensionAssassin::done(std::vector<std::vector<int>> position)
{
    std::cout<<"The Dimension Assassin attacks!"<<std::endl;
    int* Info=getInfo();
    if(Info[7]==0) {std::cout<<"dizzied";toEnter(2);delete[]Info;return;}
    assassin::buff();
    particle::buff();
    if(Info[1]!=100)
    {
        if(showstate()==0)
        {   
            if(random()<position[4][0]){std::cout<<"miss!";toEnter(2);}
            else
            {
            makerecord(position[2][0],position[0][0],position[1][0],(soldierState)7,Info[3],1);
            }
            changeparticle(getDelta());
            changeMyState(7,Up_quzheng(Info[3]*position[3][0]/100.0),1);
        }
        else
        {
            changeMyState(11,50*Info[6],2);
            if(random()<position[4][0]){std::cout<<"miss!";toEnter(2);}
            else
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
    if(Info[7]==0) {std::cout<<"晕";toEnter(2);delete[]Info;return;}
    warrior::buff();
    Reiki::buff();
    if(Info[1]!=100)
    {
        if(random()<position[4][0]){std::cout<<"miss!";toEnter(2);}
        else
        makerecord(position[2][0],position[0][0],position[1][0],(soldierState)7,Info[3],1);
        changeMyState(7,Up_quzheng(Info[3]*position[3][0]/100.0),1);
        addindex(0,getInfo()[14]);
    }
    else
    {
        if(random()<position[4][0]){std::cout<<"miss!";toEnter(2);}
        else
        {
            makerecord(position[2][0],position[0][0],position[1][0],(soldierState)7,Info[3]*2.5,1);
            makerecord(position[2][0],position[0][0],position[1][0],(soldierState)7,Info[3],2);
        }
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

void Swordman::relive()
{
    int* Info=getInfo();
    warrior::relive();
    changeReiki(-100,-100);
    if(Info[6]==3)
        changeReiki(0,50);
    else
        changeReiki(0,34);
    delete[] Info;
}


void Hypnotist::done(std::vector<std::vector<int>> position)
{
    std::cout<<"The Hypnotist attacks!"<<std::endl;
    int* Info=getInfo();
    if(Info[7]==0) {delete[]Info;return;}
    archer::buff();
    Reiki::buff();
    if(Info[1]!=100)
    {
        if(ReikiInfo()[1]==0)
        {
            if(random()<position[4][0]){std::cout<<"miss!";toEnter(2);}
            else
            makerecord(position[2][0],position[0][0],position[1][0],(soldierState)7,Info[3],1);
            changeMyState(7,Up_quzheng(Info[3]*position[3][0]/100.0),1);
        }
        else
            for(int i=0;i<position[0].size();i++)
            {
                if(random()<position[4][i]){std::cout<<"miss!";toEnter(2);}
                else
                {
                    makerecord(position[2][i],position[0][i],position[1][i],(soldierState)1,Info[6],1);
                    makerecord(position[2][i],position[0][i],position[1][i],(soldierState)7,Info[3],1);
                }
                changeMyState(7,Up_quzheng(Info[3]*position[3][i]/100.0),1);
                changeMyState(1,Up_quzheng(Info[6]*position[3][i]/100.0),1);
            }   
        addindex(0,Info[14]);
    }
    else
    {
        if(random()<position[4][0]){std::cout<<"miss!";toEnter(2);}
        else
        {
            makerecord(position[2][0],position[0][0],position[1][0],(soldierState)9,1,3);
            makerecord(position[2][0],position[0][0],position[1][0],(soldierState)7,Info[3],1);
        }
        changeMyState(7,Up_quzheng(Info[3]*position[3][0]/100.0),1);
        changeMyState(9,1,Up_quzheng(3*position[3][0]/100.0));
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

void Hypnotist::relive()
{
    int* Info=getInfo();
    archer::relive();
    changeReiki(-100,-100);
    if(Info[6]==3)
        changeReiki(0,50);
    else
        changeReiki(0,34);
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

void Fulu_Painter::relive()
{
    int* Info=getInfo();
    magician::relive();
    changeReiki(-100,-100);
    if(Info[6]==3)
        changeReiki(0,50);
    else
        changeReiki(0,34);
    delete[] Info;
}

void Fulu_Painter::thumder_Fu(std::vector<std::vector<int>> position)
{
    std::cout<<"Thumder!"<<std::endl;
    int* Info=getInfo();
    if(random()<position[4][0]){std::cout<<"miss!";toEnter(2);}
    else
    makerecord(position[2][0],position[0][0],position[1][0],(soldierState)13,6+2*Info[6],1);
    changeMyState(13,Up_quzheng((6+2*Info[6])*position[3][0]/100.0),1);
    changeReiki(-34);
    delete[] Info;
}

void Fulu_Painter::wind_Fu(std::vector<std::vector<int>> position)
{
    std::cout<<"Wind!"<<std::endl;
    int* Info=getInfo();
    changeMyState(3,5+Info[6]*5,1);
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
            if(random()<position[4][i]){std::cout<<"miss!";toEnter(2);}
            else
            makerecord(position[2][i],position[0][i],position[1][i],(soldierState)7,3+Info[6],1);
            changeMyState(7,Up_quzheng((3+Info[6])*position[3][i]/100.0),1);
        }
    changeReiki(-34);
    delete[] Info;
}

void Fulu_Painter::fire_Fu(std::vector<std::vector<int>> position)
{
    std::cout<<"fire!"<<std::endl;
    int* Info=getInfo();
    if(random()<position[4][0]){std::cout<<"miss!";toEnter(2);}
    else
    makerecord(position[2][0],position[0][0],position[1][0],(soldierState)5,3+Info[6],2);
    changeMyState(5,Up_quzheng((3+Info[6])*position[3][0]/100.0),2);
    changeReiki(-34);
    delete[] Info;
}

void Fulu_Painter::Rage_Fu(std::vector<std::vector<int>> position)
{
    std::cout<<"Rage!"<<std::endl;
    int* Info=getInfo();
    for(int i=0;i<position[0].size();i++)
        if(position[2][i]==position[2][position[0].size()])
        {makerecord(position[2][i],position[0][i],position[1][i],(soldierState)8,40,1);break;}
    changeReiki(-34);
    delete[] Info;
}

void Fulu_Painter::done(std::vector<std::vector<int>> position)
{
    std::cout<<"The Fulu Painter attacks!"<<std::endl;
    int* Info=getInfo();
    if(Info[7]==0) {delete[]Info;return;}
    magician::buff();
    Reiki::buff();
    if(Info[1]!=100)
    {
        if(ReikiInfo()[1]==0)
        {
            if(random()<position[4][0]){std::cout<<"miss!";toEnter(2);}
            else
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

void Sorcerer::relive()
{
    int* Info=getInfo();
    assassin::relive();
    changeReiki(-100,-100);
    if(Info[6]==3)
        changeReiki(0,50);
    else
        changeReiki(0,34);
    delete[] Info;
}

void Sorcerer::done(std::vector<std::vector<int>> position)
{
    std::cout<<"The Sorcerer attacks!"<<std::endl;
    int* Info=getInfo();
    if(Info[7]==0) {delete[]Info;return;}
    assassin::buff();
    Reiki::buff();
    if(Info[1]!=100)
    {

        if(ReikiInfo()[1]==1)
        {
            int ran=random();
            if(random()<position[4][0]){std::cout<<"miss!";toEnter(2);}
            else
            {
                makerecord(position[2][0],position[0][0],position[1][0],(soldierState)7,Info[3],1);
                makerecord(position[2][0],position[0][0],position[1][0],(soldierState)13,Info[6],2);
                if(ran<20+10*Info[6])
                    makerecord(position[2][0],position[0][0],position[1][0],(soldierState)6,1,1);
            }
            changeMyState(5,Up_quzheng(Info[6]*position[3][0]/100.0),2);
            changeMyState(7,Up_quzheng(Info[3]*position[3][0]/100.0),1);
            if(ran<20+10*Info[6])
                changeMyState(6,1,Up_quzheng(position[3][0]/100.0));
        }
        addindex(0,getInfo()[14]);
    }
    else
    {
        addindex(-3);
        if(int ran=random()<50)
        {
            makerecord(position[2][0],position[0][0],position[1][0],(soldierState)13,5000,1);
            changeMyState(5,5000*position[3][0]/100.0,1);
            makerecord(position[2][0],position[0][0],position[1][0],(soldierState)10,Info[0]*position[3][0]/100.0,1);
            if(Info[0]*position[3][0]/100.0>=10)
                makerecord(position[2][0],position[0][0],position[1][0],(soldierState)9,1,3);
        }
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

void fire_Warrior::buff()
{
    changeMyState(2,getbaseBuff(),1);
}

void fire_Warrior::show()
{
    std::cout<<"Fire Warrior:"<<std::endl;
    soldier::show();
    std::cout<<"fireharm: "<<fireharm;toEnter(2);
    std::cout<<"FireTotal: "<<fireAmount;toEnter(2);
}

void fire_Warrior::levelUp()
{
    warrior::levelUp();
    rate--;
}

void fire_Warrior::relive()
{
    int* Info=getInfo();
    warrior::relive();
    switch(Info[6])
    {
        case 1:rate=3;break;
        case 2:rate=2;break;
        case 3:rate=1;break;
    }
    fireharm=1,fireAmount=0,firestrengthTime=0;
    delete[] Info;
}

void fire_Warrior::done(std::vector<std::vector<int>> position)
{
    std::cout<<"The fire Warrior attacks!"<<std::endl;
    int* Info=getInfo();
    if(Info[7]==0) {delete[]Info;return;}
    buff();
    warrior::buff();
    if(Info[1]!=100)
    {            
        if(random()<position[4][0]){std::cout<<"miss!";toEnter(2);}
        else
        {
            makerecord(position[2][0],position[0][0],position[1][0],(soldierState)7,Info[3],1);
            makerecord(position[2][0],position[0][0],position[1][0],(soldierState)5,fireharm,2);
        }
        changeMyState(7,Up_quzheng(Info[3]*position[3][0]/100.0),1);
        changeMyState(5,Up_quzheng(fireharm*position[3][0]/100.0),2);
        addindex(0,getInfo()[14]);
    }
    else
    {
        firestrengthTime=1;
        fireharm++;
        for(int i=0;i<position[0].size();i++)
        {
            makerecord(position[2][i],position[0][i],position[1][i],(soldierState)5,edgeleft(fireharm+1-position[5][i],1),2);
            changeMyState(5,Up_quzheng(edgeleft(fireharm+1-position[5][i],1)*position[3][i]/100.0),2);
        }
        addindex(0,-100);
    }
    for(int i=0;i<position[0].size();i++)
        if(position[5][i]==1)
        {
            makerecord(position[2][i],position[0][i],position[1][i],(soldierState)5,fireharm,2);
            changeMyState(5,Up_quzheng(fireharm*position[3][i]/100.0),2);
        }
    if(firestrengthTime!=0)
        firestrengthTime++;
    if(firestrengthTime==2)
        firestrengthTime=0,fireharm--;
    addindex((position[6][0]-fireAmount)/rate);
    std::cout<<position[6][0]<<"-"<<fireAmount;toEnter(1);
    fireAmount+=3*((position[6][0]-fireAmount)/rate);
    delete[] Info;
    return;
}

void electri_Archer::done(std::vector<std::vector<int>> position)
{
    std::cout<<"The Electricity archer attacks!"<<std::endl;
    int* Info=getInfo();
    if(Info[7]==0) {delete[]Info;return;}
    buff();
    archer::buff();
    if(Info[1]!=100)
    {
        for(int times=0;times<Info[6]+1;times++)
        {        
            if(random()<position[4][0]){std::cout<<"miss!";toEnter(2);}
            else
            {
                makerecord(position[2][0],position[0][0],position[1][0],(soldierState)7,Info[3]/2.0,1);
                makerecord(position[2][0],position[0][0],position[1][0],(soldierState)13,1,1);
            }
            changeMyState(7,Up_quzheng(Info[3]/2.0*position[3][0]/100.0),1);
            changeMyState(13,Up_quzheng(position[3][0]/100.0),1);
            if(random()<40+20*Info[6])
                chain_electricity(position);
        }
        addindex(0,getInfo()[14]);
    }
    else
    {
        if(random()<position[4][0]){std::cout<<"miss!";toEnter(2);}
        else
        {
            makerecord(position[2][0],position[0][0],position[1][0],(soldierState)7,Info[3]*2,1);
        }
        changeMyState(7,Up_quzheng(Info[3]*2*position[3][0]/100.0),1);
        int ran=random(),times;
        if(ran<33) times=3;
        else if(ran<66) times=4;
        else times=5;
        for (int i=0;i<times;i++)
            chain_electricity(position);
        addindex(0,-100);
    }
    delete[] Info;
    return;
}


void electri_Archer::chain_electricity(std::vector<std::vector<int>> position)
{
    if(position[0].size()>1)
        for(int i=1;i<position[0].size()&&i<3;i++)
        {
            makerecord(position[2][i],position[0][i],position[1][i],(soldierState)13,1,1);
            changeMyState(13,Up_quzheng(position[3][i]/100.0),1);
        }
}

void electri_Archer::buff()
{
    changeMyState(2,getbaseBuff(),1);
}

void electri_Archer::show()
{
    std::cout<<"Electricity Archer:"<<std::endl;
    soldier::show();
}

void electri_Archer::levelUp()
{
    archer::levelUp();
}

void electri_Archer::relive()
{
    archer::relive();
}

void ice_Magician::done(std::vector<std::vector<int>> position)
{
    std::cout<<"The Ice Magician attacks!"<<std::endl;
    int* Info=getInfo();
    if(Info[7]==0) {delete[]Info;return;}
    buff();
    magician::buff();
    if(Info[1]!=100)
    {
        if(random()<position[4][0]){std::cout<<"miss!";toEnter(2);}
        else
        {
            makerecord(position[2][0],position[0][0],position[1][0],(soldierState)7,Info[3],1);
            makerecord(position[2][0],position[0][0],position[1][0],(soldierState)14,1,1);
        }
        changeMyState(7,Up_quzheng(Info[3]*position[3][0]/100.0),1);
        changeMyState(15,3+Info[6],1);
        changeMyState(14,Up_quzheng(position[3][0]/100.0),1);
        addindex(0,getInfo()[14]);
    }
    else
    {
        for(int i=1;i<position[0].size();i++)
        {
            makerecord(position[2][i],position[0][i],position[1][i],(soldierState)15,3+Info[6],3);
        }
        changeMyState(15,3+Info[6],3);
        addindex(0,-100);
    }
    delete[] Info;
    return;
}

void ice_Magician::buff()
{
    changeMyState(2,getbaseBuff(),1);
}

void ice_Magician::show()
{
    std::cout<<"Ice Magician:"<<std::endl;
    soldier::show();
}

void ice_Magician::levelUp()
{
    magician::levelUp();
}

void ice_Magician::relive()
{
    magician::relive();
}

std::vector<int> vortexSailer::allWorld;

vortexSailer::vortexSailer():assassin(12),element()
{
    int flag=1;
    worldnum=abs(worldnum);
    while(flag==1)
    {
        flag=0;
        for(int i=0;i<allWorld.size();i++)
            if(worldnum==allWorld[i])
                flag=1;
        if(flag==1)
            worldnum=random(0,10000);
    }
    allWorld.push_back(worldnum);
}

void vortexSailer::done(std::vector<std::vector<int>> position)
{
    std::cout<<"The Vortex Sailer attacks!"<<std::endl;
    int* Info=getInfo();
    if(Info[7]==0) {delete[]Info;return;}
    buff();
    vortexSailer::buff();
    if(Info[1]!=100)
    {
        int randizzied=random(), ranchaos=random();
        if(random()<position[4][0]){std::cout<<"miss!";toEnter(2);}
        else
        {
            makerecord(position[2][0],position[0][0],position[1][0],(soldierState)7,Info[3],1);
            if(ranchaos<5+5*Info[6])
            {
                makerecord(position[2][0],position[0][0],position[1][0],(soldierState)9,1,1);
                changeMyState(9,1,Up_quzheng(position[3][0]/100.0));
            }
            else if(randizzied<5+10*Info[6])
            {
                makerecord(position[2][0],position[0][0],position[1][0],(soldierState)6,1,1);
                changeMyState(6,1,Up_quzheng(position[3][0]/100.0));
            }
        }
        changeMyState(7,Up_quzheng(Info[3]*position[3][0]/100.0),1);
        if(ranchaos<5+5*Info[6])
            changeMyState(9,1,Up_quzheng(position[3][0]/100.0));
        else if(randizzied<5+10*Info[6])
            changeMyState(6,1,Up_quzheng(position[3][0]/100.0));
        addindex(0,getInfo()[14]);
    }
    else
    {
        changeMyState(16,worldnum,3);
        makerecord(position[2][0],position[0][0],position[1][0],(soldierState)16,worldnum,3);
        addindex(0,-100);
    }
    if(Info[19]==worldnum)
        changeMyState(4,1+Info[6],1);
    delete[] Info;
    return;
}

void vortexSailer::buff()
{
    changeMyState(2,getbaseBuff(),1);
}

void vortexSailer::show()
{
    std::cout<<"Vortex Sailer:"<<std::endl;
    soldier::show();
}

void vortexSailer::levelUp()
{
    assassin::levelUp();
}

void vortexSailer::relive()
{
    assassin::relive();
}

void wereWolf::done(std::vector<std::vector<int>> position)
{
    std::cout<<"The Werewolf attacks!"<<std::endl;
    int* Info=getInfo();
    if(Info[7]==0) {delete[]Info;return;}
    wild::buff();
    warrior::buff();
    if(Info[1]!=100)
    {
        if(random()<position[4][0]){std::cout<<"miss!";toEnter(2);}
        else
        {
            makerecord(position[2][0],position[0][0],position[1][0],(soldierState)7,Info[3],1);
            if(bloodstate==1)
                makerecord(position[2][0],position[0][0],position[1][0],(soldierState)17,Info[3]*0.3,1);
        }
        changeMyState(7,Up_quzheng(Info[3]*position[3][0]/100.0),1);
        addindex(Up_quzheng(Info[3]*bloody*cifang(0.75,position[5][0])/100.0));
        addindex(0,getInfo()[14]);
        if(bloodstate==1)
            changeMyState(17,Up_quzheng(Info[3]*0.3*position[3][0]/100.0),1);
    }
    else
    {
        changeMyState(2,2,2);
        bloodstate=1;
        addindex(0,-100);
    }
    if(bloodstate==1)
        bloody=25*Info[6],bloodstatetime++;
    else
        bloody=0;
    if(bloodstatetime==2)
        bloodstate=0,bloodstatetime=0;
    Makewildness(Info[0],Info[8]);
    int rate=getWildness();
    changeMyState(2,rate,1);
    changeMyState(1,-rate,1);
    delete[] Info;
    return;
}

void wereWolf::show()
{
    std::cout<<"Werewolf:"<<std::endl;
    soldier::show();
    wild::show();
    std::cout<<"Blood_sucking rate: "<<bloody;toEnter(2);
}

void wereWolf::levelUp()
{
    warrior::levelUp();
    int* Info=getInfo();
    wild::levelUp(Info[6]);
    delete[] Info;
}

void wereWolf::relive()
{
    warrior::relive();
    int* Info=getInfo();
    wild::levelUp(Info[6]);
    delete[] Info;
    bloody=0,bloodstate=0,bloodstatetime=0;
}

void Dragon::done(std::vector<std::vector<int>> position)//闪避到这儿
{
    std::cout<<"The Dragon attacks!"<<std::endl;
    int* Info=getInfo();
    Makewildness(Info[0],Info[8]);
    int rate=getWildness();
    if(Info[7]==0) {delete[]Info;return;}
    wild::buff();
    archer::buff();
    if(Info[1]!=100)
    {
        
        int fireran=random(),dizran=random();
        if(random()<position[4][0]){std::cout<<"miss!";toEnter(2);}
        else
        {
            makerecord(position[2][0],position[0][0],position[1][0],(soldierState)7,Info[3],1);
            if(dizran<15+15*rate)
                makerecord(position[2][0],position[0][0],position[1][0],(soldierState)6,1,1);
            if(fireran<25+25*rate)
                makerecord(position[2][0],position[0][0],position[1][0],(soldierState)5,Info[6],2);
        }
        changeMyState(7,Up_quzheng(Info[3]*position[3][0]/100.0),1);
        if(dizran<15+15*rate)
            changeMyState(6,1,Up_quzheng(position[3][0]/100.0));
        if(fireran<25+25*rate)
            changeMyState(5,Up_quzheng(Info[6]*position[3][0]/100.0),2); 
        addindex(0,getInfo()[14]);
    }
    else
    {
        for(int i=0;i<position[0].size();i++)
        {
            if(random()<position[4][i]){std::cout<<"miss!";toEnter(2);}
            else
            {
                makerecord(position[2][i],position[0][i],position[1][i],(soldierState)7,Info[3]*1.5,1);
                makerecord(position[2][i],position[0][i],position[1][i],(soldierState)5,3+Info[6],2);
            }
            changeMyState(7,Up_quzheng(Info[3]*1.5*position[3][0]/100.0),1);
            changeMyState(5,Up_quzheng((3+Info[6])*position[3][0]/100.0),2);
        }
        addindex(0,-100);
    }
    delete[] Info;
    return;
}

void Dragon::show()
{
    std::cout<<"Dragon:"<<std::endl;
    soldier::show();
    wild::show();
}

void Dragon::levelUp()
{
    archer::levelUp();
    int* Info=getInfo();
    wild::levelUp(Info[6]);
    delete[] Info;
}

void Dragon::relive()
{
    archer::relive();
    int* Info=getInfo();
    wild::levelUp(Info[6]);
    delete[] Info;
}

void wild_Priest::done(std::vector<std::vector<int>> position)
{
    std::cout<<"The Wild Priest attacks!"<<std::endl;
    int* Info=getInfo();
    Makewildness(Info[0],Info[8]);
    int rate=getWildness();
    if(Info[7]==0) {delete[]Info;return;}
    wild::buff();
    magician::buff();
    if(Info[1]!=100)
    {
        int chaosran=random();
        if(random()<position[4][0]){std::cout<<"miss!";toEnter(2);}
        else
        {
            makerecord(position[2][0],position[0][0],position[1][0],(soldierState)7,Info[3],1);
            if(chaosran<10+10*rate)
                makerecord(position[2][0],position[0][0],position[1][0],(soldierState)9,1,1);
        }
        changeMyState(7,Up_quzheng(Info[3]*position[3][0]/100.0),1);  
        if(chaosran<10+10*rate)
            changeMyState(9,1,Up_quzheng(position[3][0]/100.0));  
        if(random()<20*rate+20)
        {
            int flag=0;
            for(int i=0;i<position[0].size();i++)
                if(position[2][i]!=position[2][0])
                {
                    makerecord(position[2][i],position[0][i],position[1][i],(soldierState)3,20,1);
                    flag++;
                    break;
                }
            if(flag==0)
                changeMyState(3,20,1);
        }
        addindex(0,getInfo()[14]);
    }
    else
    {
        for(int i=0;i<position[0].size();i++)
        {
            if(position[2][i]==position[2][0])
            {
                makerecord(position[2][i],position[0][i],position[1][i],(soldierState)1,10000,1);
                changeMyState(1,10000*position[3][0]/100.0,1);
            }
            else
                makerecord(position[2][i],position[0][i],position[1][i],(soldierState)2,2,1);
        }
        changeMyState(2,2,1);
        addindex(0,-100);
    }
    delete[] Info;
    return;
}

void wild_Priest::show()
{
    std::cout<<"Wild Priest:"<<std::endl;
    soldier::show();
    wild::show();
}

void wild_Priest::levelUp()
{
    magician::levelUp();
    int* Info=getInfo();
    wild::levelUp(Info[6]);
    delete[] Info;
}

void wild_Priest::relive()
{
    magician::relive();
    int* Info=getInfo();
    wild::levelUp(Info[6]);
    delete[] Info;
}

void Dryads::done(std::vector<std::vector<int>> position)
{
    std::cout<<"The Dryads attacks!"<<std::endl;
    int* Info=getInfo();
    Makewildness(Info[0],Info[8]);
    int rate=getWildness();
    blood=position[5][0]-usedblood;
    if(Info[7]==0) {delete[]Info;return;}
    wild::buff();
    assassin::buff();
    if(Info[1]!=100)
    {
        if(random()<position[4][0]){std::cout<<"miss!";toEnter(2);}
        else
        {
            makerecord(position[2][0],position[0][0],position[1][0],(soldierState)7,Info[3],1);
            makerecord(position[2][0],position[0][0],position[1][0],(soldierState)17,rate+2,1);
        }
        changeMyState(7,Up_quzheng(Info[3]*position[3][0]/100.0),1);  
        changeMyState(17,Up_quzheng((rate+2)*position[3][0]/100.0),1);  
        addindex(0,getInfo()[14]);
    }
    else
    {
        for(int i=0;i<2&&i<position[0].size();i++)
        {
            int vine=blood/2;
            if(random()<position[4][0]){std::cout<<"miss!";toEnter(2);}
            else
                makerecord(position[2][i],position[0][i],position[1][i],(soldierState)12,vine,1);
            changeMyState(12,Up_quzheng(vine*position[3][0]/100.0),1);  
            usedblood+=vine;
        }
        addindex(0,-100);
    }
    delete[] Info;
    return;
}

void Dryads::show()
{
    std::cout<<"Dryads:"<<std::endl;
    soldier::show();
    wild::show();
    std::cout<<"blood: "<<blood<<std::setw(20)<<"used blood: "<<usedblood;toEnter(2);
}

void Dryads::levelUp()
{
    assassin::levelUp();
    int* Info=getInfo();
    wild::levelUp(Info[6]);
    delete[] Info;
}

void Dryads::relive()
{
    assassin::relive();
    int* Info=getInfo();
    wild::levelUp(Info[6]);
    delete[] Info;
    usedblood=0,blood=0;
}

void ParticleWarrior::makebaseBuff(int index)
{
    makebase(index);
}

void LaserArcher::makebaseBuff(int index)
{
    makebase(index);
}

void ParticleEngineer::makebaseBuff(int index)
{
    makebase(index);
}

void DimensionAssassin::makebaseBuff(int index)
{
    makebase(index);
}

void Swordman::makebaseBuff(int index)
{
    makebase(index);
}

void Hypnotist::makebaseBuff(int index)
{
    makebase(index);
}

void Fulu_Painter::makebaseBuff(int index)
{
    makebase(index);
}

void Sorcerer::makebaseBuff(int index)
{
    makebase(index);
}

void fire_Warrior::makebaseBuff(int index)
{
    makebase(index);
}

void electri_Archer::makebaseBuff(int index)
{
    makebase(index);
}

void ice_Magician::makebaseBuff(int index)
{
    makebase(index);
}

void vortexSailer::makebaseBuff(int index)
{
    makebase(index);
}

void wereWolf::makebaseBuff(int index)
{
    makebase(index);
}

void Dragon::makebaseBuff(int index)
{
    makebase(index);
}

void wild_Priest::makebaseBuff(int index)
{
    makebase(index);
}

void Dryads::makebaseBuff(int index)
{
    makebase(index);
}
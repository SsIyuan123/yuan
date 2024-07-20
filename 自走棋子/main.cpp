#include "player.h"
#include "chesstype.h"
#include "playchess.h"
#include "war.h"
#include"store.h"
#include <iostream>
#include <string>
#include <random>

int main() {
    // playchess mainchess;
    // mainchess.home();

    player a(1,"Sy");
    player b(2,"yy");
    Hypnotist Kevin,AA;
    ParticleWarrior Rihanna,AiMee;
    Swordman yy,aa;
    ParticleEngineer amy;
    a.MyTroop()->testOnFront(&yy,1,1);
    a.MyTroop()->testOnFront(&amy,1,3);
    b.MyTroop()->testOnFront(&AiMee,0,1);
    b.MyTroop()->testOnFront(&AA,0,0);
    std::vector<player*> GreatWar={&a,&b};
    war testwar(GreatWar,0);
    testwar.running();

    // mainchess.createAccount();
    
    // mainchess.determinePeopleAmount();
    // mainchess.WriteA();
    // LaserArcher Taylor,Betty;
    // mainchess.allPlayer[0].MyTroop()->gota(&Taylor);
    // mainchess.allPlayer[0].MyTroop()->gota(&Kevin);
    // mainchess.allPlayer[0].MyTroop()->turnOnFrontline();
    // mainchess.allPlayer[0].MyTroop()->turnOnFrontline();
    // mainchess.allPlayer[0].MyTroop()->showFrontline();
    // mainchess.allPlayer[1].MyTroop()->gota(&Rihanna);
    // mainchess.allPlayer[1].MyTroop()->gota(&AA);
    // mainchess.allPlayer[1].MyTroop()->turnOnFrontline();
    // mainchess.allPlayer[1].MyTroop()->turnOnFrontline();
    // mainchess.allPlayer[1].MyTroop()->showFrontline();
    // war demowar(mainchess.A);
    // demowar.running();
    // return 0;
}

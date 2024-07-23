#include "player.h"
#include "chesstype.h"
#include "playchess.h"
#include "war.h"
#include"store.h"
#include <iostream>
#include <string>
#include <random>

int main() {
    playchess mainchess;
    // mainchess.home();

    player a(1,"Sy");

    // store Mystore(a);
    // Mystore.generateSoldier();
    // Mystore.menu();

    player b(2,"yy");
    fire_Warrior Kevin,AA;
    Hypnotist Rihanna,AiMee;
    wild_Priest yy,aa;
    ParticleWarrior amy;
    // a.MyTroop()->testOnFront(&amy,1,1);
    a.MyTroop()->testOnFront(&amy,1,3);
    // b.MyTroop()->testOnFront(&Rihanna,0,1);
    b.MyTroop()->testOnFront(&AA,0,4);
    std::vector<player*> GreatWar={&a,&b};
    war testwar(GreatWar,0);
    testwar.determineBuff();
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

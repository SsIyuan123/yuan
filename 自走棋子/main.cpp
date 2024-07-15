#include "player.h"
#include "chesstype.h"
#include "playchess.h"
#include "war.h"
#include <iostream>
#include <string>
#include <random>

int main() {
    playchess mainchess;
    ParticleWarrior Rihanna,AiMee;
    LaserArcher Taylor,Betty;
    DimensionAssassin Kevin,AA;
    ParticleEngineer amy;
    mainchess.A[0].MyTroop()->gota(&Taylor);
    mainchess.A[0].MyTroop()->gota(&Kevin);
    mainchess.A[0].MyTroop()->TurnOnFronter(&Taylor,0,0);
    mainchess.A[0].MyTroop()->TurnOnFronter(&Kevin,1,1);
    mainchess.A[0].MyTroop()->showFrontline();
    mainchess.A[1].MyTroop()->gota(&Rihanna);
    mainchess.A[1].MyTroop()->gota(&AA);
    mainchess.A[1].MyTroop()->TurnOnFronter(&Rihanna,0,4);
    mainchess.A[1].MyTroop()->TurnOnFronter(&AA,0,1);
    mainchess.A[1].MyTroop()->showFrontline();
    war demowar(mainchess.A);
    demowar.running();
    return 0;
}

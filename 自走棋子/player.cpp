#include "gamehost.h"
#include "chesstype.h"
#include <iostream>
#include <string>

#include <random>

int main() {
    playchess mainchess;
    ParticleWarrior Rihanna,AiMee;
    LaserArcher Taylor,Betty;
    mainchess.A[0].MyTroop()->gota(&Taylor);
    mainchess.A[0].MyTroop()->gota(&Rihanna);
    mainchess.A[0].MyTroop()->TurnOnFronter(&Rihanna,0,1);
    mainchess.A[0].MyTroop()->TurnOnFronter(&Taylor,1,0);
    mainchess.A[0].MyTroop()->showFrontline();
    mainchess.A[1].MyTroop()->gota(&Betty);
    mainchess.A[1].MyTroop()->gota(&AiMee);
    mainchess.A[1].MyTroop()->TurnOnFronter(&AiMee,0,4);
    mainchess.A[1].MyTroop()->TurnOnFronter(&Betty,1,2);
    mainchess.A[1].MyTroop()->showFrontline();
    war demowar(mainchess.A);
    demowar.running();
    return 0;
}

#include "gamehost.h"
#include "chesstype.h"
#include <iostream>
#include <string>

#include <random>

int main() {
    playchess mainchess;
    ParticleWarrior Alex,Kim;
    mainchess.A[0].MyTroop().gota(&Alex);
    mainchess.A[0].MyTroop().TurnOnFronter(&Alex,0,3);
    mainchess.A[1].MyTroop().gota(&Kim);
    mainchess.A[1].MyTroop().TurnOnFronter(&Alex,0,2);
    war demowar(mainchess.A);
    demowar.running();
    return 0;
}

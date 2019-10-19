#ifndef DATASTRUCTURES_H
#define DATASTRUCTURES_H

enum GameSize{
    Small = 3,
    Medium = 4,
    Large = 6
};

struct Position
{
    int X;
    int Y;
    Position(int x, int y):X(x),Y(y){}
};

struct GameStats{
    const int StepCount;
    GameStats(int stepCount) : StepCount(stepCount){}
};



#endif // DATASTRUCTURES_H

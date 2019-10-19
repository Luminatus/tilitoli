#ifndef VIEWDATA_H
#define VIEWDATA_H

#include "Headers/datastructures.h"
#include "Headers/gamesession_model.h"

struct ViewData
{
    ViewData(GameSessionModel* model);
    const int tableSize;
    int tileSize;
    int windowWidth;
    int windowHeight;

    Position GetPlayerPosition();

    int getValueAt(int,int);
private:
    GameSessionModel* _gameSessionModel;
};

#endif // VIEWDATA_H

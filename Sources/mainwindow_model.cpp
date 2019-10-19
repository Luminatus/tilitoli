#include "Headers/mainwindow_model.h"
#include "Headers/datastructures.h"

MainWindowModel::MainWindowModel()
{

}

MainWindowModel::~MainWindowModel()
{
    if(_gameSessionModel != NULL)
    {
        delete _gameSessionModel;
    }
}


void MainWindowModel::InitGame(int n)
{
    bool ret = true;
    switch(n)
    {
    case Small : case Medium: case Large: ret &= _InitializeGameSession(n); break;
    default: ret = false;
    }
    if(!ret) emit InitFailed();
    else emit GameReady(_gameSessionModel);
}

bool MainWindowModel::_InitializeGameSession(int n)
{
    _gameSessionModel = new GameSessionModel(n);
    return true;
}
/*
bool MainWindowModel::loadGame(int tableSize, int redHP, int blueHP, Position redPos, Position bluePos)
{
    if(tableSize != Small && tableSize != Medium && tableSize != Large)
        return false;
    if(redHP < 1 || blueHP < 1 || redHP > 3 || blueHP > 3)
        return false;
    if(redPos.X <0 || redPos.X >= tableSize || redPos.Angle < 0 || redPos.Angle > 3
    || bluePos.X <0 || bluePos.X >= tableSize || bluePos.Angle < 0 || bluePos.Angle > 3)
        return false;
    _gameSessionModel = new GameSessionModel(tableSize);
    emit GameReady(_gameSessionModel);

    return true;


}
*/


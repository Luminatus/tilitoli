#include "Headers/viewdata.h"


ViewData::ViewData(GameSessionModel *model) : _gameSessionModel(model), tableSize(model->GetTableSize()){}

int ViewData::getValueAt(int x, int y)
{
    return _gameSessionModel->GetValueAt(x,y);
}

Position ViewData::GetPlayerPosition()
{
    return _gameSessionModel->GetPlayerPosition();
}


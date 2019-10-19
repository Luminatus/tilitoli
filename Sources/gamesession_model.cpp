#include "Headers/gamesession_model.h"

GameSessionModel::GameSessionModel(int tableSize) :
    _tableSize(tableSize),
    _playerPosition(Position(tableSize-1, tableSize-1))
{
    _goalTable.resize(tableSize);
    for(int i=0; i<tableSize; i++)
    {
        _goalTable[i].resize(tableSize);
        for(int j=1; j<=tableSize; j++)
        {
            _goalTable[i][j-1] = tableSize*i + j;
        }
    }
    _goalTable[_playerPosition.Y][_playerPosition.X] = 0;
}

void GameSessionModel::init()
{
    _playerPosition = Position(_tableSize-1, _tableSize-1);
    _stepCount =0;
    _gameTable = QVector<QVector<int> >(_goalTable);

    qsrand(time(NULL));
    int pos1_max = (_tableSize*_tableSize)-2;
    int pos2_max = (_tableSize*_tableSize)-3;
    for(int k = 0; k<(_tableSize*_tableSize)+_tableSize;k++)
    {
        int pos1 = qrand()%(pos1_max);
        int pos2 = qrand()%(pos2_max);
        if(pos1 == pos2)
        {
            pos2 = (_tableSize*_tableSize)-2;
        }
        int row1 = pos1/_tableSize;
        int col1 = pos1%_tableSize;
        int row2 = pos2/_tableSize;
        int col2 = pos2%_tableSize;

        int tmp = _gameTable[row1][col1];
        _gameTable[row1][col1] = _gameTable[row2][col2];
        _gameTable[row2][col2] = tmp;
    }

}

GameSessionModel::~GameSessionModel()
{

}

int GameSessionModel::GetTableSize()
{
    return _tableSize;
}
/*
int GameSessionModel::GetTileState(int posX, int posY)
{
    if (isValidPosition(posX,posY))
    {
        return _gameTable[posX][posY]->State;
    }
    else return ErrorState;
}
*/

bool GameSessionModel::IsGameWon()
{
    for(int i=0; i<_tableSize; i++)
    {
        for(int j=0; j< _tableSize; j++)
        {
            if(_gameTable[i][j] != _goalTable[i][j])
            {
                return false;
            }
        }
    }
    return true;
    /*if(_BluePlayer->Health==0)
    {
        if(_RedPlayer->Health==0)
            emit GameWon(None);
        else
            emit GameWon(RedPlayer);
    }
    else if(_RedPlayer->Health==0)
        emit GameWon(BluePlayer);
    else
        return false;
    return true;*/
}

int GameSessionModel::GetValueAt(int row, int col)
{
    return _gameTable[row][col];
}

Position GameSessionModel::GetPosition(int value)
{
    for(int row=0; row<_tableSize; row++)
    {
        for(int col=0; col<_tableSize; col++)
        {
            if(_gameTable[row][col]==value)
            {
                return Position(col,row);
            }
            else
            {
                continue;
            }
        }
    }
    return Position(-1,-1);
}

Position GameSessionModel::GetPlayerPosition()
{
    return _playerPosition;
}

bool GameSessionModel::isValidMove(int x, int y)
{
     int x_diff = _playerPosition.X - x;
     int y_diff = _playerPosition.Y - y;
     return (
        x >=0 &&
        y >=0 &&
        x < _tableSize &&
        y < _tableSize &&
        (x_diff == 0 || y_diff == 0) &&
        (abs(x_diff + y_diff) == 1)
     );
}

bool GameSessionModel::MakeMove(int x, int y)
{
    if(isValidMove(x,y))
    {
        _gameTable[_playerPosition.Y][_playerPosition.X] = _gameTable[y][x];
        _gameTable[y][x] = 0;
        _playerPosition.X=x; _playerPosition.Y = y;
        _stepCount++;
        return true;
    }
    else
    {
        return false;
    }
}
/*
void GameSessionModel::GameStep()
{
    if(_activePlayer!=None) return;
    if(_currentCommand==5){ endRound(); return; }
    Command redCommand = _RedPlayer->Memory[_currentCommand];
    Command blueCommand = _BluePlayer->Memory[_currentCommand];
    if(redCommand.Type==blueCommand.Type)
        executeParallelCommands();
    else if(redCommand.Type>blueCommand.Type)
    {
        executeCommand(_RedPlayer);
        executeCommand(_BluePlayer);
    }
    else
    {
        executeCommand(_BluePlayer);
        executeCommand(_RedPlayer);
    }
    _currentCommand++;
    emit MakeStep(redCommand,blueCommand);
}
*/


GameStats GameSessionModel::GetGameStats()
{
    return GameStats(_stepCount);
}


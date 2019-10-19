#ifndef GAMESESSIONMODEL_H
#define GAMESESSIONMODEL_H
#include <QObject>
#include <QVector>
#include "Headers/datastructures.h"

class GameSessionModel : public QObject
{
    Q_OBJECT
public:
    GameSessionModel(int tableSize);
    ~GameSessionModel();
    void init();
    int GetTableSize();
    bool IsGameWon();
    GameStats GetGameStats();
    Position GetPosition(int);
    Position GetPlayerPosition();
    int GetValueAt(int,int);
    bool MakeMove(int x,int y);
private:

    bool isValidMove(int x,int y);
    QVector<QVector<int> > _gameTable;
    QVector<QVector<int> > _goalTable;
    const int _tableSize;
    int _stepCount;
    Position _playerPosition;

};

#endif // GAMESESSIONMODEL_H

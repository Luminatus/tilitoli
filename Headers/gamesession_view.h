#ifndef GAMESESSION_VIEW_H
#define GAMESESSION_VIEW_H
#include <QWidget>
#include "ui_gamesession.h"
#include "Headers/gamesession_model.h"
#include "Headers/viewdata.h"

class GameSessionView : public QWidget
{
    Q_OBJECT
public:
    GameSessionView(QWidget* mainWindowView,GameSessionModel* gameSessionModel);
    ~GameSessionView();
    void start();
private:
    void updateWindow();

    QWidget* _mainWindowView;
    GameSessionModel* _gameSessionModel;
    Ui::GameSessionUI* ui;
    ViewData* _viewData;
/*
signals:
    void saveGame(int,int,int,Position,Position);
*/
public slots:
    void backToMainMenu();
    void processClick(int posX, int posY);
    void init();
};

#endif // GAMESESSION_VIEW_H

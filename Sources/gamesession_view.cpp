#include "Headers/gamesession_view.h"
#include <QPainter>
#include <QPaintEngine>
#include <QPaintEvent>
#include <QMessageBox>
#include <QTimer>

GameSessionView::GameSessionView(QWidget* mainWindowView, GameSessionModel* gameSessionModel):
    _mainWindowView(mainWindowView),
    _gameSessionModel(gameSessionModel),
    ui(new Ui::GameSessionUI){}

void GameSessionView::start()
{
    _viewData = new ViewData(_gameSessionModel);
    _viewData->tileSize = 60;

    ui->setupUi(this);
    ui->gameTable->setMinimumSize(_gameSessionModel->GetTableSize()*_viewData->tileSize,_gameSessionModel->GetTableSize()*_viewData->tileSize);
    int minwidth = ui->gameTable->width()+100;
    setMinimumSize(minwidth,ui->gameTable->height()+130);
    setMaximumSize(minwidth,ui->gameTable->height()+130);

    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowMinimizeButtonHint);
    init();
    show();
}

GameSessionView::~GameSessionView()
{
    disconnect(ui->closeButton,SIGNAL(clicked()),this,SLOT(backToMainMenu()));
    disconnect(ui->gameTable,SIGNAL(TileClicked(int,int)),this,SLOT(processClick(int,int)));

    delete _viewData;
    delete _gameSessionModel;
    delete ui;
}

void GameSessionView::init()
{
    _gameSessionModel->init();
    GameStats stats = _gameSessionModel->GetGameStats();
    ui->gameTable->setViewData(_viewData);
    ui->stepCounter->display(stats.StepCount);
    connect(ui->closeButton,SIGNAL(clicked()),this,SLOT(backToMainMenu()));
    connect(ui->gameTable,SIGNAL(TileClicked(int,int)),this,SLOT(processClick(int,int)));
}


void GameSessionView::backToMainMenu()
{
    if(!_gameSessionModel->IsGameWon())
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this,"Kilépés","Biztosan ki akarsz lépni?",
                                      QMessageBox::Yes | QMessageBox::No);
        if (reply != QMessageBox::Yes)
        {
            return;
        }
    }
    close();
    delete this;
}

void GameSessionView::updateWindow()
{
    GameStats stat = _gameSessionModel->GetGameStats();
    ui->stepCounter->display(stat.StepCount);
    update();
}

void GameSessionView::processClick(int posX, int posY)
{
    if(_gameSessionModel->MakeMove(posX, posY))
    {
        updateWindow();
        if(_gameSessionModel->IsGameWon())
        {
            QMessageBox* message = new QMessageBox();
            message->setText(QString("Nyertél! %1 lépésből teljesítetted a játékot!").arg(_gameSessionModel->GetGameStats().StepCount));
            message->show();
            connect(message,SIGNAL(finished(int)),SLOT(init()));
        }
    }
}

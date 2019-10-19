#include "Headers/tableview.h"

TableView::TableView(QWidget* parent): QWidget(parent)
{
}


void TableView:: setViewData(ViewData* viewData)
{
   _viewData = viewData;
    int tableSize = _viewData->tableSize;
    int tileSize = _viewData->tileSize;
   setMinimumSize(tableSize*tileSize+10,tableSize*tileSize+10);
   setBaseSize(tableSize*tileSize,tableSize*tileSize);
}


void TableView::paintEvent(QPaintEvent*)
{
    int tableSize = _viewData->tableSize;
    int tileSize = _viewData->tileSize;
    setMinimumSize(tableSize*tileSize,tableSize*tileSize);
    setBaseSize(tableSize*tileSize,tableSize*tileSize);

    QPainter painter(this);

    QPen tilePen;
    tilePen.setWidth(1);
    tilePen.setColor(QColor(30,40,40));

    painter.setPen(tilePen);

    QColor bgColor;
    bgColor.setRgb(40,50,60);

    QColor activeColor;
    activeColor.setRgb(50,60,85);


    painter.fillRect(0,0,tableSize*tileSize,tableSize*tileSize,bgColor);

    for (int i=0; i<tableSize; i++)
    {
        for (int j=0; j<tableSize; j++)
        {
            int value = _viewData->getValueAt(i,j);
            if(value != 0)
            {
                painter.fillRect(j*tileSize,i*tileSize,tileSize,tileSize,activeColor);
                painter.drawText(j*tileSize,i*tileSize,tileSize, tileSize,Qt::AlignCenter, QString::number(value));
            }
            painter.drawRect(j*tileSize,i*tileSize,tileSize,tileSize);
        }
    }

}

void TableView::mousePressEvent(QMouseEvent* event)
{
    int posX = event->x() / _viewData->tileSize;
    int posY = event->y() / _viewData->tileSize;

    emit TileClicked(posX,posY);
}

TableView::~TableView()
{
}

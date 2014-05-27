#include "qgamecanvas.h"

QGameCanvas::QGameCanvas(GCGridSize res, int _fps,
                         QColor _background, QColor _foreground, QQuickItem *parent) :
    m_gridSize(res),m_fps(_fps),m_backColor(_background),m_foreColor(_foreground),m_width(0),m_height(0),QQuickPaintedItem(parent)
{
    m_brush = QBrush(m_foreColor);
    this->setFillColor(m_backColor);
    m_timer.setInterval(1000/m_fps);
    connect(&m_timer, SIGNAL(timeout()),this,SLOT(slot_timerTimedOut()));
    m_gameOver = false;
    m_gameStarted = false;
    m_score = 0;

}
void QGameCanvas::startGame()
{
    m_timer.start();
    m_gameOver = false;
    m_gameStarted = true;
}
void QGameCanvas::updateScore(int score)
{   m_score = score; }

void QGameCanvas::componentComplete()
{
    QQuickPaintedItem::componentComplete();
    setupGrid();
}
void QGameCanvas::setupGrid()
{
    if (m_width == (int)this->width() || m_height == (int)this->height())
        return; //width has not changed.
    m_grid.clear();
    m_width = (int)this->width();
    m_height = (int)this->height();
    if (m_width > 0 && m_height > 0)
    {
        int pixelSize=0;
        int rows=0;
        int cols=0;
        m_gridRows = rows;
        m_gridCols = cols;
        switch (m_gridSize)
        {
        case small://30
            pixelSize = m_width/30;
            //if (pixelSize < 5)
            //{}
            //else
            {
                rows = m_height/pixelSize;
                //if (rows < 45)
                  //  return;
            }
            cols = 30;
            break;
        case medium://25
            pixelSize = m_width/25;
            //if (pixelSize < 5)
            //{}
            //else
            {
                rows = m_height/pixelSize;
               // if (rows < 38)
                 //   return;
            }
            cols = 25;
            break;
        case large://20
            pixelSize = m_width/20;
            //if (pixelSize < 5)
            //{}
            //else
            {
                rows = m_height/pixelSize;
                //if (rows < 30)
                  //  return;
            }
            cols = 20;
            break;
        }
        int offset_x = (m_width - cols * pixelSize)/2;
        int offset_y = (m_height - rows * pixelSize)/2;
        for (int i=0; i<rows; i++)
        {
            for (int j=0; j<cols; j++)
            {
                QRect rect(QPoint(j*pixelSize+offset_x,i*pixelSize+offset_y),QSize(pixelSize-2,pixelSize-2));
                m_grid.push_back(rect);
            }
        }
        m_gridRows = rows;
        m_gridCols = cols;
    }

}
void QGameCanvas::gameOver()
{
    m_gameOver = true;
    m_gameStarted = false;
}
void QGameCanvas::paint(QPainter *p_painter)
{
    emit sig_frameUpdated();
    if (!m_gameOver)
    {
        const QBrush brush = m_brush;
        const QColor color = m_foreColor;
        p_painter->setBrush(brush);
        p_painter->setPen(color);
        setupGrid();
        updateGridPoints(m_gridPoints);
        for (size_t i=0; i< m_gridPoints.size(); i++)
        {
            QRect pixel = getGridElement(m_gridPoints[i].row, m_gridPoints[i].col);
            p_painter->drawRect(pixel);
        }
        if (m_gameStarted)
        {
            p_painter->setPen(QColor("black"));
            p_painter->drawText(QPointF(10,this->height()-10),QString("Score: ") + QString::number(m_score));
        }

    }
    else
    {
        gameOverScreen(p_painter);
    }
}
void QGameCanvas::slot_timerTimedOut()
{
    this->update();
}

QRect QGameCanvas::getGridElement(int i, int j)
{
    QRect retVal = m_grid.at(i * m_gridCols + j);
    return retVal;
}

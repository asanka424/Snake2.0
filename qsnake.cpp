#include "qsnake.h"

QSnake::QSnake(GCGridSize res, int _fps, QColor _background, QColor _foreground, QQuickItem *parent) :
    QGameCanvas(res,_fps,_background, _foreground,parent)
{
    m_gameStarted = false;
    m_timer.setInterval(200);
    //connect(&m_timer, SIGNAL(timeout()),this,SLOT(moveSnake()));
    connect(this,SIGNAL(sig_frameUpdated()),this,SLOT(slot_screenUpdated()));
    m_foodPlaced = false;
}
QSnake::~QSnake(){}
void QSnake::updateGridPoints(std::vector<GridPoint> &_gridPoints)
{
    _gridPoints.clear();
    //snake points
    for (size_t i=0; i< m_snake.size(); i++)
    {
        _gridPoints.push_back(m_snake.at(i));
    }
    if (m_foodPlaced)
        _gridPoints.push_back(m_food);

}
void QSnake::gameOverScreen(QPainter *p_painter)
{
    p_painter->drawText(QPointF(this->width()/2 - 30,this->height()/2),"Game Over");
    m_timer.stop();
    QObject *rect = this->findChild<QObject*>("startButton");
    if (rect)
        rect->setProperty("visible", "true");
}

void QSnake::slot_pause()
{}
void QSnake::slot_resume()
{}
void QSnake::slot_upPressed()
{ m_direction = 2;}
void QSnake::slot_downPressed()
{ m_direction = 3;}
void QSnake::slot_leftPressed()
{ m_direction = 0;}
void QSnake::slot_rightPressed()
{ m_direction = 1;}
void QSnake::slot_start()
{
    m_snake.clear();
    for (int i=4; i>=0; i--)
    {
        GridPoint pnt;
        pnt.col = i;
        pnt.row = 0;
        m_snake.push_back(pnt);
    }
    //initial direction
    m_direction = 1; //left
   // m_timer.start();
    QObject *rect = this->findChild<QObject*>("startButton");
    if (rect)
        rect->setProperty("visible", "false");
    startGame();
    placeFood();
    m_gameStarted = true;
}

void QSnake::moveSnake()
{
    //drawSnake(true);
    //update();
}

void QSnake::placeFood()
{
    bool wrongPlace = true;
    int x,y;
    while (wrongPlace)
    {
        x = qrand() % getWidth()-1;
        y = qrand() % getHeight()-1;
        if (x < 0 || y < 0)
            break;
        for (size_t i=0; i<m_snake.size(); i++)
        {
            GridPoint point = m_snake[i];
            wrongPlace = (x == point.col && y == point.row);
            if (!wrongPlace)
                break;
        }
    }
    m_food.col = x;
    m_food.row = y;
    m_foodPlaced = true;
}

void QSnake::drawSnake(bool pop)
{
    if (pop)
        m_snake.pop_back();
    GridPoint np;
    GridPoint hp = m_snake.front();
    switch (m_direction)
    {
    case 0: //left
        np = hp;
        np.col--;
        break;
    case 1: //right
        np = hp;
        np.col++;
        break;
    case 2: //up
        np = hp;
        np.row--;
        break;
    case 3: //down
        np = hp;
        np.row++;
        break;
    }
    if (checkSnake(np))
    {
        m_gameOver = true;
        gameOver();
        m_timer.stop();
        return;
    }
    else
    {
        m_snake.insert(m_snake.begin(),np);

        //check if snake ate food
        if (pop)
        {
            if (m_snake.front() == m_food)
            {
                m_foodPlaced = false;
                drawSnake(false);
                updateSpeed();
                placeFood();
            }
        }
        updateScore((int)m_snake.size()-5);
    }
}
void QSnake::slot_screenUpdated()
{
    if (m_gameStarted)
    {
        drawSnake(true);
    }
}

bool QSnake::checkSnake(GridPoint pnt)
{
    bool retVal = false;
    if (pnt.col < 0 || pnt.col >= getWidth() || pnt.row < 0 || pnt.row >= getHeight())//boundaries
    {
        retVal = true;
    }
    if (!retVal)
    for (size_t i=0; i<m_snake.size(); i++)
    {
        GridPoint tmp = m_snake.at(i);
        if (tmp == pnt)
        {
            retVal = true;
            break;
        }
    }
    return retVal;
}

void QSnake::updateSpeed()
{
    int snakeSize = (int)m_snake.size();
    if (snakeSize > 100)
    {
        slot_updateFPS(10);
        return;
    }
    else if (snakeSize > 80)
    {
        slot_updateFPS(9);
        return;
    }
    else if (snakeSize > 60)
    {
        slot_updateFPS(8);
        return;
    }
    else if (snakeSize > 40)
    {
        slot_updateFPS(7);
        return;
    }
    else if (snakeSize > 20)
    {
        slot_updateFPS(6);
        return;
    }
}


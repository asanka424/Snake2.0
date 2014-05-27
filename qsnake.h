#ifndef QSNAKE_H
#define QSNAKE_H

#include "qgamecanvas.h"
#include <QTimer>
#include <QMutexLocker>

typedef struct
{
    int x,y;
}square;
class QSnake : public QGameCanvas
{
    Q_OBJECT
public:
    explicit QSnake(GCGridSize res = small, int _fps = 5, QColor _background = QColor("light blue"),
                    QColor _foreground = QColor("blue"),QQuickItem *parent = 0);
    void updateGridPoints(std::vector<GridPoint>& _gridPoints);
    void gameOverScreen(QPainter *p);
    ~QSnake();

signals:

public slots:
    void slot_pause();
    void slot_resume();
    void slot_upPressed();
    void slot_downPressed();
    void slot_leftPressed();
    void slot_rightPressed();
    void slot_start();
private slots:
    void moveSnake();
    void placeFood();
    void slot_screenUpdated();
private:
    void drawSnake(bool pop);
    void updateSpeed();
    bool checkSnake(GridPoint pnt);
private:
    QTimer m_timer;
    std::vector<GridPoint> m_snake;
    int m_direction; //0-left, 1-right, 2-up, 3-down
    bool m_gameOver,m_foodPlaced,m_gameStarted;
    GridPoint m_food;
    int squareSize;
    QMutex m_mutex;

};

#endif // QSNAKE_H

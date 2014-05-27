#ifndef QGAMECANVAS_H
#define QGAMECANVAS_H

#include <QQuickPaintedItem>
#include <vector>
#include <QTimer>
#include <QPainter>
#include <QColor>
#include <QPoint>
#include <iostream>
enum GCGridSize{
    small = 0,
    medium,
    large
};
struct GridPoint{
    int row;
    int col;
    bool operator==(const GridPoint& a) const
    {
        return (row == a.row && col == a.col);
    }
};


class QGameCanvas : public QQuickPaintedItem
{
    Q_OBJECT
public:
    explicit QGameCanvas(GCGridSize res = small, int _fps = 2, QColor _background = QColor("light blue"),
                         QColor _foreground = QColor("blue"),QQuickItem *parent = 0);
    virtual ~QGameCanvas(){}
    void paint(QPainter *);
    void virtual updateGridPoints(std::vector<GridPoint>& _gridPoints)= 0;
    void virtual gameOverScreen(QPainter *) = 0;
    void componentComplete();
    void gameOver();
    void startGame();
    void updateScore(int score);
    int getWidth(){return m_gridCols;}
    int getHeight(){return m_gridRows;}
private:
    void setupGrid();
    QRect getGridElement(int i, int j);

signals:
    void sig_frameUpdated();

public slots:
    void slot_changeResolution(GCGridSize res);

    void slot_setBackgroundColor(QColor color);
    void slot_setForegroundColor(QColor color);
    void slot_updateFPS(int fps);

    virtual void slot_pause() = 0;
    virtual void slot_resume() = 0;
    virtual void slot_upPressed() = 0;
    virtual void slot_downPressed() = 0;
    virtual void slot_leftPressed() = 0;
    virtual void slot_rightPressed() = 0;
    virtual void slot_start() = 0;
private slots:
    void slot_timerTimedOut();
private:
    int m_width,m_height;
    std::vector<GridPoint> m_gridPoints;
    GCGridSize m_gridSize;
    int m_fps;
    QColor m_backColor, m_foreColor;
    QBrush m_brush;
    QTimer m_timer;
    std::vector<QRect> m_grid;
    int m_gridRows,m_gridCols;
    bool m_gameOver,m_gameStarted;
    int m_score;



};

#endif // QGAMECANVAS_H

#include <qgamecanvas.h>

void QGameCanvas::slot_changeResolution(GCGridSize res)
{}

void QGameCanvas::slot_setBackgroundColor(QColor color)
{}
void QGameCanvas::slot_setForegroundColor(QColor color)
{}
void QGameCanvas::slot_updateFPS(int fps)
{
    m_fps = fps;
    m_timer.setInterval(1000/m_fps);
}



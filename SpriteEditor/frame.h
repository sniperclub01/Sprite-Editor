#ifndef FRAME_H
#define FRAME_H

#include <QObject>
#include <QColor>
#include <QImage>
#include <QPainter>

class frame : public QObject
{
    Q_OBJECT

public:
    frame(int height_, int width_, QObject *parent = 0);
    frame* duplicate();

    void setColorAtPixel(int x, int y, QColor color);
    void setCurrColor(QColor color);
    QColor getPixelColor(int x, int y);
    int getFrameWidth();
    int getFrameHeight();

private:
    int width;
    int height;
    QVector<QVector<QColor>> pixelColors;
    QColor currColor;
};

#endif // SPRITE_H

#ifndef SCENE_H
#define SCENE_H

// Qt Graphics Object Handlers
#include <QGraphicsItem>
#include <QImage>
#include <QPainter>
#include <QRubberBand>

#include <QColor>

// Qt Event Handlers
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>

#include "sprite.h"
#include <iostream>

class scene : public QGraphicsScene
{
    Q_OBJECT

public:
    scene(sprite* sprite, QObject *parent = 0);
    ~scene();

    // Draw Scene
    void clearScene();
    void drawScene();
    void prepareScene();
    void drawPixel(int x, int y);
    void erasePixel(int x, int y);
    void setSpriteSize(int size);
    QImage getCurrImage();

    void selectPixels(int x, int y);
    void outlineSelected(int x1, int y1, int x2, int y2);
    void deselectArea();
    void cropArea();
    void fillArea();

private:
    const int frameSize = 500;
    int pixelSize;
    QImage* image;
    QImage copyImage;
    QVector<QVector<QGraphicsRectItem*>> pixels;

    int slcX1, slcY1, slcX2, slcY2; // Selection coordinates, top left, bottom right.

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event); // Clicking in the scene/drawing
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent); // Moving the mouse over the scene (while clicking?)
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);

    sprite* sprite;
    QRubberBand* rBand;
    QPoint originPoint;
    QPointF originCropPoint;
};

#endif // SCENE_H

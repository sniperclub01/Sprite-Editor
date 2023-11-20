#ifndef SPRITE_H
#define SPRITE_H

//#include "ui_spriteView.h"
// Qt Graphics Objects handling
#include <QImage>
#include <QObject>
#include <QColor>
#include <QList>

#include "frame.h"
#include <iostream>

class sprite : public QObject
{
    Q_OBJECT

public:
    sprite(QObject* parent = 0);
    void setFPS(int fps);
    void playSpritePreview();

    // Frame methods
    void newFrame();
    void removeFrame(int index);
    void nextFrame();
    void prevFrame();
    void setCurrentFrame(int index);
    frame getCurrentFrame();

    int getSpriteSize();
    void setSpriteSize(int size);
    void addImage(QImage image);

    // Frame handling
    void paintPixel(int x, int y, QColor color);
    QColor getColorOfPixel(int x, int y);
    void setBrushColor(QColor color);
    QColor getBrushColor();

    // Tools
    enum Tool {
        BRUSH,
        ERASER,
        SELECTOR
    };
    void setCurrentTool(Tool tool);
    Tool getCurrentTool();

private:
    QList<frame*> frameList;
    QList<QImage> images;
    int msBetweenFrames;
    int frameIndex;
    int spriteSize;
    int maxHeight, maxWidth = 500;
    int minHeight, minWidth = 4;
    QColor brushColor;
    Tool currentTool;

};

#endif // SPRITE_H

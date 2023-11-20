#include "frame.h"

frame::frame(int height_, int width_, QObject *parent) :
            QObject(parent), width(width_), height(height_) {
    for(int i = 0; i < width; i++) {
        pixelColors.append(QVector<QColor>(height));
        for (int j = 0; j < height; j++) {
            pixelColors[i][j] = QColor(0, 0, 0, 0);
        }
    }
}

frame* frame::duplicate() {
    frame* duplicateFrame = new frame(this->width, this->height);

    for(int i = 0; i < this->width; i++) {
        for (int j = 0; j < this->height; j++) {
            duplicateFrame->setColorAtPixel(i, j, this->getPixelColor(i, j));
        }
    }
    return duplicateFrame;
}

void frame::setColorAtPixel(int x, int y, QColor color) {
    pixelColors[x][y] = color;
}

void frame::setCurrColor(QColor color) {
    this->currColor = color;
}

QColor frame::getPixelColor(int x, int y) {
    return pixelColors[x][y];
}

int frame::getFrameHeight() {
    return height;
}

int frame::getFrameWidth() {
    return width;
}

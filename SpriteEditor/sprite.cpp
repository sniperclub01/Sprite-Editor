#include "sprite.h"

sprite::sprite(QObject *parent) :
            QObject(parent), frameIndex(0), currentTool(BRUSH) {
    frameList << new frame(spriteSize, spriteSize); // sprit
}

void sprite::setFPS(int fps) {
    this->msBetweenFrames = 1000/fps;

}

void sprite::playSpritePreview() {

}

/*void sprite::displayNextFrame() {
    //QImage* image = this->frames.at(frameIndex)._frame;
     //QGraphicsScene *scene = new QGraphicsScene;
     //QGraphicsPixmapItem *item = new QGraphicsPixmapItem(QPixmap::fromImage(image));

    //ui->previewWindow->setScene(scene);
    frameIndex++;
}*/

void sprite::newFrame() {
    frame* newFrame = new frame(spriteSize, spriteSize);
    frameList.insert(frameIndex, newFrame);
    frameIndex++;
}

void sprite::removeFrame(int index) {
    if (frameList.size() > 1) {
        frameList.removeAt(index);
    }
}

void sprite::nextFrame() {
    setCurrentFrame(frameIndex+1);
}

void sprite::prevFrame() {
    setCurrentFrame(frameIndex-1);
}

void sprite::setCurrentFrame(int index) {
    if (index < 0) {
        frameIndex = 0;
    }
    else if (index > frameList.size()) {
        frameIndex = frameList.size();
    }
    else {
        frameIndex = index;
    }
}

int sprite::getSpriteSize() {
    return spriteSize;
}

void sprite::setSpriteSize(int size) {
    this->spriteSize = size;
}

void sprite::addImage(QImage image) {
    this->images.append(image);
    std::cout << "image added " << images.size() << std::endl;
}
frame sprite::getCurrentFrame() {
    //return frameList.at(frameIndex);
}

#include <iostream>
void sprite::paintPixel(int x, int y, QColor color) {
    frameList.at(frameIndex)->setColorAtPixel(x, y, color);
    std::cout<<"test";
}

QColor sprite::getColorOfPixel(int x, int y) {
    return frameList.at(frameIndex)->getPixelColor(x, y);
}

void sprite::setBrushColor(QColor color) {
    this->brushColor = color;
}

QColor sprite::getBrushColor() {
    return this->brushColor;
}

void sprite::setCurrentTool(Tool tool) {
    currentTool = tool;
}

sprite::Tool sprite::getCurrentTool() {
    return currentTool;
}

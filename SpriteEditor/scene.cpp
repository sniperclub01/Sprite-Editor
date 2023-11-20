#include "scene.h"

scene::scene(class sprite* _sprite, QObject *parent) :
    QGraphicsScene(parent), sprite(_sprite)
{
    this->setSceneRect(0, 0, frameSize, frameSize); //TODO: GET WIDTH & HEIGHT OF DESIRED FRAME
    clearScene();
}

scene::~scene() {
    delete image;
}

void scene::clearScene() {
    pixels.clear();

    this->setSceneRect(0, 0, frameSize, frameSize); //TODO: WIDTH/HEIGHT HANDLING
    this->prepareScene();

    int width, height = 500; // TODO: WIDTH/HEIGHT HANDLING
    for(int i = 0; i < width; i++) {
        pixels.append(QVector<QGraphicsRectItem*>(height));
        for (int j = 0; j < height; j++) {
            pixels[i][j] = this->addRect(
                        frameSize * i,
                        frameSize * j,
                        frameSize,
                        frameSize,
                        QPen(Qt::transparent));
        }
    }
}

/**
 * @brief scene::prepareScene
 * After the scene is cleared, prepared the painter/pixmap
 */
void scene::prepareScene() {
    this->clear();
    image = new QImage(frameSize, frameSize, QImage::Format_ARGB32); // TODO: WIDTH/HEIGHT HANDLING
    QPainter painter(image);
    this->addPixmap(QPixmap::fromImage(*image));
}

// Draw pixels to the QImage, add it to a pixmap.
void scene::drawPixel(int x, int y) {
    QPainter painter(image);
    painter.setPen(Qt::transparent);
    painter.setBrush(sprite->getBrushColor());
    painter.drawRect(x*pixelSize, y*pixelSize, this->pixelSize, this->pixelSize);
    this->addPixmap(QPixmap::fromImage(*image));
}

// Erase pixels from the QImage (set color to white), add it to a pixmap.
void scene::erasePixel(int x, int y) {
    QPainter painter(image);
    painter.setPen(Qt::transparent);
    painter.setBrush(Qt::white);
    painter.drawRect(x*pixelSize, y*pixelSize, this->pixelSize, this->pixelSize);
    this->addPixmap(QPixmap::fromImage(*image));
}

// Select pixels
void scene::selectPixels(int x, int y) {
    // TODO: IMPLEMENT
}

void scene::setSpriteSize(int size) {
    this->pixelSize = frameSize/size;
    std::cout << "Pixel size: " << pixelSize << std::endl;
}

QImage scene::getCurrImage() {
    return *image;
}

/**
 * @brief scene::mousePressEvent
 * Updates the specified pixel that is clicked on.
 * @param mouseEvent
 */
void scene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    int x = mouseEvent->scenePos().x()/pixelSize;
    int y = mouseEvent->scenePos().y()/pixelSize;
    if (x >= 0 && x < frameSize/pixelSize && y < frameSize/pixelSize && y >= 0) // TODO: WIDTH/HEIGHT HANDLING
    {
        if (sprite->getCurrentTool() == sprite::BRUSH) {
            drawPixel(x, y);
        }
        else if (sprite->getCurrentTool() == sprite::ERASER) {
            erasePixel(x, y);
        }
        else if (sprite->getCurrentTool() == sprite::SELECTOR) {
            originPoint = mouseEvent->screenPos();
            originCropPoint = mouseEvent->scenePos();

            rBand = new QRubberBand(QRubberBand::Rectangle);
        }
    }
}

void scene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    int x = mouseEvent->scenePos().x()/pixelSize;
    int y = mouseEvent->scenePos().y()/pixelSize;

    if (x >= 0 && x < frameSize/pixelSize && y < frameSize/pixelSize && y >= 0) // TODO: WIDTH/HEIGHT HANDLING
    {
        if (sprite->getCurrentTool() == sprite::BRUSH) {
            drawPixel(x, y);
        }
        else if (sprite->getCurrentTool() == sprite::ERASER) {
            erasePixel(x, y);
        }
        else if (sprite->getCurrentTool() == sprite::SELECTOR) {
//            rBand->setGeometry(QRect(origin, mouseEvent->scenePos()));
            rBand->setGeometry(QRect(originPoint, mouseEvent->screenPos()));
            rBand->show();
        }
    }
}

void scene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    if (sprite->getCurrentTool() == sprite::SELECTOR) {
        if (!copyImage.isNull()) {
            deselectArea();
        }
        rBand->hide();
        QRect convertedRect = rBand->geometry();
        convertedRect = QRect(originCropPoint.toPoint(), mouseEvent->scenePos().toPoint());
        convertedRect.getCoords(&slcX1, &slcY1, &slcX2, &slcY2);
        slcX1 = slcX1/pixelSize;
        slcY1 = slcY1/pixelSize;
        slcX2 = slcX2/pixelSize+1;
        slcY2 = slcY2/pixelSize+1;
        std::cout << slcX1 << "," << slcY1 << " " << slcX2 << "," << slcY2 << std::endl;
        outlineSelected(slcX1, slcY1, slcX2, slcY2);
    }
}

void scene::outlineSelected(int x1, int y1, int x2, int y2) {
    copyImage = image->copy();
    QPainter painter(image);
    painter.setPen(Qt::DashLine);
    painter.setBrush(Qt::transparent);
    painter.drawRect(x1*pixelSize, y1*pixelSize, (x2-x1)*pixelSize, (y2-y1)*pixelSize);
    this->addPixmap(QPixmap::fromImage(*image));
}

void scene::deselectArea() {
    this->clear();
    *image = copyImage.copy();
    this->addPixmap(QPixmap::fromImage(copyImage));
    delete copyImage;
}

void scene::cropArea() {
    rBand->hide();
    //QImage copy;
//    QImage* copyImage = new QImage(frameSize, frameSize, QImage::Format_ARGB32);

//    QRect rect = rBand->geometry().normalized();
//    std::cout << x1 << "," << y1 << " " << x2 << "," << y2 << std::endl;
//    QPainter testPainter(copy);
//    this->addPixmap(QPixmap::fromImage(*copy));
//    *copy = image->copy(QRectF(rect.topLeft(), rect.topRight()).toRect());
//    *image = *copy;
//    this->setSelectionArea(selectionArea, rBand->geometry().normalized());

//    this->erasePixel(x1, y1);
//    this->erasePixel(x2, y2);
}

void scene::fillArea() {
    for(int i = slcX1; i < slcX2; i++) {
        for(int j = slcY1; j < slcY2; j++) {
            this->drawPixel(i, j);
        }
    }
}



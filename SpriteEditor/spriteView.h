#ifndef SPRITEVIEW_H
#define SPRITEVIEW_H

#include <QMainWindow>
#include <QColorDialog>
#include <QColor>
#include "scene.h"
#include "frame.h"
#include "sprite.h"

QT_BEGIN_NAMESPACE
namespace Ui { class SpriteEditor; }
QT_END_NAMESPACE

class SpriteEditor : public QMainWindow
{
    Q_OBJECT

public:
    SpriteEditor(QWidget *parent = nullptr);
    ~SpriteEditor();

private slots:
    void on_colorButton_clicked();
    void on_setSizeButton_clicked();

    void on_newFrameButton_clicked();

    void on_brushButton_clicked();
    void on_eraserButton_clicked();

    void on_selectToolButton_clicked();

    void on_cropButton_clicked();

    void on_fillAreaButton_clicked();

private:
    Ui::SpriteEditor *ui;
    scene* scenes;
    sprite ourSprite;
};
#endif // SPRITEVIEW_H

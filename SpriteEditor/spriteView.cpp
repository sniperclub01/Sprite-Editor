#include "spriteView.h"
#include "ui_spriteView.h"

SpriteEditor::SpriteEditor(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SpriteEditor)
{
    ui->setupUi(this);
    ui->colorButton->setVisible(false);
    ui->newFrameButton->setVisible(false);
    ui->newFrameCopyButton->setVisible(false);
    ui->pauseButton->setVisible(false);
    ui->playButton->setVisible(false);
    ui->drawingView->setVisible(false);
    ui->previewWindow->setVisible(false);
    ui->brushButton->setVisible(false);
    ui->eraserButton->setVisible(false);
    ui->selectToolButton->setVisible(false);
    ui->cropAreaButton->setVisible(false);
    ui->fillAreaButton->setVisible(false);

    // Scene handling (needs work!)
    scenes = new scene(&ourSprite, ui->drawingView);

    ui->drawingView->setScene(scenes);


}

SpriteEditor::~SpriteEditor()
{
    delete ui;
}



void SpriteEditor::on_colorButton_clicked()
{
    QColor color = QColorDialog::getColor(Qt::white, this, "Choose Color");
    if (color.isValid()) {
        this->ourSprite.setBrushColor(color);
    }
    //scenes->deselectArea();
}


void SpriteEditor::on_setSizeButton_clicked()
{
    int size = ui->setSizeSpinBox->value();
    this->ourSprite.setSpriteSize(size);
    scenes->setSpriteSize(size);
    std::cout << "Sprite size: " << size << std::endl;
    ui->setSizeButton->setVisible(false);
    ui->setSizeSpinBox->setVisible(false);
    ui->setSizeLabel->setVisible(false);
    ui->colorButton->setVisible(true);
    ui->newFrameButton->setVisible(true);
    ui->newFrameCopyButton->setVisible(true);
    ui->pauseButton->setVisible(true);
    ui->playButton->setVisible(true);
    ui->drawingView->setVisible(true);
    ui->previewWindow->setVisible(true);
    ui->brushButton->setVisible(true);
    ui->brushButton->setChecked(true);
    ui->brushButton->setChecked(true);
    ui->eraserButton->setVisible(true);
    ui->eraserButton->setChecked(false);
    ui->selectToolButton->setVisible(true);
    ui->cropAreaButton->setVisible(true);
    ui->fillAreaButton->setVisible(true);

    std::cout << "Size set" << std::endl;
}


void SpriteEditor::on_newFrameButton_clicked()
{
    std::cout << "new frame clicked" << std::endl;
    this->ourSprite.addImage(this->scenes->getCurrImage());
    this->scenes->prepareScene();
    //scenes->deselectArea();
}


void SpriteEditor::on_brushButton_clicked()
{
    ourSprite.setCurrentTool(sprite::BRUSH);
    ui->brushButton->setChecked(true);
    ui->eraserButton->setChecked(false);
    ui->selectToolButton->setChecked(false);
    //scenes->deselectArea();
}


void SpriteEditor::on_eraserButton_clicked()
{
    ourSprite.setCurrentTool(sprite::ERASER);
    ui->brushButton->setChecked(false);
    ui->eraserButton->setChecked(true);
    ui->selectToolButton->setChecked(false);
    //scenes->deselectArea();
}


void SpriteEditor::on_selectToolButton_clicked()
{
    ourSprite.setCurrentTool(sprite::SELECTOR);
    ui->brushButton->setChecked(false);
    ui->eraserButton->setChecked(false);
    ui->selectToolButton->setChecked(true);
}


void SpriteEditor::on_cropButton_clicked()
{
    scenes->cropArea();
    //scenes->deselectArea();
}


void SpriteEditor::on_fillAreaButton_clicked()
{
    scenes->fillArea();
    //scenes->deselectArea();
}


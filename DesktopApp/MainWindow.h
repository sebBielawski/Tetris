#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QTimer>
#include <QPixmap>
#include <QMainWindow>

#include "../Core/Game.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow, public Game
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    virtual void keyPressEvent(QKeyEvent* event) override;
    ~MainWindow();

protected:
    virtual int playfieldRectHeight() const override;
    virtual int playfieldRectWidth() const override;
    virtual void drawBackground() override;
    virtual void drawPlayfieldCell(CellId id, int x, int y, int w, int h) override;
    virtual void updateGraphics() override;
    virtual void onLines(size_t lineCount) override;
    virtual void onGameOver() override;

private slots:
    void onTimerTimeout();

    void on_startButton_clicked();

private:
    size_t _lineCount = 0;
    QTimer _timer;
    QPixmap _pixmap;
    Ui::MainWindow* _ui;
};

#endif // MAINWINDOW_H

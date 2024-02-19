#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QKeyEvent>
#include <QPainter>
#include <QColor>
#include <QRect>
#include <QMap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    _ui(new Ui::MainWindow())
{ 
    _ui->setupUi(this);

    Q_ASSERT(_ui->playfieldWidget != nullptr);
    _pixmap = QPixmap(
        _ui->playfieldWidget->width(),
        _ui->playfieldWidget->height());

    Q_ASSERT(_ui != nullptr);
    Q_ASSERT(_ui->lineCountLabel != nullptr);
    _ui->lineCountLabel->setText(QString("Lines : %1").arg(_lineCount));

    Q_ASSERT(_ui != nullptr);
    Q_ASSERT(_ui->gameOverLabel != nullptr);
    _ui->gameOverLabel->hide();
    _ui->gameOverLabel->setStyleSheet("QLabel { background-color : white; color : red; }");

    draw();
}

MainWindow::~MainWindow()
{
    delete _ui;
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    switch (event->key()) {
    case Qt::Key_Left:
        leftShift();
        break;
    case Qt::Key_Right:
        rightShift();
        break;
    case Qt::Key_Down:
        softDrop();
        break;
    case Qt::Key_Up:
        rotateClockwise();
        break;
    case Qt::Key_Space:
        hardDrop();
        break;
    case Qt::Key::Key_P:
        _timer.isActive() ? _timer.stop() : _timer.start();
       break;
    }
    QMainWindow::keyPressEvent(event);
}

int MainWindow::playfieldRectHeight() const
{
    Q_ASSERT(_ui != nullptr);
    Q_ASSERT(_ui->playfieldWidget != nullptr);
    return _ui->playfieldWidget->rect().height();
}

int MainWindow::playfieldRectWidth() const
{
    Q_ASSERT(_ui != nullptr);
    Q_ASSERT(_ui->playfieldWidget != nullptr);
    return _ui->playfieldWidget->rect().width();
}

void MainWindow::drawBackground()
{
    _pixmap.fill(QColor(Qt::GlobalColor::black));
}

void MainWindow::drawPlayfieldCell(CellId id, int x, int y, int w, int h)
{
    Q_ASSERT(_ui != nullptr);
    QMap<CellId, QColor> m {
        { CellId::I, QColor(Qt::GlobalColor::cyan) },
        { CellId::J, QColor(Qt::GlobalColor::darkBlue) },
        { CellId::L, QColor(255, 140, 0) }, // orange
        { CellId::Locked, QColor(Qt::GlobalColor::gray) },
        { CellId::O, QColor(Qt::GlobalColor::yellow) },
        { CellId::S, QColor(Qt::GlobalColor::green) },
        { CellId::T, QColor(Qt::GlobalColor::magenta) },
        { CellId::Z, QColor(Qt::GlobalColor::red) }
    };

    auto it = m.find(id);
    Q_ASSERT(it != m.end());
    QPainter painter(&_pixmap);
    painter.fillRect(QRect(x, y, w, h), *it);
}

void MainWindow::onTimerTimeout()
{
    softDrop();
}

void MainWindow::updateGraphics()
{
    Q_ASSERT(_ui != nullptr);
    Q_ASSERT(_ui->playfieldWidget != nullptr);
    _ui->playfieldWidget->setPixmap(_pixmap);
}

void MainWindow::on_startButton_clicked()
{
    Q_ASSERT(_ui != nullptr);
    Q_ASSERT(_ui->startButton != nullptr);
    _ui->startButton->setEnabled(false);

    connect(&_timer, &QTimer::timeout, this, &MainWindow::onTimerTimeout);
    _timer.setTimerType(Qt::TimerType::PreciseTimer);
    _timer.setSingleShot(false);
    _timer.start(500);
    draw();
}

void MainWindow::onLines(size_t lineCount)
{
    _lineCount += lineCount;
    Q_ASSERT(_ui != nullptr);
    Q_ASSERT(_ui->lineCountLabel != nullptr);
    _ui->lineCountLabel->setText(QString("Lines : %1").arg(_lineCount));
}

void MainWindow::onGameOver()
{
    Q_ASSERT(_ui != nullptr);
    Q_ASSERT(_ui->gameOverLabel != nullptr);
    _ui->gameOverLabel->show();
    _timer.stop();
}



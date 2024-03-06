#include "joystick.h"

#include <QPainter>
#include <QtCore>
#include <QtGui>
#include <QPen>
#include <QBrush>
#include <QColor>
#include <QDebug>

void Joystick::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QRectF bounds = QRectF(-this->maxDistance, -this->maxDistance, this->maxDistance * 2, this->maxDistance * 2).translated(this->center());
    painter.drawEllipse(bounds);
    painter.setBrush(QColor("black"));
    painter.drawEllipse(this->centerEllipse());
}

QRectF Joystick::centerEllipse()
{
    if (this->grabCenter)
        return QRectF(-20, -20, 40, 40).translated(this->movingOffset);
    return QRectF(-20, -20, 40, 40).translated(this->center());
}

QPointF Joystick::center()
{
    return QPointF(this->width()/ 2, this->height() / 2);
}

QPointF Joystick::boundJoystick(QPointF point)
{
    QLineF limitLine = QLineF(this->center(), point);
    if (limitLine.length() > this->maxDistance) {
        limitLine.setLength(this->maxDistance);
    }
    return limitLine.p2();
}

std::pair<Direction, qreal> Joystick::joystickDirection()
{
    if (!this->grabCenter) {
        std::pair<Direction, int> myPair = std::make_pair(Direction::Left, 0);
        return myPair;
    }
    QLineF normVector = QLineF(this->center(), this->movingOffset);
    qreal currentDistance = normVector.length();
    qreal angle = normVector.angle();

    qreal distance = qMin(currentDistance / this->maxDistance, 1.0);
    if (45 <= angle && angle < 135) {
        std::pair<Direction, int> myPair = std::make_pair(Direction::Up, distance);
        return myPair;
    } else if (135 <= angle && angle < 225) {
        std::pair<Direction, int> myPair = std::make_pair(Direction::Left, distance);
        return myPair;
    } else if (225 <= angle && angle < 315) {
        std::pair<Direction, int> myPair = std::make_pair(Direction::Down, distance);
        return myPair;
    } else {
        std::pair<Direction, int> myPair = std::make_pair(Direction::Right, distance);
        return myPair;
    }
}

void Joystick::mousePressEvent(QMouseEvent *event)
{
    QWidget::mousePressEvent(event);
    this->grabCenter = this->centerEllipse().contains(event->pos());
}

void Joystick::mouseReleaseEvent(QMouseEvent *event)
{
    this->grabCenter = false;
    this->movingOffset = QPointF(0, 0);
    this->update();
}

void Joystick::mouseMoveEvent(QMouseEvent *event)
{
    if (this->grabCenter) {
        qDebug() << "Moving";
        this->movingOffset = this->boundJoystick(event->pos());
        this->update();
    }
    std::pair<Direction, qreal> result = this->joystickDirection();
    Direction dir = result.first;
    qreal value = result.second;

    qDebug() << "Direction:";
    switch (dir) {
    case Direction::Left:
        qDebug() << "Left";
        break;
    case Direction::Right:
        qDebug() << "Right";
        break;
    case Direction::Up:
        qDebug() << "Up";
        break;
    case Direction::Down:
        qDebug() << "Down";
        break;
    }
    qDebug() << "Value:" << value;
}

Joystick::Joystick(QWidget *parent)
    : QWidget(parent)
{
    this->setMinimumSize(100, 100);
    this->movingOffset = QPointF(0, 0);
    this->grabCenter = false;
    this->maxDistance = 50;
}



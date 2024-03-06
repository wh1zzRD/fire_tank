#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <QWidget>

enum class Direction {
    Left = 0,
    Right = 1,
    Up = 2,
    Down = 3
};

class Joystick: public QWidget {
    Q_OBJECT

private:
    QPointF movingOffset;
    bool grabCenter;
    qreal maxDistance;

    virtual void paintEvent(QPaintEvent *event) override;
    QRectF centerEllipse();
    QPointF center();
    QPointF boundJoystick(QPointF point);
    std::pair<Direction, qreal> joystickDirection();

    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

public:
    Joystick(QWidget *parent);
};

#endif // JOYSTICK_H

#include "QColorBox.h"


#include <QPainter>


QColorBox::QColorBox(QWidget * parent)
    :   QColorBox(Qt::white, parent)
{
}

QColorBox::QColorBox(QColor const & color, QWidget* parent)
    :   QWidget(parent),
        mBrush(color),
        mPen(Qt::transparent, 0.0)
{
}

QColor QColorBox::color() const
{
    return mBrush.color();
}

QPen QColorBox::pen() const
{
    return mPen;
}

void QColorBox::setColor(QColor const & color)
{
    mBrush = color;
    update();
}

void QColorBox::setPen(QPen const & pen)
{
    mPen = pen;
    update();
}

void QColorBox::paintEvent(QPaintEvent * event)
{
    QPainter painter(this);

    if (isEnabled()) {
        painter.setBrush(mBrush);
        painter.setPen(mPen);
    } else {
        painter.setBrush(palette().brush(QPalette::Disabled, QPalette::Window));
        painter.setPen(palette().brush(QPalette::Disabled, QPalette::WindowText).color());
    }

    painter.drawRect(rect());
}

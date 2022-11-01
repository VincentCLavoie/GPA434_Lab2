#pragma once


#include <QWidget>
#include <QBrush>
#include <QPen>


class QColorBox : public QWidget
{
    Q_OBJECT

public:
    QColorBox(QWidget * parent = nullptr);
    QColorBox(QColor const & color, QWidget * parent = nullptr);

    QColor color() const;
    QPen pen() const;

    void setColor(QColor const & color);
    void setPen(QPen const & pen);

protected:
    void paintEvent(QPaintEvent * event) override;

private:
    QBrush mBrush;
    QPen mPen;
};


#pragma once



#include "QInteractiveMousePainterWidget.h"



class QInteractiveImageViewer : public QInteractiveMousePainterWidget
{
    Q_OBJECT

public:
    QInteractiveImageViewer(QWidget * parent = nullptr);
    ~QInteractiveImageViewer() = default;

    QImage image() const;
    QPixmap pixmap() const;

    virtual void setImage(QImage const & image);
    virtual void setPixmap(QPixmap const & image);
    
    virtual void clear();

    void fit();

    void setBackground(QBrush const & brush, QPen const & pen);

protected:
    void prePaint(QPainter & painter) override;
    void paint(QPainter & painter) override;

    void keyPressEvent(QKeyEvent * event) override;
    void resizeEvent(QResizeEvent * event) override;

private:
    bool mAutoFit;
    QBrush mBackgroundBrush;
    QPen mBackgroundPen;
    QPixmap mImage;

    void autoFit();
};

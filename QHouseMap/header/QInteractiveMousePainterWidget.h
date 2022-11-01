#pragma once


#include <QWidget>
#include <QPainter>
#include <QGraphicsAnchorLayout>


class QInteractiveMousePainterWidget : public QWidget
{
    Q_OBJECT

public:
    QInteractiveMousePainterWidget(QWidget * parent = nullptr);
    ~QInteractiveMousePainterWidget();

    QPoint currentMouseOnScreen() const;
    QPointF currentMouseOnPainter() const;

    int currentScale() const;
    qreal currentScaleFactor() const;
    qreal currentOrientationInDegrees() const;

    QPointF mapPainterToScreen(QPoint const & point);
    QPoint mapScreenToPainter(QPointF const & point);

    void center(QPointF const & position);
    void center(QSizeF const & size);
    void center(QRectF const & rectangle);

    void fit(QRectF const & rectangle);

    // %m = mouse screen position
    // %M = mouse painter position
    // %s = scale
    // %f = scale factor
    // %r = rotation
    void addOverlayInformation(QString const & format); // 
    void clearOverlay();
    void setShowOverlay(bool show);
    void setOverlayUniformWidth(bool uniformWidth);

    void setOverlayFormat(QPen const & boxPen, QBrush const & boxBrush, QPen textPen);

    class CustomOverlay
    {
    public:
        virtual QString updateInfo(QInteractiveMousePainterWidget * widget) = 0;
    };
    void setCustomOverlay(CustomOverlay * customOverlay);
    void clearCustomOverlay();

protected:
    virtual void prePaint(QPainter & painter);
    virtual void paint(QPainter & painter);
    virtual void postPaint(QPainter & painter);

    void paintEvent(QPaintEvent * event) override;

    void keyPressEvent(QKeyEvent * event) override;
    void keyReleaseEvent(QKeyEvent * event) override;
    void mouseMoveEvent(QMouseEvent * event) override;
    void mousePressEvent(QMouseEvent * event) override;
    void mouseReleaseEvent(QMouseEvent * event) override;
    void mouseDoubleClickEvent(QMouseEvent * event) override;
    void wheelEvent(QWheelEvent * event) override;

private:
    enum class MouseActivity{ None, Translate, Rotate };

    MouseActivity mMouseActivity;       // Describe current mouse state
    QPainter mPainter;                  // The painter to draw
    QPoint mMouseScreen;                // The last mouse coordinate                        [widget space]      always available while the mouse is on the application
    QPointF mMousePainter;              // The last mouse coordinate                        [painter space]     always available while the mouse is on the application
    QPoint mMouseDownScreen;            // The last mouse pressed event mouse coordinate    [widget space]
    QPoint mScreenTarget;               // The target point                                 [widget space]
    QPointF mPainterTarget;             // The target point                                 [painter space]
    qreal mPainterScale;                // The target scale factor                          [painter space]
    qreal mPainterRotation;             // The target rotation angle                        [painter space]
    qreal mScaleFactor;                 // The scale factor x from 2^x

    QTransform mScreenToPainterTransform;
    QTransform mPainterToScreenTransform;

    void registerCurrentMousePos(QPoint const & position);
    void processTransform(bool doUpdate);

    //-----
    bool mShowOverlay;
    bool mOverlayUniformWidth;
    QMargins mOverlayMargins;
    QMargins mOverlayPaddings;
    QPen mOverlayPen;
    QBrush mOverlayBrush;
    QPen mOverlayTextPen;

    struct OverlayInfo {
        QString (QInteractiveMousePainterWidget::*func)(QString const &) const;
        QString text;
    };
    QVector<QList<OverlayInfo>> mOverlays;
    QString text(QString const& text) const;
    QString mouseScreenPosition(QString const& text) const;
    QString mousePainterPosition(QString const& text) const;
    QString scale(QString const& text) const;
    QString scaleFactor(QString const& text) const;
    QString rotation(QString const& text) const;
    QStringList overlays() const;

    QScopedPointer<CustomOverlay> mCustomOverlay;
};

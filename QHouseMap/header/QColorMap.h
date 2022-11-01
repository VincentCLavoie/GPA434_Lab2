#pragma once


#include <QColor>
#include <QVector>
#include <QMap>
#include <QImage>


class QColorMap
{
public:
    enum class ColorSpace { RGB, HSL, HSV };

    QColorMap();
    ~QColorMap() = default;

    class Stop {
    public:
        Stop(qreal position = 0.0, QColor const & color = Qt::black, ColorSpace colorSpace = ColorSpace::RGB);
        ~Stop() = default;

        qreal position() const;
        QColor const& color() const;
        ColorSpace colorSpace() const;

        void setPosition(qreal position);
        void setColor(QColor const& color);
        void setColorSpace(ColorSpace colorSpace);
        void set(qreal position, QColor const& color, ColorSpace colorSpace = ColorSpace::RGB);

    private:
        ColorSpace mColorSpace;
        qreal mPosition;
        QColor mColor;
    };

    size_t stopsCount() const;
    bool isStopExist(qreal position) const;
    Stop stop(int index) const;
    Stop stop(qreal position) const;
    bool setStop(Stop const & stop);
    bool removeStop(qreal position);
    void resetStops();

    qreal gamma() const;
    void setGamma(qreal gamma);
    void resetGamma();

    qreal accessRangeMinimum() const;
    qreal accessRangeMaximum() const;
    void setAccessRangeMinimum(qreal min);
    void setAccessRangeMaximum(qreal max);
    void setAccessRange(qreal max);
    void setAccessRange(qreal min, qreal max);
    void resetAccessRange();

    size_t colorCount() const;
    void setColorCount(size_t colorCount);
    QColor const & color(size_t index) const;
    QColor const & color(qreal position) const;

    void reset();

    QImage toImage(QSize const & size, Qt::Orientation orientation = Qt::Vertical) const;

    static QColorMap default();
    static QColorMap heat();
    //static ColorMap electricBlue();
    //static ColorMap hot();
    //static ColorMap cold();

    static double linearInterpolation(double x1, double y1, double x2, double y2, double x);
    static double gammaInterpolation(double x1, double y1, double x2, double y2, double x, double gamma);

private:
    using Stops = QMap<qreal, Stop>;
    using Colors = QVector<QColor>;

    qreal mGamma;
    qreal mAccessRangeMinimum;
    qreal mAccessRangeMaximum;
    Stops mStops;
    Colors mColors;

    void rgbInterpolation(double x1, double x2, QColor const& c1, QColor const& c2, double value, QColor& color) const;
    void hsvInterpolation(double x1, double x2, QColor const& c1, QColor const& c2, double value, QColor& color) const;
    void hslInterpolation(double x1, double x2, QColor const& c1, QColor const& c2, double value, QColor& color) const;

    void buildColorMap();
};


#pragma once

#include "qhousemap_global.h"

#include "Statistics.h"
#include <QVector>
#include <QRect>
#include <QImage>

#include "AnnualWeather.h"

class HouseDevice;

class QHOUSEMAP_EXPORT QHouseMap
{
public:
    using Int = int;
    using Real = double;

    class Element {
    public:
        Element(Int id = 0);
        Element(Int id, Real dens, Real temp, Real xVel, Real yVel);

        bool isValid() const;
        static Element invalid();

        Int id{};
        Real density{};
        Real temperature{};
        Real xVelocity{};
        Real yVelocity{};
    };

    class ElementStatistics
    {
    public:
        Statistics<> const& density() const;
        Statistics<> const& temperature() const;
        Statistics<> const& xVelocity() const;
        Statistics<> const& yVelocity() const;

        void reset();
        void add(Element const& data);

    private:
        Statistics<> mDensity;
        Statistics<> mTemperature;
        Statistics<> mXVelocity;
        Statistics<> mYVelocity;
    };

    using StatisticsHistory = QVector<ElementStatistics>;

    class IdInfo
    {
    public:
        IdInfo(size_t size = 2);

        void setTemperatureDiffusionCoeff(int idFrom, int idTo, Real coef);
        void setTemperatureDiffusionCoeff(QVector<QVector<Real>> const& coeffs, bool applySymmetry = false);

        size_t size() const;

        QVector<Real> const& temperatureCoeffFrom(int idFrom) const;
        double temperatureCoeffFrom(int idFrom, int idTo) const;

        QString const& name(int id) const;
        bool setNames(QVector<QString> const& names);

        QColor const& color(int id) const;
        bool setColors(QVector<QColor> const& colors);

        ElementStatistics const& statistics(int id) const;
        StatisticsHistory const& statsHistory(int id) const;
        void logHistory();
        void clearHistory();
        void resetStat();
        void addStat(Element const& data);

    private:
        size_t mSize;

        QVector<QString> mNames;
        QVector<QColor> mColors;
        QVector<ElementStatistics> mStats;
        QVector<StatisticsHistory> mStatsHistory;
        QVector<QVector<Real>> mTemperatureDiffusionCoeffs;

        void setCoeffsIdentity();
    };


    class Map
    {
    public:
        bool isValid() const;
        QSize size() const;
        QRect rect() const;
        QRect userRect() const;

        void resize(QSize const& size);
        void clear();

        Element const& data(int x, int y) const;
        Element const& data(QPoint const& position) const;
        void set(int x, int y, Element const& data);
        void set(QPoint const& position, Element const& data);

        void set(Element const& data);
        void set(QRect const& rect, Element const& data);
        void setHorizontalLine(QPoint const& position, int length, Element const& data, size_t halfWidth = 0);
        void setVerticalLine(QPoint const& position, int length, Element const& data, size_t halfWidth = 0);
        void setRectangleOutline(QRect const& rect, Element const& data, size_t halfWidth = 0);
        void setRectangle(QRect const& rect, Element const& outlineData, Element const& areaData, size_t halfWidth = 0);

        bool set(QImage const& image, QVector<QPair<int, QPair<QString, QColor>>> const& idInfoMapping);

        QImage imageId() const;

    private:
        Map(IdInfo& idInfo);
        ~Map();

        static const Element mInvalidData;
        static QSize const mMinSize, mMaxSize;
        IdInfo* mIdInfo;
        QSize mSize;
        QRect mRect;
        QRect mUserRect;
        QVector<Element> mData;

        inline bool clip(int x, int y) const { return x < mRect.left() || x > mRect.right() || y < mRect.top() || y > mRect.bottom(); }
        inline bool clip(QPoint const& position) const { return !mRect.contains(position); }
        inline bool clipUser(int x, int y) const { return x < mUserRect.left() || x > mUserRect.right() || y < mUserRect.top() || y > mUserRect.bottom(); }
        inline bool clipUser(QPoint const& position) const { return !mUserRect.contains(position); }

        inline int _offset(int x, int y) const { return x + y * mSize.width(); }
        inline int _offset(QPoint const& position) const { return _offset(position.x(), position.y()); }
        inline Element& _data(int x, int y) { return mData[_offset(x, y)]; }
        inline Element const& _data(int x, int y) const { return mData[_offset(x, y)]; }
        inline Element& _data(QPoint const& position) { return _data(position.x(), position.y()); }
        inline Element const& _data(QPoint const& position) const { return _data(position.x(), position.y()); }

        void _set(Element const& data);
        void _set(QRect const& rect, Element const& data, QRect const& refRect);
        void _setHorizontalLine(QPoint const& position, int length, Element const& data, QRect const& refRect, size_t halfWidth = 0);
        void _setVerticalLine(QPoint const& position, int length, Element const& data, QRect const& refRect, size_t halfWidth = 0);
        void _setRectangleOutline(QRect const& rect, Element const& data, QRect const& refRect, size_t halfWidth = 0);
        void _setRectangle(QRect const& rect, Element const& outlineData, Element const& areaData, QRect const& refRect, size_t halfWidth = 0);

        inline void _set(QRect const& rect, Element const& data) { _set(rect, data, mRect); }
        inline void _setHorizontalLine(QPoint const& position, int length, Element const& data, size_t halfWidth = 0) { _setHorizontalLine(position, length, data, mRect, halfWidth); }
        inline void _setVerticalLine(QPoint const& position, int length, Element const& data, size_t halfWidth = 0) { _setVerticalLine(position, length, data, mRect, halfWidth); }
        inline void _setRectangleOutline(QRect const& rect, Element const& data, size_t halfWidth = 0) { _setRectangleOutline(rect, data, mRect, halfWidth); }
        inline void _setRectangle(QRect const& rect, Element const& outlineData, Element const& areaData, size_t halfWidth = 0) { _setRectangle(rect, outlineData, areaData, mRect, halfWidth); }

        friend class QHouseMap;
        friend class HouseDevice;
    };

    QHouseMap();
    ~QHouseMap();

    IdInfo const& idInfo() const;

    bool isValid() const;
    Map& initializationMap();

    bool process(int nTimes = 1);

    Map const& curMap() const;
    ElementStatistics const& globalStatistics() const;
    StatisticsHistory const& globalStatHistory() const;

    void reset();

    bool processExternalTemperature() const;
    void setProcessExternalTemperature(bool process);

    int ticCount() const;
    double elapsedTime() const;
    QString elapsedTimeString() const;

    double actualTemperature() const;

    void setAnnualWeather(AnnualWeather* annualWeather);

    size_t deviceCount() const;
    bool addDevice(HouseDevice* houseDevice);
    HouseDevice const& device(size_t index) const;

protected:
    IdInfo mIdInfo;
    Map mInitMap;
    bool mProcessExternalTemperature{ true };
    int mTicCount;

    Map mCurMap;
    Map mProcessMap;
    ElementStatistics mGlobalStatistics;
    StatisticsHistory mGlobalStatHistory;

    AnnualWeather* mAnnualWeather;
    std::vector<HouseDevice*> mHouseDevices;

private:
    void setIdTemperature(int id, double temperature);
    void heatDiffusion(double diffusionWeight = 1.0);
    void swapProcessBuffer();

    void processStatistics();

    friend class HouseDevice;
};



#include "QInteractiveDataViewer.h"

class HouseDataProxy : public QInteractiveDataViewer::DataProxy
{
public:
    HouseDataProxy(QHouseMap& mapData) : mMapData{ mapData } {}

    bool isValid() const override { return mMapData.curMap().isValid(); }
    QSize size() const override { return mMapData.curMap().size(); }

protected:
    QHouseMap & mMapData;
};

class HouseTemperatureDataProxy : public HouseDataProxy
{
public:
    HouseTemperatureDataProxy(QHouseMap& mapData) : HouseDataProxy(mapData) {}

    qreal data(int x, int y) const override { return mMapData.curMap().data(x, y).temperature; }
    qreal min() const override { return mMapData.globalStatistics().temperature().min(); }
    qreal max() const override { return mMapData.globalStatistics().temperature().max(); }
};



class House1 : public QHouseMap
{
public:
    House1();
};

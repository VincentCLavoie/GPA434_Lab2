#pragma once



#include <QString>
#include <QWidget>
#include "QHouseMap.h"


// Forward declaration
class QDeviceHMI;

//
class HouseDevice
{
public:
    HouseDevice(QHouseMap & house);

    bool isValid() const;

    bool isPowerOn() const;
    bool isPowerOff() const;
    void setPower(bool powerIsOn);
    void togglePower();

    QPoint position() const;
    QRect rect() const;
    QColor color() const;

    QString userName() const;
    void setUserName(QString const & userName);

    void setPosition(QPoint const & position);
    void setColor(QColor const & color);

    virtual QSize size() const = 0;
    virtual QString deviceName() const = 0;

    virtual QDeviceHMI * createHMI() = 0;

    void drawOn(QPainter & painter) const;

protected:
    QHouseMap::Element const & getElement(QPoint const & position) const;
    void setTemperature(QPoint const & position, double temperature);

private:
    QHouseMap & mHouse;
    bool mPowerOn;
    QPoint mPosition;
    QRect mRect;
    QColor mColor;
    QString mUserName;

    void updateRect();
};


// Définition de la classe intéractive HMI
// Cette classe est conçue pour un assemblage de widgets.
class QDeviceHMI : public QWidget
{
    Q_OBJECT

public:
    QDeviceHMI(HouseDevice & houseDevice);

    virtual void updateDevice() = 0;

protected:
    HouseDevice & mHouseDevice;
};


// Définition de la classe intéractive HMI
// Cette classe est conçue pour du dessin personnalisé.
class QPaintDeviceHMI : public QDeviceHMI
{
    Q_OBJECT

public:
    QPaintDeviceHMI(HouseDevice & houseDevice);

protected:
    void updateDevice() final;
    void paintEvent(QPaintEvent * event) override;

    virtual void paint(QPainter & painter) = 0;
};


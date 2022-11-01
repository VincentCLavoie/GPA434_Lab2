#include "EzHomeSens200.h"







EzHomeSens200::EzHomeSens200(QHouseMap & house)
    : SinglePointTemperatureSensor(house)
{
}

QString EzHomeSens200::deviceName() const
{
    return QString("EzHomeSens200");
}

QDeviceHMI* EzHomeSens200::createHMI()
{
    return new EzHomeSens200HMI(*this);
}





#include <QVBoxLayout>

EzHomeSens200HMI::EzHomeSens200HMI(EzHomeSens200 & device)
    :   QDeviceHMI(device),
        mPowerStateLabel{ new QLabel },
        mPowerOffButton{ new QPushButton("Turn off") },
        mPowerOnButton{ new QPushButton("Turn on") },
        mTempLCDNumber{ new QLCDNumber }
{
    QHBoxLayout* buttonLayout{ new QHBoxLayout };
    buttonLayout->addWidget(mPowerOffButton);
    buttonLayout->addWidget(mPowerOnButton);

    QVBoxLayout* mainLayout{ new QVBoxLayout };
    mainLayout->addWidget(mPowerStateLabel);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addWidget(mTempLCDNumber);
    mainLayout->addStretch();

    mPowerStateLabel->setAlignment(Qt::AlignCenter);
    mTempLCDNumber->setDigitCount(5);
    mTempLCDNumber->setFixedHeight(50);
    mTempLCDNumber->setSegmentStyle(QLCDNumber::Flat);

    setLayout(mainLayout);

    connect(mPowerOffButton, &QPushButton::clicked, this, &EzHomeSens200HMI::turnOff);
    connect(mPowerOnButton, &QPushButton::clicked, this, &EzHomeSens200HMI::turnOn);

    updateDevice();
}

void EzHomeSens200HMI::updateDevice()
{
    mPowerStateLabel->setText(mHouseDevice.isPowerOn() ? "Device is ON" : "Device is OFF");
    mPowerOffButton->setEnabled(mHouseDevice.isPowerOn());
    mPowerOnButton->setEnabled(mHouseDevice.isPowerOff());
    mTempLCDNumber->display(mHouseDevice.isPowerOn() ? static_cast<HouseSensor&>(mHouseDevice).measure() : 0.0);
}

void EzHomeSens200HMI::turnOn()
{
    mHouseDevice.setPower(true);
    updateDevice();
}
void EzHomeSens200HMI::turnOff()
{
    mHouseDevice.setPower(false);
    updateDevice();
}






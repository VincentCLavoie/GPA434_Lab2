#include "EzHomeThermal200.h"




EzHomeThermal200::EzHomeThermal200(QHouseMap& house)
    : OnOffHeatPump(house)
{
}

QSize EzHomeThermal200::size() const
{
    return QSize(3, 3);
}

QString EzHomeThermal200::deviceName() const
{
    return QString("EzHomeThermal200");
}

QDeviceHMI* EzHomeThermal200::createHMI()
{
    return new EzHomeThermal200HMI(*this);
}



#include <QLayout>



EzHomeThermal200HMI::EzHomeThermal200HMI(EzHomeThermal200 & device)
    :   QDeviceHMI(device),
        mPowerStateLabel{ new QLabel },
        mActiveStateLabel{ new QLabel },
        mPowerOffButton{ new QPushButton("Power Off") },
        mPowerOnButton{ new QPushButton("Power On") },
        mActiveOffButton{ new QPushButton("Deactivate") },
        mActiveOnButton{ new QPushButton("Activate") },
        mThermalSetPointSB{ new QScrollBar },
        mThermalSetPointLabel{ new QLabel }
{

    QHBoxLayout* powerLayout{ new QHBoxLayout };
    powerLayout->addWidget(mPowerOffButton);
    powerLayout->addWidget(mPowerOnButton);

    QHBoxLayout* activeLayout{ new QHBoxLayout };
    activeLayout->addWidget(mActiveOffButton);
    activeLayout->addWidget(mActiveOnButton);

    QVBoxLayout* mainLayout{ new QVBoxLayout };
    mainLayout->addWidget(mPowerStateLabel);
    mainLayout->addLayout(powerLayout);
    mainLayout->addWidget(mActiveStateLabel);
    mainLayout->addLayout(activeLayout);
    mainLayout->addWidget(mThermalSetPointLabel);
    mainLayout->addWidget(mThermalSetPointSB);
    mainLayout->addStretch();

    setLayout(mainLayout);

    mPowerStateLabel->setAlignment(Qt::AlignCenter);
    mActiveStateLabel->setAlignment(Qt::AlignCenter);
    mThermalSetPointLabel->setAlignment(Qt::AlignCenter);
    mThermalSetPointSB->setRange(-10, 50);
    mThermalSetPointSB->setOrientation(Qt::Horizontal);
    mThermalSetPointSB->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    mThermalSetPointLabel->setNum(mThermalSetPointSB->value());

    connect(mPowerOffButton, &QPushButton::clicked, this, &EzHomeThermal200HMI::turnPowerOff);
    connect(mPowerOnButton, &QPushButton::clicked, this, &EzHomeThermal200HMI::turnPowerOn);
    connect(mActiveOffButton, &QPushButton::clicked, this, &EzHomeThermal200HMI::turnActiveOff);
    connect(mActiveOnButton, &QPushButton::clicked, this, &EzHomeThermal200HMI::turnActiveOn);
    connect(mThermalSetPointSB, &QScrollBar::valueChanged, this, &EzHomeThermal200HMI::setThermalPoint);

    mThermalSetPointSB->setValue(22);

    updateDevice();
}

void EzHomeThermal200HMI::updateDevice()
{
    mPowerStateLabel->setText(mHouseDevice.isPowerOn() ? "This device is powered On" : "This device is powered Off");
    mActiveStateLabel->setText(mHouseDevice.isPowerOn() ? (static_cast<EzHomeThermal200&>(mHouseDevice).isActive() ? "Pumping heat" : "Pending") : "-");

    mPowerOffButton->setEnabled(mHouseDevice.isPowerOn());
    mPowerOnButton->setEnabled(mHouseDevice.isPowerOff());

    mActiveOffButton->setEnabled(mHouseDevice.isPowerOn() && static_cast<EzHomeThermal200&>(mHouseDevice).isActive());
    mActiveOnButton->setEnabled(mHouseDevice.isPowerOn() && !static_cast<EzHomeThermal200&>(mHouseDevice).isActive());

    mThermalSetPointSB->setEnabled(mHouseDevice.isPowerOn());
    mThermalSetPointLabel->setEnabled(mThermalSetPointSB->isEnabled());

    mThermalSetPointLabel->setText("Thermal point is set at " + QString::number(mThermalSetPointSB->value()) + "°C");
}

void EzHomeThermal200HMI::turnPowerOn()
{
    mHouseDevice.setPower(true);
    updateDevice();
}
void EzHomeThermal200HMI::turnPowerOff()
{
    mHouseDevice.setPower(false);
    updateDevice();
}
void EzHomeThermal200HMI::turnActiveOn()
{
    static_cast<EzHomeThermal200&>(mHouseDevice).setActive(true);
    updateDevice();
}
void EzHomeThermal200HMI::turnActiveOff()
{
    static_cast<EzHomeThermal200&>(mHouseDevice).setActive(false);
    updateDevice();
}
void EzHomeThermal200HMI::setThermalPoint()
{
    static_cast<EzHomeThermal200&>(mHouseDevice).setThermalSetPoint(mThermalSetPointSB->value());
    updateDevice();
}

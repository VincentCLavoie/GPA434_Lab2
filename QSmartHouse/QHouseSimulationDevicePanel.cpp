#include "QHouseSimulationDevicePanel.h"
#include "QHouseSimulationVisualisationPanel.h" //$


#include <QGridLayout>
#include <HouseDevice.h>


QHouseSimulationDevicePanel::QHouseSimulationDevicePanel(QHouseMap & houseMap, QWidget * parent)
	:	QGroupBox(parent),
		mHouseMap{ houseMap },
		mDeviceComboBox{ new QComboBox },
		mDeviceStackedWidget{ new QStackedWidget }
{
	setTitle("Dispositif");
    setMinimumWidth(250);
    setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);

    QGridLayout* frameLayout{ new QGridLayout };
    QFrame* frameWidget{ new QFrame };
    frameWidget->setLayout(frameLayout);
    frameLayout->addWidget(mDeviceStackedWidget);
    frameWidget->setFrameStyle(QFrame::Box | QFrame::Sunken);

    QVBoxLayout* deviceLayout{ new QVBoxLayout };
    setLayout(deviceLayout);
    deviceLayout->addWidget(mDeviceComboBox);
    deviceLayout->addWidget(frameWidget);
    deviceLayout->addStretch();

    connect(mDeviceComboBox, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), mDeviceStackedWidget, &QStackedWidget::setCurrentIndex);
    connect(mDeviceComboBox, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &QHouseSimulationDevicePanel::deviceChanged);
}

QHouseSimulationDevicePanel::~QHouseSimulationDevicePanel()
{
}

void QHouseSimulationDevicePanel::updateDevice()
{
    static_cast<QDeviceHMI*>(mDeviceStackedWidget->currentWidget())->updateDevice();
}

size_t QHouseSimulationDevicePanel::deviceCount() const
{
    return mHouseMap.deviceCount();
}

void QHouseSimulationDevicePanel::addDevice(HouseDevice * device)
{
    if (device && mHouseMap.addDevice(device)) {
        mDeviceComboBox->addItem(device->deviceName() + " : " + device->userName(), mDeviceComboBox->count());
        mDeviceStackedWidget->addWidget(device->createHMI());
    }
}
/*$
void QHouseSimulationDevicePanel::ConnectionCapteurs(QHouseSimulationDevicePanel val1, QHouseSimulationVisualisationPanel val2)
{
    connect(val1, deviceChanged, val2);
}
*/
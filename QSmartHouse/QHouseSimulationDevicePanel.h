#pragma once


#include <QGroupBox>
#include <QStackedWidget>
#include <QComboBox>
#include <QHouseMap.h>


class QHouseSimulationDevicePanel : public QGroupBox
{
	Q_OBJECT

public:
	QHouseSimulationDevicePanel(QHouseMap & houseMap, QWidget * parent = nullptr);
	~QHouseSimulationDevicePanel();

	size_t deviceCount() const;
	void addDevice(HouseDevice * device);
	//$void ConnectionCapteurs(QHouseSimulationDevicePanel val1, QHouseSimulationVisualisationPanel val2);

signals:
	void deviceChanged(int id);

public slots:
	void updateDevice();

private:
	QHouseMap & mHouseMap;
	QComboBox * mDeviceComboBox;
	QStackedWidget * mDeviceStackedWidget;
};

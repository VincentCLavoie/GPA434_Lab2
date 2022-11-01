#pragma once


#include <QGroupBox>
#include <QLabel>
#include <QComboBox>
#include <QHouseMap.h>


class QHouseSimulationGlobalInformationPanel : public QGroupBox
{
	Q_OBJECT

public:
	QHouseSimulationGlobalInformationPanel(QHouseMap & houseMap, QWidget * parent = nullptr);
	~QHouseSimulationGlobalInformationPanel();

public slots:
	void updateInfo();

private:
	QHouseMap & mHouseMap;
	QLabel * mElapsedTimeLabel;
	QLabel * mAmbiantTemperatureLabel;
	QLabel * mGlobalTempMinLabel;
	QLabel * mGlobalTempMaxLabel;
	QLabel * mGlobalTempAvgLabel;
	QLabel * mLocalTempMinLabel;
	QLabel * mLocalTempMaxLabel;
	QLabel * mLocalTempAvgLabel;
	QComboBox* mLocalComboBox;
};

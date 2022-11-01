#include "QHouseSimulationGlobalInformationPanel.h"


#include <QFormLayout>


QHouseSimulationGlobalInformationPanel::QHouseSimulationGlobalInformationPanel(QHouseMap & houseMap, QWidget *parent)
	:	QGroupBox(parent),
		mHouseMap{ houseMap },
		mElapsedTimeLabel{ new QLabel("-") },
		mAmbiantTemperatureLabel{ new QLabel("-") },
		mGlobalTempMinLabel{ new QLabel("-") },
		mGlobalTempMaxLabel{ new QLabel("-") },
		mGlobalTempAvgLabel{ new QLabel("-") },
		mLocalTempMinLabel{ new QLabel("-") },
		mLocalTempMaxLabel{ new QLabel("-") },
		mLocalTempAvgLabel{ new QLabel("-") },
		mLocalComboBox{ new QComboBox }
{
	setTitle("Information générale");

	QGroupBox* globalGroupBox{ new QGroupBox("Température globale") };
	QFormLayout * globalLayout{ new QFormLayout };
	globalGroupBox->setLayout(globalLayout);
	globalLayout->addRow(new QLabel("Minimum"), mGlobalTempMinLabel);
	globalLayout->addRow(new QLabel("Maximum"), mGlobalTempMaxLabel);
	globalLayout->addRow(new QLabel("Moyenne"), mGlobalTempAvgLabel);

	QGroupBox* localGroupBox{ new QGroupBox("Température locale") };
	QFormLayout* localLayout{ new QFormLayout };
	localGroupBox->setLayout(localLayout);
	localLayout->addRow(mLocalComboBox);
	localLayout->addRow(new QLabel("Minimum"), mLocalTempMinLabel);
	localLayout->addRow(new QLabel("Maximum"), mLocalTempMaxLabel);
	localLayout->addRow(new QLabel("Moyenne"), mLocalTempAvgLabel);

	QFormLayout * layout{ new QFormLayout };
	setLayout(layout);
	layout->addRow(new QLabel("Temps écoulé"), mElapsedTimeLabel);
	layout->addRow(new QLabel("Température ambiante"), mAmbiantTemperatureLabel);
	layout->addRow(globalGroupBox);
	layout->addRow(localGroupBox);

	for (int i{}; i < mHouseMap.idInfo().size(); ++i) {
		mLocalComboBox->addItem(mHouseMap.idInfo().name(i), i);
	}
	mLocalComboBox->setCurrentIndex(1);
	updateInfo();
}

QHouseSimulationGlobalInformationPanel::~QHouseSimulationGlobalInformationPanel()
{
}

void QHouseSimulationGlobalInformationPanel::updateInfo()
{
	mElapsedTimeLabel->setText(mHouseMap.elapsedTimeString());
	mAmbiantTemperatureLabel->setText(QString("%1°C").arg(mHouseMap.actualTemperature(), 0, 'f', 1));

    if (mHouseMap.globalStatistics().temperature().isValid()) {
		mGlobalTempMinLabel->setText(QString("%1°C").arg(mHouseMap.globalStatistics().temperature().min(), 0, 'f', 1));
		mGlobalTempMaxLabel->setText(QString("%1°C").arg(mHouseMap.globalStatistics().temperature().max(), 0, 'f', 1));
		mGlobalTempAvgLabel->setText(QString("%1°C").arg(mHouseMap.globalStatistics().temperature().mean(), 0, 'f', 1));
    } else {
		mGlobalTempMinLabel->setText("-");
		mGlobalTempMaxLabel->setText("-");
		mGlobalTempAvgLabel->setText("-");
    }
    if (mHouseMap.idInfo().statistics(mLocalComboBox->currentData().toInt()).temperature().isValid()) {
		mLocalTempMinLabel->setText(QString("%1°C").arg(mHouseMap.idInfo().statistics(mLocalComboBox->currentData().toInt()).temperature().min(), 0, 'f', 1));
		mLocalTempMaxLabel->setText(QString("%1°C").arg(mHouseMap.idInfo().statistics(mLocalComboBox->currentData().toInt()).temperature().max(), 0, 'f', 1));
		mLocalTempAvgLabel->setText(QString("%1°C").arg(mHouseMap.idInfo().statistics(mLocalComboBox->currentData().toInt()).temperature().mean(), 0, 'f', 1));
    } else {
		mLocalTempMinLabel->setText("-");
		mLocalTempMaxLabel->setText("-");
		mLocalTempAvgLabel->setText("-");
    }
}

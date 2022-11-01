#pragma once


#include <QGroupBox>
#include <QButtonGroup>
#include <QRadioButton>
#include <QComboBox>
#include <QList>
#include <AnnualWeather.h>
#include <QHouseMap.h>


class QHouseSimulationTemperaturePanel : public QGroupBox
{
    Q_OBJECT

public:
    QHouseSimulationTemperaturePanel(QHouseMap & houseMap, QWidget * parent = nullptr);
    ~QHouseSimulationTemperaturePanel();

    bool add(AnnualWeather * item);

private:
    class ManualScrollBarlConstantWeatherWidget;

    QHouseMap & mHouseMap;
    QList<AnnualWeather*> mAnnualWeatherListItems;

    QButtonGroup * mButtonGroup;
    QRadioButton * mFunctionWeatherRadioButton;
    QRadioButton * mManualWeatherRadioButton;
    QComboBox * mFunctionComboBox;
    ManualScrollBarlConstantWeatherWidget * mManualScrollBarlConstantWeather;

private slots:
    void updateGui();
    void updateWeatherControl();

};


#include <QScrollBar>
#include <QLabel>

class QHouseSimulationTemperaturePanel::ManualScrollBarlConstantWeatherWidget : public QWidget, public AnnualWeather // Exemple d'héritage multiple
{
    Q_OBJECT

public:
    ManualScrollBarlConstantWeatherWidget(QWidget * parent = nullptr);

    QString name() const override;
    double temperature(size_t secondOfYear) const override;

private:
    QScrollBar * mManualTemperatureScrollBar;
    QLabel * mManualTemperatureLabel;

private slots:
    void updateTemperatureLabel();
};

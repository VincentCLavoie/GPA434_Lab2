#include "QHouseSimulationTemperaturePanel.h"


#include <QFormLayout>


QHouseSimulationTemperaturePanel::QHouseSimulationTemperaturePanel(QHouseMap & houseMap, QWidget *parent)
    :   QGroupBox(parent),
        mHouseMap{ houseMap },
        mButtonGroup{ new QButtonGroup(this) },
        mFunctionWeatherRadioButton{ new QRadioButton("Fonction") },
        mManualWeatherRadioButton{ new QRadioButton("Manuel") },
        mFunctionComboBox{ new QComboBox },
        mManualScrollBarlConstantWeather{ new ManualScrollBarlConstantWeatherWidget }
{
    setTitle("Contrôle de la température ambiante");

    mButtonGroup->setExclusive(true);
    mButtonGroup->addButton(mFunctionWeatherRadioButton, 0);
    mButtonGroup->addButton(mManualWeatherRadioButton, 1);
    mManualWeatherRadioButton->setChecked(true);

    QFormLayout * layout{ new QFormLayout };
    setLayout(layout);
    layout->addRow(mFunctionWeatherRadioButton, mFunctionComboBox);
    layout->addRow(mManualWeatherRadioButton, mManualScrollBarlConstantWeather);

    connect(mButtonGroup, static_cast<void(QButtonGroup::*)(QAbstractButton*)>(&QButtonGroup::buttonClicked), this, &QHouseSimulationTemperaturePanel::updateGui);
    connect(mFunctionComboBox, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &QHouseSimulationTemperaturePanel::updateWeatherControl);

    updateGui();
}

QHouseSimulationTemperaturePanel::~QHouseSimulationTemperaturePanel()
{
    for (auto weatherItem : mAnnualWeatherListItems) {
        delete weatherItem;
    }
}

bool QHouseSimulationTemperaturePanel::add(AnnualWeather * item)
{
    if (mAnnualWeatherListItems.contains(item)) {
        return false;
    }

    mAnnualWeatherListItems.append(item);
    mFunctionComboBox->addItem(item->name());

    updateGui();
    return true;
}

void QHouseSimulationTemperaturePanel::updateGui()
{
    mFunctionWeatherRadioButton->setEnabled(mFunctionComboBox->count() > 0);
    mFunctionComboBox->setEnabled(mButtonGroup->checkedId() == 0);
    mManualScrollBarlConstantWeather->setEnabled(mButtonGroup->checkedId() == 1);

    updateWeatherControl();
}

void QHouseSimulationTemperaturePanel::updateWeatherControl()
{
    mHouseMap.setAnnualWeather(mButtonGroup->checkedId() == 0 ? (mAnnualWeatherListItems[mFunctionComboBox->currentIndex()]) : mManualScrollBarlConstantWeather);
}






QHouseSimulationTemperaturePanel::ManualScrollBarlConstantWeatherWidget::ManualScrollBarlConstantWeatherWidget(QWidget * parent)
    :   QWidget(parent), AnnualWeather(),
        mManualTemperatureScrollBar{ new QScrollBar },
        mManualTemperatureLabel{ new QLabel }
{
    QHBoxLayout * layout{ new QHBoxLayout };
    setLayout(layout);

    layout->addWidget(mManualTemperatureScrollBar);
    layout->addWidget(mManualTemperatureLabel);

    mManualTemperatureScrollBar->setOrientation(Qt::Horizontal);
    mManualTemperatureScrollBar->setRange(-45, 45);
    mManualTemperatureScrollBar->setValue(0);
    mManualTemperatureScrollBar->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
    mManualTemperatureLabel->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);

    connect(mManualTemperatureScrollBar, &QScrollBar::valueChanged, this, &ManualScrollBarlConstantWeatherWidget::updateTemperatureLabel);

    updateTemperatureLabel();
}

QString QHouseSimulationTemperaturePanel::ManualScrollBarlConstantWeatherWidget::name() const
{
    return "Manuel";
}

double QHouseSimulationTemperaturePanel::ManualScrollBarlConstantWeatherWidget::temperature(size_t secondOfYear) const
{
    return mManualTemperatureScrollBar->value();
}

void QHouseSimulationTemperaturePanel::ManualScrollBarlConstantWeatherWidget::updateTemperatureLabel()
{
    mManualTemperatureLabel->setText(QString::number(mManualTemperatureScrollBar->value()) + "°C");
}

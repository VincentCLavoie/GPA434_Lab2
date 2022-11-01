#include "QHouseSimulationVisualisationPanel.h"


#include <QLayout>
#include "HouseDevice.h"


class DataViewOverlay : public QInteractiveMousePainterWidget::CustomOverlay
{
public:
    DataViewOverlay(QHouseMap& houseMap) : mHouseMap{ &houseMap } {}

    QString updateInfo(QInteractiveMousePainterWidget* widget) override {
        QPoint dataPosition(qRound(widget->currentMouseOnPainter().x()), qRound(widget->currentMouseOnPainter().y()));
        if (mHouseMap->curMap().rect().contains(dataPosition)) {
            return QString("(%1, %2) [%3] : %4°C")
                .arg(dataPosition.x())
                .arg(dataPosition.y())
                .arg(mHouseMap->idInfo().name(mHouseMap->curMap().data(dataPosition).id))
                .arg(mHouseMap->curMap().data(dataPosition).temperature, 0, 'f', 1);
        }

        return QString("(%1, %2) : aucune donnée").arg(dataPosition.x()).arg(dataPosition.y());
    }

private:
    QHouseMap * mHouseMap;
};


QHouseSimulationVisualisationPanel::QHouseSimulationVisualisationPanel(QHouseMap & houseMap, QWidget * parent)
    :   QWidget(parent),
        mHouseMap{ houseMap },
        mDeviceId{ -1 },
        mInteractiveDataViewer{ new QInteractiveDataViewer },
        mButtonGroup{ new QButtonGroup },
        mHousePlanRadioButton{ new QPushButton("Plan de la maison") },
        mTemperatureRadioButton{ new QPushButton("Température") }
{
    QHBoxLayout* selectionLayout{ new QHBoxLayout };
    selectionLayout->addWidget(mHousePlanRadioButton);
    selectionLayout->addWidget(mTemperatureRadioButton);

    mHousePlanRadioButton->setCheckable(true);
    mTemperatureRadioButton->setCheckable(true);
 
    mButtonGroup->setExclusive(true);
    mButtonGroup->addButton(mHousePlanRadioButton, 0);
    mButtonGroup->addButton(mTemperatureRadioButton, 1);
    mButtonGroup->button(0)->setChecked(true);
    
    QVBoxLayout* layout{ new QVBoxLayout };
    setLayout(layout);

    layout->addLayout(selectionLayout);
    layout->addWidget(mInteractiveDataViewer);

    mInteractiveDataViewer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    mInteractiveDataViewer->setMinimumSize(QSize(400, 200));
    mInteractiveDataViewer->colorMap().setStop(QColorMap::Stop(0.0, QColor(96, 0, 128), QColorMap::ColorSpace::HSV));
    mInteractiveDataViewer->colorMap().setStop(QColorMap::Stop(0.25, QColor(0, 0, 255), QColorMap::ColorSpace::HSV));
    mInteractiveDataViewer->colorMap().setStop(QColorMap::Stop(0.75, QColor(0, 255, 0), QColorMap::ColorSpace::HSV));
    mInteractiveDataViewer->colorMap().setStop(QColorMap::Stop(1.0, QColor(255, 0, 0), QColorMap::ColorSpace::HSV));
    mInteractiveDataViewer->colorMap().setAccessRange(-45.0, 45.0);
    mInteractiveDataViewer->setCustomOverlay(new DataViewOverlay(mHouseMap));

    connect(mButtonGroup, static_cast<void(QButtonGroup::*)(int)>(&QButtonGroup::buttonClicked), this, &QHouseSimulationVisualisationPanel::updateView);
    
    updateView();
}

QHouseSimulationVisualisationPanel::~QHouseSimulationVisualisationPanel()
{
}

void QHouseSimulationVisualisationPanel::updateView()
{
    switch (mButtonGroup->checkedId()) {
        case 0: {
                QImage im(mHouseMap.initializationMap().imageId());
                if (mDeviceId >= 0) {
                    QPainter painter(&im);
                    mHouseMap.device(mDeviceId).drawOn(painter);
                }
                mInteractiveDataViewer->setImage(im);
            }
            break;
        case 1:
            mInteractiveDataViewer->setData(new HouseTemperatureDataProxy(mHouseMap));
            break;
    }
}

void QHouseSimulationVisualisationPanel::setDeviceId(int id)
{
    if (id >= 0 && id < mHouseMap.deviceCount()) {
        mDeviceId = id;
    } else {
        mDeviceId = -1;
    }
        
    updateView();
}
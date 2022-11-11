#pragma once


#include <QGroupBox>
#include <QPushButton>
#include <QLabel>
#include <QScrollBar>
#include "QColorBox.h"
#include <QMessageBox.h>
#include <Qwidget.h>

#include <QHouseMap.h>
#include <QTimer>


class QHouseSimulationControlPanel : public QGroupBox
{
    Q_OBJECT
    
public:
    QHouseSimulationControlPanel(QHouseMap & houseMap, QWidget * parent = nullptr);
    ~QHouseSimulationControlPanel();

    bool isSimulationRunning() const;
    double simulationSpeed() const;

public slots:
    void startSimulation();
    void stopSimulation();
    void resetSimulation();
    void afficheAPropos();

signals:
    void simulationStarted();
    void simulationStopped();
    void simulationReset(); // English vocabulary note : reset is past tens for reset, not 'reseted'
    void simulationTicked(int numberOfSteps);

private:
    QHouseMap & mHouseMap;
    QPushButton * mStartStopButton;
    QPushButton * mResetButton;
    QColorBox * mCurrentStateColorBox;
    QScrollBar * mSpeedScrollBar;
    QLabel * mSpeedTitleLabel;
    QLabel * mSpeedValueLabel;

    QTimer mSimulationTimer;
    QPushButton* mAPropos; 
    QMessageBox* mMessage;

    void updateGui();

private slots:
    void startStopSimulation();
    void updateSimulationSpeed();
    void simulationTic();
};

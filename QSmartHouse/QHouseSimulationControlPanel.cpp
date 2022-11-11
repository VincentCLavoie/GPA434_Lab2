#include "QHouseSimulationControlPanel.h"


#include <QLayout>


QHouseSimulationControlPanel::QHouseSimulationControlPanel(QHouseMap & houseMap, QWidget * parent)
    :   QGroupBox(parent),
        mHouseMap{ houseMap },
        mStartStopButton{ new QPushButton("Démarrer") },
        mResetButton{ new QPushButton("Reprendre à zéro") },
        mCurrentStateColorBox{ new QColorBox(QColor(255, 0, 0)) },
        mSpeedScrollBar{ new QScrollBar },
        mSpeedTitleLabel{ new QLabel("Vitesse") },
        mSpeedValueLabel{ new QLabel("1x") },
        mAPropos(),
        mMessage()
{
    mCurrentStateColorBox->setFixedHeight(4);

    mSpeedTitleLabel->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
    mSpeedScrollBar->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
    mSpeedValueLabel->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
    mSpeedScrollBar->setOrientation(Qt::Horizontal);
    mSpeedScrollBar->setRange(-2, 7);
    mSpeedScrollBar->setValue(0);

    setTitle("Contrôle de la simulation");

    QVBoxLayout * controlLayout{ new QVBoxLayout };
    controlLayout->addWidget(mStartStopButton);
    controlLayout->addWidget(mCurrentStateColorBox);
    controlLayout->setSpacing(0);

    QHBoxLayout * speedLayout{ new QHBoxLayout };
    speedLayout->addWidget(mSpeedTitleLabel);
    speedLayout->addWidget(mSpeedScrollBar);
    speedLayout->addWidget(mSpeedValueLabel);

    QVBoxLayout * mainLayout{ new QVBoxLayout };
    mainLayout->addLayout(controlLayout);
    mainLayout->addLayout(speedLayout);
    mainLayout->addWidget(mResetButton);

    setLayout(mainLayout);

    updateGui();

    mSimulationTimer.setInterval(30);

    connect(mStartStopButton, &QPushButton::clicked, this, &QHouseSimulationControlPanel::startStopSimulation);
    connect(mResetButton, &QPushButton::clicked, this, &QHouseSimulationControlPanel::resetSimulation);
    connect(mSpeedScrollBar, &QScrollBar::valueChanged, this, &QHouseSimulationControlPanel::updateSimulationSpeed);
    connect(&mSimulationTimer, &QTimer::timeout, this, &QHouseSimulationControlPanel::simulationTic);
    connect(mAPropos, &QPushButton::clicked, this, &QHouseSimulationControlPanel::afficheAPropos);
}

QHouseSimulationControlPanel::~QHouseSimulationControlPanel()
{
}

bool QHouseSimulationControlPanel::isSimulationRunning() const
{
    return mSimulationTimer.isActive();
}

double QHouseSimulationControlPanel::simulationSpeed() const
{
    return std::pow(2.0, mSpeedScrollBar->value());
}

void QHouseSimulationControlPanel::startSimulation()
{
    mSimulationTimer.start();
    mStartStopButton->setText("Arrêter");
    mCurrentStateColorBox->setColor(QColor(0, 255, 0));
}

void QHouseSimulationControlPanel::stopSimulation()
{
    mSimulationTimer.stop();
    mStartStopButton->setText("Démarrer");
    mCurrentStateColorBox->setColor(QColor(255, 0, 0));
}

void QHouseSimulationControlPanel::resetSimulation()
{
    mHouseMap.reset();

    emit simulationReset();
}

void QHouseSimulationControlPanel::updateGui()
{
    if (mHouseMap.isValid()) {
        mStartStopButton->setEnabled(true);
        mResetButton->setEnabled(true);
        mCurrentStateColorBox->setEnabled(true);
        mSpeedScrollBar->setEnabled(true);
        mSpeedTitleLabel->setEnabled(true);
        mSpeedValueLabel->setEnabled(true);
    } else {
        mStartStopButton->setEnabled(false);
        mResetButton->setEnabled(false);
        mCurrentStateColorBox->setEnabled(false);
        mSpeedScrollBar->setEnabled(false);
        mSpeedTitleLabel->setEnabled(false);
        mSpeedValueLabel->setEnabled(false);
    }
}

void QHouseSimulationControlPanel::startStopSimulation()
{
    if (isSimulationRunning()) {
        stopSimulation();
    } else {
        startSimulation();
    }
}

void QHouseSimulationControlPanel::updateSimulationSpeed()
{
    mSpeedValueLabel->setText(QString::number(simulationSpeed()) + "x");
}

void QHouseSimulationControlPanel::simulationTic()
{
    int timeStepCount{ static_cast<int>(std::pow(2.0, -mSpeedScrollBar->minimum()) * simulationSpeed()) };
    mHouseMap.process(timeStepCount);

    emit simulationTicked(timeStepCount);
}

void QHouseSimulationControlPanel::afficheAPropos()
{
    mMessage->about(this, "À propos...", "Smart House\n\nGPA434 | Laboratoire 2 d'ingénierie des systèmes orienté objet\n\nRéalisé par :\n- Vincent Lavoie\n- Liliam Acosta\n- Russel Bulaon\n\nCe laboratoire permet de visualiser les effets de trois simulations météorologiques distinctes sur une maison et les différentes pièces présentes dans la maison.\n\nLes ajouts réalisés sont les suivants:\n- Météo annuelle environnementale:\n");
}

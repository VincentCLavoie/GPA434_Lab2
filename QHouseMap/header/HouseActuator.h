#pragma once


#include "HouseDevice.h"


// Classe repr�sentant un actuateur.
class HouseActuator : public HouseDevice
{
public:
    HouseActuator(QHouseMap & house);

    virtual bool isActive() const = 0;
    virtual void actuate() = 0;
};



// Classe repr�sentant une pompe thermique.
// Permet de dissiper une temp�rature sp�cifique (chaud ou froid).
class HeatPump : public HouseActuator
{
public:
    HeatPump(QHouseMap & house);

    void setThermalSetPoint(double thermalSetPoint);
    double thermalSetPoint() const;

protected:
    void actuate() override;

private:
    double mThermalSetPoint;
};



// Classe repr�sentant une pompe thermique � deux �tats : active ou inactive.
class OnOffHeatPump : public HeatPump
{
public:
    OnOffHeatPump(QHouseMap & house);

    bool isActive() const override;

    void setActive(bool active);
    void toggleActive();

private:
    bool mActive;
};
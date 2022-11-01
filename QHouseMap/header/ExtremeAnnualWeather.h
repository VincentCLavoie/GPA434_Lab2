#pragma once


#include "AnnualWeather.h"


class ExtremeAnnualWeather : public AnnualWeather
{
public:
    QString name() const override;
    double temperature(size_t secondOfYear) const override;
    //ExtremeAnnualWeather* clone() const override;
};


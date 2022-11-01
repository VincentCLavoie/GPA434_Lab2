#pragma once


#include "AnnualWeather.h"


class TypicalMontrealAnnualWeather : public AnnualWeather
{
public:
    QString name() const override;
    double temperature(size_t secondOfYear) const override;
    //TypicalMontrealAnnualWeather* clone() const override;
};


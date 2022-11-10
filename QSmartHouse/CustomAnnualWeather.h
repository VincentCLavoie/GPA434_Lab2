#pragma once


#include "AnnualWeather.h"


class CustomAnnualWeather : public AnnualWeather
{
public:
    QString name() const override;
    double temperature(size_t secondOfYear) const override;

    
};


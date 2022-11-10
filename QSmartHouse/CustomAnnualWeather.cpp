#include "CustomAnnualWeather.h"

QString CustomAnnualWeather::name() const
{
	return QString("Custom Annual Weather");
}

double CustomAnnualWeather::temperature(size_t secondOfYear) const 
{
	return 30.0;
}

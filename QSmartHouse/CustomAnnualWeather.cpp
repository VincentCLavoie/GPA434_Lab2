#include "CustomAnnualWeather.h"

QString CustomAnnualWeather::name() const
{
	return QString("Custom Annual Weather");
}

double CustomAnnualWeather::temperature(size_t secondOfYear) const 
{
	double tmensuel, tsaisonal, x, y;
	const double tmmax = 30.0,
				 tmmin = 1.0,
				 thmax = 5.0,
				 thmin = 2.0;
	const int tannee = 31536000,
			  tmois = 2628000,
			  theure = 3600;
	

	x = 0.5 * (sin((secondOfYear % tannee * 2 * 3.1416) / (tmois * 12))) + 0.5; //0.5 * (sin((secondOfYear %tannee * 2 * 3.1416) / (tmois * 12)) )+ 0.5; où tmois = 2628000
	y = 0.5 * (sin((secondOfYear % tannee * 2 * 3.1416) / (theure * 24))) + 0.5; //0.5 * (sin((secondOfYear %tannee * 2 * 3.1416) / (theure * 24)) )+ 0.5; où theure = 3600

	tmensuel = (tmmax - tmmin) * x + tmmin;
	tsaisonal = (thmax - thmin) * y + thmin;

	return tmensuel + tsaisonal;
}

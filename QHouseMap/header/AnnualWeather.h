#pragma once


#include <QString>


// Cette classe permet la d�finition des conditions m�t�orologiques en fonction d'un moment de l'ann�e.
// Pour l'instant, seule la temp�rature est support�e.
class AnnualWeather
{
public:
    // Fonction retournant le nom du patron.
    virtual QString name() const = 0;

    // Fonction retournant la temp�rature en fonction du moment de l'ann�e donn�.
    // Le moment est donn� en seconde de l'ann�e.
    // 
    // secondOfYear est bas� sur : 
    //      60 secondes/minute
    //      60 minutes/heure
    //      24 heures/jour
    //      365 jours/ann�e
    // -> il y a donc 31'536'000 secondes par ann�e
    // 
    // source int�ressante : https://en.climate-data.org/north-america/canada/quebec/montreal-3704/
    virtual double temperature(size_t secondOfYear) const = 0;
};


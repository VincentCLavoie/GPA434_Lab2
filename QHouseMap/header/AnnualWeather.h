#pragma once


#include <QString>


// Cette classe permet la définition des conditions météorologiques en fonction d'un moment de l'année.
// Pour l'instant, seule la température est supportée.
class AnnualWeather
{
public:
    // Fonction retournant le nom du patron.
    virtual QString name() const = 0;

    // Fonction retournant la température en fonction du moment de l'année donné.
    // Le moment est donné en seconde de l'année.
    // 
    // secondOfYear est basé sur : 
    //      60 secondes/minute
    //      60 minutes/heure
    //      24 heures/jour
    //      365 jours/année
    // -> il y a donc 31'536'000 secondes par année
    // 
    // source intéressante : https://en.climate-data.org/north-america/canada/quebec/montreal-3704/
    virtual double temperature(size_t secondOfYear) const = 0;
};


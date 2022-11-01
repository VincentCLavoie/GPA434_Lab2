#include "EzHomeSens666.h"




EzHomeSens666::EzHomeSens666(QHouseMap & house)
    : SinglePointTemperatureSensor(house)
{
}

QString EzHomeSens666::deviceName() const
{
    return QString("EzHomeSens666");
}

QDeviceHMI* EzHomeSens666::createHMI()
{
    return new EzHomeSens666HMI(*this);
}


EzHomeSens666HMI::EzHomeSens666HMI(EzHomeSens666 & device)
    : QPaintDeviceHMI(device)
{
}
void EzHomeSens666HMI::paint(QPainter& painter)
{
    // Dessine la couleur de fond
    painter.setBrush(QColor(64, 64, 64));
    painter.drawRect(rect());

    // Si le "device" est invalide, affiche un texte centré et quitte
    if (!mHouseDevice.isValid()) {
        painter.setPen(QColor(128, 128, 128));
        painter.drawText(rect(), "Invalid device", QTextOption(Qt::AlignCenter));
        return;
    }

    // Affiche trois métriques de référence pour la température : 
    //  - à gauche (valeur min)
    //  - à droite (valeur max)
    //  - en haut (valeur centre)
    QFontMetrics fontMetrics(painter.font());
    painter.setPen(QColor(128, 196, 128));
    painter.drawText(rect().center() + QPoint(-60 - fontMetrics.width("-45°C"), 0), QString("-45°C"));
    painter.drawText(rect().center() + QPoint(60, 0), QString("45°C"));
    painter.drawText(rect().center() + QPoint(-fontMetrics.width("0°C") / 2, -60), QString("0°C"));

    // Affiche la température actuelle
    painter.setPen(QColor(128, 255, 96));
    QString value(QString("%1°C").arg(static_cast<HouseSensor&>(mHouseDevice).measure(), 0, 'f', 1));
    painter.drawText(rect().center() + QPoint(-fontMetrics.width(value) / 2, 20), value);

    // Affiche l'aiguille 
    // Dessine un polygon suite à deux changements de référentiel : translation et rotation
    QPolygon polygon;
    polygon << QPoint(0, 0)
            << QPoint(-10, 0)
            << QPoint(0, 50)
            << QPoint(10, 0);
    painter.setBrush(QColor(96, 128, 96));
    painter.setPen(QColor(128, 255, 96));
    painter.translate(rect().center());
    painter.rotate(-180.0 + static_cast<HouseSensor&>(mHouseDevice).measure() / 45.0 * 90.0);
    painter.drawPolygon(polygon);
}




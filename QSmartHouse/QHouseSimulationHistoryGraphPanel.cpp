#include "QHouseSimulationHistoryGraphPanel.h"


#include <QValueAxis>


QHouseSimulationHistoryGraphPanel::QHouseSimulationHistoryGraphPanel(QHouseMap & houseMap, QWidget * parent)
	:	QChartView(parent),
        mHouseMap{ houseMap },
		mHistoryStatsSeries0{ new QtCharts::QLineSeries },
		mHistoryStatsSeries1{ new QtCharts::QLineSeries },
		mHistoryStatsChart{ new QtCharts::QChart }
{
	setChart(mHistoryStatsChart);
    setRenderHint(QPainter::Antialiasing);

    mHistoryStatsSeries0->setName("Extérieur");
    mHistoryStatsSeries1->setName("Intérieur");
    mHistoryStatsSeries0->setPen(QPen(QColor(255, 0, 196), 1.5));
    mHistoryStatsSeries1->setPen(QPen(QColor(255, 128, 0), 1.5));
    mHistoryStatsChart->legend()->setAlignment(Qt::AlignBottom);
    mHistoryStatsChart->addSeries(mHistoryStatsSeries0);
    mHistoryStatsChart->addSeries(mHistoryStatsSeries1);
    mHistoryStatsChart->createDefaultAxes();
    mHistoryStatsChart->setTitle("Historique des températures");
    mHistoryStatsChart->axes(Qt::Horizontal).first()->setTitleText("Jours");
    mHistoryStatsChart->axes(Qt::Vertical).first()->setTitleText("Température °C");


    static_cast<QtCharts::QValueAxis*>(mHistoryStatsChart->axes(Qt::Horizontal).first())->setLabelFormat("%0.1lf");
    static_cast<QtCharts::QValueAxis*>(mHistoryStatsChart->axes(Qt::Vertical).first())->setLabelFormat("%0.1lf");
}

QHouseSimulationHistoryGraphPanel::~QHouseSimulationHistoryGraphPanel()
{
}

void QHouseSimulationHistoryGraphPanel::updateGraph()
{
    double x{ mHouseMap.elapsedTime() / (60.0 * 60.0 * 24.0) };
    double y0{ mHouseMap.idInfo().statsHistory(0).last().temperature().mean() };
    double y1{ mHouseMap.idInfo().statsHistory(1).last().temperature().mean() };
    mHistoryStatsSeries0->append(x, y0);
    mHistoryStatsSeries1->append(x, y1);

    static_cast<QtCharts::QValueAxis*>(mHistoryStatsChart->axes(Qt::Horizontal).first())->setRange(0.0, x);
    QtCharts::QValueAxis* vAxis{ static_cast<QtCharts::QValueAxis*>(mHistoryStatsChart->axes(Qt::Vertical).first()) };
    vAxis->setRange(qMin(qMin(y0, y1), vAxis->min()), qMax(qMax(y0, y1), vAxis->max()));
}

void QHouseSimulationHistoryGraphPanel::resetGraph()
{
    mHistoryStatsSeries0->clear();
    mHistoryStatsSeries1->clear();
}

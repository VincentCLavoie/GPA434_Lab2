#pragma once


#include <QChartView>
#include <QChart>
#include <QLineSeries>
#include <QHouseMap.h>


class QHouseSimulationHistoryGraphPanel : public QtCharts::QChartView
{
	Q_OBJECT

public:
	QHouseSimulationHistoryGraphPanel(QHouseMap & houseMap, QWidget * parent = nullptr);
	~QHouseSimulationHistoryGraphPanel();

public slots:
	void updateGraph();
	void resetGraph();

private:
	QHouseMap & mHouseMap;
	QtCharts::QLineSeries* mHistoryStatsSeries0;
	QtCharts::QLineSeries* mHistoryStatsSeries1;
	QtCharts::QChart* mHistoryStatsChart;
};

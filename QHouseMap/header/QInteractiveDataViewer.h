#pragma once


#include "QInteractiveImageViewer.h"
#include "QColorMap.h"


class QInteractiveDataViewer : public QInteractiveImageViewer
{
    Q_OBJECT

public:
    QInteractiveDataViewer(QWidget * parent = nullptr);
    ~QInteractiveDataViewer() = default;

    class DataProxy
    {
    public:
        virtual bool isValid() const = 0;
        virtual QSize size() const = 0;
        virtual qreal data(int x, int y) const = 0;
        virtual qreal min() const = 0;
        virtual qreal max() const = 0;
    };

    void setData(DataProxy * proxy);
    
    void setImage(QImage const& image) override;
    void setPixmap(QPixmap const& image) override;
    void clear() override;

    QColorMap & colorMap();

public slots:
    void updateData();

private:
    bool mProxyMode;
    QScopedPointer<DataProxy> mDataProxy;
    QColorMap mColorMap;
};


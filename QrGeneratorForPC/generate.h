#ifndef GENERATE_H
#define GENERATE_H
#include <QString>
#include <QMap>

class Generate
{
public:
    void setPCnameSeries(const QString& pc_name, const QString& pc_series);
    bool generateQR();
    Generate();

private:
    QString pc_name;
    QString pc_series;
};

#endif // GENERATE_H

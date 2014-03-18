/*
 * Author: Jarno Tuovinen
 */
#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QDesktopWidget>
#include <QDebug>
#include <QLabel>
#include <QWidget>

#include "gsvwrapper.h"

#define DEFAULT_LAT 51.494966
#define DEFAULT_LNG -0.146674

#define IMG_SCALE 40

namespace Ui {
    class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

private:
    Ui::MainWidget *ui;

    GSVWrapper *gsvw;

    QLabel* images[13][26];
    void initImages();

public slots:
    void updatePid(QString pid);
    void printLog(QString str);
    void newMeta(double,double,QString,QString);
    void newTile(QImage tile,
                 double lat,
                 double lng,
                 int xCoord,
                 int yCoord,
                 int zoomLevel);

private slots:
    void on_leZoom_returnPressed();
    void on_pbInitGrid_clicked();
    void on_pbClearCache_clicked();
    void on_pbResetNH_clicked();
    void on_pbResetAll_clicked();
    void on_pbGetImageByPidAndZoom_clicked();
    void on_pbGetMetadata_clicked();
};

#endif // MAINWIDGET_H

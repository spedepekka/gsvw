/*
 * Author: Jarno Tuovinen
 */
#include "mainwidget.h"
#include "ui_mainwidget.h"

static QPixmap initialPicture();

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);

    // Move widget to center of the screen
    move(QApplication::desktop()->screen()->rect().center() - rect().center());

    // Set some texts
    ui->leLat->setText(QString::number(DEFAULT_LAT));
    ui->leLng->setText(QString::number(DEFAULT_LNG));

    initImages();

    // Make wrapper
    gsvw = new GSVWrapper();
    gsvw->setVerbose(true); // Enable verbose

    // Connect signals
    connect(gsvw, SIGNAL(tileReady(QImage,double,double,int,int,int)),
            this, SLOT(newTile(QImage,double,double,int,int,int)));

    connect(gsvw, SIGNAL(metaReady(double,double,QString,QString)),
            this, SLOT(newMeta(double,double,QString,QString)));
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::initImages()
{
    for (int y = 0; y < 26; y++) {
        for (int x = 0; x < 13; x++) {
            QLayoutItem *i = ui->grid->itemAtPosition(x, y);
            if(i != 0) {
                QWidget *w = i->widget();
                if(w != 0)
                    delete w;
            }
            QLabel *l = new QLabel(this);
            l->setPixmap(initialPicture());
            ui->grid->addWidget(l, x, y);
            images[x][y] = l;
        }
    }
    update();
}

void MainWidget::updatePid(QString pid)
{
    ui->lePid->setText(pid);
    printLog("new pid");
}

void MainWidget::printLog(QString str)
{
    QString time = QDateTime::currentDateTime().toString("hh:mm:ss.zzz"); // Time format

    ui->pteLog->appendPlainText(QString("%1: %2").arg(time).arg(str));
}

void MainWidget::newMeta(double lat, double lng, QString fieldName, QString data)
{
    if(fieldName == "pano_id") {
        ui->lePid->setText(data);
        printLog(tr("New pid %1").arg(data));
    } else {
        printLog(tr("Data = %1").arg(data));
    }
}

void MainWidget::newTile(QImage tile, double lat, double lng, int xCoord, int yCoord, int zoomLevel)
{
    tile = tile.scaled(QSize(IMG_SCALE, IMG_SCALE));
    images[yCoord][xCoord]->setPixmap(QPixmap::fromImage(tile));
}

void MainWidget::on_pbGetMetadata_clicked()
{
    bool ok1;
    bool ok2;
    double lat = ui->leLat->text().toDouble(&ok1);
    double lng = ui->leLng->text().toDouble(&ok2);
    if(ok1 && ok2)
        gsvw->getMeta(lat, lng, "pano_id");
    else
        qDebug() << "Invalid lat and/or lng";
}

void MainWidget::on_pbGetImageByPidAndZoom_clicked()
{
    initImages();

    bool ok1;
    bool ok2;
    bool ok3;
    double lat = ui->leLat->text().toDouble(&ok1);
    double lng = ui->leLng->text().toDouble(&ok2);
    int zoom = ui->leZoom->text().toDouble(&ok3);
    if(ok1 && ok2 && ok3)
        gsvw->getPano(lat, lng, zoom);
    else
        qDebug() << "Invalid lat and/or lng";
}

static QPixmap initialPicture()
{
    QPixmap out(IMG_SCALE, IMG_SCALE);
    out.fill();
    return out;
}

void MainWidget::on_pbResetAll_clicked()
{
    gsvw->reset();
}

void MainWidget::on_pbResetNH_clicked()
{
    gsvw->networkhandler.reset();
}

void MainWidget::on_pbClearCache_clicked()
{
    gsvw->clearCache();
}

void MainWidget::on_pbInitGrid_clicked()
{
    initImages();
}

void MainWidget::on_leZoom_returnPressed()
{
    on_pbGetImageByPidAndZoom_clicked();
}

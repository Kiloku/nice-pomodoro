#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateCountdown()));
    trayMenu = new QMenu("NicePomo", this);
    trayIcon = new QSystemTrayIcon(QIcon(":/images/PomoGreen.png"));
    //trayIcon->setIcon();
    trayIcon->show();
    setWindowIcon(QIcon(":images/PomoGreen.png"));
}

MainWindow::~MainWindow()
{
    trayIcon->hide();
    delete ui;
}


void MainWindow::on_startButton_clicked()
{
    timer->start(interval);
    //trayIcon->show();

    sentAlert = false;

    ui->timeElapsedBox->setTime(QTime(0,0,0,0));

    if (mode == none || mode == shortRest || mode == longRest)
    {
        mode = working;
        ui->startButton->setText("Start Break");
        ui->elapsedLabel->setText("Time Working");
    }
    else
    {
        if(breaksToLongRest <= 0)
        {
            mode = longRest;
            breaksToLongRest = 3;
        }
        else
        {
            mode = shortRest;
            breaksToLongRest--;
        }
        ui->startButton->setText("Start Work");
        ui->elapsedLabel->setText("Time on break");
    }
}

void MainWindow::updateCountdown()
{
    QTime added = ui->timeElapsedBox->time().addMSecs(interval);
    ui->timeElapsedBox->setTime(added);

    QTimeEdit *currentTimeEdit;
    QTime timeTo = QTime(0,0,0,0);
    if (mode == working){
        currentTimeEdit = ui->workTimeBox;
    }
    if (mode == shortRest){
        currentTimeEdit = ui->restTimeBox;
    }

    timeTo = timeTo.addMSecs(ui->timeElapsedBox->time().msecsTo(currentTimeEdit->time()));
    int currentTimerSeconds = QTime(0,0,0,0).secsTo(currentTimeEdit->time());
    int timeToInSeconds = QTime(0,0,0,0).secsTo(timeTo);
    int timeElapsedSeconds = QTime(0,0,0,0).secsTo(ui->timeElapsedBox->time());

    if (timeElapsedSeconds > currentTimerSeconds){
       /* if (ui->alertWhenOver->isChecked() && !sentAlert){
            //trayIcon->Information()
        }*/
        if (timeElapsedSeconds % 2 == 0){
            trayIcon->setIcon(QIcon(":images/PomoRed.png"));
            setWindowIcon(QIcon(":images/PomoRed.png"));
        }
        else{
            trayIcon->setIcon(QIcon(":images/PomoOrange.png"));
            setWindowIcon(QIcon(":images/PomoOrange.png"));
        }
    }
    else if (timeElapsedSeconds >= (currentTimerSeconds * (ui->redThresholdInput->value() / 100.f))){
        trayIcon->setIcon(QIcon(":images/PomoRed.png"));
        setWindowIcon(QIcon(":images/PomoRed.png"));
    }
    else if (timeElapsedSeconds >= ((currentTimerSeconds * (ui->orangeThresholdInput->value() / 100.f)))){
        trayIcon->setIcon(QIcon(":images/PomoOrange.png"));
        setWindowIcon(QIcon(":images/PomoOrange.png"));
    }
    else if (timeElapsedSeconds >= ((currentTimerSeconds * (ui->yellowThresholdInput->value() / 100.f)))){
        trayIcon->setIcon(QIcon(":images/PomoYellow.png"));
        setWindowIcon(QIcon(":images/PomoYellow.png"));
    }
    else{
        trayIcon->setIcon(QIcon(":images/PomoGreen.png"));
        setWindowIcon(QIcon(":images/PomoGreen.png"));

    }

}

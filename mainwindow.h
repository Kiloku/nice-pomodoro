#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QMenu>
#include <QSystemTrayIcon>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_startButton_clicked();
    void updateCountdown();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    int interval = 1000;
    int a = 0;
    int breaksToLongRest = 3;
    enum Mode : short {none, working, shortRest, longRest};
    Mode mode = none;
    QSystemTrayIcon *trayIcon;
    QMenu *trayMenu;

    bool sentAlert;
};
#endif // MAINWINDOW_H

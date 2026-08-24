#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void numberClicked();
    void operatorClicked();
    void decimalClicked();
    void calculate();
    void clearAll();
    void backspace();

private:
    Ui::MainWindow *ui;
    double firstNumber;
    QString pendingOperator;
    bool waitingForNumber;
};

#endif // MAINWINDOW_H

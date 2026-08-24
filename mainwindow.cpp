#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPushButton>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      firstNumber(0),
      waitingForNumber(true)
{
    ui->setupUi(this);

    // Number buttons
    connect(ui->btn0, &QPushButton::clicked, this, &MainWindow::numberClicked);
    connect(ui->btn1, &QPushButton::clicked, this, &MainWindow::numberClicked);
    connect(ui->btn2, &QPushButton::clicked, this, &MainWindow::numberClicked);
    connect(ui->btn3, &QPushButton::clicked, this, &MainWindow::numberClicked);
    connect(ui->btn4, &QPushButton::clicked, this, &MainWindow::numberClicked);
    connect(ui->btn5, &QPushButton::clicked, this, &MainWindow::numberClicked);
    connect(ui->btn6, &QPushButton::clicked, this, &MainWindow::numberClicked);
    connect(ui->btn7, &QPushButton::clicked, this, &MainWindow::numberClicked);
    connect(ui->btn8, &QPushButton::clicked, this, &MainWindow::numberClicked);
    connect(ui->btn9, &QPushButton::clicked, this, &MainWindow::numberClicked);

    // Operators
    connect(ui->btnPlus, &QPushButton::clicked, this, &MainWindow::operatorClicked);
    connect(ui->btnMinus, &QPushButton::clicked, this, &MainWindow::operatorClicked);
    connect(ui->btnMultiply, &QPushButton::clicked, this, &MainWindow::operatorClicked);
    connect(ui->btnDivide, &QPushButton::clicked, this, &MainWindow::operatorClicked);

    // Other buttons
    connect(ui->btnDecimal, &QPushButton::clicked, this, &MainWindow::decimalClicked);
    connect(ui->btnEquals, &QPushButton::clicked, this, &MainWindow::calculate);
    connect(ui->btnClear, &QPushButton::clicked, this, &MainWindow::clearAll);
    connect(ui->btnBackspace, &QPushButton::clicked, this, &MainWindow::backspace);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::numberClicked()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if (!button)
        return;

    QString number = button->text();

    if (waitingForNumber || ui->display->text() == "0")
    {
        ui->display->setText(number);
        waitingForNumber = false;
    }
    else
    {
        ui->display->setText(ui->display->text() + number);
    }
}

void MainWindow::operatorClicked()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if (!button)
        return;

    firstNumber = ui->display->text().toDouble();
    pendingOperator = button->text();
    waitingForNumber = true;
}

void MainWindow::decimalClicked()
{
    if (waitingForNumber)
    {
        ui->display->setText("0.");
        waitingForNumber = false;
    }
    else if (!ui->display->text().contains("."))
    {
        ui->display->setText(ui->display->text() + ".");
    }
}

void MainWindow::calculate()
{
    if (pendingOperator.isEmpty())
        return;

    double secondNumber = ui->display->text().toDouble();
    double result = 0;

    if (pendingOperator == "+")
        result = firstNumber + secondNumber;
    else if (pendingOperator == "-")
        result = firstNumber - secondNumber;
    else if (pendingOperator == "*")
        result = firstNumber * secondNumber;
    else if (pendingOperator == "/")
    {
        if (secondNumber == 0)
        {
            QMessageBox::warning(this, "Error", "Cannot divide by zero!");
            clearAll();
            return;
        }

        result = firstNumber / secondNumber;
    }

    ui->display->setText(QString::number(result, 'g', 12));
    pendingOperator.clear();
    waitingForNumber = true;
}

void MainWindow::clearAll()
{
    ui->display->setText("0");
    firstNumber = 0;
    pendingOperator.clear();
    waitingForNumber = true;
}

void MainWindow::backspace()
{
    if (waitingForNumber)
        return;

    QString text = ui->display->text();
    text.chop(1);

    if (text.isEmpty())
        text = "0";

    ui->display->setText(text);
}

#include "mainwindow.h"
#include "./ui_mainwindow.h"
#define SIZE 11

double num_first=0;   //первое число мат. выражения
char sign;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_percent, SIGNAL(clicked()), this, SLOT(operation()));
    connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(math_operation()));
    connect(ui->pushButton_minus, SIGNAL(clicked()), this, SLOT(math_operation()));
    connect(ui->pushButton_division, SIGNAL(clicked()), this, SLOT(math_operation()));
    connect(ui->pushButton_multiply, SIGNAL(clicked()), this, SLOT(math_operation()));
    ui->pushButton_plus->setCheckable(true);
    ui->pushButton_minus->setCheckable(true);
    ui->pushButton_division->setCheckable(true);
    ui->pushButton_multiply->setCheckable(true);
    ui->pushButton_equals->setCheckable(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}
// ввод цифр
void MainWindow::digits_numbers(){
    QPushButton *button = (QPushButton *)sender(); // указатель на активированную кнопку (объект, который подает сигнал)
    QString newLabel;
    if(ui->result->text().contains(".") && button->text()=="0")
    {
        newLabel = (ui->result->text() + button->text());
    }
    else
    {
        double all_numbers = (ui->result->text() + button->text()).toDouble();
        newLabel = QString::number(all_numbers, 'g', SIZE);

    }
    ui->result->setText(newLabel);

}



void MainWindow::on_pushButton_dot_clicked()
{
    QString newLabel = ui->result->text();
    if(!newLabel.contains('.'))
        ui->result->setText(newLabel + '.');
}

void MainWindow::operation(){
    QPushButton *button = (QPushButton *)sender();
    QString currentLabel = ui->result->text();
    double all_numbers = (currentLabel.toDouble());
    if(button->text() == "%")
    {
        all_numbers *=  0.01;
    }
    QString newLabel = QString::number(all_numbers, 'g', SIZE);
    ui->result->setText(newLabel);

}


void MainWindow::on_pushButton_plus_minus_clicked()
{
    if(ui->result->text().front() == '-')
    {
        ui->result->setText(ui->result->text().removeFirst());
    }
    else
        ui->result->setText('-' + ui->result->text());

}


void MainWindow::on_pushButton_AC_clicked()
{
    ui->result->setText("0");
    ui->num_first->setText("");
    ui->pushButton_plus->setChecked(false);
    ui->pushButton_minus->setChecked(false);
    ui->pushButton_division->setChecked(false);
    ui->pushButton_multiply->setChecked(false);
}

void MainWindow::math_operation()
{
    if (ui->pushButton_equals->isChecked())
    {
        ui->pushButton_plus->setChecked(false);
        ui->pushButton_minus->setChecked(false);
        ui->pushButton_division->setChecked(false);
        ui->pushButton_multiply->setChecked(false);
        ui->num_first->setText(ui->num_first->text().removeLast());
    }


    QPushButton *button = (QPushButton *)sender();
    button->setChecked(true);
    if(ui->pushButton_plus->isChecked())
    {
        sign = '+';
    } else if (ui->pushButton_minus->isChecked())
    {
        sign = '-';
    } else if (ui->pushButton_division->isChecked())
    {
      sign = '/';
    }
    else if (ui->pushButton_multiply->isChecked())
    {
       sign = 'x';
    }

    if (ui->pushButton_equals->isChecked())
    {
        ui->num_first->setText(ui->num_first->text() + sign);
    }
    else{
        num_first = ui->result->text().toDouble();

        ui->result->setText("");
        ui->num_first->setText(QString::number(num_first, 'g', SIZE) + sign);
    }
    ui->pushButton_equals->setChecked(true);
}


void MainWindow::on_pushButton_equals_clicked()
{
    double labelNumber, num_second;
    QString newLabel;
    num_second = ui->result->text().toDouble();
    if(ui->pushButton_plus->isChecked())
    {
        labelNumber = num_first + num_second;
        ui->pushButton_plus->setChecked(false);
        newLabel = QString::number(labelNumber, 'g', SIZE);
        ui->result->setText(newLabel);
    } else if (ui->pushButton_minus->isChecked())
    {
        labelNumber = num_first - num_second;
        ui->pushButton_minus->setChecked(false);
        newLabel = QString::number(labelNumber, 'g', SIZE);
        ui->result->setText(newLabel);

    } else if (ui->pushButton_division->isChecked())
    {
        if(num_second == 0)
        {
           ui->result->setText("0");
        }
        else
        {
            labelNumber = num_first / num_second;
            ui->pushButton_division->setChecked(false);
            newLabel = QString::number(labelNumber, 'g', SIZE);
            ui->result->setText(newLabel);
        }


    } else if (ui->pushButton_multiply->isChecked())
    {
        labelNumber = num_first * num_second;
        ui->pushButton_multiply->setChecked(false);
        newLabel = QString::number(labelNumber, 'g', SIZE);
        ui->result->setText(newLabel);

    }
    ui->num_first->setText("");
    ui->pushButton_equals->setChecked(false);

}


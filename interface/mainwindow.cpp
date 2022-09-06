#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->group, SIGNAL(buttonClicked(QAbstractButton*)), this,
                SLOT(on_button_clicked(QAbstractButton*)));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_button_clicked(QAbstractButton* btn)
{
    str = ui->input->text();
    str += btn->text();

    if (btn == ui->sin || btn == ui->cos || btn == ui->tan ||
        btn == ui->asin || btn == ui->acos || btn == ui->atan || 
        btn == ui->log || btn == ui->ln) {
        str += "(";
    }
    if (btn == ui->unary) {
        str.chop(1);
        if (str.endsWith("-")) {
            str.chop(1);
        } else {
            str += "-";
        }
    }

    ui->input->setText(str);
}

void MainWindow::on_all_clean_clicked()
{
    str = "";
    ui->input->clear();
}

void MainWindow::on_backspace_clicked()
{
    str = ui->input->text();
    str.chop(1);
    ui->input->setText(str);
    if (str.isEmpty()) {
        ui->input->clear();
    }
}

void MainWindow::on_equal_clicked()
{
    QString textArea = ui->input->text();
    QString xArea = ui->text_X->text();
    if (xArea.isEmpty()) {
        str.replace("X", "0");
    } else {
        str.replace("X", xArea);
    }
    if (textArea.isEmpty()) {
        ui->input->setText("Enter an expression");
    } else {
        std::string tmpArea = textArea.toUtf8().data();
        char tmpCharArea[256] = "\0";
        strcpy(tmpCharArea, tmpArea.c_str());
        std::string tmpXArea = xArea.toUtf8().data();
        char tmpCharXArea[256] = "\0";
        strcpy(tmpCharXArea, tmpXArea.c_str());
        setlocale(LC_NUMERIC, "C");
        QString result;
        result = QString("%1").arg(s21_calculate(tmpCharArea, tmpCharXArea));
        if (result.contains("incorrect input")) {
            QMessageBox *error = new QMessageBox;
            error->setWindowTitle("ERROR!");
            error->setText("An incorrect expression");
            error->show();
        } else {
            ui->input->setText(result);
        }
    }
}

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QString>
#include <QMessageBox>
#include <QInputDialog>
#include <QStyleOption>
#include <clocale>

#ifdef __cplusplus
extern "C" {
    #include "../s21_calculator.h"
}
#endif

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        QString str{};
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

    private slots:
        void on_button_clicked(QAbstractButton *btn);
        void on_all_clean_clicked();
        void on_equal_clicked();

        void on_backspace_clicked();

private:
        Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

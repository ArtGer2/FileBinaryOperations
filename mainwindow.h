#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QFileDialog>
#include <QMainWindow>
#include <QFile>
#include "filemanager.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QTimer>

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

    void on_ImportButton_clicked();

    void on_xorButton_clicked();

    void on_exportButton_clicked();

    void checkFiles();

private:
    Ui::MainWindow *ui;
    QString importDirectory;
    QString exportDirectory;
    QStringList importFiles;
    FileManager fl;
    QStringList result;
    QTimer *timer;

};
#endif // MAINWINDOW_H

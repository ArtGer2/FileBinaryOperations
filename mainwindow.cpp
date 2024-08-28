#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "fileprocessor.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &MainWindow::checkFiles);
    timer->start(10000);

}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_ImportButton_clicked()
{

    importDirectory = QFileDialog::getExistingDirectory(this, "Select the directory", QDir::homePath());
    importFiles = fl.findFiles(ui->lineEdit->text(), importDirectory);

}


void MainWindow::on_xorButton_clicked()
{
    if(importFiles.isEmpty()){
        QMessageBox::information(
            nullptr,
            "Error",
            "No files have been selected"
            );
    }
    else{

    QByteArray key = ui->textEdit->toPlainText().toUtf8();
    if (key.size()!=8){
        QMessageBox::information(
            nullptr,
            "Error",
            "The key must be 8 bytes in size"
            );
    }
    else{
        for (auto file:importFiles){
            result.append(FileProcessor::modifyData(file.toUtf8(),key));
        }
        ui->label_2->setText("XOR Completed");
    }
    }
}


void MainWindow::on_exportButton_clicked()
{
    if(result.isEmpty()){
        QMessageBox::information(
            nullptr,
            "Error",
            "The files have not been processed"
            );
    }
    else{
    exportDirectory = QFileDialog::getExistingDirectory(this, "Select the directory", QDir::homePath());
    auto rewrite = ui->checkRewrite->checkState();
    fl.saveFiles(exportDirectory,result,rewrite);

    if (ui->CheckDelete->checkState()){
        fl.filesDelete();
        ui->statusbar->showMessage("Files deleted",10000);
    }


    }
}

void MainWindow::checkFiles() {
    if(!importDirectory.isEmpty()){
        QStringList files = fl.findFiles(ui->lineEdit->text(), importDirectory);
        if (!files.isEmpty()) {
            importFiles = files;
            ui->statusbar->showMessage("Files checked and updated",3000);
        } else {
            ui->statusbar->showMessage("No files found",3000);
        }
    }
    if (ui->checkBox->checkState()){
        if (!exportDirectory.isEmpty()){
            auto rewrite = ui->checkRewrite->checkState();
            fl.saveFiles(exportDirectory,result,rewrite);
            ui->statusbar->showMessage("Files checked, updated and recorded",3000);
        }
    }
}

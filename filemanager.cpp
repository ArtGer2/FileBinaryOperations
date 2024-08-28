#include "filemanager.h"

FileManager::FileManager() {}
QStringList FileManager::findFiles(const QString &mask, const QString &directoryPath){
    QDir directory(directoryPath);

    QStringList filters;
    if (mask.isEmpty()) {
        filters << "*";
    } else {
        filters << mask;
    }


    fileInfoList = directory.entryInfoList(filters, QDir::Files);

    QStringList fileContents;
    for (const QFileInfo &fileInfo : fileInfoList) {
        QFile file(fileInfo.absoluteFilePath());

        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            QString content = in.readAll();
            fileContents.append(content);
            file.close();
        } else {
            qWarning() << "Unable to open file (possibly in use):" << fileInfo.absoluteFilePath();
        }
    }


    return fileContents;
}

void FileManager::saveFiles(const QString &directoryPath, const QStringList &info, const bool &rewrite) {
    QDir dir(directoryPath);


    if (!dir.exists() && !dir.mkpath(directoryPath)) {
        return;
    }


    if (fileInfoList.size() != info.size()) {
        return;
    }

    for (int i = 0; i < fileInfoList.size(); ++i) {
        const QFileInfo &fileInfo = fileInfoList.at(i);
        QString originalFilePath = fileInfo.absoluteFilePath();
        QString baseName = fileInfo.completeBaseName();
        QString extension = fileInfo.suffix();
        QString newFilePath;

        if (rewrite) {
            newFilePath = dir.filePath(fileInfo.fileName());
        } else {

            int counter = 1;

            QFileInfo newFileInfo;
            do {
                newFilePath = dir.filePath(QString("%1_%2.%3").arg(baseName).arg(counter).arg(extension));
                newFileInfo.setFile(newFilePath);
                ++counter;
            } while (newFileInfo.exists());
        }


        QFile file(newFilePath);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            out << info.at(i);
            file.close();
        } else {
        }
    }
}
void FileManager::filesDelete(){

    for (auto &fileInfo : fileInfoList) {

        QFile file(fileInfo.absoluteFilePath());
        if (file.exists()) {
            if (file.remove()) {
                qDebug() << "File deleted:" << fileInfo.fileName();
            } else {
                qWarning() << "Failed to delete file:" << fileInfo.fileName();
            }
        } else {
            qWarning() << "File does not exist:" << fileInfo.fileName();
        }
    }
}

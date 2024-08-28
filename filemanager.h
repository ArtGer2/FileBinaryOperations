#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include <QDir>
#include <QStringList>
#include <QFileInfoList>
class FileManager
{
public:
    FileManager();

    QStringList findFiles(const QString &mask, const QString &directoryPath);
    void saveFiles(const QString &directoryPath,const QStringList &info,const bool &rewrite);
    void filesDelete();
private:
    QFileInfoList fileInfoList;
};

#endif // FILEMANAGER_H

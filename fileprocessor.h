#ifndef FILEPROCESSOR_H
#define FILEPROCESSOR_H
#include <QByteArray>
#include <QDebug>
class FileProcessor
{
public:
    FileProcessor();
    static QByteArray modifyData(const QByteArray &data, const QByteArray &operationKey);
};

#endif // FILEPROCESSOR_H

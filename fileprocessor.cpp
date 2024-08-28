#include "fileprocessor.h"

FileProcessor::FileProcessor() {}
QByteArray FileProcessor::modifyData(const QByteArray &data, const QByteArray &operationKey) {

    if (operationKey.size() != 8) {
        qWarning() << "Operation key must be 8 bytes long.";
        return QByteArray();
    }

    QByteArray modifiedData;
    modifiedData.resize(data.size());

    for (int i = 0; i < data.size(); ++i) {
        char keyByte = operationKey[i % 8];
        modifiedData[i] = data[i] ^ keyByte;
    }

    return modifiedData;
}

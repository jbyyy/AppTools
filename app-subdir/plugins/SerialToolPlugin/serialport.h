#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QSerialPort>

#include "serialparam.h"

class SerialPort : public QSerialPort
{
    Q_OBJECT
public:
    SerialPort(QObject *parent = nullptr);
    ~SerialPort();

    bool openSerial(const SerialParam &param);

public slots:
    void onWrite(const QByteArray&);

signals:
    void serialOnLine(bool);
    void errorMessage(const QString&);
    void serialMessage(const QByteArray&);

private slots:
    void onError();
    void onReadyRead();

private:
    void buildConnect();
};

#endif // SERIALPORT_H
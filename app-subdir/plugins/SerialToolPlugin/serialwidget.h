#ifndef SERIALWIDGET_H
#define SERIALWIDGET_H

#include <QWidget>

class SerialWidgetPrivate;
class SerialWidget : public QWidget
{
    Q_OBJECT
public:   
    enum MessageType { Send, Recv, SuccessInfo, ErrorInfo};

    explicit SerialWidget(QWidget *parent = nullptr);
    ~SerialWidget();

signals:

private slots:
    void onSearchPort();
    void onSendData();

    void onPortChanged(const QString&);
    void onBaudRateChanged(const QString&);
    void onDataBitsChanged(const QString&);
    void onStopBitsChanged(const QString&);
    void onParityChanged(const QString&);
    void onFlowControlChanged(const QString&);

    void onOpenOrCloseSerial(bool);

    void onSerialOnline(bool);
    void onAppendError(const QString&);
    void onSerialRecvMessage(const QByteArray &bytes);

    void onAutoSend(bool);


private:
    void setupUI();
    void init();
    void buildConnect();
    void setSerialParam();
    void destorySerialThread();

    void appendDisplay(MessageType, const QString&);
    void setSendCount(int);
    void setRecvCount(int);


    SerialWidgetPrivate *d;
};

#endif // SERIALWIDGET_H

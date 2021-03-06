#ifndef CONFIGWIDGET_H
#define CONFIGWIDGET_H

#include <QWidget>

class ConfigWidgetPrivate;
class ConfigWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ConfigWidget(QWidget *parent = nullptr);
    ~ConfigWidget();

private:
    void setupUI();
    void initWindow();
    void setWindowParam();

    void save();

    QScopedPointer<ConfigWidgetPrivate> d;
};

#endif // CONFIGWIDGET_H

#ifndef COMMONWIDGET_H
#define COMMONWIDGET_H

#include "controls_global.h"

#include <QWidget>

class CommonWidgetPrivate;
class CONTROLS_EXPORT CommonWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CommonWidget(QWidget *parent = nullptr);
    ~CommonWidget();

    void hideRestoreMaxButton();
    void hideMinButton();

    void setTitle(const QString&);
    void setIcon(const QIcon&);

    void setCentralWidget(QWidget*);

signals:
    void aboutToclose();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    void setupUI();
    QWidget* titleWidget();
    void buildConnnect();

    CommonWidgetPrivate *d;
};

#endif // COMMONWIDGET_H
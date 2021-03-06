#include "mpages.h"

#include <QtWidgets>

namespace Core {

class MPagesPrivate{
public:
    MPagesPrivate(QObject *parent)
        : owner(parent){
        button = new QPushButton;
        button->setProperty("class", "GroupItemButton");
    }
    QObject *owner;
    QPushButton *button;
    QWidget *widget = nullptr;
};

MPages::MPages(QObject *parent)
    : QObject(parent)
    , d(new MPagesPrivate(this))
{
}

MPages::~MPages()
{

}

QPushButton *MPages::button() const
{
    return d->button;
}

QWidget *MPages::widget() const
{
    return d->widget;
}

void MPages::setWidget(QWidget *widget)
{
    d->widget = widget;
}

void MPages::setButtonName(const QString &text)
{
    d->button->setText(text);
}

void MPages::setButtonGroup(MPages::Group group)
{
    d->button->setProperty("Group", group);
}

}

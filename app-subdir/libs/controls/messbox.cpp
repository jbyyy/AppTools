#include "messbox.h"

#include <QtWidgets>

class MessBoxPrivate{
public:
    MessBoxPrivate(CommonWidget *parent) : owner(parent){
        iconLabel = new QLabel(owner);
        messageLabel = new QLabel(owner);
        messageLabel->setObjectName("MessageLabel");
        //messageLabel->setWordWrap(true);
        closeButton = new QPushButton(QObject::tr("Close"), owner);
        closeButton->setObjectName("MessCloseButton");
        yesButton = new QPushButton(QObject::tr("Yes"), owner);
        yesButton->setObjectName("YesButton");
        noButton = new QPushButton(QObject::tr("No"), owner);
        noButton->setObjectName("NoButton");
    }
    CommonWidget *owner;
    QLabel *iconLabel;
    QLabel *messageLabel;
    QPushButton *yesButton;
    QPushButton *noButton;
    QPushButton *closeButton;
};

MessBox::MessBox(QWidget *parent) : Dialog(parent)
  , d(new MessBoxPrivate(this))
{
    setWindowFlags(Qt::Dialog | Qt::Popup | Qt::FramelessWindowHint);
    setWindowModality(Qt::ApplicationModal);
    setMinButtonVisible(false);
    setRestoreMaxButtonVisible(false);
    setupUI();
    buildConnect();
    resize(450, 280);
}

MessBox::~MessBox()
{
    delete d;
}

Dialog::ExecFlags MessBox::Info(QWidget *parent, const QString &msg, MessButton button)
{
    MessBox messBox(parent);
    messBox.setIconLabelObjectName("InfoLabel");
    messBox.setMessage(msg);
    if(button == (YESButton | NOButton)){
        messBox.setYesAndNoButtonVisible(true);
    }else if(button == CloseButton){
        messBox.setCloseButtonVisible(true);
    }
    return messBox.exec();
}

Dialog::ExecFlags MessBox::Warning(QWidget *parent, const QString &msg, MessButton button)
{
    MessBox messBox(parent);
    messBox.setIconLabelObjectName("WarningLabel");
    messBox.setMessage(msg);
    if(button == (YESButton | NOButton)){
        messBox.setYesAndNoButtonVisible(true);
    }else if(button == CloseButton){
        messBox.setCloseButtonVisible(true);
    }
    return messBox.exec();
}

void MessBox::setMessage(const QString &msg)
{
    d->messageLabel->setText(msg);
}

void MessBox::setIconLabelObjectName(const QString &objectName)
{
    d->iconLabel->setObjectName(objectName);
}

void MessBox::setYesAndNoButtonVisible(bool state)
{
    d->yesButton->setVisible(state);
    d->noButton->setVisible(state);
}

void MessBox::setCloseButtonVisible(bool state)
{
    d->closeButton->setVisible(state);
}

void MessBox::setupUI()
{
    QHBoxLayout *mLayout = new QHBoxLayout;
    mLayout->setSpacing(20);
    mLayout->addStretch(0);
    mLayout->addWidget(d->iconLabel);
    mLayout->addWidget(d->messageLabel);
    mLayout->addStretch(0);

    QWidget *btnWidget = new QWidget(this);
    btnWidget->setObjectName("MessBtnWidget");
    QHBoxLayout *btnLayout = new QHBoxLayout(btnWidget);
    btnLayout->setContentsMargins(5, 5, 10, 5);
    btnLayout->setSpacing(5);
    btnLayout->addStretch(0);
    btnLayout->addWidget(d->yesButton);
    btnLayout->addWidget(d->noButton);
    btnLayout->addWidget(d->closeButton);

    d->yesButton->hide();
    d->noButton->hide();
    d->closeButton->hide();

    QWidget *widget = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(widget);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addLayout(mLayout);
    layout->addWidget(btnWidget);

    setCentralWidget(widget);
}

void MessBox::buildConnect()
{
    connect(d->closeButton, &QPushButton::clicked, this, &MessBox::rejected);
    connect(d->yesButton, &QPushButton::clicked, this, &MessBox::accept);
    connect(d->noButton, &QPushButton::clicked, this, &MessBox::rejected);
}

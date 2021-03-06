#include "loginwidget.h"
#include "registerwidget.h"
#include "useraccountsystem.h"
#include "accountquery.h"

#include <controls/accountcontrols.h>

#include <QtWidgets>

namespace AccountSystem {

class LoginWidgetPrivate{
public:
    LoginWidgetPrivate(QWidget *parent)
        : owner(parent){
        avatarWidget = new AvatarWidget(owner);
        usernameBox = new EditComboBox(owner);
        promptLabel = new QLabel(owner);
        promptLabel->setObjectName("PromptLabel");
        passwordEdit = new PasswordLineEdit(owner);
        autoLoginBox = new QCheckBox(QObject::tr("AutoLogin"), owner);
    }
    QWidget *owner;
    AvatarWidget *avatarWidget;
    EditComboBox *usernameBox;
    QLabel *promptLabel;
    PasswordLineEdit *passwordEdit;
    QCheckBox *autoLoginBox;
    AccountQuery *accountQuery = nullptr;
};

LoginWidget::LoginWidget(AccountQuery *accountQuery,
                         const QStringList &usernameList,
                         QWidget *parent)
    : Dialog(parent)
    , d(new LoginWidgetPrivate(this))
{
    setObjectName("LoginWidget");
    setTitle(tr("Login Widget"));
    d->accountQuery = accountQuery;
    setMinButtonVisible(true);
    setupUI();
    buildConnect();
    for(const QString& username: usernameList)
        d->usernameBox->addAccount(username);
    resize(300, 485);
}

LoginWidget::~LoginWidget()
{
}

QString LoginWidget::username() const
{
    return d->usernameBox->currentText().trimmed();
}

QString LoginWidget::password() const
{
    return d->passwordEdit->text().trimmed();
}

QStringList LoginWidget::usernameList() const
{
    return d->usernameBox->accountList();
}

bool LoginWidget::autoLogin()
{
    return d->autoLoginBox->isChecked();
}

void LoginWidget::onLogin()
{
    d->promptLabel->clear();
    QString username = d->usernameBox->currentText().trimmed();
    if(username.isEmpty()){
        d->promptLabel->setText(tr("Please enter username!"));
        d->usernameBox->setFocus();
        return;
    }
    QString password = d->passwordEdit->text().trimmed();
    if(password.isEmpty()){
        d->promptLabel->setText(tr("Please enter password!"));
        d->passwordEdit->setFocus();
        return;
    }

    if(d->accountQuery->checkAccount(username, password)){
        if(!d->usernameBox->accountList().contains(username))
            d->usernameBox->addAccount(username);
        accept();
        return;
    }
    d->promptLabel->setText(tr("Incorrect account or password!"));
}

void LoginWidget::onRegister()
{
    RegisterWidget regist(d->accountQuery, this);
    if(regist.exec() == RegisterWidget::Accepted){
        d->usernameBox->addAccount(regist.username());
        d->passwordEdit->setText(regist.password());
        accept();
    }
}

void LoginWidget::setupUI()
{
    QPushButton *registerButton = new QPushButton(tr("Registered"), this);
    registerButton->setObjectName("FlatButton");
    connect(registerButton, &QPushButton::clicked, this, &LoginWidget::onRegister);

    QPushButton *loginButton = new QPushButton(tr("Login"), this);
    loginButton->setObjectName("BlueButton");
    connect(loginButton, &QPushButton::clicked, this, &LoginWidget::onLogin);

    QHBoxLayout *chooseLayout = new QHBoxLayout;
    chooseLayout->setContentsMargins(0, 0, 0, 0);
    chooseLayout->addWidget(d->autoLoginBox);
    chooseLayout->addWidget(registerButton);

    QWidget *widget = new QWidget(this);
    widget->setObjectName("WhiteWidget");
    QVBoxLayout *layout = new QVBoxLayout(widget);
    layout->addWidget(d->avatarWidget);
    layout->addWidget(d->usernameBox);
    layout->addWidget(d->promptLabel);
    layout->addWidget(d->passwordEdit);
    layout->addLayout(chooseLayout);
    layout->addWidget(loginButton);

    setCentralWidget(widget);
}

void LoginWidget::buildConnect()
{
    connect(d->passwordEdit, &PasswordLineEdit::returnPressed, this, &LoginWidget::onLogin);
}

}

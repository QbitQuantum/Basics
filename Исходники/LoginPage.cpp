///
//  Constructor
//
LoginPage::LoginPage(WContainerWidget *parent) :
    WContainerWidget(parent),
    mLoggedIn(false),
    mLogoutRequested(false)
{
    setStyleClass("maindiv");

    WLabel* loginText = new WLabel("Enter username and password:"******"");
    WText *userNameText = new WText("User Name:");

    mPasswordLineEdit = new WLineEdit("");
    mPasswordLineEdit->setEchoMode(WLineEdit::Password);

    WText *passwordText = new WText("Password:"******"Login");

    WGridLayout *loginLayout = new WGridLayout();
    loginLayout->addWidget(userNameText, 0, 0, AlignRight);
    loginLayout->addWidget(mUserNameLineEdit, 0, 1, AlignLeft);
    loginLayout->addWidget(passwordText, 1, 0, AlignRight);
    loginLayout->addWidget(mPasswordLineEdit, 1, 1, AlignLeft);

    WGridLayout *textLayout = new WGridLayout();
    textLayout->addWidget(loginText, 0, 0, AlignCenter);

    WGridLayout *buttonLayout = new WGridLayout();
    buttonLayout->addWidget(loginButton, 0, 0, AlignCenter | AlignMiddle);

    WImage *chbLogo = new WImage(tr("logo-image").toUTF8());
    WGridLayout *chbLogoLayout = new WGridLayout();
    chbLogoLayout->addWidget(chbLogo, 0, 0, AlignCenter);

    WLabel *titleLabel = new WLabel(tr("page-top-text"));
    titleLabel->setStyleClass("logintitlediv");
    WGridLayout *titleLayout = new WGridLayout();
    titleLayout->addWidget(titleLabel, 0, 0, AlignCenter);

    WContainerWidget *loginContainer = new WContainerWidget();
    loginContainer->setStyleClass("logindiv");

    mFailureLabel = new WLabel("Invalid username and/or password.  Try again.");
    mFailureLabel->setStyleClass("redtext");

    WVBoxLayout *layout = new WVBoxLayout();
    layout->addLayout(chbLogoLayout, AlignCenter);
    layout->addLayout(titleLayout, AlignCenter);
    layout->addLayout(textLayout, AlignCenter);
    layout->addLayout(loginLayout);
    layout->addWidget(mFailureLabel);
    layout->addLayout(buttonLayout, AlignCenter | AlignMiddle);

    mFailureLabel->hide();

    loginContainer->setLayout(layout, AlignTop);

    WVBoxLayout *pageLayout = new WVBoxLayout();
    pageLayout->addWidget(loginContainer);
    pageLayout->addWidget(new WText(tr("login-page-text")));

    setLayout(pageLayout, AlignMiddle | AlignCenter);

    loginButton->clicked().connect(SLOT(this, LoginPage::login));
    mPasswordLineEdit->enterPressed().connect(SLOT(this, LoginPage::login));

    resetAll();
}
WWidget *RootLogin::Layout()
{
    m_cgiRoot->setTitle(m_lang->GetString("ROOT_LOGIN_TITLE"));

    Div *root = new Div("RootLogin");

    Div *dvNoScript = new Div(root, "dvNoScript");
    new WText(m_lang->GetString("WARN_NO_SCRIPT"), dvNoScript);

    Div *dvLogin = new Div(root, "dvLogin");
    new WText(m_lang->GetString("ROOT_LOGIN_FORM_TITLE"), dvLogin);

    Div *dvLangBar = new Div(dvLogin, "dvLangBar");
    new WText(L"<span style=\"color: #333; font-family: Tahoma !important; letter-spacing: 1px;\">"
	          "<a href=\"?enroot\" style=\"color: #666; text-decoration: none;\">EN</a>"
              "&nbsp;|&nbsp;"
              "<a href=\"?faroot\" style=\"color: #666; text-decoration: none;\">فا</a>"
			  "</span>", dvLangBar);

    Div *dvLoginForm = new Div(dvLogin, "dvLoginForm", "form");
    WGridLayout *dvLoginFormLayout = new WGridLayout();

    m_loginUserEdit = new WLineEdit();
    m_loginPwdEdit = new WLineEdit();
    m_loginPwdEdit->setEchoMode(WLineEdit::Password);
    m_loginCaptchaEdit = new WLineEdit();

    dvLoginFormLayout->addWidget(new WText(m_lang->GetString("ROOT_LOGIN_FORM_USER_TEXT")),
                                 0, 0, AlignLeft | AlignMiddle);
    dvLoginFormLayout->addWidget(m_loginUserEdit, 0, 1);

    dvLoginFormLayout->addWidget(new WText(m_lang->GetString("ROOT_LOGIN_FORM_PWD_TEXT")),
                                 1, 0, AlignLeft | AlignMiddle);
    dvLoginFormLayout->addWidget(m_loginPwdEdit, 1, 1);

    dvLoginFormLayout->addWidget(new WText(m_lang->GetString("ROOT_LOGIN_FORM_CAPTCHA_TEXT")),
                                 2, 0, AlignLeft | AlignMiddle);
    dvLoginFormLayout->addWidget(m_loginCaptchaEdit, 2, 1);

    dvLoginFormLayout->setVerticalSpacing(11);
    dvLoginFormLayout->setColumnStretch(0, 100);
    dvLoginFormLayout->setColumnStretch(1, 200);
    dvLoginForm->resize(300, WLength::Auto);
    dvLoginForm->setLayout(dvLoginFormLayout);

    m_loginCaptchaImage = m_captcha->GenCap();
    dvLogin->addWidget(m_loginCaptchaImage);

    m_errLoginText = new WText(dvLogin);
    WPushButton *loginBtn = new WPushButton(m_lang->GetString("ROOT_LOGIN_FORM_LOGIN_TEXT"),
                                            dvLogin);
    loginBtn->setStyleClass("formButton");

    WText *forgotLink = new WText(
            L"<p style=\"text-align: right !important; margin-top: 25px;\">"
            + m_lang->GetString("ROOT_LOGIN_FORM_FORGOT_TEXT") + L"</p>",
            dvLogin);
    forgotLink->setStyleClass("link");

    m_dvForgot = new Div(dvLogin, "dvForgot");
    m_forgotFormFlag = false;

    Div *dvCopyright = new Div(root, "dvCopyright");
    new WText(Base::Copyright(m_cgiEnv->CurrentLang), dvCopyright);

    WSignalMapper<WText *> *forgotMap = new WSignalMapper<WText *>(this);
    forgotMap->mapped().connect(this, &RootLogin::ForgotForm);
    forgotMap->mapConnect(forgotLink->clicked(), forgotLink);

    WLengthValidator *loginUserValidator = new WLengthValidator(Base::MIN_USERNAME_LENGTH,
                                                                Base::MAX_USERNAME_LENGTH);
    loginUserValidator->setMandatory(true);
    m_loginUserEdit->setValidator(loginUserValidator);

    WLengthValidator *loginPwdValidator = new WLengthValidator(Base::MIN_PASSWORD_LENGTH,
                                                               Base::MAX_PASSWORD_LENGTH);
    loginPwdValidator->setMandatory(true);
    m_loginPwdEdit->setValidator(loginPwdValidator);

    m_loginCaptchaValidator = new WIntValidator(m_captcha->Result, m_captcha->Result);
    m_loginCaptchaValidator->setMandatory(true);
    m_loginCaptchaEdit->setValidator(m_loginCaptchaValidator);

    m_loginUserEdit->enterPressed().connect(this, &RootLogin::LoginOK);
    m_loginPwdEdit->enterPressed().connect(this, &RootLogin::LoginOK);
    m_loginCaptchaEdit->enterPressed().connect(this, &RootLogin::LoginOK);
    loginBtn->clicked().connect(this, &RootLogin::LoginOK);

    return root;
}
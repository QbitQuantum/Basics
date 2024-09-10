void MorePage::initializeWidget()
{
    //导航栏
    QString strTitle = tr("更多...");
    navigationBar = new NavigationBar(this);
    navigationBar->setTitleText(strTitle);

    QHBoxLayout* pHLTop = new QHBoxLayout();
    pHLTop->addWidget(navigationBar);
    pHLTop->setSpacing(0);
    pHLTop->setMargin(0);
    this->setTopbarLayout(pHLTop);


    //个人信息
    QLabel* themeWidget = new QLabel;
    QPixmap pixmap = QPixmap(ImagePath::MOREPAGE_THEME);
    pixmap.setDevicePixelRatio(2);
    themeWidget->setAutoFillBackground(true);
    themeWidget->setFixedHeight(this->screenHeight()*0.25);
    themeWidget->setFixedWidth(this->screenWidth());
    themeWidget->setPixmap(pixmap);
    themeWidget->setScaledContents(true);

    btnPersonalInfo = new QToolButton;
    btnPersonalInfo->setFixedWidth(this->screenWidth());
    btnPersonalInfo->setFixedHeight(this->screenHeight()*0.15);
    btnPersonalInfo->setIconSize(QSize(btnPersonalInfo->height()*0.7, btnPersonalInfo->height()*0.7));
    btnPersonalInfo->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    btnPersonalInfo->setStyleSheet("font:16px; color:white;background-color:rgba(0,0,0,0)");
    connect(btnPersonalInfo, SIGNAL(clicked()), SLOT(on_btnPersonal_clicked()));

    QVBoxLayout* themeLayout = new QVBoxLayout;
    themeLayout->addWidget(btnPersonalInfo);
    themeLayout->setMargin(0);
    themeWidget->setLayout(themeLayout);

    //设置
    btnSetting = new GroupButton;
    btnSetting->setStyleSheet(SheetStyle::GROUPBUTTON_BOTTOMBORDER);
    QPixmap settingPixmap(ImagePath::SETTING);
    this->setGroupButton(btnSetting, settingPixmap, tr("设置"));
    connect(btnSetting, SIGNAL(clicked()), SLOT(on_btnSetting_clicked()));

    QVBoxLayout* vblTotalLayout = new QVBoxLayout;
    vblTotalLayout->addWidget(themeWidget);
    vblTotalLayout->addSpacing(this->screenHeight()*0.026);
    vblTotalLayout->addWidget(btnSetting);
    vblTotalLayout->setAlignment(Qt::AlignTop);
    vblTotalLayout->setMargin(0);
    vblTotalLayout->setSpacing(0);
    this->setBodyPartLayout(vblTotalLayout);

    //屏幕触摸滚动设置
    this->setBodyScreenHeight(this->scrollAreaHasBottomBarHeight());
    this->installScrollViewportArea();
    this->loadLocalData(curAccountID);
}
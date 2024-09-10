QFrame *CentralWidget::createRightPanel()
{
    QVBoxLayout *rightPanelLayout = new QVBoxLayout;

    rightPanelLayout->addWidget(new Section(tr(SECTION_CONNECT)));
    rightPanelLayout->addWidget(createConnectButton());

    rightPanelLayout->addWidget(new Section(tr(SECTION_CONNECT_STATUS)));
    rightPanelLayout->addWidget(createConnectionStatusUi());

    rightPanelLayout->addWidget(new Section(tr(SECTION_BATTERY)));
    rightPanelLayout->addWidget(createBatteryChargeUi());

    rightPanelLayout->addWidget(new Section(tr(SECTION_OBSTACLE)));
    rightPanelLayout->addWidget(createDistanceToObstacleUi());

    rightPanelLayout->addWidget(new Section(tr(SECTION_SPEED)));
    rightPanelLayout->addWidget(createSpeedUi());
    rightPanelLayout->addStretch(1);

    QFrame *rightPanelWidget = new QFrame;
    rightPanelWidget->setMinimumWidth(200);
    rightPanelWidget->setFrameStyle(QFrame::StyledPanel | QFrame::Raised);
    rightPanelWidget->setLayout(rightPanelLayout);

    return rightPanelWidget;
}
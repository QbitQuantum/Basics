UpdateItem::UpdateItem(QFrame *parent)
    :SettingsItem(parent),
      m_appIcon(new SmallLabel),
      m_appName(new SmallLabel),
      m_appVersion(new SmallLabel),
      m_appChangelog(new SmallLabel),
      m_details(new QPushButton)
{
    TranslucentFrame *iconContainer = new TranslucentFrame;
    iconContainer->setFixedWidth(36);

    m_iconLayout = new QVBoxLayout;
    m_iconLayout->setMargin(0);
    m_iconLayout->setSpacing(0);
    m_iconLayout->addWidget(m_appIcon, 0, Qt::AlignCenter);
    m_iconLayout->addStretch();

    iconContainer->setLayout(m_iconLayout);

    m_appIcon->setFixedSize(36, 36);

    QFont changelogFont("Noto Mono");
    changelogFont.setPointSize(10);

    m_appChangelog->setFont(changelogFont);
    m_appChangelog->setWordWrap(true);
    m_appChangelog->setTextFormat(Qt::RichText);
    m_appChangelog->setTextInteractionFlags(Qt::NoTextInteraction);
    m_appChangelog->setContextMenuPolicy(Qt::NoContextMenu);
    m_appChangelog->setOpenExternalLinks(true);
    m_appChangelog->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    m_appChangelog->setFocusPolicy(Qt::NoFocus);
    m_appChangelog->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_details->setFlat(true);
    m_details->setText(tr("Details"));

    QHBoxLayout* logLayout = new QHBoxLayout;
    logLayout->setMargin(0);
    logLayout->setSpacing(0);
    logLayout->addWidget(m_appChangelog, 1);
    logLayout->addWidget(m_details);

    QHBoxLayout *nameLayout = new QHBoxLayout;
    nameLayout->setMargin(0);
    nameLayout->setSpacing(0);
    nameLayout->addWidget(m_appName);
    nameLayout->addSpacing(4);
    nameLayout->addWidget(m_appVersion);
    nameLayout->addStretch();

    QVBoxLayout* rightLayout = new QVBoxLayout;
    rightLayout->setMargin(0);
    rightLayout->setSpacing(0);
    rightLayout->addStretch();
    rightLayout->addLayout(nameLayout);
    rightLayout->addSpacing(1);
    rightLayout->addLayout(logLayout);
    rightLayout->addStretch();

    QHBoxLayout* layout = new QHBoxLayout();
    layout->setMargin(10);
    layout->setSpacing(0);
    layout->addWidget(iconContainer);
    layout->addSpacing(10);
    layout->addLayout(rightLayout, 1);

    setLayout(layout);

    connect(m_details, &QPushButton::clicked, [this] {
        m_details->hide();
        // The point of this timer is that the calculation should be taken
        // after the relayout of this item caused by the hide of details button.
        QTimer::singleShot(0, this, &UpdateItem::expandChangelog);
    });

//    connect(m_openWebsite, &QPushButton::clicked, [this] {
//        qDebug() << QString("open website %1 to see release notes of %2").arg(m_anchorAddress).arg(m_anchorName);
//        QDesktopServices::openUrl(m_anchorAddress);
//    });
    setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Expanding);
}
FindBarBase::FindBarBase(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout *lay = new QHBoxLayout(this);
    lay->setMargin(2);

    QToolButton *closeBtn = new QToolButton(this);
    closeBtn->setIcon(QIcon::fromTheme(QStringLiteral("dialog-close")));
    closeBtn->setObjectName(QStringLiteral("close"));
    closeBtn->setIconSize(QSize(16, 16));
    closeBtn->setToolTip(i18n("Close"));

#ifndef QT_NO_ACCESSIBILITY
    closeBtn->setAccessibleName(i18n("Close"));
#endif

    closeBtn->setAutoRaise(true);
    lay->addWidget(closeBtn);

    QLabel *label = new QLabel(i18nc("Find text", "F&ind:"), this);
    lay->addWidget(label);

    mSearch = new PimCommon::LineEditWithCompleter(this);
    mSearch->setObjectName(QStringLiteral("searchline"));
    mSearch->setToolTip(i18n("Text to search for"));
    mSearch->setClearButtonShown(true);
    label->setBuddy(mSearch);
    lay->addWidget(mSearch);

    mFindNextBtn = new QPushButton(QIcon::fromTheme(QStringLiteral("go-down-search")), i18nc("Find and go to the next search match", "Next"), this);
    mFindNextBtn->setToolTip(i18n("Jump to next match"));
    mFindNextBtn->setObjectName(QStringLiteral("findnext"));
    lay->addWidget(mFindNextBtn);
    mFindNextBtn->setEnabled(false);

    mFindPrevBtn = new QPushButton(QIcon::fromTheme(QStringLiteral("go-up-search")), i18nc("Find and go to the previous search match", "Previous"), this);
    mFindPrevBtn->setToolTip(i18n("Jump to previous match"));
    mFindPrevBtn->setObjectName(QStringLiteral("findprevious"));
    lay->addWidget(mFindPrevBtn);
    mFindPrevBtn->setEnabled(false);

    QPushButton *optionsBtn = new QPushButton(this);
    optionsBtn->setText(i18n("Options"));
    optionsBtn->setToolTip(i18n("Modify search behavior"));
    mOptionsMenu = new QMenu(optionsBtn);
    mCaseSensitiveAct = mOptionsMenu->addAction(i18n("Case sensitive"));
    mCaseSensitiveAct->setCheckable(true);

    optionsBtn->setMenu(mOptionsMenu);
    lay->addWidget(optionsBtn);

    connect(closeBtn, &QToolButton::clicked, this, &FindBarBase::closeBar);
    connect(mFindNextBtn, &QPushButton::clicked, this, &FindBarBase::findNext);
    connect(mFindPrevBtn, &QPushButton::clicked, this, &FindBarBase::findPrev);
    connect(mCaseSensitiveAct, &QAction::toggled, this, &FindBarBase::caseSensitivityChanged);
    connect(mSearch, &KLineEdit::textChanged, this, &FindBarBase::autoSearch);
    connect(mSearch, &KLineEdit::clearButtonClicked, this, &FindBarBase::slotClearSearch);

    mStatus = new QLabel;
    mStatus->setObjectName(QStringLiteral("status"));
    QFontMetrics fm(mStatus->font());
    mNotFoundString = i18n("Phrase not found");
    mStatus->setFixedWidth(fm.width(mNotFoundString));
    lay->addWidget(mStatus);

    setSizePolicy(QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed));
    //lay->addStretch();
    hide();
}
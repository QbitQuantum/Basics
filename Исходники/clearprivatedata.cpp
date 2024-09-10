ClearPrivateData::ClearPrivateData(QWidget *parent)
    : QDialog(parent, Qt::WindowTitleHint | Qt::WindowSystemMenuHint)
{
    setWindowTitle(tr("Clear Private Data"));

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(new QLabel(tr("Clear the following items:")));

    m_browsingHistory = new QCheckBox(tr("&Browsing History"));
    m_browsingHistory->setChecked(true);
    layout->addWidget(m_browsingHistory);

    m_downloadHistory = new QCheckBox(tr("&Download History"));
    m_downloadHistory->setChecked(true);
    layout->addWidget(m_downloadHistory);

    m_searchHistory = new QCheckBox(tr("&Search History"));
    m_searchHistory->setChecked(true);
    layout->addWidget(m_searchHistory);

    m_cookies = new QCheckBox(tr("&Cookies"));
    m_cookies->setChecked(true);
    layout->addWidget(m_cookies);

    m_cache = new QCheckBox(tr("C&ached Web Pages"));
#if QT_VERSION < 0x040500
    m_cache->setEnabled(false);
#endif
    m_cookies->setChecked(true);
    layout->addWidget(m_cache);

    m_favIcons = new QCheckBox(tr("Website &Icons"));
    m_favIcons->setChecked(true);
    layout->addWidget(m_favIcons);

    QPushButton *acceptButton = new QPushButton(tr("Clear &Private Data"));
    acceptButton->setDefault(true);
    QPushButton *rejectButton = new QPushButton(tr("&Cancel"));
    QDialogButtonBox *buttonBox = new QDialogButtonBox;
    buttonBox->addButton(acceptButton, QDialogButtonBox::AcceptRole);
    buttonBox->addButton(rejectButton, QDialogButtonBox::RejectRole);
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
    layout->addWidget(buttonBox);

    setLayout(layout);
    acceptButton->setFocus(Qt::OtherFocusReason);
}
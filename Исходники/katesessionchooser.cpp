KateSessionChooser::KateSessionChooser(QWidget *parent, const QString &lastSession)
    : QDialog(parent)
{
    setWindowTitle(i18n("Session Chooser"));
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    m_sessions = new QTreeWidget(this);
    m_sessions->setMinimumSize(400, 200);
    mainLayout->addWidget(m_sessions);
    QStringList header;
    header << i18n("Session Name");
    header << i18nc("The number of open documents", "Open Documents");
    header << QString();
    m_sessions->setHeaderLabels(header);
    m_sessions->header()->setStretchLastSection(false);
    m_sessions->header()->setSectionResizeMode(0, QHeaderView::Stretch);
    m_sessions->header()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    m_sessions->header()->setSectionResizeMode(2, QHeaderView::Fixed);
    m_sessions->header()->resizeSection(2, 32);
    m_sessions->setRootIsDecorated(false);
    m_sessions->setItemsExpandable(false);
    m_sessions->setAllColumnsShowFocus(true);
    m_sessions->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_sessions->setSelectionMode(QAbstractItemView::SingleSelection);

    qCDebug(LOG_KATE) << "Last session is:" << lastSession;

    KateSessionList slist = KateApp::self()->sessionManager()->sessionList();
    qSort(slist.begin(), slist.end(), KateSession::compareByName);

    foreach(const KateSession::Ptr & session, slist) {
        KateSessionChooserItem *item = new KateSessionChooserItem(m_sessions, session);
        QPushButton *tmp = new QPushButton(QIcon::fromTheme(QStringLiteral("document")), QString(), m_sessions);
        QMenu *popup = new QMenu(tmp);
        QAction *a = popup->addAction(i18n("Clone session settings"));
        a->setData(QVariant::fromValue((void *)item));
        connect(a, SIGNAL(triggered()), this, SLOT(slotCopySession()));
        a = popup->addAction(i18n("Delete this session"));
        a->setData(QVariant::fromValue((void *)item));
        connect(a, SIGNAL(triggered()), this, SLOT(slotDeleteSession()));
        tmp->setMenu(popup);
        m_sessions->setItemWidget(item, 2, tmp);

        if (session->name() == lastSession) {
            m_sessions->setCurrentItem(item);
        }
    }
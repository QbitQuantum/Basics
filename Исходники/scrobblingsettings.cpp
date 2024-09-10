ScrobblingSettings::ScrobblingSettings(QWidget *parent)
    : QWidget(parent)
{
    setupUi(this);

    connect(loginButton, SIGNAL(clicked()), this, SLOT(save()));
    connect(Scrobbler::self(), SIGNAL(authenticated(bool)), SLOT(showStatus(bool)));
    connect(Scrobbler::self(), SIGNAL(error(QString)), SLOT(showError(QString)));
    connect(user, SIGNAL(textChanged(QString)), SLOT(controlLoginButton()));
    connect(pass, SIGNAL(textChanged(QString)), SLOT(controlLoginButton()));
//    connect(enableScrobbling, SIGNAL(toggled(bool)), Scrobbler::self(), SLOT(setEnabled(bool)));
//    connect(showLove, SIGNAL(toggled(bool)), Scrobbler::self(), SLOT(setLoveEnabled(bool)));
    connect(Scrobbler::self(), SIGNAL(enabled(bool)), enableScrobbling, SLOT(setChecked(bool)));
    connect(scrobbler, SIGNAL(currentIndexChanged(int)), this, SLOT(scrobblerChanged()));
    loginButton->setEnabled(false);

    QMap<QString, QString> scrobblers=Scrobbler::self()->availableScrobblers();
    QStringList keys=scrobblers.keys();
    keys.sort();
    QString firstMpdClient;
    for (const QString &k: keys) {
        bool viaMpd=Scrobbler::viaMpd(scrobblers[k]);
        if (viaMpd) {
            scrobbler->addItem(tr("%1 (via MPD)", "scrobbler name (via MPD)").arg(k), k);
        } else {
            scrobbler->addItem(k);
        }
        if (viaMpd && firstMpdClient.isEmpty()) {
            firstMpdClient=k;
        }
    }
    if (scrobbler->count()>1) {
        scrobblerName->setVisible(false);
    } else {
        scrobblerName->setText(scrobbler->itemText(0));
        scrobbler->setVisible(false);
        scrobblerLabel->setBuddy(nullptr);
    }
    scrobblerName->setVisible(scrobbler->count()<2);
    if (firstMpdClient.isEmpty()) {
        REMOVE(noteLabel)
    } else {
        noteLabel->setText(tr("If you use a scrobbler which is marked as '(via MPD)' (such as %1), "
                                "then you will need to have this already started and running. "
                                "Cantata can only 'Love' tracks via this, and cannot enable/disable scrobbling.").arg(firstMpdClient));
    }

    #ifdef Q_OS_MAC
    expandingSpacer->changeSize(0, 0, QSizePolicy::Fixed, QSizePolicy::Fixed);
    #endif
}
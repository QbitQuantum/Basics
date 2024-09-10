void Configuration::findApplication(const QString &query)
{
    for (int i = (m_findApplicationUi.resultsLayout->count() - 1); i >= 0; --i)
    {
        m_findApplicationUi.resultsLayout->takeAt(i)->widget()->deleteLater();
        m_findApplicationUi.resultsLayout->removeItem(m_findApplicationUi.resultsLayout->itemAt(i));
    }

    if (query.length() < 3)
    {
        m_findApplicationDialog->adjustSize();

        return;
    }

    KService::List services = KServiceTypeTrader::self()->query("Application", QString("exist Exec and ( (exist Keywords and '%1' ~subin Keywords) or (exist GenericName and '%1' ~~ GenericName) or (exist Name and '%1' ~~ Name) )").arg(query));

    if (!services.isEmpty())
    {
        foreach (const KService::Ptr &service, services)
        {
            if (!service->noDisplay() && service->property("NotShowIn", QVariant::String) != "KDE")
            {
                Launcher* launcher = new Launcher(KUrl(service->entryPath()), m_applet);

                QWidget* entryWidget = new QWidget(static_cast<QWidget*>(parent()));
                QLabel* iconLabel = new QLabel(entryWidget);
                QLabel* textLabel = new QLabel(QString("%1<br /><small>%3</small>").arg(launcher->title()).arg(launcher->description()), entryWidget);

                iconLabel->setPixmap(launcher->icon().pixmap(32, 32));

                textLabel->setFixedSize(240, 40);

                QHBoxLayout* entryWidgetLayout = new QHBoxLayout(entryWidget);
                entryWidgetLayout->addWidget(iconLabel);
                entryWidgetLayout->addWidget(textLabel);
                entryWidgetLayout->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

                entryWidget->setToolTip(QString("<b>%1</b><br /><i>%2</i>").arg(launcher->title()).arg(launcher->description()));
                entryWidget->setLayout(entryWidgetLayout);
                entryWidget->setFixedSize(300, 40);
                entryWidget->setObjectName(service->entryPath());
                entryWidget->installEventFilter(this);
                entryWidget->setCursor(QCursor(Qt::PointingHandCursor));

                m_findApplicationUi.resultsLayout->addWidget(entryWidget);

                delete launcher;
            }
        }
    }
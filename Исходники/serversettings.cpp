ServerSettings::ServerSettings(QWidget *p)
    : QWidget(p)
    , haveBasicCollection(false)
    , isCurrentConnection(false)
    , allOptions(true) // will be toggled
    , prevIndex(0)
{
    setupUi(this);
    #if defined ENABLE_DEVICES_SUPPORT
    musicFolderNoteLabel->appendText(QLatin1String("<i> ")+i18n("This folder will also be used to locate music files "
                                     "for transferring to (and from) devices.")+QLatin1String("</i>"));
    #endif
    connect(combo, SIGNAL(activated(int)), SLOT(showDetails(int)));
    connect(removeButton, SIGNAL(clicked(bool)), SLOT(remove()));
    connect(addButton, SIGNAL(clicked(bool)), SLOT(add()));
    connect(name, SIGNAL(textChanged(QString)), SLOT(nameChanged()));
    connect(basicDir, SIGNAL(textChanged(QString)), SLOT(basicDirChanged()));
    addButton->setIcon(Icons::self()->addIcon);
    removeButton->setIcon(Icons::self()->removeIcon);
    addButton->setAutoRaise(true);
    removeButton->setAutoRaise(true);

    #if defined Q_OS_WIN
    hostLabel->setText(i18n("Host:"));
    #endif
    basicCoverName->setToolTip(coverName->toolTip());
    basicCoverNameLabel->setToolTip(coverName->toolTip());
    coverNameLabel->setToolTip(coverName->toolTip());
    coverName->setValidator(new CoverNameValidator(this));
    basicCoverName->setValidator(new CoverNameValidator(this));
    #ifdef ENABLE_SIMPLE_MPD_SUPPORT
    name->setValidator(new CollectionNameValidator(this));
    #endif
    #ifndef ENABLE_HTTP_STREAM_PLAYBACK
    REMOVE(streamUrlLabel)
    REMOVE(streamUrl)
    REMOVE(streamUrlNoteLabel)
    #endif

    #ifdef Q_OS_MAC
    expandingSpacer->changeSize(0, 0, QSizePolicy::Fixed, QSizePolicy::Fixed);
    #endif
}
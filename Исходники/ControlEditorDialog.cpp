ControlEditorDialog::ControlEditorDialog
        (
            QWidget *parent,
            RosegardenDocument *doc,
            DeviceId device
       ):
        QMainWindow(parent),
        m_studio(&doc->getStudio()),
        m_doc(doc),
        m_device(device),
        m_modified(false)
{
    RG_DEBUG << "ControlEditorDialog::ControlEditorDialog: device is " << m_device << endl;

    QWidget *mainFrame = new QWidget(this);
    QVBoxLayout *mainFrameLayout = new QVBoxLayout;
    setCentralWidget(mainFrame);
    setAttribute(Qt::WA_DeleteOnClose);

    // everything else failed, so screw it, let's just set the fscking minimum
    // width the brute force way
    setMinimumWidth(935);

    setWindowTitle(tr("Manage Controllers"));

    QString deviceName(tr("<no device>"));
    MidiDevice *md =
        dynamic_cast<MidiDevice *>(m_studio->getDevice(m_device));
    if (md)
        deviceName = strtoqstr(md->getName());

    // spacing hack!
    new QLabel("", mainFrame);
    new QLabel(tr("  Controllers for %1 (device %2)")
           .arg(deviceName)
           .arg(device), mainFrame);
    new QLabel("", mainFrame);
    
    QStringList sl;
    sl  << tr("Name  ")
        << tr("Type  ")
        << tr("Number  ")
        << tr("Description  ")
        << tr("Min. value  ")
        << tr("Max. value  ")
        << tr("Default value  ")
        << tr("Color  ")
        << tr("Position on instrument panel");
    
    m_treeWidget = new QTreeWidget(mainFrame);
    m_treeWidget->setHeaderLabels(sl);
    m_treeWidget->setSortingEnabled(true);
    
    mainFrameLayout->addWidget(m_treeWidget);
    
    QFrame *btnBox = new QFrame(mainFrame);
    mainFrameLayout->addWidget(btnBox);
    mainFrame->setLayout(mainFrameLayout);

    btnBox->setSizePolicy(
        QSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed));

    // QT3: I don't think it's necessary to replace the following ",4, 10" with
    // anything to explicitly set the dimensions of the HBox, but there might be
    // some compatibility trickery I'm not remembering, etc.  Leaving as a
    // reminder in case the layout turns out broken:
    QHBoxLayout* layout = new QHBoxLayout(btnBox /*, 4, 10 */);

    m_addButton = new QPushButton(tr("Add"), btnBox);
    m_deleteButton = new QPushButton(tr("Delete"), btnBox);

    m_closeButton = new QPushButton(tr("Close"), btnBox);

    m_addButton->setToolTip(tr("Add a Control Parameter to the Studio"));

    m_deleteButton->setToolTip(tr("Delete a Control Parameter from the Studio"));

    m_closeButton->setToolTip(tr("Close the Control Parameter editor"));

    layout->addStretch(10);
    layout->addWidget(m_addButton);
    layout->addWidget(m_deleteButton);
    layout->addSpacing(30);

    layout->addWidget(m_closeButton);
    layout->addSpacing(5);

    connect(m_addButton, SIGNAL(released()),
            SLOT(slotAdd()));

    connect(m_deleteButton, SIGNAL(released()),
            SLOT(slotDelete()));

    setupActions();

    connect(CommandHistory::getInstance(), SIGNAL(commandExecuted()),
            this, SLOT(slotUpdate()));

    connect(m_treeWidget, SIGNAL(itemDoubleClicked(QTreeWidgetItem *, int)),
            SLOT(slotEdit(QTreeWidgetItem *, int)));

    // Highlight all columns - enable extended selection mode
    //
    m_treeWidget->setAllColumnsShowFocus(true);
    
    m_treeWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);

    initDialog();
    
    // Set the top item in the list, if able.
    if (m_treeWidget->topLevelItemCount()) {
        m_treeWidget->setCurrentItem(m_treeWidget->topLevelItem(0));
    }
}
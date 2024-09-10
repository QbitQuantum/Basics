// ----------------------------------------------------------------------------
// CReporterSendSelectedDialog::createcontent
// ----------------------------------------------------------------------------
void CReporterSendSelectedDialog::createcontent()
{
    Q_D(CReporterSendSelectedDialog);
    setObjectName("CrashReporterSendSelectedDialog");

    int nbrOfFiles = d_ptr->files.count();
    QString message;

    if (nbrOfFiles == 1) {
        //% "<p>This system has 1 stored crash report. Select reports to send to %1 for analysis or to delete.</p>"
        message = qtTrId("qtn_system_has_1_crash_report_send_to_%s").arg(d->server);

    }
    else {
        //% "<p>This system has %1 stored crash reports. Select reports to send to %2 for analysis or to delete.</p>"
        message = qtTrId("qtn_system_has_%1_crash_reports_send_to_%2").arg(nbrOfFiles).arg(d->server);

    }

    // Create content to be placed on central widget.
    QGraphicsWidget *panel = centralWidget();

    // Create layout and policy.
    MLayout *layout = new MLayout(panel);
    layout->setContentsMargins(0,0,0,0);
    panel->setLayout(layout);
    MLinearLayoutPolicy  *policy = new MLinearLayoutPolicy(layout, Qt::Vertical);
    policy->setObjectName("DialogMainLayout");

    // Create message label and hack it to support wordwrapping
    MLabel *messagelabel = new MLabel(message, panel);
    messagelabel->setWordWrap(true);
    messagelabel->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
    messagelabel->setObjectName("DialogMessageLabel");
    messagelabel->setStyleName("CommonFieldLabelInverted");

    d->list = new MList(panel);
    d->cellCreator = new MContentItemCreator;

    d->list->setCellCreator(d->cellCreator);
    d->model = new CReporterSendFileListModel(d->files);
    d->list->setItemModel(d->model);
    d->list->setSelectionMode(MList::MultiSelection);

    // Add widgets to the layout
    policy->addItem(messagelabel, Qt::AlignLeft | Qt::AlignTop);
    policy->addItem(d->list, Qt::AlignLeft | Qt::AlignTop);

    // Add buttons to button area.
    QSignalMapper *mapper = new QSignalMapper(this);
    //% "Send Selected"
    MButton* dialogButton = new MButton(qtTrId("qtn_send_selected_button"));
    dialogButton->setStyleName("CommonSingleButtonInverted");
    policy->addItem(dialogButton, Qt::AlignCenter);
//    MButtonModel *dialogButton = addButton(qtTrId("qtn_send_selected_button"), M::ActionRole);
    connect(dialogButton, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(dialogButton, static_cast<int>(CReporter::SendSelectedButton));

    //% "Send All"
    dialogButton = new MButton(qtTrId("qtn_send_all_button"));
    dialogButton->setStyleName("CommonSingleButtonInverted");
    policy->addItem(dialogButton, Qt::AlignCenter);
//    dialogButton = addButton(qtTrId("qtn_send_all_button"), M::ActionRole);
    connect(dialogButton, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(dialogButton, static_cast<int>(CReporter::SendAllButton));

    //% "Delete Selected"
    dialogButton = new MButton(qtTrId("qtn_delete_selected_button"));
    dialogButton->setStyleName("CommonSingleButtonInverted");
    policy->addItem(dialogButton, Qt::AlignCenter);
//    dialogButton = addButton(qtTrId("qtn_delete_selected_button"), M::DestructiveRole);
    connect(dialogButton, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(dialogButton, static_cast<int>(CReporter::DeleteSelectedButton));

    connect(mapper, SIGNAL(mapped(int)), SIGNAL(actionPerformed(int)));
    connect(mapper, SIGNAL(mapped(int)), SLOT(accept()));
}
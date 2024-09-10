void ConversationPage::processAttachments(const QMailMessage &message)
{
    if (!message.status() & QMailMessageMetaData::HasAttachments)
        return;

    connect(this, SIGNAL(downloadCompleted()), this, SLOT(saveAttachment()));

    bool oneTimeFlag = true;
    for (uint i = 1; i < message.partCount(); ++i)
    {
        QMailMessagePart sourcePart = message.partAt(i);
        if (!(sourcePart.multipartType() == QMailMessagePartContainer::MultipartNone))
            continue;

        if (oneTimeFlag)
        {
            MSeparator *separator = new MSeparator();
            separator->setObjectName("Separator");
            m_policy->addItem(separator);
            oneTimeFlag = false;
        }

        MStylableWidget *w = new MStylableWidget(this);
        QGraphicsLinearLayout *layout = new QGraphicsLinearLayout(Qt::Horizontal);
        w->setLayout(layout);
        //% "Attached: "
        MLabel *label = new MLabel(qtTrId("xx_attached"));
        label->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        label->setObjectName ("AttachmentText");
        layout->addItem(label);
        MButton *button = new MButton(sourcePart.displayName());
        button->setObjectName ("AttachmentButton");
        button->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        layout->addItem(button);

        //% "Download..."
        AttachmentAction *action = new AttachmentAction(qtTrId("xx_download_context_menu"), button, sourcePart);
        connect(action, SIGNAL(triggered()), this, SLOT(openAttachmentDownloadDialog()));

        //% "Open..."
        action = new AttachmentAction(qtTrId("xx_open_context_menu"), button, sourcePart);
        connect(action, SIGNAL(triggered()), this, SLOT(openAttachmentOpenDialog()));
        m_policy->addItem (w);
    }
}
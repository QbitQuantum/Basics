void EditMetadataDialog::showSaveMenu()
{
    popup = new MythPopupBox(GetMythMainWindow(), "Menu");

    QLabel *label = popup->addLabel(tr("Save Changes?"), MythPopupBox::Large, false);
    label->setAlignment(Qt::AlignCenter | Qt::WordBreak);
    QAbstractButton *topButton;

    if (metadataOnly)
    {
        topButton = popup->addButton(tr("Save Changes"), this,
                                        SLOT(saveToMetadata()));
    }
    else
    {
        topButton = popup->addButton(tr("Save Changes"), this,
                                     SLOT(saveAll()));
    }

    popup->addButton(tr("Exit/Do Not Save"), this,
                            SLOT(closeDialog()));

    popup->addButton(tr("Cancel"), this, SLOT(cancelPopup()));

    popup->ShowPopup(this, SLOT(cancelPopup()));

    topButton->setFocus();
}
bool UIListBtnType::incSearchStart(void)
{
    MythPopupBox *popup = new MythPopupBox(GetMythMainWindow(),
                                           "incserach_popup");

    QLabel *caption = popup->addLabel(tr("Search"), MythPopupBox::Large);
    caption->setAlignment(Qt::AlignCenter);

    MythComboBox *modeCombo = new MythComboBox(false, popup, "mode_combo" );
    modeCombo->insertItem(tr("Starts with text"));
    modeCombo->insertItem(tr("Contains text"));
    popup->addWidget(modeCombo);

    MythLineEdit *searchEdit = new MythLineEdit(false, popup, "mode_combo");
    searchEdit->setText(m_incSearch);
    popup->addWidget(searchEdit);
    searchEdit->setFocus();

    popup->addButton(tr("Search"));
    popup->addButton(tr("Cancel"), popup, SLOT(reject()));

    DialogCode res = popup->ExecPopup();

    if (kDialogCodeButton0 == res)
    {
        m_incSearch = searchEdit->text();
        m_bIncSearchContains = (modeCombo->currentIndex() == 1);
        incSearchNext();
    }

    popup->hide();
    popup->deleteLater();

    return (kDialogCodeButton0 == res);
}
bool pixosIfaceOptsDialog::validate()
{
    bool valid = true;
    QString combobox = m_dialog->iface_type->currentText();
    QString type = m_dialog->iface_type->itemData(
        m_dialog->iface_type->currentIndex()).toString();
    QWidget *focus = NULL;
    QString message;

    if (type == "8021q")
    {
        // VLAN ID must be set between 1 <= vid <= 4'094
        // QSpinBox widget enforces these limits
        ;
    }

    if (!valid)
    {
        QMessageBox::warning(this, "Firewall Builder",
                             tr("Input not valid: %1").arg(message), "&Continue",
                             QString::null, QString::null, 0, 1);
        focus->setFocus();
    }
    return valid;
}
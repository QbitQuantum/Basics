QPushButton *QIMessageBox::createButton (int aButton)
{
    if (aButton == 0)
        return 0;

    QString text;
    QDialogButtonBox::ButtonRole role;
    switch (aButton & ButtonMask)
    {
        case Ok:     text = tr("OK");     role = QDialogButtonBox::AcceptRole; break;
        case Yes:    text = tr("Yes");    role = QDialogButtonBox::YesRole; break;
        case No:     text = tr("No");     role = QDialogButtonBox::NoRole; break;
        case Cancel: text = tr("Cancel"); role = QDialogButtonBox::RejectRole; break;
        case Ignore: text = tr("Ignore"); role = QDialogButtonBox::AcceptRole; break;
        case Copy:   text = tr("Copy");   role = QDialogButtonBox::ActionRole; break;
        default:
            AssertMsgFailed(("Type %d is not implemented", aButton));
            return NULL;
    }

    QPushButton *b = mButtonBox->addButton (text, role);

    if (aButton & Default)
    {
        b->setDefault (true);
        b->setFocus();
    }

    if (aButton & Escape)
        mButtonEsc = aButton & ButtonMask;

    return b;
}
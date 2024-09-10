QString WebDialogProvider::getText(QWidget *parent,
                                const QString &title, const QString &label,
                                QLineEdit::EchoMode mode, const QString &text, bool *ok,
                                Qt::WindowFlags flags)
{
    QLineEdit *le = new QLineEdit;
    le->setText(text);
    le->setEchoMode(mode);
    le->setFocus();
    le->selectAll();

    WebDialogProvider dlg(title, label, parent, le, flags);

    QString result;
    bool accepted = (dlg.exec() == QDialog::Accepted);
    if (ok)
    {
        *ok = accepted;
    }
    if (accepted)
    {
        result = le->text();
    }

    return result;
}
QTime QtopiaInputDialog::getTime(QWidget *parent, const QString &title, const QString &label, const QTime &time,
                                 const QTime &minTime, const QTime &maxTime, bool *ok)
{
    QTimeEdit *te = new QTimeEdit(time);
    QFont font(te->font());
    font.setPointSize(font.pointSize()+3);
    te->setFont(font);
    te->setMinimumTime(minTime);
    te->setMaximumTime(maxTime);

    QtopiaInputDialog dlg(parent, title, label, te);
    bool accepted = (QtopiaApplication::execDialog(&dlg) == QDialog::Accepted);
    if (ok)
        *ok = accepted;
    return te->time();
}
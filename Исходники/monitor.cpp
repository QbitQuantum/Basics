void MonitorWindow::save()
{
    QString s = QFileDialog::getSaveFileName ("sim.log", QString::null, this);
    if (s.isEmpty()) return;
    QFile f(s);
    if (!f.open(IO_WriteOnly)){
        QMessageBox::warning(this, i18n("Error"), i18n("Can't create file %1") .arg(s));
        return;
    }
    QCString t;
    if (edit->hasSelectedText()){
        t = unquoteText(edit->selectedText()).local8Bit();
    }else{
        t = unquoteText(edit->text()).local8Bit();
    }
#if defined(WIN32) || defined(__OS2__)
    t.replace(QRegExp("\n"),"\r\n");
#endif
    f.writeBlock(t, t.length());
}
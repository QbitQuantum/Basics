bool ToolsConfigWidget::eventFilter(QObject *o, QEvent *e)
{
    if (e->type() == QEvent::DragEnter || e->type() == QEvent::DragMove) {
        QDragMoveEvent *dme = static_cast<QDragMoveEvent*>(e);
        if (KURLDrag::canDecode(dme))
            dme->accept();
        return true;
    } else if (e->type() == QEvent::Drop) {
        QDropEvent *de = static_cast<QDropEvent*>(e);
        KURL::List fileList;
        if (KURLDrag::decode(de, fileList)) {
            KURL::List::ConstIterator it;
            for (it = fileList.begin(); it != fileList.end(); ++it) {
                if ((*it).isLocalFile() && KDesktopFile::isDesktopFile((*it).path())) {
                    KDesktopFile df((*it).path());
                    ToolsConfigEntry *entry = new ToolsConfigEntry;
                    entry->menutext = df.readName();
                    entry->cmdline = (*it).path();
                    entry->isdesktopfile = true;
                    entry->captured = false;
                    addEntry(entry, &m_toolsmenuEntries);
                }
            }
        }
        return true;
    }

    return ToolsConfigWidgetBase::eventFilter(o, e);
}
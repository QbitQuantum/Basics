void QToolBarAreaLayout::saveState(QDataStream &stream) const
{
    // save toolbar state
    stream << (uchar) ToolBarStateMarkerEx;

    int lineCount = 0;
    for (int i = 0; i < QInternal::DockCount; ++i)
        lineCount += docks[i].lines.count();

    stream << lineCount;

    for (int i = 0; i < QInternal::DockCount; ++i) {
        const QToolBarAreaLayoutInfo &dock = docks[i];

        for (int j = 0; j < dock.lines.count(); ++j) {
            const QToolBarAreaLayoutLine &line = dock.lines.at(j);

            stream << i << line.toolBarItems.count();

            for (int k = 0; k < line.toolBarItems.count(); ++k) {
                const QToolBarAreaLayoutItem &item = line.toolBarItems.at(k);
                QWidget *widget = const_cast<QLayoutItem*>(item.widgetItem)->widget();
                QString objectName = widget->objectName();
                if (objectName.isEmpty()) {
                    qWarning("QMainWindow::saveState(): 'objectName' not set for QToolBar %p '%s'",
                                widget, widget->windowTitle().toLocal8Bit().constData());
                }
                stream << objectName;
                stream << (uchar) !widget->isHidden();
                stream << item.pos;
                stream << item.size;

                uint geom0, geom1;
                packRect(&geom0, &geom1, widget->geometry(), widget->isWindow());
                stream << geom0 << geom1;
            }
        }
    }
}
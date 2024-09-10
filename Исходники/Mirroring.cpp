bool Mirroring::accept()
{
    if (ui->shapes->selectedItems().isEmpty()) {
        QMessageBox::critical(this, windowTitle(),
            tr("Select a shape for mirroring, first."));
        return false;
    }

    App::Document* activeDoc = App::GetApplication().getDocument((const char*)this->document.toLatin1());
    if (!activeDoc) {
        QMessageBox::critical(this, windowTitle(),
            tr("No such document '%1'.").arg(this->document));
        return false;
    }

    Gui::WaitCursor wc;
    unsigned int count = activeDoc->countObjectsOfType(Base::Type::fromName("Part::Mirroring"));
    activeDoc->openTransaction("Mirroring");

    QString shape, label;
    QRegExp rx(QString::fromLatin1(" \\(Mirror #\\d+\\)$"));
    QList<QTreeWidgetItem *> items = ui->shapes->selectedItems();
    float normx=0, normy=0, normz=0;
    int index = ui->comboBox->currentIndex();
    if (index == 0)
        normz = 1.0f;
    else if (index == 1)
        normy = 1.0f;
    else
        normx = 1.0f;
    double basex = ui->baseX->value();
    double basey = ui->baseY->value();
    double basez = ui->baseZ->value();
    for (QList<QTreeWidgetItem *>::iterator it = items.begin(); it != items.end(); ++it) {
        shape = (*it)->data(0, Qt::UserRole).toString();
        label = (*it)->text(0);

        // if we already have the suffix " (Mirror #<number>)" remove it
        int pos = label.indexOf(rx);
        if (pos > -1)
            label = label.left(pos);
        label.append(QString::fromLatin1(" (Mirror #%1)").arg(++count));

        QString code = QString::fromLatin1(
            "__doc__=FreeCAD.getDocument(\"%1\")\n"
            "__doc__.addObject(\"Part::Mirroring\")\n"
            "__doc__.ActiveObject.Source=__doc__.getObject(\"%2\")\n"
            "__doc__.ActiveObject.Label=\"%3\"\n"
            "__doc__.ActiveObject.Normal=(%4,%5,%6)\n"
            "__doc__.ActiveObject.Base=(%7,%8,%9)\n"
            "del __doc__")
            .arg(this->document).arg(shape).arg(label)
            .arg(normx).arg(normy).arg(normz)
            .arg(basex).arg(basey).arg(basez);
        Gui::Application::Instance->runPythonCode((const char*)code.toLatin1());
        QByteArray from = shape.toLatin1();
        Gui::Command::copyVisual("ActiveObject", "ShapeColor", from);
        Gui::Command::copyVisual("ActiveObject", "LineColor", from);
        Gui::Command::copyVisual("ActiveObject", "PointColor", from);
    }

    activeDoc->commitTransaction();
    activeDoc->recompute();
    return true;
}
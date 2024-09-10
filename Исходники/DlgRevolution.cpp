void DlgRevolution::accept()
{
    if (!this->validate())
        return;
    Gui::WaitCursor wc;
    App::Document* activeDoc = App::GetApplication().getActiveDocument();
    activeDoc->openTransaction("Revolve");

    try{
        QString shape, type, name, solid;
        QList<QTreeWidgetItem *> items = ui->treeWidget->selectedItems();
        if (ui->checkSolid->isChecked()) {
            solid = QString::fromLatin1("True");}
        else {
            solid = QString::fromLatin1("False");}

        App::PropertyLinkSub axisLink;
        this->getAxisLink(axisLink);
        QString strAxisLink;
        if (axisLink.getValue()){
            strAxisLink = QString::fromLatin1("(App.ActiveDocument.%1, %2)")
                    .arg(QString::fromLatin1(axisLink.getValue()->getNameInDocument()))
                    .arg(axisLink.getSubValues().size() ==  1 ?
                             QString::fromLatin1("\"%1\"").arg(QString::fromLatin1(axisLink.getSubValues()[0].c_str()))
                             : QString() );
        } else {
            strAxisLink = QString::fromLatin1("None");
        }

        QString symmetric;
        if (ui->checkSymmetric->isChecked()) {
            symmetric = QString::fromLatin1("True");}
        else {
            symmetric = QString::fromLatin1("False");}

        for (QList<QTreeWidgetItem *>::iterator it = items.begin(); it != items.end(); ++it) {
            shape = (*it)->data(0, Qt::UserRole).toString();
            type = QString::fromLatin1("Part::Revolution");
            name = QString::fromLatin1(activeDoc->getUniqueObjectName("Revolve").c_str());
            Base::Vector3d axis = this->getDirection();
            Base::Vector3d pos = this->getPosition();


            QString code = QString::fromLatin1(
                "FreeCAD.ActiveDocument.addObject(\"%1\",\"%2\")\n"
                "FreeCAD.ActiveDocument.%2.Source = FreeCAD.ActiveDocument.%3\n"
                "FreeCAD.ActiveDocument.%2.Axis = (%4,%5,%6)\n"
                "FreeCAD.ActiveDocument.%2.Base = (%7,%8,%9)\n"
                "FreeCAD.ActiveDocument.%2.Angle = %10\n"
                "FreeCAD.ActiveDocument.%2.Solid = %11\n"
                "FreeCAD.ActiveDocument.%2.AxisLink = %12\n"
                "FreeCAD.ActiveDocument.%2.Symmetric = %13\n"
                "FreeCADGui.ActiveDocument.%3.Visibility = False\n")
                .arg(type).arg(name).arg(shape) //%1, 2, 3
                .arg(axis.x,0,'f',15) //%4
                .arg(axis.y,0,'f',15) //%5
                .arg(axis.z,0,'f',15) //%6
                .arg(pos.x, 0,'f',15) //%7
                .arg(pos.y, 0,'f',15) //%8
                .arg(pos.z, 0,'f',15) //%9
                .arg(getAngle(),0,'f',15) //%10
                .arg(solid) //%11
                .arg(strAxisLink) //%12
                .arg(symmetric) //13
                ;
            Gui::Command::runCommand(Gui::Command::App, code.toLatin1());
            QByteArray to = name.toLatin1();
            QByteArray from = shape.toLatin1();
            Gui::Command::copyVisual(to, "ShapeColor", from);
            Gui::Command::copyVisual(to, "LineColor", from);
            Gui::Command::copyVisual(to, "PointColor", from);
        }

        activeDoc->commitTransaction();
        activeDoc->recompute();
    } catch (Base::Exception &err) {
        QMessageBox::critical(this, windowTitle(),
            tr("Creating Revolve failed.\n\n%1").arg(QString::fromUtf8(err.what())));
        return;
    } catch (...){
        QMessageBox::critical(this, windowTitle(),
            tr("Creating Revolve failed.\n\n%1").arg(QString::fromUtf8("Unknown error")));
        return;
    }

    QDialog::accept();
}
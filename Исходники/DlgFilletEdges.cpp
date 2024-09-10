bool DlgFilletEdges::accept()
{
    if (!d->object) {
        QMessageBox::warning(this, tr("No shape selected"),
            tr("No valid shape is selected.\n"
               "Please select a valid shape in the drop-down box first."));
        return false;
    }
    App::Document* activeDoc = App::GetApplication().getActiveDocument();
    QAbstractItemModel* model = ui->treeView->model();
    bool end_radius = !ui->treeView->isColumnHidden(2);
    bool todo = false;

    QString shape, type, name;
    std::string fillet = getFilletType();
    int index = ui->shapeObject->currentIndex();
    shape = ui->shapeObject->itemData(index).toString();
    type = QString::fromAscii("Part::%1").arg(QString::fromAscii(fillet.c_str()));

    if (d->fillet)
        name = QString::fromAscii(d->fillet->getNameInDocument());
    else
        name = QString::fromAscii(activeDoc->getUniqueObjectName(fillet.c_str()).c_str());

    activeDoc->openTransaction(fillet.c_str());
    QString code;
    if (!d->fillet) {
        code = QString::fromAscii(
        "FreeCAD.ActiveDocument.addObject(\"%1\",\"%2\")\n"
        "FreeCAD.ActiveDocument.%2.Base = FreeCAD.ActiveDocument.%3\n")
        .arg(type).arg(name).arg(shape);
    }
    code += QString::fromAscii("__fillets__ = []\n");
    for (int i=0; i<model->rowCount(); ++i) {
        QVariant value = model->index(i,0).data(Qt::CheckStateRole);
        Qt::CheckState checkState = static_cast<Qt::CheckState>(value.toInt());

        // is item checked
        if (checkState & Qt::Checked) {
            // the index value of the edge
            int id = model->index(i,0).data(Qt::UserRole).toInt();
            double r1 = model->index(i,1).data().toDouble();
            double r2 = r1;
            if (end_radius)
                r2 = model->index(i,2).data().toDouble();
            code += QString::fromAscii(
                "__fillets__.append((%1,%2,%3))\n")
                .arg(id).arg(r1,0,'f',2).arg(r2,0,'f',2);
            todo = true;
        }
    }

    if (!todo) {
        QMessageBox::warning(this, tr("No edge selected"),
            tr("No edge entity is checked to fillet.\n"
               "Please check one or more edge entities first."));
        return false;
    }

    Gui::WaitCursor wc;
    code += QString::fromAscii(
        "FreeCAD.ActiveDocument.%1.Edges = __fillets__\n"
        "del __fillets__\n"
        "FreeCADGui.ActiveDocument.%2.Visibility = False\n")
        .arg(name).arg(shape);
    Gui::Application::Instance->runPythonCode((const char*)code.toAscii());
    activeDoc->commitTransaction();
    activeDoc->recompute();
    if (d->fillet) {
        Gui::ViewProvider* vp;
        vp = Gui::Application::Instance->getViewProvider(d->fillet);
        if (vp) vp->show();
    }

    QByteArray to = name.toAscii();
    QByteArray from = shape.toAscii();
    Gui::Command::copyVisual(to, "ShapeColor", from);
    Gui::Command::copyVisual(to, "LineColor", from);
    Gui::Command::copyVisual(to, "PointColor", from);
    return true;
}
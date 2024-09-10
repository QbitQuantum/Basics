void DlgExtrusion::apply()
{
    if (ui->treeWidget->selectedItems().isEmpty()) {
        QMessageBox::critical(this, windowTitle(), 
            tr("Select a shape for extrusion, first."));
        return;
    }

    Gui::WaitCursor wc;
    App::Document* activeDoc = App::GetApplication().getDocument(this->document.c_str());
    if (!activeDoc) {
        QMessageBox::critical(this, windowTitle(), 
            tr("The document '%1' doesn't exist.").arg(QString::fromUtf8(this->label.c_str())));
        return;
    }
    activeDoc->openTransaction("Extrude");

    Base::Reference<ParameterGrp> hGrp = App::GetApplication().GetUserParameter()
        .GetGroup("BaseApp")->GetGroup("Preferences")->GetGroup("Mod/Part");
    bool addBaseName = hGrp->GetBool("AddBaseObjectName", false);

    QString shape, type, name, label;
    QList<QTreeWidgetItem *> items = ui->treeWidget->selectedItems();
    for (QList<QTreeWidgetItem *>::iterator it = items.begin(); it != items.end(); ++it) {
        shape = (*it)->data(0, Qt::UserRole).toString();
        type = QString::fromLatin1("Part::Extrusion");
        if (addBaseName) {
            QString baseName = QString::fromLatin1("Extrude_%1").arg(shape);
            label = QString::fromLatin1("%1_Extrude").arg((*it)->text(0));
            name = QString::fromLatin1(activeDoc->getUniqueObjectName((const char*)baseName.toLatin1()).c_str());
        }
        else {
            name = QString::fromLatin1(activeDoc->getUniqueObjectName("Extrude").c_str());
            label = name;
        }

        double len = ui->dirLen->value();
        double dirX = ui->dirX->value();
        double dirY = ui->dirY->value();
        double dirZ = ui->dirZ->value();
        double angle = ui->taperAngle->value().getValue();
        bool makeSolid = ui->makeSolid->isChecked();

        // inspect geometry
        App::DocumentObject* obj = activeDoc->getObject((const char*)shape.toLatin1());
        if (!obj || !obj->isDerivedFrom(Part::Feature::getClassTypeId())) continue;
        Part::Feature* fea = static_cast<Part::Feature*>(obj);
        const TopoDS_Shape& data = fea->Shape.getValue();
        if (data.IsNull()) continue;

        // check for planes
        if (ui->checkNormal->isChecked() && data.ShapeType() == TopAbs_FACE) {
            BRepAdaptor_Surface adapt(TopoDS::Face(data));
            if (adapt.GetType() == GeomAbs_Plane) {
                double u = 0.5*(adapt.FirstUParameter() + adapt.LastUParameter());
                double v = 0.5*(adapt.FirstVParameter() + adapt.LastVParameter());
                BRepLProp_SLProps prop(adapt,u,v,1,Precision::Confusion());
                if (prop.IsNormalDefined()) {
                    gp_Pnt pnt; gp_Vec vec;
                    // handles the orientation state of the shape
                    BRepGProp_Face(TopoDS::Face(data)).Normal(u,v,pnt,vec);
                    dirX = vec.X();
                    dirY = vec.Y();
                    dirZ = vec.Z();
                }
            }
        }

        QString code = QString::fromLatin1(
            "FreeCAD.getDocument(\"%1\").addObject(\"%2\",\"%3\")\n"
            "FreeCAD.getDocument(\"%1\").%3.Base = FreeCAD.getDocument(\"%1\").%4\n"
            "FreeCAD.getDocument(\"%1\").%3.Dir = (%5,%6,%7)\n"
            "FreeCAD.getDocument(\"%1\").%3.Solid = (%8)\n"
            "FreeCAD.getDocument(\"%1\").%3.TaperAngle = (%9)\n"
            "FreeCADGui.getDocument(\"%1\").%4.Visibility = False\n"
            "FreeCAD.getDocument(\"%1\").%3.Label = '%10'\n")
            .arg(QString::fromLatin1(this->document.c_str()))
            .arg(type).arg(name).arg(shape)
            .arg(dirX*len)
            .arg(dirY*len)
            .arg(dirZ*len)
            .arg(makeSolid ? QLatin1String("True") : QLatin1String("False"))
            .arg(angle)
            .arg(label);
        Gui::Application::Instance->runPythonCode((const char*)code.toLatin1());
        QByteArray to = name.toLatin1();
        QByteArray from = shape.toLatin1();
        Gui::Command::copyVisual(to, "ShapeColor", from);
        Gui::Command::copyVisual(to, "LineColor", from);
        Gui::Command::copyVisual(to, "PointColor", from);
    }

    activeDoc->commitTransaction();
    try {
        ui->statusLabel->clear();
        activeDoc->recompute();
        ui->statusLabel->setText(QString::fromLatin1
            ("<span style=\" color:#55aa00;\">%1</span>").arg(tr("Succeeded")));
    }
    catch (const std::exception& e) {
        ui->statusLabel->setText(QString::fromLatin1
            ("<span style=\" color:#ff0000;\">%1</span>").arg(tr("Failed")));
        Base::Console().Error("%s\n", e.what());
    }
    catch (const Base::Exception& e) {
        ui->statusLabel->setText(QString::fromLatin1
            ("<span style=\" color:#ff0000;\">%1</span>").arg(tr("Failed")));
        Base::Console().Error("%s\n", e.what());
    }
    catch (...) {
        ui->statusLabel->setText(QString::fromLatin1
            ("<span style=\" color:#ff0000;\">%1</span>").arg(tr("Failed")));
        Base::Console().Error("General error in extrusion\n");
    }
}
void PMeshViewer::addMesh(const QStringList &fileNames)
{
    int startIndex = meshList.size();
    
    for (int i = 0; i < fileNames.size(); ++i)
    {
        QString suffix = QFileInfo(fileNames[i]).suffix();

        vtkPolyDataAlgorithm *reader = NULL;

        if (suffix == "obj")
        {
            vtkOBJReader *rd = vtkOBJReader::New();
            rd->SetFileName(fileNames[i].toAscii().data());
            reader = rd;
        }
        else if (suffix == "ply")
        {
            vtkPLYReader *rd = vtkPLYReader::New();
            rd->SetFileName(fileNames[i].toAscii().data());
            reader = rd;
        }
        else if (suffix == "stl")
        {
            vtkSTLReader *rd = vtkSTLReader::New();
            rd->SetFileName(fileNames[i].toAscii().data());
            reader = rd;
        }
        else // This should not happen, but just in case.
        {
            uninstallPipeline();
            cout << "Error in loadMesh: file type " <<
                    suffix.toAscii().data() << " is unsupported.\n" << flush;
            return;
        }

        // Append to mesh list
        PMeshPart part;
        part.name = QFileInfo(fileNames[i]).baseName();
        part.source = fileNames[i];
        part.data = reader->GetOutput();
        reader->Update();
        
        part.normals = vtkPolyDataNormals::New();
        part.normals->SetInput(part.data);
        part.mapper = vtkPolyDataMapper::New();
        part.mapper->SetInput(part.normals->GetOutput());
        part.mapper->Update();
        part.actor = vtkActor::New();
        part.actor->SetMapper(part.mapper);
        meshList.append(part);
        reader->Delete();

        // Append to mesh table
        int j = meshTable->rowCount();
        meshTable->insertRow(j);
        meshTable->setRowHeight(j, RowHeight);

        QTableWidgetItem *item = new QTableWidgetItem;
        item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);
        item->setCheckState(Qt::Checked);
        meshTable->setItem(j, 0, item);

        item = new QTableWidgetItem;
        item->setFlags(Qt::ItemIsEnabled);
        item->setBackground(QBrush(QColor(255, 255, 255)));
        meshTable->setItem(j, 1, item);

        item = new QTableWidgetItem(part.name);
        item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable |
                       Qt::ItemIsEditable);
        item->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        meshTable->setItem(j, 2, item);
        
        item = new QTableWidgetItem(part.source);
        item->setFlags(Qt::ItemIsEnabled);
        item->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        meshTable->setItem(j, 4, item);
    }

    int width = meshTable->width();
    int height = meshTable->height();
    int bestHeight = qMin(MaxHeight,
                          (meshTable->rowCount() + 2) * RowHeight);
    if (height < bestHeight)
        meshTable->resize(width, bestHeight);

    installPipeline(startIndex);

    setWindowTitle(QString("%1 - %2").arg(appName).arg(projectName));
}
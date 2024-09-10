void AdcListReader::readDirectory(QTreeWidgetItem *item)
{
    QString pathParent = item ? item->data(0, Qt::UserRole).toString() : QDir::separator();
    QString filename = xml.attributes().value(sName).toString().trimmed();
    bool isConvOk = false;
    if (filename == "") {
        xml.raiseError(errorString(QObject::tr("Invalid Entry: <%1> has a missing or empty %2= attribute.")
                                   .arg(sDIRECTORY).arg(sName)));
        return;
    }

    QString filedate = xml.attributes().value(sDate).toString().trimmed();

    QTreeWidgetItem *folder = createChildItem(item, ShowListing::DirFileTree::DirType);
    folder->setIcon(0, treeWidget->folderIcon);
    folder->setData(0, Qt::UserRole, pathParent + QDir::separator() + filename);
    folder->setText(0, filename);
    folder->setData(1, Qt::UserRole, 0);

    if (xml.attributes().value("Incomplete").toString().trimmed() == "1") {
        folder->setTextColor(0, QColor(Qt::blue));
    }

    qulonglong filedateparsed = filedate.toLongLong(&isConvOk);
    if (isConvOk) {
        folder->setData(2, Qt::UserRole, filedateparsed);
    }


    while (!cancelRequested && !xml.hasError() && xml.readNextStartElement()) {
        // When a directory has been processed, notify listeners
        emit broadcastProgress(xml.device()->pos());
        if (xml.name() == sDIRECTORY)
            readDirectory(folder);
        else if (xml.name() == sFILE)
            readFile(folder);
        else
            xml.skipCurrentElement();
    }
    if (cancelRequested) {
        return;
    }


    qulonglong folderSize = folder->data(1, Qt::UserRole).toLongLong();
    folder->setText(1, QString(">> %1").arg(humanizeBigNums(folderSize, 2)));
    folder->setTextColor(1, getColorFromSize(folderSize));
    qulonglong parentsize = folderSize + item->data(1, Qt::UserRole).toLongLong();
    item->setData(1, Qt::UserRole, parentsize);
}
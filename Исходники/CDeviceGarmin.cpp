void CDeviceGarmin::uploadMap(const QList<IMapSelection*>& mss)
{
    Garmin::IDevice * dev = getDevice();
    if(dev == 0) return;

    QList<IMapSelection*>::const_iterator ms = mss.begin();

    while(ms != mss.end())
    {
        if((*ms)->type == IMapSelection::eVector)
        {
            break;
        }
        ++ms;
    }
    if(ms == mss.end()) return;

    CMapSelectionGarmin * gms = (CMapSelectionGarmin*)(*ms);
    QTemporaryFile tmpfile;
    tmpfile.open();

    CGarminExport dlg(0);
    dlg.exportToFile(*gms, tmpfile.fileName());
    if(dlg.hadErrors())
    {
        QMessageBox::warning(0,tr("Error..."), tr("Failed to create image file."),QMessageBox::Abort,QMessageBox::Abort);
        return;
    }

    QStringList keys;
    QMap<QString, CMapSelectionGarmin::map_t>::const_iterator map = gms->maps.begin();
    while(map != gms->maps.end())
    {
        if(!map->unlockKey.isEmpty())
        {
            keys << map->unlockKey;
        }
        ++map;
    }

    QFileInfo fi(tmpfile.fileName());

    qDebug() << fi.size();
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
    try
    {
        dev->uploadMap(tmpfile.fileName().toLocal8Bit(), (quint32)fi.size() , keys.isEmpty() ? 0 : keys[0].toLatin1().data());
        if (CResources::self().playSound())
        {
            QSound::play(":/sounds/xfer-done.wav");
        }
        QApplication::restoreOverrideCursor();
    }
    catch(int)
    {
        QMessageBox::warning(0,tr("Device Link Error"),dev->getLastError().c_str(),QMessageBox::Ok,QMessageBox::NoButton);
        QApplication::restoreOverrideCursor();
        return;
    }

    theMainWindow->getCanvas()->setFadingMessage(tr("Upload maps finished!"));
}
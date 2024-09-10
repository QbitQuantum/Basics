void BootOptionsDialog::accept()
{
    QDir dir;
    QFile file;
    QStringList filters;
    QStringList allFiles;
    QString fileName;

    if(m_ui->atariDOS->isChecked()) selectedDOS = "$bootata";
    if(m_ui->myDOS->isChecked()) selectedDOS = "$bootmyd";
    if(m_ui->dosXL->isChecked()) selectedDOS = "$bootdxl";
    if(m_ui->smartDOS->isChecked()) selectedDOS = "$bootsma";
    if(m_ui->spartaDOS->isChecked()) selectedDOS = "$bootspa";
    if(m_ui->myPicoDOS->isChecked()) {
        selectedDOS = "$bootpic";
        g_disablePicoHiSpeed = m_ui->disablePicoHiSpeed->isChecked();
    }

    bootDir = g_respeQtAppPath + "/" + selectedDOS;

    // First delete existing boot files in the Folder Image
    // then copy new boot files from the appropriate DOS directory

    dir.setPath(bootFolderPath_);
    filters << "*dos.sys" << "dup.sys" << "dosxl.sys"
            << "autorun.sys" << "ramdisk.com" << "menu.com"
            << "startup.exc" << "x*.dos" << "startup.bat" << "$*.bin";
    allFiles =  dir.entryList(filters, QDir::Files);
    foreach(fileName, allFiles) {
        file.remove(bootFolderPath_ + "/" + fileName);
    }
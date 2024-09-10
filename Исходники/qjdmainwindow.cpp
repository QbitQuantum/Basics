void QJDMainWindow::creatNewLine(QString lineName)
{
    QString lowerCaseLineName;
    lowerCaseLineName=lineName.toLower();
    lowerCaseLineName.simplified();
    lowerCaseLineName.remove(" ");
    qDebug()<<"creatNewLine::"<<lineName<<lowerCaseLineName;  // 所有大写阿,带空格的之类的统一小写,并且去空格

    //1. 创建文件夹,需要获取当前area文件夹名称,通过当前的名称获取
    QDir newDir;
    newDir.setPath(areaWidget->getAbsolutePath());
    if(newDir.exists(lowerCaseLineName))
    {
        QMessageBox::warning(this,"Warning!","Do not creat the same LINE again!");
        return;
    }

    if(!newDir.mkdir(lowerCaseLineName))
        qDebug()<<"Creat New Line Dir failed";

    //2. 创建.Line Desc
    QFile newDesc;
    newDesc.setFileName(newDir.path()+"/"+lowerCaseLineName+"/DescName");
    if(!newDesc.open(QFile::WriteOnly))
    {
        qDebug()<<"creat new desc open failed";
    }
    QTextStream ts(&newDesc);
    ts<<lineName<<"\n";
    newDesc.close();

    // 3. 创建Data文件夹
    QDir dataDir;
    QString dataDirPath=areaWidget->getAbsolutePath()+"/"+lowerCaseLineName;
    dataDir.setPath(dataDirPath);
    if(dataDir.exists("Data"))
    {
        QMessageBox::warning(this,"Warning!","Can not creat the Data Dir for this LINE!");
        return;
    }

    if(!dataDir.mkdir("Data"))
        qDebug()<<"Creat Line Data Dir failed";

    QFile dataDesc;
    dataDesc.setFileName(dataDir.path()+"/Data/DescName");
    if(!dataDesc.open(QFile::WriteOnly))
    {
        qDebug()<<"creat data dir desc open failed";
    }
    QTextStream datats(&dataDesc);
    datats<<"Data\n";
    dataDesc.close();

    // 4. 创建各个类型文件的文件夹
    QStringList fileTypeList=settings.value("FileType").toStringList();
    for(int i=0; i<fileTypeList.size(); i++)
    {
        QDir typeDir;
        QString typeDirPath=dataDirPath+"/Data";
        typeDir.setPath(typeDirPath);
        if(typeDir.exists(fileTypeList.at(i)))
        {
            QMessageBox::warning(this,"Warning!","Can not creat the Same Type Dir for this LINE Data!");
            return;
        }

        if(!typeDir.mkdir(fileTypeList.at(i)))
            qDebug()<<"Creat Line Data Dir failed";
    }


    setHomeDir(getHomeDir());
    areaWidget->expandToDepth(1);
}
void ProjectHandle::loadData(){

    QString Name = QFileDialog::getOpenFileName(NULL,tr("Open picture"), ".",tr("Project files (*.bmp *.jpg *.jpeg *.png)"));
    if (Name.isEmpty()){
        return;
    }


    QImage* load_image = new QImage(Name);

    New_dlg dlg(libPath);
    QPixmap pic =QPixmap::fromImage(load_image->scaled(dlg.pic_label->size())) ;
    dlg.pic_label->setPixmap(pic);

    QFile libFile(libPath);
    if(!libFile.open(QFile::ReadOnly | QFile::WriteOnly)){
        emit addToLog("Не найден файл библиотек");
        QDir dir;
        QFileInfo inf(libPath);
        dir=inf.dir();
        dir.mkdir(dir.absolutePath());
        QTextStream s(&libFile);
        s << "";
    }else{

        QTextStream readS(&libFile);
        while(!readS.atEnd()){
            QString inp;
            readS >> inp;
            dlg.material_Box->addItem(inp);
        }
    }


    if(!dlg.exec()){
        delete load_image;
        return;
    }

    colorMap = load_image;

    PObject object;
    if(dlg.width_sizeBox->currentText()=="um"){
        object.width = dlg.width_SpinBox->value();
    }else{
        object.width = dlg.width_SpinBox->value()*1000;
    }

    if(dlg.height_sizeBox->currentText()=="um"){
        object.height = dlg.height_SpinBox->value();
    }else{
        object.height = dlg.height_SpinBox->value()*1000;
    }

    object.map = new Image;
    object.map->data = new uchar[colorMap->width()*colorMap->height()];
    object.material     =   dlg.material_Box->currentText();
    object.map->sizeX   =   colorMap->width() ;
    object.map->sizeY   =   colorMap->height() ;


    calculate(&object);

    map=object.map;
    object.path=Name;

    QFileInfo inf(Name);
    projObjects.insert(inf.fileName(),object);

    curName=inf.fileName();
    emit addToList(inf.fileName());
    emit cleanGl();
    emit set_glwMap(map);
    emit imageLoad(map->sizeX,map->sizeY);
}
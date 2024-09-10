bool FormMaterialIndicesManager::updateMaterials(QImage& image){
    bSkipUpdating = true;

    // Calculate image color map
    colorIndices.clear();
    for(int w = 0 ; w < image.width() ; w++){
        for(int h = 0 ; h < image.height() ; h++){
            QRgb pixel          = image.pixel(w,h);
            QColor bgColor = QColor(pixel);
            int indeks = bgColor.red()*255*255 + bgColor.green()*255 + bgColor.blue();
            colorIndices[indeks] = pixel;

    }}
    if(colorIndices.size() > 32){
    QMessageBox msgBox;
        msgBox.setText("Error: too much colors!");
        msgBox.setInformativeText(" Sorry, but this image does not look like a material texture.\n"
                                  " Your image contains more than 32 different colors");
        msgBox.setStandardButtons(QMessageBox::Cancel);
        msgBox.exec();
        bSkipUpdating = false;
        return false;
    }

    typedef std::map<int,QRgb>::iterator it_type;
    ui->listWidgetMaterialIndices->clear();

    // generate materials list
    int indeks = 1;
    for(it_type iterator = colorIndices.begin(); iterator != colorIndices.end(); iterator++) {
           qDebug() << "Material index:  " << iterator->first << " Color :" << QColor(iterator->second);

           QListWidgetItem* pItem =new QListWidgetItem("Material"+QString::number(indeks++));
           QColor mColor = QColor(iterator->second);
           pItem->setForeground(mColor); // sets red text
           pItem->setBackground(mColor); // sets green background
           QColor textColor = QColor(255-mColor.red(),255-mColor.green(),255-mColor.blue());
           pItem->setTextColor(textColor);
           ui->listWidgetMaterialIndices->addItem(pItem);

    }


    qDebug() << "Updating material indices. Total indices count:" << ui->listWidgetMaterialIndices->count();
    for(int i = 0 ; i < METALLIC_TEXTURE ; i++){
        materialIndices[i].clear();
        for(int m = 0 ; m < ui->listWidgetMaterialIndices->count() ; m++){
            QString m_name = ui->listWidgetMaterialIndices->item(m)->text();
            FBOImageProporties tmp;
            tmp.copySettings(imagesPointers[i]->imageProp);
            materialIndices[i][m_name] = tmp;
        }
    }


    lastMaterialIndex = 0;
    QString cText = ui->listWidgetMaterialIndices->item(lastMaterialIndex)->text();
    ui->listWidgetMaterialIndices->item(lastMaterialIndex)->setText(cText+" (selected material)");

    QColor bgColor = ui->listWidgetMaterialIndices->item(lastMaterialIndex)->backgroundColor();
    FBOImageProporties::currentMaterialIndeks = bgColor.red()*255*255 + bgColor.green()*255 + bgColor.blue();

    bSkipUpdating = false;



    return true;
}
void Dialog_paper::on_pushButton_5_clicked() // убрать из списка предпочтений
{
    if(indexSel==-1)return;
    QString nm=ui->listWidget_2->item(indexSel)->text(), rm;
    // убрать из списка
    ui->listWidget_2->takeItem(indexSel);
    indexSel=-1;
    ui->pushButton_5->setEnabled(false);
    // убрать из файла
    sett.beginGroup("Paper sizes");
    bool go=true;
    int  i=0, j=0;
    while(go)
    {
        rm=sett.value("name"+QString::number(i), "").toString();
        if (nm!=rm){
            if(rm.isEmpty()){go=false;}else{
            sett.setValue("index"+QString::number(j), sett.value("index"+QString::number(i)).toInt());
            sett.setValue("name"+QString::number(j), rm);
            sett.setValue("W"+QString::number(j), sett.value("W"+QString::number(i),0).toDouble());
            sett.setValue("H"+QString::number(j++), sett.value("H"+QString::number(i)).toDouble());
            }
        }
        if(i>100)go=false;  // на всякий случай...
        i++;
    }
    sett.remove("index"+QString::number(j));
    sett.remove("name"+QString::number(j));
    sett.remove("W"+QString::number(j));
    sett.remove("H"+QString::number(j));
    sett.endGroup();
    chen=true;
}
void MainWindow::on_btn_search_clicked()
{
    QSqlQuery query;
    ui->statusBar->showMessage( tr("Search Button clicked"),2000);
    int numC=ui->tableWidget_resultat->rowCount();
    for(;numC>=0;numC--){
        ui->tableWidget_resultat->removeRow(numC);
    }

    QString str=ui->lineEdit_search->text();
    bool boo;
    if(str.compare("")==0)
    {
        boo=query.exec("select * from TPatient");
        if(!boo)
        {
            qDebug() << query.lastError().text();
            qDebug() << "can't find !\n";
        }
     }
    else
    {
        QString sql="select * from TPatient where Nom='"+str+"' or Id='"+str+"' or Prenom='"+str+"' or DateConsultation='"+str+"'";
        boo=query.exec(sql);
        if(!boo)
        {
            qDebug() << query.lastError().text();
        }

    }
    int i=0;
    for(; query.next(); i++)
    {
        ui->tableWidget_resultat->insertRow(i);
        ui->tableWidget_resultat->setItem( i, 0, new QTableWidgetItem(query.value(0).toString()));
        ui->tableWidget_resultat->setItem( i, 1, new QTableWidgetItem(query.value(1).toString()));
        ui->tableWidget_resultat->setItem( i, 2, new QTableWidgetItem(query.value(2).toString()));
        ui->tableWidget_resultat->setItem( i, 3, new QTableWidgetItem(query.value(8).toString()));
        ui->tableWidget_resultat->setItem( i, 4, new QTableWidgetItem(query.value(9).toString()+" mn"));

        QLabel *modifier = new QLabel();
        modifier->setText("      Modifier");
        modifier->setCursor(Qt::PointingHandCursor);
        QPalette pa;
        pa.setColor(QPalette::Text,Qt::blue);
        modifier->setPalette(pa);
        ui->tableWidget_resultat->setCellWidget(i,5,modifier);


        QLabel *supprimer=new QLabel();
        supprimer->setText("     Supprimer");
        supprimer->setCursor(Qt::PointingHandCursor);
        QPalette pa2;
        pa2.setColor(QPalette::Text,Qt::red);
        supprimer->setPalette(pa2);
        ui->tableWidget_resultat->setCellWidget(i,6,supprimer);

    }
    if(i==0){
        ui->tableWidget_resultat->insertRow(0);
        ui->tableWidget_resultat->setItem(0, 0, new QTableWidgetItem("No record"));
    }
}
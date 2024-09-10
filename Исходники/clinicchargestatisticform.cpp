void ClinicChargeStatisticForm::updateTable()
{
    initTable();
    QDate startDate = m_startDateEdit->date();
    QDate endDate = m_endDateEdit->date();

    if(startDate > endDate)
        return;

    QString strName = m_nameEdit->text();
    Gender eGender = (Gender)m_genderComboBox->currentIndex();
    if(myDB::connectDB())
    {
        QSqlTableModel *model = new QSqlTableModel;
        model->setTable(strClinicCharge);
        QString strSql = "" , strTemp = "";

        strTemp = "Gender = " + QString::number((int)eGender);
        strSql += strTemp;

        if(!strName.isEmpty())
        {
            strTemp = " and Name = \'" + strName + "\'";
            strSql += strTemp;
        }

        QString strStartTime = startDate.toString("yyyy-MM-dd") + "T00:00:00";
        QString strEndTime = endDate.toString("yyyy-MM-dd") + "T23:59:59";

        strTemp = " and Time between \'" + strStartTime + "\' and \'" + strEndTime + "\'";
        strSql += strTemp;

        model->setFilter(strSql);
        model->select();

        int index = 0;
        for(int i = 0; i < model->rowCount();i++)
        {
            QSqlRecord record = model->record(i);
            QString strID = record.value("ID").toString();
            QSqlTableModel *mymodel = new QSqlTableModel;
            mymodel->setTable(strClinicChargeDetails);
            mymodel->setFilter("ChargeId = \'" + strID + "\'");
            mymodel->select();
            for(int j = 0; j < mymodel->rowCount(); j++)
            {
                m_resultsModel->setItem(index,0,new QStandardItem(strID));

                m_resultsModel->setItem(index,1,new QStandardItem(record.value("Name").toString()));
                m_resultsModel->setItem(index,2,new QStandardItem(record.value("Department").toString()));
                m_resultsModel->setItem(index,3,new QStandardItem(record.value("Doctor").toString()));
                QSqlRecord record1 = mymodel->record(j);
                m_resultsModel->setItem(index,4,new QStandardItem(record1.value("ChargeItemName").toString()));
                m_resultsModel->setItem(index,5,new QStandardItem(record1.value("ChargeItemCount").toString()));
                m_resultsModel->setItem(index,6,new QStandardItem(record1.value("ChargeItemPrice").toString()));
                m_resultsModel->setItem(index,7,new QStandardItem(record.value("Time").toString()));
                index++;
            }
        }
    }
}
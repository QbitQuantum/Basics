bool CChinesePinyinTable::initTable()
{
    bool value_ret = false;


    int num_records = sizeof(p2h)/sizeof(p2h[0]);
    int i=0;


    if(!openDatabase())
    {
       value_ret =  DataBaseNotOpen;
    }
    else
    {

            QSqlQuery query(db);

            QString strSqlDelete = "delete * from "+ m_TableName;

            query.exec(strSqlDelete);

            for(i=0;i<num_records;i++)
            {
                  pyhz_tab tempRecord = p2h[i];

                  QChar firstAlphabet = tempRecord.py.at(0);

                  QChar lowFirstAlphabet = firstAlphabet.toLower();

                  tempRecord.py.replace(0,1,lowFirstAlphabet);

                  QString strSQL = "insert into " + m_TableName + " (pinyin,pinyin_shengdiao,shengdiao,ChineseCharactor,First_Alphabet) values (\'"
                                                             + tempRecord.py + "\',\'"
                                                             + tempRecord.py_shengdiao + "\',"
                                                             + QString::number(tempRecord.shengdiao) + ",\'"
                                                             + tempRecord.hz + "\',\'"
                                                             + lowFirstAlphabet + "\')";

                 /*QString strSQL = "insert into " + m_TableName + " (pinyin,pinyin_shengdiao) values (\'"
                                                                               + tempRecord.py + "\',\'"
                                                                               + tempRecord.py_shengdiao + "\')";*/
               //  strSQL = "select * from " + m_TableName;

                  //qDebug()<<strSQL;

                  if(query.exec(strSQL))
                  {
                     value_ret = true;
                  }
                  else
                  {
                     value_ret = false;
                  }
            }

    }

    return value_ret;
}
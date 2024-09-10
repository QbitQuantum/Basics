void DataSearchConfig::on_btn_CreateTable_clicked()
{
    if(CreateTable())
    {
        QMessageBox::information(this,
                                 tr("Succes"),
                                 tr("Table succesfully created"));
    }
    else
    {
        QMessageBox::critical(this,
                              tr("Error"),
                              tr("Table could not be created..!"));
    }
}
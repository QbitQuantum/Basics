    foreach (QSerialPortInfo info, QSerialPortInfo::availablePorts())
    {
        //QListWidgetItem * item = new QListWidgetItem( info.portName(),this->ui->list);
        QListWidgetItem * item = new QListWidgetItem( info.portName());
        this->ui->list->addItem(item);
        item->setFlags(Qt::ItemIsUserCheckable|Qt::ItemIsEnabled|Qt::ItemIsSelectable);
        item->setCheckState(Qt::Checked);

    }
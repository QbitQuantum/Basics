void ClassesDatas::read(const QJsonObject &json){

    // Clear
    SuperListItem::deleteModel(m_model, false);

    // Read
    QJsonArray jsonList = json["classes"].toArray();
    QStandardItem* item;
    SystemClass* sysClass;
    for (int i = 0; i < jsonList.size(); i++){
        item = new QStandardItem;
        sysClass= new SystemClass;
        sysClass->read(jsonList[i].toObject());
        item->setData(QVariant::fromValue(
                          reinterpret_cast<quintptr>(sysClass)));
        item->setFlags(item->flags() ^ (Qt::ItemIsDropEnabled));
        item->setText(sysClass->toString());
        m_model->appendRow(item);
    }
}
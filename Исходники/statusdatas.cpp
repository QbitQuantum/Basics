void StatusDatas::setDefault() {
    int i, length;
    SystemStatus *status;
    QStandardItem *item;

    QString names[] = {
        "KO"
    };
    int iconsID[] = {
        -1
    };
    length = (sizeof(names)/sizeof(*names));

    for (i = 0; i < length; i++) {
        status = new SystemStatus(i + 1, new LangsTranslation(names[i]),
            iconsID[i]);
        item = new QStandardItem;
        item->setData(QVariant::fromValue(reinterpret_cast<quintptr>(status)));
        item->setFlags(item->flags() ^ (Qt::ItemIsDropEnabled));
        item->setText(status->toString());
        m_model->appendRow(item);
    }
}
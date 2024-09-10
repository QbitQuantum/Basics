void MusicCloudSharedSongTableWidget::receiveDataFinshed(const QNDataItems &items)
{
    clear();
    int count = items.count();
    if(count == 0)
    {
        emit updateLabelMessage(tr("List Is Empty!"));
        createUploadFileWidget();
        return;
    }

    delete m_openFileWidget;
    m_openFileWidget = nullptr;

    setRowCount(count);
    QHeaderView *headerview = horizontalHeader();
    for(int i=0; i<count; ++i)
    {
        QNDataItem dataItem = items[i];
        QTableWidgetItem *item = new QTableWidgetItem;
        item->setData(MUSIC_DATAS_ROLE, QVariant::fromValue<QNDataItem>(dataItem));
        setItem(i, 0, item);

                          item = new QTableWidgetItem;
        item->setToolTip(dataItem.m_name);
        item->setText(MusicUtils::Widget::elidedText(font(), item->toolTip(), Qt::ElideRight, headerview->sectionSize(1) - 20));
        item->setTextColor(QColor(MusicUIObject::MColorStyle12_S));
        item->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        setItem(i, 1, item);

                          item = new QTableWidgetItem;
        item->setToolTip(MusicUtils::Number::size2Label(dataItem.m_size));
        item->setText(MusicUtils::Widget::elidedText(font(), item->toolTip(), Qt::ElideRight, headerview->sectionSize(2) - 5));
        item->setTextColor(QColor(MusicUIObject::MColorStyle12_S));
        item->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        setItem(i, 2, item);

        ///insert server datas into caches
        MusicUploadData data;
        data.m_path = dataItem.m_name.trimmed();
        data.m_name = data.m_path;
        data.m_state = MusicUploadData::Successed;
        if(!m_waitedFiles.contains(data))
        {
            m_waitedFiles << data;
        }
    }

    m_currentUploadIndex = m_waitedFiles.count();
    emit updateLabelMessage(tr("List Update Finished!"));
}
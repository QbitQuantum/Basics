void Bb10Ui::joinChannel()
{
    QVariantList index = m_channelListView->selected();
    if (index.length() < 2)
        return;

    QModelIndex modelIndex = static_cast<DataModelAdapter*>(m_channelListView->dataModel())->getQModelIndex(index);
    BufferInfo bufInfo = modelIndex.data(NetworkModel::BufferInfoRole).value<BufferInfo>();
    QString bufferName = bufInfo.bufferName();
    switchToOrJoinChat(bufferName, false);
}
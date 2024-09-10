QItemSelection MemoryPacketModel::getLastPacketRow()
{
    QItemSelection selection;
    if (packetsList.size() > 0)
        selection.select(createIndex(packetsList.size() - 1, 0), createIndex(packetsList.size() - 1, columnNames.size() - 1));

    return selection;
}
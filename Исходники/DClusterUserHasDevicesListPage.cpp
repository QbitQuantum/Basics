void DClusterUserHasDevicesListPage::delAuthorizedDeviceWidget(QList<quint64> &delList)
{
    if(delList.count() == 0) return;
    QHash<quint64, DClusterAuthDevInfo*> devList = authorizedDeviceInfoList->fetchList();
    QHashIterator<quint64, DClusterAuthDevInfo*> iter(devList);
    while(iter.hasNext())
    {
        iter.next();
        DClusterAuthDevInfo* info = iter.value();
        for(int i = 0; i < delList.count(); i++)
        {
            if(info->getDeviceID() == delList.at(i))
            {
                delDeviceWidget(info->getDeviceID());
                authorizedDeviceInfoList->remove(info->getDeviceID());
                break;
            }
        }
    }
}
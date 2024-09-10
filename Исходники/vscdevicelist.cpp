void VSCDeviceList::NotifyDelVGroup(int nId)
{	
	QTreeWidgetItem *qtreewidgetitem = ui.treeWidget->topLevelItem(VSC_DEVICE_INDEX_IPC);

	int cnt = qtreewidgetitem->childCount();
	//VDC_DEBUG( "%s cnt %d\n",__FUNCTION__, cnt);
	for (int i = 0; i < cnt; i ++)
	{
		QTreeWidgetItem * pChild = qtreewidgetitem->child(i);
		VSCDeviceIPCGroup *pGroup = dynamic_cast<VSCDeviceIPCGroup*>(pChild);
		if (pGroup && pGroup->GetDeviceId() == nId)
		{
			qtreewidgetitem->removeChild(pChild);
		}
	}
	return;
}
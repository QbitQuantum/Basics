void VSCDeviceTree::VSCZbIpcRecordClick()//nur的IPC的startrecordclick
{
	QTreeWidgetItem *item = NULL;
    item = currentItem();

    VDC_DEBUG( "%s \n",__FUNCTION__);
    if(item != NULL)
    {
        VSCZbTreeItemIPC *pVSCZbIpc = dynamic_cast<VSCZbTreeItemIPC * >(item);
        if (pVSCZbIpc)
        {
            VDC_DEBUG( "%s \n",__FUNCTION__);
            u32 nId = pVSCZbIpc->GetDeviceId();
			//qDebug() << QString("hahahaa2: %1").arg(pVSCZbIpc->GetDeviceId());
			gFactory->StartRecord(nId);
			//TODO  VSCZbIPCRecord()?
			//if(pVSCZbIpc->GetDeviceParam().m_Conf.data.conf.Recording==1)
				pVSCZbIpc->VSCZbIPCUpdateRecord(true);
        }
    }

	return;
}
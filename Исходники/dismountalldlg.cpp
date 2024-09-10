void 
CDismountAllDialog::QueueEjectWorkItemCallback(WORK_ITEM_PARAM& WiParam)
{
	int itemIndex = m_deviceListView.GetItemCount();

	m_deviceListView.InsertItem(itemIndex, _T("Dismounting"));
	m_deviceListView.AddItem(itemIndex, 1, WiParam.DisplayName);

	BOOL success = QueueUserWorkItem(WorkItemStart, &WiParam, WT_EXECUTEDEFAULT);
	if (!success)
	{
		ATLTRACE("QueueUserWorkItem failed, error=0x%X\n", GetLastError());
		--m_workItemCount;
		ATLASSERT(FALSE && "QueueUserWorkItem failed");
	}
}
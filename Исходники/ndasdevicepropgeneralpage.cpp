void
CNdasDevicePropGeneralPage::OnReset()
{
	ATLTRACE(__FUNCTION__ "\n");

	ATLVERIFY(AtlWaitWithMessageLoop(m_ThreadCompleted));

	ATLVERIFY(m_imageList.Destroy());
	ATLVERIFY(DestroyAcceleratorTable(m_hAccel));
}
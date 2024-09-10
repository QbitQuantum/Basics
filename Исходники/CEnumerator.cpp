HDEVNOTIFY CEnumerator::GetRegisteredDevNotify(HANDLE HidDeviceObject)
{
	DEV_BROADCAST_HANDLE NotificationFilter;

	memset(&NotificationFilter, 0, sizeof(DEV_BROADCAST_HANDLE));
	NotificationFilter.dbch_size = sizeof(DEV_BROADCAST_HANDLE);
	NotificationFilter.dbch_devicetype = 6;
	NotificationFilter.dbch_handle = HidDeviceObject;

	return RegisterDeviceNotificationW(m_hEnumNotifWnd, &NotificationFilter, 0);
}
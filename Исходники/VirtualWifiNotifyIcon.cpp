void VirtualWifiNotifyIcon::start_dynamic_show()
{
	m_isdynamic_show=true;
	_beginthread(dynamic_show_icon_thread,0,this);
}
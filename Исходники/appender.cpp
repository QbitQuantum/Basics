Appender * Appender::getAppender(com_device_t &dev)
{
	xAutoLock lock(&comlog_appender_getlock);

	//devµÄ²ÎÊý¼ì²é
	__CHECKINT(dev.log_size, 1, COM_MAXLOGFILE, COM_MAXLOGFILE);
	
	Appender *app = NULL; 
	switch (dev.type) {
		case COM_FILEDEVICE:
			_com_debug("create file appender");
			app = FileAppender::getAppender(dev);
			break;
		case COM_NETDEVICE:
			_com_debug("create net appender");
			app = NetAppender::getAppender(dev);
			break;
		case COM_TTYDEVICE:
			_com_debug("create tty appender");
			app = TtyAppender::getAppender(dev);
			break;
		case COM_ULLOGDEVICE:
		case COM_ULNETDEVICE:
			_com_debug("create ul appender");
			app = UlLogAppender::getAppender(dev);
			break;
		case COM_AFILEDEVICE:
			_com_debug("create async file appender");
			app = AsyncFileAppender::getAppender(dev);
			break;
		default:
			_com_error("sorry i can't know the type[%d]", dev.type);
			break;
	}
	if (app != NULL) {
		app->setLayout(dev.layout);
		_core_debug("dev =%lx appender layout=%lx", dev.layout, app->_layout);
		app->_open = dev.open;
	}

	return app;
}
KDE_EXPORT void
wake_laptop_daemon()
{
	DCOPClient      *dclient = kapp->dcopClient();
        if (!dclient || (!dclient->isAttached() && !dclient->attach())) 
		return;

	TQByteArray data;
	TQDataStream arg( data, IO_WriteOnly );
	(void) dclient->send( "kded", "klaptopdaemon", "restart()", data );
}
XCH_STATUS _IDB_XCH::status( XCH_STATUS status, XCH_ERRORCODE errorcode, uint16_t notifycode )
{
	lock.lock();

	XCH_STATUS cur_status = xch_status;

	if( cur_status != XCH_STATUS_DEAD )
	{
		cur_status = xch_status = status;
		xch_errorcode = errorcode;
		xch_notifycode = notifycode;

		if( status == XCH_STATUS_DEAD )
			setflags( ENTRY_FLAG_DEAD );
	}

	lock.unlock();

	return cur_status;
}
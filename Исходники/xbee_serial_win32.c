int xbee_ser_break( xbee_serial_t *serial, int enabled)
{
	BOOL success;

	XBEE_SER_CHECK( serial);

	if (enabled)
	{
		success = SetCommBreak( serial->hCom);
	}
	else
	{
		success = ClearCommBreak( serial->hCom);
	}

	#ifdef XBEE_SERIAL_VERBOSE
		if (success == 0)
		{
			printf( "%s: {Set|Clear}CommBreak error %lu\n", __FUNCTION__,
					GetLastError());
		}
	#endif

	return success ? 0 : -EIO;
}
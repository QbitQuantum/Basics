XnStatus PlayerNode::HandleEndRecord(EndRecord record)
{
	XN_VALIDATE_INPUT_PTR(m_pNodeNotifications);
	XnStatus nRetVal = record.Decode();
	XN_IS_STATUS_OK(nRetVal);
	DEBUG_LOG_RECORD(record, "End");

	if (!m_bDataBegun)
	{
		XN_LOG_WARNING_RETURN(XN_STATUS_CORRUPT_FILE, XN_MASK_OPEN_NI, "File does not contain any data!");
	}

	nRetVal = m_eofReachedEvent.Raise();
	XN_IS_STATUS_OK(nRetVal);

	if (m_bRepeat)
	{
		nRetVal = Rewind();
		XN_IS_STATUS_OK(nRetVal);
	}
	else
	{
		m_bEOF = TRUE;
		CloseStream();
	}

	return XN_STATUS_OK;	
}
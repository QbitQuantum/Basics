bool CMsmqWarpper::OpenPublicQueue(LPCWSTR wszPathName, bool connecttype)
{
	if (wszPathName == NULL)
	{
		return false;
	}

	HRESULT hr = MQ_OK;

	if (connecttype)
	{
		DWORD dwFormatNameBufferLength = 256; 
		WCHAR wszFormatNameBuffer[256] = {0};

		hr = MQPathNameToFormatName(wszPathName,
			wszFormatNameBuffer,
			&dwFormatNameBufferLength);
		if (FAILED(hr))
		{
			return false;
		}

		hr = MQOpenQueue(wszFormatNameBuffer, 
			MQ_SEND_ACCESS, 
			MQ_DENY_NONE, 
			&m_hQueue
			);
	}
	else
	{
		hr = MQOpenQueue(wszPathName, 
			MQ_SEND_ACCESS, 
			MQ_DENY_NONE, 
			&m_hQueue
			);
	}
	if (FAILED(hr))
	{
		return false;
	}

	return true;

}
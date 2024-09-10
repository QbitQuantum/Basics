long SDMDeletesub::Send()
{
	int result;
	result = SendTo(source);
	if (result <= 0)
		return SDM_MESSAGE_SEND_ERROR;
	return result;
}
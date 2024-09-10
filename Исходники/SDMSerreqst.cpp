long SDMSerreqst::Send(const SDMComponent_ID& destination)
{
	int result;
	result = SendTo(destination);
	if (result <= 0)
		return SDM_MESSAGE_SEND_ERROR;
	return result;
}
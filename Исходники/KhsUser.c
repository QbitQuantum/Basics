HRESULT KhspFilterReplyMessage(
	_In_ PFILTER_MESSAGE_HEADER MessageHeader,
	_In_ BOOLEAN Flags)
{
	HS_SERVICE_RESPONSE response;

	response.ReplyHeader.MessageId = MessageHeader->MessageId;
	response.ReplyHeader.Status = STATUS_SUCCESS;
	response.Flags = Flags;

	return FilterReplyMessage(
		HsKhsPortHandle,
		&response.ReplyHeader,
		MessageHeader->ReplyLength);
}
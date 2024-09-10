int PCSCv2Part10_find_TLV_property_by_tag_from_hcard(SCARDHANDLE hCard,
	int property, int * value)
{
	unsigned char buffer[MAX_BUFFER_SIZE];
	LONG rv;
	DWORD length;
	unsigned int i;
	PCSC_TLV_STRUCTURE *pcsc_tlv;
	DWORD properties_in_tlv_ioctl;
	int found;

	rv = SCardControl(hCard, CM_IOCTL_GET_FEATURE_REQUEST, NULL, 0,
		buffer, sizeof buffer, &length);
	if (rv != SCARD_S_SUCCESS)
		return -1;

	/* get the number of elements instead of the complete size */
	length /= sizeof(PCSC_TLV_STRUCTURE);

	pcsc_tlv = (PCSC_TLV_STRUCTURE *)buffer;
	found = 0;
	for (i = 0; i < length; i++)
	{
		if (FEATURE_GET_TLV_PROPERTIES == pcsc_tlv[i].tag)
		{
			properties_in_tlv_ioctl = ntohl(pcsc_tlv[i].value);
			found = 1;
		}
	}

	if (! found)
		return -3;

	rv= SCardControl(hCard, properties_in_tlv_ioctl, NULL, 0,
		buffer, sizeof buffer, &length);
	if (rv != SCARD_S_SUCCESS)
		return -1;

	return PCSCv2Part10_find_TLV_property_by_tag_from_buffer(buffer,
		length, property, value);
}
BOOL rdp_recv_deactivate_all(rdpRdp* rdp, wStream* s)
{
	UINT16 lengthSourceDescriptor;

	if (rdp->state == CONNECTION_STATE_ACTIVE)
		rdp->deactivation_reactivation = TRUE;
	else
		rdp->deactivation_reactivation = FALSE;

	/*
	 * Windows XP can send short DEACTIVATE_ALL PDU that doesn't contain
	 * the following fields.
	 */
	if (Stream_GetRemainingLength(s) > 0)
	{
		do
		{
			if (Stream_GetRemainingLength(s) < 4)
				break;

			Stream_Read_UINT32(s, rdp->settings->ShareId); /* shareId (4 bytes) */

			if (Stream_GetRemainingLength(s) < 2)
				break;

			Stream_Read_UINT16(s, lengthSourceDescriptor); /* lengthSourceDescriptor (2 bytes) */

			if (Stream_GetRemainingLength(s) < lengthSourceDescriptor)
				break;

			Stream_Seek(s, lengthSourceDescriptor); /* sourceDescriptor (should be 0x00) */
		}
		while (0);
	}

	rdp_client_transition_to_state(rdp, CONNECTION_STATE_CAPABILITIES_EXCHANGE);

	while (rdp->state != CONNECTION_STATE_ACTIVE)
	{
		if (rdp_check_fds(rdp) < 0)
			return FALSE;

		if (freerdp_shall_disconnect(rdp->instance))
			break;

		SwitchToThread();
	}

	return TRUE;
}
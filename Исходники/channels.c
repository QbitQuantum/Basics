BOOL WTSVirtualChannelClose(
	/* __in */ void* hChannelHandle)
{
	wStream* s;
	wts_data_item* item;
	WTSVirtualChannelManager* vcm;
	rdpPeerChannel* channel = (rdpPeerChannel*) hChannelHandle;

	if (channel)
	{
		vcm = channel->vcm;

		if (channel->channel_type == RDP_PEER_CHANNEL_TYPE_SVC)
		{
			if (channel->index < channel->client->settings->ChannelCount)
				channel->client->settings->ChannelDefArray[channel->index].handle = NULL;
		}
		else
		{
			WaitForSingleObject(vcm->mutex, INFINITE);
			list_remove(vcm->dvc_channel_list, channel);
			ReleaseMutex(vcm->mutex);

			if (channel->dvc_open_state == DVC_OPEN_STATE_SUCCEEDED)
			{
				s = stream_new(8);
				wts_write_drdynvc_header(s, CLOSE_REQUEST_PDU, channel->channel_id);
				WTSVirtualChannelWrite(vcm->drdynvc_channel, stream_get_head(s), stream_get_length(s), NULL);
				stream_free(s);
			}
		}

		if (channel->receive_data)
			stream_free(channel->receive_data);

		if (channel->receive_event)
			CloseHandle(channel->receive_event);

		if (channel->receive_queue)
		{
			while ((item = (wts_data_item*) list_dequeue(channel->receive_queue)) != NULL)
			{
				wts_data_item_free(item);
			}

			list_free(channel->receive_queue);
		}

		if (channel->mutex)
			CloseHandle(channel->mutex);

		free(channel);
	}

	return TRUE;
}
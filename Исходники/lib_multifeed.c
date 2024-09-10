static INT32 find_feed_node(struct MULTIFEED_INFO *info, struct FEED_INFO *feed_node )
{
	INT32 ret = -1;
	UINT8 i = 0;
	struct FEED_INFO * feed;
	if( feed_node == NULL )
		return ret;
	for( i=0; i<info->num; i++ )
	{
		feed = get_feed_node( info, i );
		if( feed == NULL )
			return ret;
		if( feed_node->transport_stream_id == feed->transport_stream_id
			&& feed_node->original_network_id == feed->original_network_id
			&& feed_node->service_id == feed->service_id
			&& feed_node->is_known == feed->is_known
			&& MEMCMP( feed_node->name, feed->name, sizeof(feed->name) )==0
			&& MEMCMP( &feed_node->p_node, &feed->p_node, sizeof(feed->p_node) )==0 )
		{
			ret = i;
			break;
		}
	}
	return ret;
}
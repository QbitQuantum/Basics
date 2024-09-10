INT32 DB_get_node_by_id(DB_VIEW *v_attr, UINT32 id, UINT32 *node_addr)
{
	UINT16 i;
		
	*node_addr = 0;
	for(i = 0; i < v_attr->node_num; i++)
	{
		if(0 == MEMCMP((UINT8 *)&id, v_attr->node_buf[i].node_id, NODE_ID_SIZE))
		{
			MEMCPY((UINT8 *)node_addr, v_attr->node_buf[i].node_addr, NODE_ADDR_SIZE);
			break;
		}
	}

	if(*node_addr == 0)
	{
		NODE_API_PRINTF("DB_get_node_by_id(): node id %d not find!\n",id);
		return DBERR_API_NOFOUND;
	}
/*
	if(SUCCESS != DO_read_node(id, node_addr,node_len, node))
	{
		NODE_API_PRINTF("DB_get_node_by_id(): node_id = %d failed!\n",id);
		return DBERR_PACK;
	}
*/
	return DB_SUCCES;

}
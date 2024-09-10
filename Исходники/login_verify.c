int user_addr_store(void * sub_proc,void * message)
{
	
	int ret;
	struct user_address * user_addr;
	MSG_EXPAND * expand;
	struct expand_flow_trace * flow_trace;
	struct login_info * login_data;
	DB_RECORD * db_record;
	int trace_offset;
	
	ret=message_get_record(message,&login_data,0);
	if(ret<0)
		return ret;
	ret=message_get_define_expand(message,&expand,DTYPE_MSG_EXPAND,SUBTYPE_FLOW_TRACE);
	if(ret<0)
		return ret;
	if(expand==NULL)
		return -EINVAL;
	flow_trace=expand->expand;

	if(flow_trace->record_num<=0)
		return -EINVAL;
	trace_offset=DIGEST_SIZE*(flow_trace->record_num-1);
	db_record=memdb_find_byname(login_data->user,DTYPE_CRYPTO_DEMO,SUBTYPE_USER_ADDR);
	if(db_record!=NULL)
	{
		user_addr=(struct user_address *)db_record->record;
		if(Memcmp(user_addr->addr,flow_trace->trace_record+trace_offset,DIGEST_SIZE)==0)
			return 0;	
		memdb_remove_record(db_record);
	}
	user_addr=Talloc0(sizeof(struct user_address));
	if(user_addr==NULL)
		return -ENOMEM;
	Strncpy(user_addr->user,login_data->user,DIGEST_SIZE);
	Memcpy(user_addr->addr,flow_trace->trace_record+trace_offset,DIGEST_SIZE);
	memdb_store(user_addr,DTYPE_CRYPTO_DEMO,SUBTYPE_USER_ADDR,login_data->user);
	return 1;
}
//???????ͷŵ?callback
static int free_callback(void* param)
{
	int loop;
	struct mod_conf_param* data = (struct mod_conf_param*) param;

	if(data)
	{
		for(loop=0; loop<data->count; loop++)
		{
			if(data->acp[loop])
			{
				if(data->acp[loop]->hdr)
				{
					if(strLen(data->acp[loop]->hdr->header))
						stringClean(&data->acp[loop]->hdr->header);
					if(strLen(data->acp[loop]->hdr->value))
						stringClean(&data->acp[loop]->hdr->value);		
					memPoolFree(header_info_pool, data->acp[loop]->hdr);
					data->acp[loop]->hdr = NULL;
				}
				memPoolFree(action_part_pool, data->acp[loop]);
				data->acp[loop] = NULL;
			}
		}
		memPoolFree(mod_config_pool, data);
		data = NULL;
	}

	return 0;
}
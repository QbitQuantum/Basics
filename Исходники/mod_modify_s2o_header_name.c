static int free_callback(void* param)
{
	struct mod_conf_param* data = (struct mod_conf_param*) param;
	if(data)
	{
		if(strLen(data->orig_name))
			stringClean(&data->orig_name);
		if(strLen(data->new_name))
			stringClean(&data->new_name);
		memPoolFree(mod_config_pool, data);
		data = NULL;
	}
	return 0;
}
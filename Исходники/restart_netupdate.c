/*---------------------------------------------------------- * 
* func name: check_upgrade_configfile() 
* function : 分析版本配置文件.检查是否需要更新. 
* calllist :            
*            
*
* calledlist:  
* input    :  
* output   :  
* parameter: line 
             sver
* 			 sfile
             model
* return   : NULL  失败
* 			 成功  版本信息的sw_version的地址
* 			 
* 	 
* 
* notice   : 使用前get_system_version_info()必需先调用成功.
*--------------------------------------------------------*/
static int check_config_version(char *line, char **sver, char **sfile, const char *model,const char* swversion)
{
	int i;
	char *sitems[] = {NULL, NULL, NULL, NULL,NULL}; /* model,softversion, version, file */

	i = 0;
	char *token = get_new_line(&line, ";");
	while(token)
	{
		sitems[i++] = token;
		if(i == 3)
			break;
		token = get_new_line(&line, ";");
	}

	if(i != 3)
	{
		//not enough field, return 0
		return 0;		
	}

	//split the STB model version
	//1=35001-01001
	char *s = sitems[0];
	token = get_new_line(&s, "=");
	if(token == 0)
	{
		//not follow the format 
		return 0;
	}
	//check with the ver in bootloader
	/*
	CHUNK_HEADER blk_header;
	unsigned long id = 0;
	sto_chunk_goto(&id, 0, 1);
	sto_get_chunk_header(id, &blk_header);
	*/
	
	//libc_printf("STB module = %s\n",s);
    //libc_printf("updata System softversion = %s\n",sitems[1]);
	//libc_printf("updataversion = %s, %d\n", sitems[2], calcheck_version(sitems[2]));
	//libc_printf("file = %s\n", sitems[3]);
    
	//libc_printf("System bootload version = %s\n", model);
	//libc_printf("System soft version = %s\n", swversion);
	if(STRCMP(s, (char *)model) != 0)
	{
		//not for the model
		return 0;
	}
    
	if(STRCMP(get_svn_version(sitems[1]),get_svn_version((char *)swversion)) <= 0)
	{
		//have no new version.
		return 0;
	}

    
	if(sver) 
		*sver =  sitems[1];
	if(sfile) 
		*sfile = sitems[2];
	
	return 1;
}
int proc_tcm_makeidentity(void * sub_proc,void * recv_msg)
{
	int ret=0;
	int fd;

	BYTE local_uuid[DIGEST_SIZE];	
	
	BYTE Buf[DIGEST_SIZE*32];
	BYTE NameBuf[DIGEST_SIZE*4];
	UINT32 result;
	RECORD(TCM_PIK_DESC,USERINFO)  * pik_userinfo;
	RECORD(MESSAGE,SIZED_BINDATA) req_blob;
        RECORD(VTCM_IN_KEY,TCM_BIN_KEY) tcm_pik;
        RECORD(VTCM_IN_KEY,TCM_BIN_PUBKEY) tcm_pikpub;
        RECORD(TCM_KEY_MANAGE,PRIVATE_KEY) tcm_pik_info;
	void * new_msg;
	int key_len;
	void * tcm_key_template;

    	UINT32 smkHandle;
    	UINT32 ownerHandle;
    	UINT32 keyHandle;
    	UINT32 keyAuthHandle;
	char uuid[DIGEST_SIZE*2+1];
	DB_RECORD * db_record;
        

	printf("begin pik makeidentity!\n");

	// get pik_userinfo from message
	
	ret=message_get_record(recv_msg,&pik_userinfo,0);
	if(ret<0)
		return -EINVAL;
	if(pik_userinfo==NULL)
		return -EINVAL;

	// get this node's machine uuid
        ret=proc_share_data_getvalue("uuid",pik_userinfo->node_uuid);
	if(ret<0)
		return ret;

	// get this node's hostname
	
	ret=gethostname(pik_userinfo->node_name,DIGEST_SIZE);
	if(ret!=0)
		Memset(pik_userinfo->node_name,0,DIGEST_SIZE);

	// build tcm session
    	ret=TCM_APCreate(TCM_ET_OWNER, NULL, "ooo", &ownerHandle);
    	printf("ownerHandle is : %x\n",ownerHandle);
    	if(ret<0)
    	{
		print_cubeerr("TCM_APCreate failed!\n");
		return -EINVAL;	
    	}	

    	ret=TCM_APCreate(TCM_ET_SMK, NULL, "sss", &smkHandle);
    	printf("smkHandle is : %x\n",smkHandle);
    	if(ret<0)
    	{
		printf("TCM_APCreate failed!\n");
		return -EINVAL;	
    	}	

	int userinfolen;
    	BYTE * req;
    	int reqlen;	
	// get userinfo blob 

	tcm_key_template=memdb_get_template(TYPE_PAIR(TCM_PIK_DESC,USERINFO));
	if(tcm_key_template==NULL)
		return -EINVAL;
	userinfolen=struct_2_blob(pik_userinfo,Buf,tcm_key_template);
	if(userinfolen<0)
		return userinfolen;

	db_record=memdb_store(pik_userinfo,TYPE_PAIR(TCM_PIK_DESC,USERINFO),NULL);
	if(db_record==NULL)
		return -EINVAL;
	// do makeidentity   
    	ret = TCM_MakeIdentity(ownerHandle, smkHandle,
		userinfolen,Buf,"kkk",
		&tcm_pik, &req, &reqlen);
    	if(ret<0)
    	{
		print_cubeerr("TCM_MakeIdentity failed!\n");
		return -EINVAL;	
    	}

	// build an expand message record for req data
	req_blob.size=reqlen;
	req_blob.bindata=req;	

	// terminate session	
    	ret=TCM_APTerminate(ownerHandle);
    	if(ret<0)
    	{
		print_cubeerr("TCM_APTerminate failed!\n");
		return -EINVAL;	
    	}	

    	ret=TCM_APTerminate(smkHandle);
    	if(ret<0)
    	{
		print_cubeerr("TCM_APTerminate failed!\n");
		return -EINVAL;	
	}
	
	// generate TCM pik info ,left pubkey_uuid for fill
	tcm_key_template=memdb_get_template(TYPE_PAIR(VTCM_IN_KEY,TCM_BIN_KEY));
	if(tcm_key_template==NULL)
		return -EINVAL;
	key_len=struct_2_blob(&tcm_pik,Buf,tcm_key_template);
	if(key_len<0)
		return key_len;

	Memset(&tcm_pik_info,0,sizeof(tcm_pik_info));
	calculate_context_sm3(Buf,key_len,tcm_pik_info.uuid);
	Memcpy(tcm_pik_info.vtcm_uuid,local_uuid,DIGEST_SIZE);
	tcm_pik_info.issmkwrapped=1;
	tcm_pik_info.key_usage=TCM_KEY_IDENTITY;
	tcm_pik_info.key_flags=TCM_ISVOLATILE|TCM_PCRIGNOREDONREAD;

	// store pik file
	digest_to_uuid(tcm_pik_info.uuid,uuid);
	uuid[DIGEST_SIZE*2]=0;
	printf("get pik's uuid is %s!\n",uuid);	

	Strcpy(NameBuf,"tcmkey/");
	Strcat(NameBuf,uuid);

        fd=open(NameBuf,O_CREAT|O_WRONLY,0666);
        if(fd<0)
                return fd;
        write(fd,Buf,key_len);
        close(fd);

	// Get pikpub from pik 
	//
	ret=TCM_ExGetPubkeyFromTcmkey(&tcm_pikpub,&tcm_pik);
	if(ret!=0)
	{
		print_cubeerr("Get Pubpik failed!\n");
		return -EINVAL;
	}

	
	tcm_key_template=memdb_get_template(TYPE_PAIR(VTCM_IN_KEY,TCM_BIN_PUBKEY));
	if(tcm_key_template==NULL)
		return -EINVAL;
	key_len=struct_2_blob(&tcm_pikpub,Buf,tcm_key_template);
	if(key_len<0)
		return key_len;
	calculate_context_sm3(Buf,key_len,tcm_pik_info.pubkey_uuid);
	db_record=memdb_store(&tcm_pik_info,TYPE_PAIR(TCM_KEY_MANAGE,PRIVATE_KEY),NULL);

	// build a message and send it 
	new_msg=message_create(TYPE_PAIR(TCM_PIK_DESC,USERINFO),recv_msg);
	if(new_msg==NULL)
		return -EINVAL;
	ret=message_add_record(new_msg,pik_userinfo);
	if(ret<0)
		return ret;
	
	ret=message_add_expand_data(new_msg,TYPE_PAIR(MESSAGE,SIZED_BINDATA),&req_blob);
	if(ret<0)
		return -EINVAL;
	ret=message_add_expand_data(new_msg,TYPE_PAIR(VTCM_IN_KEY,TCM_BIN_PUBKEY),&tcm_pikpub);
	if(ret<0)
		return -EINVAL;

	ret=ex_module_sendmsg(sub_proc,new_msg);
	return ret;
}
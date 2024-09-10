int symm_crypt_init(void * sub_proc,void * para)
{
	int ret;
	// add youself's plugin init func here
    	struct init_struct * init_para=para;
    	if(para==NULL)	 
		return -EINVAL;
	Memset(passwd,0,DIGEST_SIZE);	   
	Strncpy(passwd,init_para->passwd,DIGEST_SIZE);
	return 0;
}
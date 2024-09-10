int _routine_manage_init()
{
	int ret;
	ret=Galloc0(&manage_proc,sizeof(ROUTINE));
	if(ret<0)
		return ret;	
	Strncpy(manage_proc->name,"manage_proc",DIGEST_SIZE);

	ret=comp_proc_uuid(myproc_context->uuid,manage_proc->name,manage_proc->uuid);
	if(ret<0)
		return -EINVAL;
	return 0;
}
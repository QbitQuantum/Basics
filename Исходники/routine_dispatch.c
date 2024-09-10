int _routine_dispatch_init()
{
	int ret;
	ret=Galloc0(&dispatch_proc,sizeof(ROUTINE));
	if(ret<0)
		return ret;	
	Strncpy(dispatch_proc->name,"dispatch_proc",DIGEST_SIZE);

	ret=comp_proc_uuid(myproc_context->uuid,dispatch_proc->name,dispatch_proc->uuid);
	if(ret<0)
		return -EINVAL;
	return 0;
}
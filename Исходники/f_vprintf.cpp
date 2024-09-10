int lib_dos_f_VPrintf_2(emumsg_syscall_t *msg)
{
	/* Make real syscall */

	msg->arg[0]._long = VPrintf(msg->arg[0]._strptr,(IPTR *)msg->arg[1]._aptr);

	return HOOK_DONE;
}
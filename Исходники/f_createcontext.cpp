int lib_gadtools_f_CreateContext_2(emumsg_syscall_t *msg)
{
	/* Make real syscall */
	msg->arg[0]._aptr = CreateContext(
		(struct Gadget **)msg->arg[0]._aptr
	);

	return HOOK_DONE;
}
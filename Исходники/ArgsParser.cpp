void registerArgs(const arg *allowedArgs)
{
	args = allowedArgs;
	stdout = __acrt_iob_func(1);
}
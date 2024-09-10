VOID
ExecuteWbinvdInstruction (
	IN       AMD_CONFIG_PARAMS *StdHeader
	)
{
	__wbinvd ();
}
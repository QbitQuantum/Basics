static int sceUtilityMsgDialogAbort()
{
	if (currentDialogType != UTILITY_DIALOG_MSG)
	{
		WARN_LOG(SCEUTILITY, "sceUtilityMsgDialogAbort(): wrong dialog type");
		return SCE_ERROR_UTILITY_WRONG_TYPE;
	}
	
	int ret = msgDialog.Abort();
	DEBUG_LOG(SCEUTILITY, "%08x=sceUtilityMsgDialogAbort()", ret);
	return ret;
}
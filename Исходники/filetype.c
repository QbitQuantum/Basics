void imb_filetypes_exit(void)
{
	ImFileType *type;

	for (type = IMB_FILE_TYPES; type < IMB_FILE_TYPES_LAST; type++)
		if (type->exit)
			type->exit();

#ifdef WITH_QUICKTIME
	quicktime_exit();
#endif
}
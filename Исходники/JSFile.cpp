void file_finalize(JSContext *cx, JSObject *obj)
{
	FileData* fdata = (FileData*)JS_GetInstancePrivate(cx, obj, &file_class_ex.base, NULL);
	if(fdata)
	{
		free(fdata->path);
		if(fdata->fptr)
		{
			if(fdata->locked)
			{
				_unlock_file(fdata->fptr);
#if DEBUG
				fdata->lockLocation = __FILE__;
				fdata->line = __LINE__;
#endif
				fclose(fdata->fptr);
			}
			else
				_fclose_nolock(fdata->fptr);
		}
		delete fdata;
	}
}
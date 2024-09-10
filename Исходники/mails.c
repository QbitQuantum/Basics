int SetActiveGroup(struct ClassData * data, STRPTR YahooGroup )
{
	UBYTE buf[2048];
	
	/* crea los nombres de fichero done luego se guardaran los mensages
	 * y el index ( group.idx y group.db )
	 */
	
	DBG_STRING(data->MailsFolder);
	DBG_STRING(YahooGroup);
	
	// this must be called with the semaphore locked !
	if(data->subtask.task == NULL)
	{
		/* Si la subtask esta activa debe tener el control de
		 * data->ActiveGroup, si no tiene que ser liberado
		 */
		
		ExpungeIndex(data, &(data->ActiveGroup));
	}
	
	if(!(data->ActiveGroup = malloc(sizeof(struct GroupFolder))))
		goto done;
	
	if(!(data->ActiveGroup->YahooGroup = strdup( YahooGroup )))
		goto done;
	
	*buf = 0;
	data->LastError = ERR_OVERFLOW;
	if(AddPart( buf, data->MailsFolder, sizeof(buf)-1))
	{
		if(AddPart( buf, data->ActiveGroup->YahooGroup, sizeof(buf)-1))
		{
			STRPTR gfolder = NULL, db = NULL, idx = NULL;
			long buflen = strlen(buf) 
				+ MAX(strlen(IDX_EXT),strlen(DB_EXT)) + 2;
			
			data->LastError = ERR_NOMEM;
			if((gfolder = strdup( buf )))
			{
				if((db = malloc( buflen )))
				{
					if((idx = malloc( buflen )))
					{
						free( data->ActiveGroup->index );
						free( data->ActiveGroup->unixf );
						free( data->ActiveGroup->folder);
						
						data->ActiveGroup->index	= idx;
						data->ActiveGroup->unixf	= db;
						data->ActiveGroup->folder	= gfolder;
						
						SNPrintf(data->ActiveGroup->unixf, buflen-1, "%s%s", gfolder, DB_EXT );
						SNPrintf(data->ActiveGroup->index, buflen-1, "%s%s", gfolder, IDX_EXT );
						
						data->LastError = ERR_NOERROR;
						
						ClearReaderMail( data );
						
						DBG_STRING(data->ActiveGroup->index);
						DBG_STRING(data->ActiveGroup->unixf);
						DBG_STRING(data->ActiveGroup->folder);
					}
				}
			}
			
			if( data->LastError != ERR_NOERROR )
			{
				free( gfolder );
				free( db );
				free( idx );
			}
		}
	}
	
done:
	if( data->LastError != ERR_NOERROR )
	{
		if( data->ActiveGroup )
		{
			free( data->ActiveGroup->YahooGroup );
			free( data->ActiveGroup );
			data->ActiveGroup = NULL;
		}
	}
	return(data->LastError);
}
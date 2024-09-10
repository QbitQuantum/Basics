void ami_fetch_file_poll(const char *scheme_ignored)
{
	struct nsObject *node;
	struct nsObject *nnode;
	struct ami_file_fetch_info *fetch;
	fetch_error_code errorcode;
	
	if(IsMinListEmpty(ami_file_fetcher_list)) return;

	node = (struct nsObject *)GetHead((struct List *)ami_file_fetcher_list);

	do
	{
		errorcode = FETCH_ERROR_NO_ERROR;
		nnode=(struct nsObject *)GetSucc((struct Node *)node);

		fetch = (struct ami_file_fetch_info *)node->objstruct;

		if(fetch->locked) continue;

		if(!fetch->aborted)
		{
			if(fetch->fh)
			{
				ULONG len;

				len = FRead(fetch->fh,ami_file_fetcher_buffer,1,1024);

				if (len == (ULONG)-1)
					errorcode = FETCH_ERROR_MISC;
				else if (len > 0)
					ami_fetch_file_send_callback(
							FETCH_DATA, fetch,
							ami_file_fetcher_buffer,
							len, errorcode);

				if((len<1024) && (!fetch->aborted))
				{
					ami_fetch_file_send_callback(FETCH_FINISHED,
						fetch, NULL, 0,
						errorcode);

					fetch->aborted = true;
				}
			}
			else
			{
				fetch->fh = FOpen(fetch->path,MODE_OLDFILE,0);

				if(fetch->fh)
				{
					char header[64];
					struct ExamineData *fib;
					if(fib = ExamineObjectTags(EX_FileHandleInput,fetch->fh,TAG_DONE))
					{
						fetch->len = fib->FileSize;
						FreeDosObject(DOS_EXAMINEDATA,fib);
					}

					fetch_set_http_code(fetch->fetch_handle,200);
					fetch->mimetype = fetch_mimetype(fetch->path);
					LOG(("mimetype %s len %ld",fetch->mimetype,fetch->len));

					snprintf(header, sizeof header,
							"Content-Type: %s",
							fetch->mimetype);
					ami_fetch_file_send_callback(FETCH_HEADER,
						fetch, header, strlen(header), errorcode);

					snprintf(header, sizeof header,
							"Content-Length: %ld",
							fetch->len);
					ami_fetch_file_send_callback(FETCH_HEADER,
						fetch, header, strlen(header), errorcode);

				}
				else
				{
					STRPTR errorstring;

					errorstring = ASPrintf("%s %s",messages_get("FileError"),fetch->path);
					fetch_set_http_code(fetch->fetch_handle,404);
					
					errorcode = FETCH_ERROR_HTTP_NOT2;
					ami_fetch_file_send_callback(FETCH_ERROR, fetch,
						errorstring, 0,
						errorcode);
					fetch->aborted = true;
					FreeVec(errorstring);
				}
			}
		}

		if(fetch && fetch->aborted)
		{
			fetch_remove_from_queues(fetch->fetch_handle);
			fetch_free(fetch->fetch_handle);
			return;
		}
	}while(node=nnode);
}
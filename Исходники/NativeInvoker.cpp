int NativeInvoker::Invoke(cell_t *result)
{
	int err = SP_ERROR_NONE;

	if (pContext == NULL)
	{
		return SP_ERROR_INVALID_NATIVE;
	}

	if (m_errorstate != SP_ERROR_NONE)
	{
		err = m_errorstate;
		Cancel();
		return err;
	}

	cell_t tresult;

	if (result == NULL)
	{
		result = &tresult;
	}

	//This is for re-entrancy!
	IPluginContext *ctx = pContext;
	cell_t _temp_params[SP_MAX_EXEC_PARAMS + 1];
	cell_t *temp_params = &_temp_params[1];
	ParamInfo temp_info[SP_MAX_EXEC_PARAMS];
	unsigned int numparams = m_curparam;
	unsigned int i;
	bool docopies = true;

	if (numparams)
	{
		//Save the info locally, then reset it for re-entrant calls.
		memcpy(temp_info, m_info, numparams * sizeof(ParamInfo));
	}
	m_curparam = 0;
	pContext = NULL;

	/* Initialize 0th parameter */
	_temp_params[0] = numparams;

	/* Browse the parameters and build arrays */
	for (i = 0; i < numparams; i++)
	{
		/* Is this marked as an array? */
		if (temp_info[i].marked)
		{
			if (!temp_info[i].str.is_sz)
			{
				/* Allocate a normal/generic array */
				if ((err = ctx->HeapAlloc(temp_info[i].size, 
										  &temp_info[i].local_addr,
										  &temp_info[i].phys_addr))
					!= SP_ERROR_NONE)
				{
					break;
				}
				if (temp_info[i].orig_addr)
				{
					memcpy(temp_info[i].phys_addr, temp_info[i].orig_addr, sizeof(cell_t) * temp_info[i].size);
				}
			}
			else
			{
				/* Calculate cells required for the string */
				size_t cells = (temp_info[i].size + sizeof(cell_t) - 1) / sizeof(cell_t);

				/* Allocate the buffer */
				if ((err = ctx->HeapAlloc(cells,
										  &temp_info[i].local_addr,
										  &temp_info[i].phys_addr))
					!= SP_ERROR_NONE)
				{
					break;
				}
				/* Copy original string if necessary */
				if ((temp_info[i].str.sz_flags & SM_PARAM_STRING_COPY) && (temp_info[i].orig_addr != NULL))
				{
					/* Cut off UTF-8 properly */
					if (temp_info[i].str.sz_flags & SM_PARAM_STRING_UTF8)
					{
						if ((err = ctx->StringToLocalUTF8(temp_info[i].local_addr, 
														  temp_info[i].size, 
														  (const char *)temp_info[i].orig_addr,
														  NULL))
							!= SP_ERROR_NONE)
						{
							break;
						}
					}
					/* Copy a binary blob */
					else if (temp_info[i].str.sz_flags & SM_PARAM_STRING_BINARY)
					{
						memmove(temp_info[i].phys_addr, temp_info[i].orig_addr, temp_info[i].size);
					}
					/* Copy ASCII characters */
					else
					{
						if ((err = ctx->StringToLocal(temp_info[i].local_addr,
													  temp_info[i].size,
													  (const char *)temp_info[i].orig_addr))
							!= SP_ERROR_NONE)
						{
							break;
						}
					}
				}
			} /* End array/string calculation */
			/* Update the pushed parameter with the byref local address */
			temp_params[i] = temp_info[i].local_addr;
		}
		else
		{
			/* Just copy the value normally */
			temp_params[i] = m_params[i];
		}
	}

	/* Make the call if we can */
	if (err == SP_ERROR_NONE)
	{
		*result = native(ctx, _temp_params);
		if (ctx->GetLastNativeError() != SP_ERROR_NONE)
		{
			docopies = false;
			ctx->ClearLastNativeError();
		}
	}
	else
	{
		docopies = false;
	}

	/* i should be equal to the last valid parameter + 1 */
	while (i--)
	{
		if (!temp_info[i].marked)
		{
			continue;
		}

		if (docopies && (temp_info[i].flags & SM_PARAM_COPYBACK))
		{
			if (temp_info[i].orig_addr)
			{
				if (temp_info[i].str.is_sz)
				{
					memcpy(temp_info[i].orig_addr, temp_info[i].phys_addr, temp_info[i].size);

				}
				else
				{
					if (temp_info[i].size == 1)
					{
						*temp_info[i].orig_addr = *(temp_info[i].phys_addr);
					}
					else
					{
						memcpy(temp_info[i].orig_addr, 
							temp_info[i].phys_addr, 
							temp_info[i].size * sizeof(cell_t));
					}
				}
			}
		}

		if ((err = ctx->HeapPop(temp_info[i].local_addr)) != SP_ERROR_NONE)
		{
			return err;
		}
	}

	return err;
}
	SQLerror Query(SQLrequest* req)
	{
		if (!sock)
			return SQLerror(SQL_BAD_CONN, "Socket was NULL, check if SQL server is running.");

		/* Pointer to the buffer we screw around with substitution in */
		char* query;

		/* Pointer to the current end of query, where we append new stuff */
		char* queryend;

		/* Total length of the unescaped parameters */
		unsigned long maxparamlen, paramcount;

		/* The length of the longest parameter */
		maxparamlen = 0;

		for(ParamL::iterator i = req->query.p.begin(); i != req->query.p.end(); i++)
		{
			if (i->size() > maxparamlen)
				maxparamlen = i->size();
		}

		/* How many params are there in the query? */
		paramcount = count(req->query.q.c_str(), '?');

		/* This stores copy of params to be inserted with using numbered params 1;3B*/
		ParamL paramscopy(req->query.p);

		/* To avoid a lot of allocations, allocate enough memory for the biggest the escaped query could possibly be.
		 * sizeofquery + (maxtotalparamlength*2) + 1
		 *
		 * The +1 is for null-terminating the string
		 */

		query = new char[req->query.q.length() + (maxparamlen*paramcount*2) + 1];
		queryend = query;

		for(unsigned long i = 0; i < req->query.q.length(); i++)
		{
			if(req->query.q[i] == '?')
			{
				/* We found a place to substitute..what fun.
				 * use mssql calls to escape and write the
				 * escaped string onto the end of our query buffer,
				 * then we "just" need to make sure queryend is
				 * pointing at the right place.
				 */

				/* Is it numbered parameter?
				 */

				bool numbered;
				numbered = false;

				/* Numbered parameter number :|
				 */
				unsigned int paramnum;
				paramnum = 0;

				/* Let's check if it's a numbered param. And also calculate it's number.
				 */

				while ((i < req->query.q.length() - 1) && (req->query.q[i+1] >= '0') && (req->query.q[i+1] <= '9'))
				{
					numbered = true;
					++i;
					paramnum = paramnum * 10 + req->query.q[i] - '0';
				}

				if (paramnum > paramscopy.size() - 1)
				{
					/* index is out of range!
					 */
					numbered = false;
				}

				if (numbered)
				{
					/* Custom escaping for this one. converting ' to '' should make SQL Server happy. Ugly but fast :]
					 */
					char* escaped = new char[(paramscopy[paramnum].length() * 2) + 1];
					char* escend = escaped;
					for (std::string::iterator p = paramscopy[paramnum].begin(); p < paramscopy[paramnum].end(); p++)
					{
						if (*p == '\'')
						{
							*escend = *p;
							escend++;
							*escend = *p;
						}
						*escend = *p;
						escend++;
					}
					*escend = 0;

					for (char* n = escaped; *n; n++)
					{
						*queryend = *n;
						queryend++;
					}
					delete[] escaped;
				}
				else if (req->query.p.size())
				{
					/* Custom escaping for this one. converting ' to '' should make SQL Server happy. Ugly but fast :]
					 */
					char* escaped = new char[(req->query.p.front().length() * 2) + 1];
					char* escend = escaped;
					for (std::string::iterator p = req->query.p.front().begin(); p < req->query.p.front().end(); p++)
					{
						if (*p == '\'')
						{
							*escend = *p;
							escend++;
							*escend = *p;
						}
						*escend = *p;
						escend++;
					}
					*escend = 0;

					for (char* n = escaped; *n; n++)
					{
						*queryend = *n;
						queryend++;
					}
					delete[] escaped;
					req->query.p.pop_front();
				}
				else
					break;
			}
			else
			{
				*queryend = req->query.q[i];
				queryend++;
			}
		}
		*queryend = 0;
		req->query.q = query;

		MsSQLResult* res = new MsSQLResult((Module*)mod, req->source, req->id);
		res->dbid = host.id;
		res->query = req->query.q;

		char* msquery = strdup(req->query.q.data());
		LoggingMutex->Lock();
		ServerInstance->Logs->Log("m_mssql",LOG_DEBUG,"doing Query: %s",msquery);
		LoggingMutex->Unlock();
		if (tds_submit_query(sock, msquery) != TDS_SUCCEED)
		{
			std::string error("failed to execute: "+std::string(req->query.q.data()));
			delete[] query;
			delete res;
			free(msquery);
			return SQLerror(SQL_QSEND_FAIL, error);
		}
		delete[] query;
		free(msquery);

		int tds_res;
		while (tds_process_tokens(sock, &tds_res, NULL, TDS_TOKEN_RESULTS) == TDS_SUCCEED)
		{
			//ServerInstance->Logs->Log("m_mssql",LOG_DEBUG,"<******> result type: %d", tds_res);
			//ServerInstance->Logs->Log("m_mssql",LOG_DEBUG,"AFFECTED ROWS: %d", sock->rows_affected);
			switch (tds_res)
			{
				case TDS_ROWFMT_RESULT:
					break;

				case TDS_DONE_RESULT:
					if (sock->rows_affected > -1)
					{
						for (int c = 0; c < sock->rows_affected; c++)  res->UpdateAffectedCount();
						continue;
					}
					break;

				case TDS_ROW_RESULT:
					while (tds_process_tokens(sock, &tds_res, NULL, TDS_STOPAT_ROWFMT|TDS_RETURN_DONE|TDS_RETURN_ROW) == TDS_SUCCEED)
					{
						if (tds_res != TDS_ROW_RESULT)
							break;

						if (!sock->current_results)
							continue;

						if (sock->res_info->row_count > 0)
						{
							int cols = sock->res_info->num_cols;
							char** name = new char*[MAXBUF];
							char** data = new char*[MAXBUF];
							for (int j=0; j<cols; j++)
							{
								TDSCOLUMN* col = sock->current_results->columns[j];
								name[j] = col->column_name;

								int ctype;
								int srclen;
								unsigned char* src;
								CONV_RESULT dres;
								ctype = tds_get_conversion_type(col->column_type, col->column_size);
#if _TDSVER >= 82
									src = col->column_data;
#else
									src = &(sock->current_results->current_row[col->column_offset]);
#endif
								srclen = col->column_cur_size;
								tds_convert(sock->tds_ctx, ctype, (TDS_CHAR *) src, srclen, SYBCHAR, &dres);
								data[j] = (char*)dres.ib;
							}
							ResultReady(res, cols, data, name);
						}
					}
					break;

				default:
					break;
			}
		}
		ResultsMutex->Lock();
		results.push_back(res);
		ResultsMutex->Unlock();
		return SQLerror();
	}
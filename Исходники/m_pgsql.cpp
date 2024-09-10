	SQLerror DoQuery(SQLrequest &req)
	{
		if((status == WREAD) || (status == WWRITE))
		{
			if(!qinprog)
			{
				/* Parse the command string and dispatch it */

				/* Pointer to the buffer we screw around with substitution in */
				char* query;
				/* Pointer to the current end of query, where we append new stuff */
				char* queryend;

				/* Total length of the unescaped parameters */
				unsigned long maxparamlen, paramcount;

				/* The length of the longest parameter */
				maxparamlen = 0;

				for(ParamL::iterator i = req.query.p.begin(); i != req.query.p.end(); i++)
				{
					if (i->size() > maxparamlen)
						maxparamlen = i->size();
				}

				/* How many params are there in the query? */
				paramcount = count(req.query.q.c_str(), '?');

				/* This stores copy of params to be inserted with using numbered params 1;3B*/
				ParamL paramscopy(req.query.p);

				/* To avoid a lot of allocations, allocate enough memory for the biggest the escaped query could possibly be.
				 * sizeofquery + (maxtotalparamlength*2) + 1
				 *
				 * The +1 is for null-terminating the string for PQsendQuery()
				 */

				query = new char[req.query.q.length() + (maxparamlen*paramcount*2) + 1];
				queryend = query;

				/* Okay, now we have a buffer large enough we need to start copying the query into it and escaping and substituting
				 * the parameters into it...
				 */

				for(unsigned int i = 0; i < req.query.q.length(); i++)
				{
					if(req.query.q[i] == '?')
					{
						/* We found a place to substitute..what fun.
						 * Use the PgSQL calls to escape and write the
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

						while ((i < req.query.q.length() - 1) && (req.query.q[i+1] >= '0') && (req.query.q[i+1] <= '9'))
						{
							numbered = true;
							++i;
							paramnum = paramnum * 10 + req.query.q[i] - '0';
						}

						if (paramnum > paramscopy.size() - 1)
						{
							/* index is out of range!
							 */
							numbered = false;
						}

						if (numbered)
						{
							int error = 0;
							size_t len = 0;

#ifdef PGSQL_HAS_ESCAPECONN
							len = PQescapeStringConn(sql, queryend, paramscopy[paramnum].c_str(), paramscopy[paramnum].length(), &error);
#else
							len = PQescapeString         (queryend, paramscopy[paramnum].c_str(), paramscopy[paramnum].length());
#endif
							if (error)
							{
								ServerInstance->Logs->Log("m_pgsql", DEBUG, "BUG: Apparently PQescapeStringConn() failed somehow...don't know how or what to do...");
							}

							/* Incremenet queryend to the end of the newly escaped parameter */
							queryend += len;
						}
						else if (req.query.p.size())
						{
							int error = 0;
							size_t len = 0;

#ifdef PGSQL_HAS_ESCAPECONN
							len = PQescapeStringConn(sql, queryend, req.query.p.front().c_str(), req.query.p.front().length(), &error);
#else
							len = PQescapeString         (queryend, req.query.p.front().c_str(), req.query.p.front().length());
#endif
							if(error)
							{
								ServerInstance->Logs->Log("m_pgsql",DEBUG, "BUG: Apparently PQescapeStringConn() failed somehow...don't know how or what to do...");
							}

							/* Incremenet queryend to the end of the newly escaped parameter */
							queryend += len;

							/* Remove the parameter we just substituted in */
							req.query.p.pop_front();
						}
						else
						{
							ServerInstance->Logs->Log("m_pgsql",DEBUG, "BUG: Found a substitution location but no parameter to substitute :|");
							break;
						}
					}
					else
					{
						*queryend = req.query.q[i];
						queryend++;
					}
				}

				/* Null-terminate the query */
				*queryend = 0;
				req.query.q = query;

				if(PQsendQuery(sql, query))
				{
					qinprog = true;
					delete[] query;
					return SQLerror();
				}
				else
				{
					delete[] query;
					return SQLerror(SQL_QSEND_FAIL, PQerrorMessage(sql));
				}
			}
		}
		return SQLerror(SQL_BAD_CONN, "Can't query until connection is complete");
	}
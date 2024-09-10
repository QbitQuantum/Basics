	SQLerror Query(SQLrequest &req)
	{
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
		 * The +1 is for null-terminating the string
		 */

		query = new char[req.query.q.length() + (maxparamlen*paramcount*2) + 1];
		queryend = query;

		for(unsigned long i = 0; i < req.query.q.length(); i++)
		{
			if(req.query.q[i] == '?')
			{
				/* We found a place to substitute..what fun.
				 * use sqlite calls to escape and write the
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
					char* escaped;
					escaped = sqlite3_mprintf("%q", paramscopy[paramnum].c_str());
					for (char* n = escaped; *n; n++)
					{
						*queryend = *n;
						queryend++;
					}
					sqlite3_free(escaped);
				}
				else if (req.query.p.size())
				{
					char* escaped;
					escaped = sqlite3_mprintf("%q", req.query.p.front().c_str());
					for (char* n = escaped; *n; n++)
					{
						*queryend = *n;
						queryend++;
					}
					sqlite3_free(escaped);
					req.query.p.pop_front();
				}
				else
					break;
			}
			else
			{
				*queryend = req.query.q[i];
				queryend++;
			}
		}
		*queryend = 0;
		req.query.q = query;

		SQLite3Result* res = new SQLite3Result(mod, req.GetSource(), req.id);
		res->dbid = host.id;
		res->query = req.query.q;
		paramlist params;
		params.push_back(this);
		params.push_back(res);

		char *errmsg = 0;
		sqlite3_update_hook(conn, QueryUpdateHook, &params);
		if (sqlite3_exec(conn, req.query.q.data(), QueryResult, &params, &errmsg) != SQLITE_OK)
		{
			std::string error(errmsg);
			sqlite3_free(errmsg);
			delete[] query;
			delete res;
			return SQLerror(SQL_QSEND_FAIL, error);
		}
		delete[] query;

		results.push_back(res);
		SendNotify();
		return SQLerror();
	}
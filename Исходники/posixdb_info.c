fsal_posixdb_status_t fsal_posixdb_getInfoFromName(fsal_posixdb_conn * p_conn,  /* IN */
                                                   posixfsal_handle_t * p_parent_directory_handle,      /* IN/OUT */
                                                   fsal_name_t * p_objectname,  /* IN */
                                                   fsal_path_t * p_path,        /* OUT */
                                                   posixfsal_handle_t *
                                                   p_handle /* OUT */ )
{
  PGresult *p_res;
  fsal_posixdb_status_t st;
  char handleid_str[MAX_HANDLEIDSTR_SIZE];
  char handlets_str[MAX_HANDLETSSTR_SIZE];
  const char *paramValues[3] = { handleid_str, handlets_str, p_objectname->name };

  /* sanity check */
  if(!p_conn || !p_handle)
    {
      ReturnCodeDB(ERR_FSAL_POSIXDB_FAULT, 0);
    }

  CheckConn(p_conn);

  LogFullDebug(COMPONENT_FSAL, "object_name='%s'\n", p_objectname->name);

  BeginTransaction(p_conn, p_res);
  /* lookup for the handle of the file */
  if(p_parent_directory_handle && p_parent_directory_handle->data.id)
    {
      snprintf(handleid_str, MAX_HANDLEIDSTR_SIZE, "%lli", p_parent_directory_handle->data.id);
      snprintf(handlets_str, MAX_HANDLETSSTR_SIZE, "%i", p_parent_directory_handle->data.ts);
      p_res = PQexecPrepared(p_conn, "lookupHandleByName", 3, paramValues, NULL, NULL, 0);
      CheckResult(p_res);
    }
  else
    {
      // get root handle :
      p_res = PQexecPrepared(p_conn, "lookupRootHandle", 0, NULL, NULL, NULL, 0);
      CheckResult(p_res);
    }
  /* p_res contains : Parent.handleid, Parent.handlets, Handle.deviceId, Handle.inode, Handle.nlink, Handle.ctime, Handle.ftype  */

  /* entry not found */
  if(PQntuples(p_res) != 1)
    {
      PQclear(p_res);
      RollbackTransaction(p_conn, p_res);
      ReturnCodeDB(ERR_FSAL_POSIXDB_NOENT, 0);
    }

  p_handle->data.id = atoll(PQgetvalue(p_res, 0, 0));
  p_handle->data.ts = atoi(PQgetvalue(p_res, 0, 1));
  posixdb_internal_fillFileinfoFromStrValues(&(p_handle->data.info), PQgetvalue(p_res, 0, 2), PQgetvalue(p_res, 0, 3), PQgetvalue(p_res, 0, 4),      /* nlink */
                                             PQgetvalue(p_res, 0, 5),   /* ctime */
                                             PQgetvalue(p_res, 0, 6)    /* ftype */
      );
  PQclear(p_res);

  /* Build the path of the object */
  if(p_path && p_objectname)
    {
      /* build the path of the Parent */
      st = fsal_posixdb_buildOnePath(p_conn, p_parent_directory_handle, p_path);
      if(st.major != ERR_FSAL_POSIXDB_NOERR)
        {
          RollbackTransaction(p_conn, p_res);
          return st;
        }

      /* then concatenate the filename */
      if(!(p_path->len + 1 + p_objectname->len < FSAL_MAX_PATH_LEN))
        {
          RollbackTransaction(p_conn, p_res);
          ReturnCodeDB(ERR_FSAL_POSIXDB_PATHTOOLONG, 0);
        }
      p_path->path[p_path->len] = '/';
      strcpy(&p_path->path[p_path->len + 1], p_objectname->name);
      p_path->len += 1 + p_objectname->len;

      /* add the the path to cache */
      fsal_posixdb_CachePath(p_handle, p_path);
    }
  else
    {
      /* update handle if it was in cache */
      fsal_posixdb_UpdateInodeCache(p_handle);
    }

  EndTransaction(p_conn, p_res);

  ReturnCodeDB(ERR_FSAL_POSIXDB_NOERR, 0);
}
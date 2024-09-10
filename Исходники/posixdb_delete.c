fsal_posixdb_status_t fsal_posixdb_deleteHandle(fsal_posixdb_conn * p_conn,     /* IN */
                                                posixfsal_handle_t *
                                                p_parent_directory_handle /* IN */ )
{
/*    char           handleid_str[MAX_HANDLEIDSTR_SIZE];
    char           handlets_str[MAX_HANDLETSSTR_SIZE];
    const char    *paramValues[2]; */
  int found;
  result_handle_t res;
  fsal_posixdb_status_t st;
  char query[2048];

  BeginTransaction(p_conn);

  LogFullDebug(COMPONENT_FSAL, "Deleting %llu.%u\n", p_parent_directory_handle->data.id,
         p_parent_directory_handle->data.ts);

  snprintf(query, 2048,
           "SELECT Handle.deviceid, Handle.inode, Handle.nlink, Handle.ctime, Handle.ftype "
           "FROM Handle WHERE handleid=%llu AND handlets=%u FOR UPDATE",
           p_parent_directory_handle->data.id, p_parent_directory_handle->data.ts);

  st = db_exec_sql(p_conn, query, &res);
  if(FSAL_POSIXDB_IS_ERROR(st))
    goto rollback;

  found = mysql_num_rows(res);
  mysql_free_result(res);

  if(found)
    {
      /* entry found */
      st = fsal_posixdb_recursiveDelete(p_conn, p_parent_directory_handle->data.id,
                                        p_parent_directory_handle->data.ts, FSAL_TYPE_DIR);
      if(FSAL_POSIXDB_IS_ERROR(st))
        goto rollback;
    }

  return EndTransaction(p_conn);

 rollback:
  RollbackTransaction(p_conn);
  return st;

}
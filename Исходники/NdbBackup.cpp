int  
NdbBackup::execRestore(bool _restore_data,
		       bool _restore_meta,
		       int _node_id,
		       unsigned _backup_id){
  const int buf_len = 1000;
  char buf[buf_len];

  ndbout << "getBackupDataDir "<< _node_id <<endl;

  const char* path = getBackupDataDirForNode(_node_id);
  if (path == NULL)
    return -1;  

  ndbout << "getHostName "<< _node_id <<endl;
  const char *host;
  if (!getHostName(_node_id, &host)){
    return -1;
  }

  /* 
   * Copy  backup files to local dir
   */ 

  BaseString::snprintf(buf, buf_len,
	   "scp %s:%s/BACKUP/BACKUP-%d/BACKUP-%d*.%d.* .",
	   host, path,
	   _backup_id,
	   _backup_id,
	   _node_id);

  ndbout << "buf: "<< buf <<endl;
  int res = system(buf);  
  
  ndbout << "scp res: " << res << endl;
  
  BaseString::snprintf(buf, 255, "%sndb_restore -c \"%s:%d\" -n %d -b %d %s %s .", 
#if 1
	   "",
#else
	   "valgrind --leak-check=yes -v "
#endif
	   ndb_mgm_get_connected_host(handle),
	   ndb_mgm_get_connected_port(handle),
	   _node_id, 
	   _backup_id,
	   _restore_data?"-r":"",
	   _restore_meta?"-m":"");

  ndbout << "buf: "<< buf <<endl;
  res = system(buf);

  ndbout << "ndb_restore res: " << res << endl;

  return res;
  
}
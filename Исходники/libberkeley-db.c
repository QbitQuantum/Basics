int next_counter(DB_ENV *env, DB *db, DB_TXN *parent,
		 unsigned char *key, u_int32_t key_size,
		 unsigned char *lockid, u_int32_t lockid_size) {
  DB_LOCK lock;
  DBT DBTKey, DBTData; 
  DB_TXN *tid; 
  int counter, tries, ret, t_ret, lockheld;
  u_int32_t id;

  /* Initialization. */ 
  memset(&lock, 0, sizeof(lock)); 
  memset(&DBTKey, 0, sizeof(DBTKey)); 
  memset(&DBTData, 0, sizeof(DBTData)); 
  DBTKey.data = key;
  DBTKey.size = key_size;
  DBTData.data = lockid;
  DBTData.size = lockid_size;

  tries = 0;

 loop:
  lockheld = 0;

  /* Begin the transaction. */ 
  if ((ret = env->txn_begin(env, parent, &tid, 0)) != 0) { 
    env->err(env, ret, "DB_ENV->txn_begin"); 
    return (-1); 
  }

  id = tid->id(tid);

  if ((ret = env->lock_get(env, id, 0, &DBTData, DB_LOCK_WRITE, &lock)) != 0)
    goto fail;

  lockheld = 1;

  memset(&DBTData, 0, sizeof(DBTData)); 
  DBTData.data = &counter;
  DBTData.ulen = sizeof(counter);
  DBTData.flags |= DB_DBT_USERMEM;

  if ((ret = db->get(db, tid, &DBTKey, &DBTData, 0)) != 0) 
    goto fail;

  ++counter;

  memset(&DBTData, 0, sizeof(DBTData)); 
  DBTData.data = &counter;
  DBTData.size = sizeof(counter);

  if ((ret = db->put(db, tid, &DBTKey, &DBTData, 0)) != 0) 
    goto fail;

  if ((ret = env->lock_put(env, &lock)) != 0) 
    goto fail;

  if ((ret = tid->commit(tid, DB_TXN_NOSYNC)) != 0) { 
    env->err(env, ret, "DB_TXN->commit"); 
    return (-2); 
  } 
  return (counter); 


 fail:
  if (lockheld)
    if ((ret = env->lock_put(env, &lock)) != 0) 
      return (-3);

  /* Abort and retry the operation. */ 
  if ((t_ret = tid->abort(tid)) != 0) { 
    env->err(env, t_ret, "DB_TXN->abort"); 
    return (-4);
  } 
  if (tries++ == 100)
    return (-5); 
  goto loop;
}
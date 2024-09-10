/** 
 * @brief Unlock the Handle line previously locked by fsal_posixdb_lockHandleForUpdate
 * 
 * @param p_conn
 *        Database connection
 * 
 * @return ERR_FSAL_POSIXDB_NOERR if no error,
 *         another error code else.
 */
fsal_posixdb_status_t fsal_posixdb_cancelHandleLock(fsal_posixdb_conn * p_conn /* IN */ )
{
  RollbackTransaction(p_conn);

  ReturnCodeDB(ERR_FSAL_POSIXDB_NOERR, 0);
}
xbShort xbXBase::LockFile( int fn, xbShort LockType, xbOffT lockLen)
{

  int mode;
  int rc;
  int tries = 0;

  /* convert the xbase locking command into a windows locking command */
  if( LockType == XB_UNLOCK )
    mode = LK_UNLCK;
  else if( LockType == XB_LOCK || LockType == XB_LOCK_HOLD )
    mode = LK_NBLCK;
  else
    return XB_INVALID_LOCK_OPTION;

  do{
    rc = locking( fn, mode, lockLen );
    if( rc )
      _sleep( 1 );
  } while( rc == -1 && tries++ < GetLockRetryCount());
  
  if( rc )
    return XB_LOCK_FAILED;
  
  return 0;
}
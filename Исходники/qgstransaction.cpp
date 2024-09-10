bool QgsTransaction::rollback( QString& errorMsg )
{
  if ( !mTransactionActive )
    return false;

  if ( !rollbackTransaction( errorMsg ) )
    return false;

  setLayerTransactionIds( nullptr );
  mTransactionActive = false;

  emit afterRollback();

  return true;
}
 void Transaction::Commit()
 {
   SQLRETURN Ret = SQLTransact(Conn.GetEnv().GetHolder().GetHandle(), Conn.GetHolder().GetHandle(), SQL_COMMIT);
   if (Ret != SQL_SUCCESS)
     throw TransactionException("Error commit transaction", teErrorCommit);
   Commited = true;
 }
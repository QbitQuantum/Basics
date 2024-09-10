bool wb_db::deleteOset(pwr_tStatus *sts, wb_oset *o)
{
  DbTxn *txn = 0;

  m_env->txn_begin(m_txn, &txn, 0);

  try {
    //del_family(txn, o);
    //unadopt(txn, wb_Position(o));
    //del_ohead(txn, o);
    //del_clist(txn, o);
    //del_name(txn, o);
    //del_body(txn, o);

    txn->commit(0);
  }
  catch (DbException &e) {
    txn->abort();
  }

  return true;
}
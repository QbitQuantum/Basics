void
tw_set_pos_l (t1_window_t * tw, int nth, int op, int line)
{
  int rc;
#if 0
  rc = SQLSetPos (tw->tw_stmt, nth, SQL_POSITION, SQL_LOCK_NO_CHANGE);
  tw->tw_rc = rc;
  if (rc != SQL_SUCCESS)
    print_error (SQL_NULL_HENV, SQL_NULL_HDBC, tw->tw_stmt);
#endif
  rc = SQLSetPos (tw->tw_stmt, nth, op, SQL_LOCK_NO_CHANGE);
  tw->tw_rc = rc;
  if (!quiet)
    printf ("SQLSetPos %s %d %d = %d  line %d\n", tw->tw_name, nth, op, rc, line);
  if (rc != SQL_SUCCESS)
    print_error (SQL_NULL_HENV, SQL_NULL_HDBC, tw->tw_stmt);
  if (!quiet && nth != 0 && op == SQL_REFRESH
      && rc != SQL_ERROR)
    {
      printf ("      = ");
      t1_print (&tw->tw_set [nth-1], SQL_ROW_SUCCESS);
    }
}
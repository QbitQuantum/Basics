static awk_value_t *
do_pg_getresult(int nargs, awk_value_t *result)
{
  PGconn *conn;
  PGresult *res;

  if (do_lint && (nargs > 1))
    lintwarn(ext_id, _("pg_getresult: called with too many arguments"));

  if (!(conn = find_handle(conns, 0))) {
    set_ERRNO(_("pg_getresult called with unknown connection handle"));
    RET_NULSTR;
  }

  if (!(res = PQgetResult(conn)))
    /* this just means there are no results currently available, so it is
       not necessarily an error */
    RET_NULSTR;
  return process_result(conn, res, result);
}
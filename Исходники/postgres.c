static void postgres_ingest_stats(postgres_check_info_t *ci) {
  if(ci->rv == PGRES_TUPLES_OK) {
    /* metrics */
    int nrows, ncols, i, j;
    nrows = PQntuples(ci->result);
    ncols = PQnfields(ci->result);
    noit_stats_set_metric(&ci->current, "row_count", METRIC_INT32, &nrows);
    for (i=0; i<nrows; i++) {
      noitL(nldeb, "postgres: row %d [%d cols]:\n", i, ncols);
      if(ncols<2) continue;
      if(PQgetisnull(ci->result, i, 0)) continue;
      for (j=1; j<ncols; j++) {
        Oid coltype;
        int iv, *piv;
        int64_t lv, *plv;
        double dv, *pdv;
        char *sv;
        char mname[128];
  
        snprintf(mname, sizeof(mname), "%s`%s",
                 PQgetvalue(ci->result, i, 0), PQfname(ci->result, j));
        coltype = PQftype(ci->result, j);
        noitL(nldeb, "postgres:   col %d (%s) type %d: %s\n", j, mname, coltype,
              PQgetisnull(ci->result, i, j) ? "[[null]]" : PQgetvalue(ci->result, i, j));
        switch(coltype) {
          case BOOLOID:
            if(PQgetisnull(ci->result, i, j)) piv = NULL;
            else {
              iv = strcmp(PQgetvalue(ci->result, i, j), "f") ? 1 : 0;
              piv = &iv;
            }
            noit_stats_set_metric(&ci->current, mname, METRIC_INT32, piv);
            break;
          case INT2OID:
          case INT4OID:
          case INT8OID:
            if(PQgetisnull(ci->result, i, j)) plv = NULL;
            else {
              lv = strtoll(PQgetvalue(ci->result, i, j), NULL, 10);
              plv = &lv;
            }
            noit_stats_set_metric(&ci->current, mname, METRIC_INT64, plv);
            break;
          case FLOAT4OID:
          case FLOAT8OID:
          case NUMERICOID:
            if(PQgetisnull(ci->result, i, j)) pdv = NULL;
            else {
              dv = atof(PQgetvalue(ci->result, i, j));
              pdv = &dv;
            }
            noit_stats_set_metric(&ci->current, mname, METRIC_DOUBLE, pdv);
            break;
          default:
            if(PQgetisnull(ci->result, i, j)) sv = NULL;
            else sv = PQgetvalue(ci->result, i, j);
            noit_stats_set_metric(&ci->current, mname, METRIC_GUESS, sv);
            break;
        }
      }
    }
  }
}
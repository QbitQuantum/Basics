/*
 * Function: pg_get_result
 *
 * Executes a PostgreSQL Query using connection details from a Zabbix agent
 * request structure and updates the agent result structure with the value of
 * the first column of the first row returned.
 *
 * type may be 
 *
 * Query parameters may be provided as a NULL terminated sequence of *char
 * values in the ... parameter.
 *
 * Parameter [request]: Zabbix agent request structure.
 *          Passed to pg_connect to fetch as valid PostgreSQL
 *          server connection
 *
 * Parameter [result]:  Zabbix agent result structure
 *
 * Parameter [type]:    Result type to set. May be one of AR_STRING, AR_UINT64
 *          or AR_DOUBLE.
 *
 * Paramater [query]:   PostgreSQL query to execute. Query should return a
 *          single scalar string value. Parameters defined using PostgreSQL's
 *          '$n' notation will be replaced with the corresponding variadic
 *          argument provided in ...
 *
 * Returns: SYSINFO_RET_OK or SYSINFO_RET_FAIL on error
 */
int    pg_get_result(AGENT_REQUEST *request, AGENT_RESULT *result, int type, const char *query, PGparams params)
{
    int         ret = SYSINFO_RET_FAIL;             // Request result code
    const char  *__function_name = "pg_get_result"; // Function name for log file
    
    PGconn      *conn = NULL;
    PGresult    *res = NULL;
    char        *value = NULL;
    
    zabbix_log(LOG_LEVEL_DEBUG, "In %s(%s)", __function_name, request->key);
    
    // Connect to PostreSQL
    if(NULL == (conn = pg_connect(request)))
        goto out;
    
    // Execute a query
    res = pg_exec(conn, query, params);

    if(PQresultStatus(res) != PGRES_TUPLES_OK) {
        zabbix_log(LOG_LEVEL_ERR, "Failed to execute PostgreSQL query in %s(%s) with: %s", __function_name, request->key, PQresultErrorMessage(res));
        goto out;
    }
    
    if(0 == PQntuples(res)) {
        zabbix_log(LOG_LEVEL_DEBUG, "No results returned for query \"%s\" in %s(%s)", query, __function_name, request->key);
        goto out;
    }
    
    // get scalar value (freed later by PQclear)
    value = PQgetvalue(res, 0, 0);

    // Set result
    switch(type) {
        case AR_STRING:
            // string result (zabbix will clean the strdup'd buffer)
            SET_STR_RESULT(result, strdup(value));
            break;

        case AR_UINT64:
            // integer result
            // Convert E Notation
            if(1 < strlen(value) && '.' == value[1]) {
                double dbl = strtod(value, NULL);
                SET_UI64_RESULT(result, (unsigned long long) dbl);
            } else {
                SET_UI64_RESULT(result, strtoull(value, NULL, 10));
            }
            break;

        case AR_DOUBLE:
            // double result
            SET_DBL_RESULT(result, strtold(value, NULL));
            break;

        default:
            // unknown result type
            zabbix_log(LOG_LEVEL_ERR, "Unsupported result type: 0x%0X in %s", type, __function_name);
            goto out;
    }

    ret = SYSINFO_RET_OK;
    
out:
    PQclear(res);
    PQfinish(conn);
    
    zabbix_log(LOG_LEVEL_DEBUG, "End of %s(%s)", __function_name, request->key);
    return ret;
}
int
writeIpStats(int action,
             u_char * var_val,
             u_char var_val_type,
             size_t var_val_len,
             u_char * statP, oid * name, size_t name_len)
{
    long           *buf, *oldbuf;
    MIB_IPSTATS     ipStats;
    int             var;
    int             retval = SNMP_ERR_NOERROR;
    /*
     * #define for ip scalar objects are 1 less than corresponding sub-id in MIB
     * * i.e. IPFORWARDING defined as 0, but ipForwarding registered as 1
     */
    var = name[7] - 1;
    switch (var) {
    case IPFORWARDING:
        buf = &ipForwarding;
        oldbuf = &oldipForwarding;
        break;
    case IPDEFAULTTTL:
        buf = &ipTTL;
        oldbuf = &oldipTTL;
        break;
    default:
        return SNMP_ERR_NOTWRITABLE;
    }

    switch (action) {
    case RESERVE1:             /* Check values for acceptability */
        if (var_val_type != ASN_INTEGER) {
            snmp_log(LOG_ERR, "not integer\n");
            return SNMP_ERR_WRONGTYPE;
        }
        if (var_val_len > sizeof(int)) {
            snmp_log(LOG_ERR, "bad length\n");
            return SNMP_ERR_WRONGLENGTH;
        }
        switch (var) {
        case IPFORWARDING:
            if (((int) *var_val < 1) || ((int) *var_val > 2)) {
                snmp_log(LOG_ERR, "not supported ip forwarding : %d\n",
                         *var_val);
                return SNMP_ERR_WRONGVALUE;
            }
            break;
        case IPDEFAULTTTL:
            if ((int) *var_val < 0) {
                snmp_log(LOG_ERR, "not supported ip Default : %d\n",
                         (int) *var_val);
                return SNMP_ERR_WRONGVALUE;
            }
        }
        break;

    case RESERVE2:             /* Allocate memory and similar resources */
        break;

    case ACTION:
        /*
         * Save the old value, in case of UNDO 
         */

        *oldbuf = *buf;
        *buf = (int) *var_val;
        break;

    case UNDO:                 /* Reverse the SET action and free resources */
        *buf = *oldbuf;
        break;

    case COMMIT:               /* Confirm the SET, performing any irreversible actions,
                                 * and free resources */
        switch (var) {
        case IPFORWARDING:
            /*
             * Currently windows supports only ON->OFF 
             */
            ipStats.dwForwarding = *buf;
            ipStats.dwDefaultTTL = MIB_USE_CURRENT_TTL;
            if (SetIpStatistics(&ipStats) != NO_ERROR) {
                retval = SNMP_ERR_COMMITFAILED;
                snmp_log(LOG_ERR,
                         "Can't set ipForwarding, supports only enable->disable \n");
            }
            break;
        case IPDEFAULTTTL:
            if (SetIpTTL((UINT) * buf) != NO_ERROR) {
                retval = SNMP_ERR_COMMITFAILED;
                snmp_log(LOG_ERR, "Can't set ipDefaultTTL\n");
            }
            break;
        }

    case FREE:                 /* Free any resources allocated */
        break;
    }
    return retval;
}                               /* end of writeIpStats */
int
write_rte(int action,
          u_char * var_val,
          u_char var_val_type,
          size_t var_val_len, u_char * statP, oid * name, size_t length)
{
    int             var, retval = NO_ERROR;
    static PMIB_IPFORWARDROW oldroute_row = NULL;
    static int      mask_flag = 0, nexthop_flag = 0;
    static int      index_flag = 0, metric_flag = 0;
    static int      dest_flag = 0;
    DWORD           status = NO_ERROR;
    /*
     * object identifier is of form:
     * 1.3.6.1.2.1.4.21.1.X.A.B.C.D ,  where A.B.C.D is IP address.
     * IPADDR starts at offset 10.
     */

    if (length != 14) {
        snmp_log(LOG_ERR, "length error\n");
        return SNMP_ERR_NOCREATION;
    }
    /*
     * #define for ipRouteTable entries are 1 less than corresponding sub-id in MIB
     * * i.e. IPROUTEDEST defined as 0, but ipRouteDest registered as 1
     */
    var = name[9] - 1;

    switch (action) {
    case RESERVE1:
        switch (var) {
        case IPROUTEMETRIC1:
        case IPROUTEMETRIC2:
        case IPROUTEMETRIC3:
        case IPROUTEMETRIC4:
        case IPROUTEMETRIC5:
        case IPROUTETYPE:
        case IPROUTEAGE:
        case IPROUTEIFINDEX:
            if (var_val_type != ASN_INTEGER) {
                snmp_log(LOG_ERR, "not integer\n");
                return SNMP_ERR_WRONGTYPE;
            }
            if (var_val_len > sizeof(int)) {
                snmp_log(LOG_ERR, "bad length\n");
                return SNMP_ERR_WRONGLENGTH;
            }
            if (var == IPROUTETYPE) {
                if ((*((int *) var_val)) < 2 || (*((int *) var_val)) > 4) {
                    snmp_log(LOG_ERR, "invalid ipRouteType\n");
                    return SNMP_ERR_WRONGVALUE;
                }
            } else if ((var == IPROUTEIFINDEX) || (var == IPROUTEAGE)) {
                if ((*((int *) var_val)) < 0) {
                    snmp_log(LOG_ERR, "invalid ipRouteIfIndex\n");
                    return SNMP_ERR_WRONGVALUE;
                }
            } else {
                if ((*((int *) var_val)) < -1) {
                    snmp_log(LOG_ERR, "not right1");
                    return SNMP_ERR_WRONGVALUE;
                }
            }
            break;
        case IPROUTENEXTHOP:
        case IPROUTEMASK:
        case IPROUTEDEST:
            if (var_val_type != ASN_IPADDRESS) {
                snmp_log(LOG_ERR, "not right4");
                return SNMP_ERR_WRONGTYPE;
            }
            if (var_val_len != 4) {
                snmp_log(LOG_ERR, "incorrect ipAddress length");
                return SNMP_ERR_WRONGLENGTH;
            }
            break;
        default:
            DEBUGMSGTL(("snmpd", "unknown sub-id %d in write_rte\n",
                        var + 1));
            retval = SNMP_ERR_NOTWRITABLE;
        }
        break;

    case RESERVE2:
        /*
         * Save the old value, in case of UNDO 
         */
        if (oldroute_row == NULL) {
            oldroute_row =
                (PMIB_IPFORWARDROW) malloc(sizeof(MIB_IPFORWARDROW));
            *oldroute_row = *route_row;
        }
        break;

    case ACTION:               /* Perform the SET action (if reversible) */
        switch (var) {
        case IPROUTEMETRIC1:
            metric_flag = 1;
            route_row->dwForwardMetric1 = *((int *) var_val);
            break;
        case IPROUTEMETRIC2:
            route_row->dwForwardMetric2 = *((int *) var_val);
            break;
        case IPROUTEMETRIC3:
            route_row->dwForwardMetric3 = *((int *) var_val);
            break;
        case IPROUTEMETRIC4:
            route_row->dwForwardMetric4 = *((int *) var_val);
            break;
        case IPROUTEMETRIC5:
            route_row->dwForwardMetric5 = *((int *) var_val);
            break;
        case IPROUTETYPE:
            route_row->dwForwardType = *((int *) var_val);
            break;
        case IPROUTEAGE:
            /*
             * Irrespective of suppied value, this will be set with 0.
             * * As row will be updated and this field gives the number of 
             * * seconds since this route was last updated
             */
            route_row->dwForwardAge = *((int *) var_val);
            break;
        case IPROUTEIFINDEX:
            index_flag = 1;
            route_row->dwForwardIfIndex = *((int *) var_val);
            break;

        case IPROUTENEXTHOP:
            nexthop_flag = 1;
            route_row->dwForwardNextHop = *((DWORD *) var_val);
            break;
        case IPROUTEMASK:
            mask_flag = 1;
            route_row->dwForwardMask = *((DWORD *) var_val);
            break;
        case IPROUTEDEST:
            dest_flag = 1;
            route_row->dwForwardDest = *((DWORD *) var_val);
            break;
        default:
            DEBUGMSGTL(("snmpd", "unknown sub-id %d in write_rte\n",
                        var + 1));
            retval = SNMP_ERR_NOTWRITABLE;
        }
        return retval;
    case UNDO:
        /*
         * Reverse the SET action and free resources 
         */
        if (oldroute_row) {
            *route_row = *oldroute_row;
            free(oldroute_row);
            oldroute_row = NULL;
            free(route_row);
            route_row = NULL;
        }
        break;

    case COMMIT:
        /*
         * When this case entered 'route_row' will have user supplied values for asked entries. 
         * * Thats why it is enough if we call SetIpForwardEntry/CreateIpForwardEntry only once 
         * * SetIpForwardENtry is not done in ACTION phase, as that will reset ipRouteAge on success
         * * and if any varbind fails, then we can't UNDO the change for ipROuteAge. 
         */
        if (route_row) {
            if (!create_flag) {

                if (SetIpForwardEntry(route_row) != NO_ERROR) {
                    snmp_log(LOG_ERR,
                             "Can't set route table's row with specified value\n");
                    retval = SNMP_ERR_COMMITFAILED;
                } else {
                    /*
                     * SET on IpRouteNextHop, IpRouteMask & ipRouteDest creates new row. 
                     * *If Set succeeds, then delete the old row.
                     * * Don't know yet whether SET on ipRouteIfIndex creates new row.
                     * * If it creates then index_flag should be added to following if statement
                     */

                    if (dest_flag || nexthop_flag || mask_flag) {
                        oldroute_row->dwForwardType = 2;
                        if (SetIpForwardEntry(oldroute_row) != NO_ERROR) {
                            snmp_log(LOG_ERR,
                                     "Set on ipRouteTable created new row, but failed to delete the old row\n");
                            retval = SNMP_ERR_GENERR;
                        }
                    }
                }
            }
            /*
             * Only if create_flag, mask, nexthop, ifIndex and metric are specified, create new entry 
             */
            if (create_flag) {
                if (mask_flag && nexthop_flag && metric_flag && index_flag) {
                    if ((status =
                         CreateIpForwardEntry(route_row)) != NO_ERROR) {
                        snmp_log(LOG_ERR,
                                 "Inside COMMIT: CreateIpNetEntry failed, status %lu\n",
                                 status);
                        retval = SNMP_ERR_COMMITFAILED;
                    }
                } else {
                    /*
                     * For new entry, mask, nexthop, ifIndex and metric must be supplied 
                     */
                    snmp_log(LOG_ERR,
                             "case COMMIT, can't create without index, mask, nextHop and metric\n");
                    retval = SNMP_ERR_WRONGVALUE;
                }
            }
        }

    case FREE:
        /*
         * Free any resources allocated 
         */
        free(oldroute_row);
        oldroute_row = NULL;
        free(route_row);
        route_row = NULL;
        mask_flag = nexthop_flag = metric_flag = index_flag = dest_flag =
            0;
        break;
    }
    return retval;
}
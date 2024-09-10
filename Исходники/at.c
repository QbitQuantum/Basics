int
write_arp(int action,
          u_char * var_val,
          u_char var_val_type,
          size_t var_val_len, u_char * statP, oid * name, size_t length)
{
    int             var, retval = SNMP_ERR_NOERROR;
    static PMIB_IPNETROW oldarp_row = NULL;
    MIB_IPNETROW    temp_row;
    DWORD           status = NO_ERROR;

    /*
     * IP Net to Media table object identifier is of form:
     * 1.3.6.1.2.1.4.22.1.?.interface.A.B.C.D,  where A.B.C.D is IP address.
     * Interface is at offset 10,
     * IPADDR starts at offset 11.
     */

    if (name[6] == 3) {         /* AT group oid */
        if (length != 16) {
            snmp_log(LOG_ERR, "length error\n");
            return SNMP_ERR_NOCREATION;
        }
    } else {                    /* IP NetToMedia group oid */
        if (length != 15) {
            snmp_log(LOG_ERR, "length error\n");
            return SNMP_ERR_NOCREATION;
        }
    }


    /*
     * #define for ipNetToMediaTable entries are 1 less than corresponding sub-id in MIB
     * * i.e. IPMEDIAIFINDEX defined as 0, but ipNetToMediaIfIndex registered as 1
     */
    var = name[9] - 1;
    switch (action) {
    case RESERVE1:
        switch (var) {
        case IPMEDIAIFINDEX:
            if (var_val_type != ASN_INTEGER) {
                snmp_log(LOG_ERR, "not integer\n");
                return SNMP_ERR_WRONGTYPE;
            }
            if ((*((int *) var_val)) < 0) {
                snmp_log(LOG_ERR, "invalid media ifIndex");
                return SNMP_ERR_WRONGVALUE;
            }
            if (var_val_len > sizeof(int)) {
                snmp_log(LOG_ERR, "bad length\n");
                return SNMP_ERR_WRONGLENGTH;
            }
            break;
        case IPMEDIANETADDRESS:
            if (var_val_type != ASN_IPADDRESS) {
                snmp_log(LOG_ERR, "not IP Address\n");
                return SNMP_ERR_WRONGTYPE;
            }
            if ((*((int *) var_val)) < 0) {
                snmp_log(LOG_ERR, "invalid media net address");
                return SNMP_ERR_WRONGVALUE;
            }
            if (var_val_len > sizeof(DWORD)) {
                snmp_log(LOG_ERR, "bad length\n");
                return SNMP_ERR_WRONGLENGTH;
            }
            break;
        case IPMEDIATYPE:
            if (var_val_type != ASN_INTEGER) {
                snmp_log(LOG_ERR, "not integer\n");
                return SNMP_ERR_WRONGTYPE;
            }
            if ((*((int *) var_val)) < 1 || (*((int *) var_val)) > 4) {
                snmp_log(LOG_ERR, "invalid media type");
                return SNMP_ERR_WRONGVALUE;
            }
            if (var_val_len > sizeof(int)) {
                snmp_log(LOG_ERR, "bad length\n");
                return SNMP_ERR_WRONGLENGTH;
            }
            break;
        case IPMEDIAPHYSADDRESS:
            if (var_val_type != ASN_OCTET_STR) {
                snmp_log(LOG_ERR, "not octet str");
                return SNMP_ERR_WRONGTYPE;
            }
            if (var_val_len != 6) {
                snmp_log(LOG_ERR, "not correct ipAddress length: %d",
                         var_val_len);
                return SNMP_ERR_WRONGLENGTH;
            }
            break;
        default:
            DEBUGMSGTL(("snmpd", "unknown sub-id %d in write_rte\n",
                        var + 1));
            return SNMP_ERR_NOTWRITABLE;
        }
        break;
    case RESERVE2:
        /*
         * Save the old value, in case of UNDO 
         */
        if (oldarp_row == NULL) {
            oldarp_row = (PMIB_IPNETROW) malloc(sizeof(MIB_IPNETROW));
            *oldarp_row = *arp_row;
        }
        break;
    case ACTION:               /* Perform the SET action (if reversible) */
        switch (var) {

        case IPMEDIAIFINDEX:
            temp_row = *arp_row;
            arp_row->dwIndex = *((int *) var_val);
            /*
             * In case of new entry, physical address is mandatory.
             * * SetIpNetEntry will be done in COMMIT case 
             */
            if (!create_flag) {
                if (SetIpNetEntry(arp_row) != NO_ERROR) {
                    arp_row->dwIndex = temp_row.dwIndex;
                    retval = SNMP_ERR_COMMITFAILED;
                }
                /*
                 * Don't know yet, whether change in ifIndex creates new row or not 
                 */
                /*
                 * else{ 
                 */
                /*
                 * temp_row.dwType = 2; 
                 */
                /*
                 * if(SetIpNetEntry(&temp_row) != NO_ERROR) 
                 */
                /*
                 * retval = SNMP_ERR_COMMITFAILED; 
                 */
                /*
                 * } 
                 */
            }
            break;
        case IPMEDIANETADDRESS:
            temp_row = *arp_row;
            arp_row->dwAddr = *((int *) var_val);
            if (!create_flag) {
                if (SetIpNetEntry(arp_row) != NO_ERROR) {
                    arp_row->dwAddr = oldarp_row->dwAddr;
                    retval = SNMP_ERR_COMMITFAILED;
                } else {
                    temp_row.dwType = 2;
                    if (SetIpNetEntry(&temp_row) != NO_ERROR) {
                        snmp_log(LOG_ERR,
                                 "Failed in ACTION, while deleting old row \n");
                        retval = SNMP_ERR_COMMITFAILED;
                    }
                }
            }
            break;
        case IPMEDIATYPE:
            arp_row->dwType = *((int *) var_val);
            if (!create_flag) {
                if (SetIpNetEntry(arp_row) != NO_ERROR)
                    retval = SNMP_ERR_COMMITFAILED;
            }
            break;
        case IPMEDIAPHYSADDRESS:
            memcpy(arp_row->bPhysAddr, var_val, var_val_len);
            arp_row->dwPhysAddrLen = var_val_len;
            if (!create_flag) {
                if (SetIpNetEntry(arp_row) != NO_ERROR)
                    retval = SNMP_ERR_COMMITFAILED;
            }
            break;
        default:
            DEBUGMSGTL(("snmpd", "unknown sub-id %d in write_arp\n",
                        var + 1));
            retval = SNMP_ERR_NOTWRITABLE;
        }
        return retval;
    case UNDO:
        /*
         * Reverse the SET action and free resources 
         */
        if (oldarp_row != NULL) {
            /*
             * UNDO the changes done for existing entry. 
             */
            if (!create_flag) {
                if ((status = SetIpNetEntry(oldarp_row)) != NO_ERROR) {
                    snmp_log(LOG_ERR, "Error in case UNDO, status : %d\n",
                             status);
                    retval = SNMP_ERR_UNDOFAILED;
                }
            }

            if (oldarp_row->dwAddr != arp_row->dwAddr) {
                arp_row->dwType = 2;    /*If row was added/created delete that row */

                if ((status = SetIpNetEntry(arp_row)) != NO_ERROR) {
                    snmp_log(LOG_ERR,
                             "Error while deleting added row, status : %d\n",
                             status);
                    retval = SNMP_ERR_UNDOFAILED;
                }
            }
            free(oldarp_row);
            oldarp_row = NULL;
            free(arp_row);
            arp_row = NULL;
            return retval;
        }
        break;
    case COMMIT:
        /*
         * if new entry and physical address specified, create new entry 
         */
        if (create_flag) {
            if (arp_row->dwPhysAddrLen != 0) {
                if ((status = CreateIpNetEntry(arp_row)) != NO_ERROR) {
                    snmp_log(LOG_ERR,
                             "Inside COMMIT: CreateIpNetEntry failed, status %d\n",
                             status);
                    retval = SNMP_ERR_COMMITFAILED;
                }
            } else {
                /*
                 * For new entry, physical address must be set. 
                 */
                snmp_log(LOG_ERR,
                         "Can't create new entry without physical address\n");
                retval = SNMP_ERR_WRONGVALUE;
            }
            /*
             * unset the create_flag, so that CreateIpNetEntry called only once 
             */
            create_flag = 0;
        }

    case FREE:
        /*
         * Free any resources allocated 
         */
        free(oldarp_row);
        oldarp_row = NULL;
        free(arp_row);
        arp_row = NULL;
        break;
    }
    return retval;
}
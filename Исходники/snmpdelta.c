int
main(int argc, char *argv[])
{
    netsnmp_session session, *ss;
    netsnmp_pdu    *pdu, *response;
    netsnmp_variable_list *vars;
    int             arg;
    char           *gateway;

    int             count;
    struct varInfo *vip;
    u_int           value = 0;
    struct counter64 c64value;
    float           printvalue;
    time_t          last_time = 0;
    time_t          this_time;
    time_t          delta_time;
    int             sum;        /* what the heck is this for, its never used? */
    char            filename[128] = { 0 };
    struct timeval  tv;
    struct tm       tm;
    char            timestring[64] = { 0 }, valueStr[64] = {
    0}, maxStr[64] = {
    0};
    char            outstr[256] = { 0 }, peakStr[64] = {
    0};
    int             status;
    int             begin, end, last_end;
    int             print = 1;
    int             exit_code = 0;

    switch (arg = snmp_parse_args(argc, argv, &session, "C:", &optProc)) {
    case -2:
        exit(0);
    case -1:
        usage();
        exit(1);
    default:
        break;
    }

    gateway = session.peername;

    for (; optind < argc; optind++) {
	if (current_name >= MAX_ARGS) {
	    fprintf(stderr, "%s: Too many variables specified (max %d)\n",
	    	argv[optind], MAX_ARGS);
	    exit(1);
	}
        varinfo[current_name++].name = argv[optind];
    }

    if (current_name == 0) {
        usage();
        exit(1);
    }

    if (dosum) {
	if (current_name >= MAX_ARGS) {
	    fprintf(stderr, "Too many variables specified (max %d)\n",
	    	MAX_ARGS);
	    exit(1);
	}
        varinfo[current_name++].name = 0;
    }

    SOCK_STARTUP;

    /*
     * open an SNMP session 
     */
    ss = snmp_open(&session);
    if (ss == NULL) {
        /*
         * diagnose snmp_open errors with the input netsnmp_session pointer 
         */
        snmp_sess_perror("snmpdelta", &session);
        SOCK_CLEANUP;
        exit(1);
    }

    if (tableForm && timestamp) {
        printf("%s", gateway);
    }
    for (count = 0; count < current_name; count++) {
        vip = varinfo + count;
        if (vip->name) {
            vip->oidlen = MAX_OID_LEN;
            vip->info_oid = (oid *) malloc(sizeof(oid) * vip->oidlen);
            if (snmp_parse_oid(vip->name, vip->info_oid, &vip->oidlen) ==
                NULL) {
                snmp_perror(vip->name);
                SOCK_CLEANUP;
                exit(1);
            }
            sprint_descriptor(vip->descriptor, vip);
            if (tableForm)
                printf("\t%s", vip->descriptor);
        } else {
            vip->oidlen = 0;
            strcpy(vip->descriptor, SumFile);
        }
        vip->value = 0;
        zeroU64(&vip->c64value);
        vip->time = 0;
        vip->max = 0;
        if (peaks) {
            vip->peak_count = -1;
            vip->peak = 0;
            vip->peak_average = 0;
        }
    }

    wait_for_period(period);

    end = current_name;
    sum = 0;
    while (1) {
        pdu = snmp_pdu_create(SNMP_MSG_GET);

        if (deltat)
            snmp_add_null_var(pdu, sysUpTimeOid, sysUpTimeLen);

        if (end == current_name)
            count = 0;
        else
            count = end;
        begin = count;
        for (; count < current_name
             && count < begin + varbindsPerPacket - deltat; count++) {
            if (varinfo[count].oidlen)
                snmp_add_null_var(pdu, varinfo[count].info_oid,
                                  varinfo[count].oidlen);
        }
        last_end = end;
        end = count;

      retry:
        status = snmp_synch_response(ss, pdu, &response);
        if (status == STAT_SUCCESS) {
            if (response->errstat == SNMP_ERR_NOERROR) {
                if (timestamp) {
                    gettimeofday(&tv, (struct timezone *) 0);
                    memcpy(&tm, localtime((time_t *) & tv.tv_sec),
                           sizeof(tm));
                    if (((period % 60)
                         && (!peaks || ((period * peaks) % 60)))
                        || keepSeconds)
                        sprintf(timestring, " [%02d:%02d:%02d %d/%d]",
                                tm.tm_hour, tm.tm_min, tm.tm_sec,
                                tm.tm_mon + 1, tm.tm_mday);
                    else
                        sprintf(timestring, " [%02d:%02d %d/%d]",
                                tm.tm_hour, tm.tm_min,
                                tm.tm_mon + 1, tm.tm_mday);
                }

                vars = response->variables;
                if (deltat) {
                    if (!vars || !vars->val.integer) {
                        fprintf(stderr, "Missing variable in reply\n");
                        continue;
                    } else {
                        this_time = *(vars->val.integer);
                    }
                    vars = vars->next_variable;
                } else {
                    this_time = 1;
                }

                for (count = begin; count < end; count++) {
                    vip = varinfo + count;

                    if (vip->oidlen) {
                        if (!vars || !vars->val.integer) {
                            fprintf(stderr, "Missing variable in reply\n");
                            break;
                        }
                        vip->type = vars->type;
                        if (vars->type == ASN_COUNTER64) {
                            u64Subtract(vars->val.counter64,
                                        &vip->c64value, &c64value);
                            memcpy(&vip->c64value, vars->val.counter64,
                                   sizeof(struct counter64));
                        } else {
                            value = *(vars->val.integer) - vip->value;
                            vip->value = *(vars->val.integer);
                        }
                        vars = vars->next_variable;
                    } else {
                        value = sum;
                        sum = 0;
                    }
                    delta_time = this_time - vip->time;
                    if (delta_time <= 0)
                        delta_time = 100;
                    last_time = vip->time;
                    vip->time = this_time;
                    if (last_time == 0)
                        continue;

                    if (vip->oidlen && vip->type != ASN_COUNTER64) {
                        sum += value;
                    }

                    if (tableForm) {
                        if (count == begin) {
                            sprintf(outstr, "%s", timestring + 1);
                        } else {
                            outstr[0] = '\0';
                        }
                    } else {
                        sprintf(outstr, "%s %s", timestring,
                                vip->descriptor);
                    }

                    if (deltat || tableForm) {
                        if (vip->type == ASN_COUNTER64) {
                            fprintf(stderr,
                                    "time delta and table form not supported for counter64s\n");
                            exit(1);
                        } else {
                            printvalue =
                                ((float) value * 100) / delta_time;
                            if (tableForm)
                                sprintf(valueStr, "\t%.2f", printvalue);
                            else
                                sprintf(valueStr, " /sec: %.2f",
                                        printvalue);
                        }
                    } else {
                        printvalue = (float) value;
                        sprintf(valueStr, " /%d sec: ", period);
                        if (vip->type == ASN_COUNTER64)
                            printU64(valueStr + strlen(valueStr),
                                     &c64value);
                        else
                            sprintf(valueStr + strlen(valueStr), "%u",
                                    value);
                    }

                    if (!peaks) {
                        strcat(outstr, valueStr);
                    } else {
                        print = 0;
                        if (vip->peak_count == -1) {
                            if (wait_for_peak_start(period, peaks) == 0)
                                vip->peak_count = 0;
                        } else {
                            vip->peak_average += printvalue;
                            if (vip->peak < printvalue)
                                vip->peak = printvalue;
                            if (++vip->peak_count == peaks) {
                                if (deltat)
                                    sprintf(peakStr,
                                            " /sec: %.2f	(%d sec Peak: %.2f)",
                                            vip->peak_average /
                                            vip->peak_count, period,
                                            vip->peak);
                                else
                                    sprintf(peakStr,
                                            " /%d sec: %.0f	(%d sec Peak: %.0f)",
                                            period,
                                            vip->peak_average /
                                            vip->peak_count, period,
                                            vip->peak);
                                vip->peak_average = 0;
                                vip->peak = 0;
                                vip->peak_count = 0;
                                print = 1;
                                strcat(outstr, peakStr);
                            }
                        }
                    }

                    if (printmax) {
                        if (printvalue > vip->max) {
                            vip->max = printvalue;
                        }
                        if (deltat)
                            sprintf(maxStr, "	(Max: %.2f)", vip->max);
                        else
                            sprintf(maxStr, "	(Max: %.0f)", vip->max);
                        strcat(outstr, maxStr);
                    }

                    if (print) {
                        if (fileout) {
                            sprintf(filename, "%s-%s", gateway,
                                    vip->descriptor);
                            print_log(filename, outstr + 1);
                        } else {
                            if (tableForm)
                                printf("%s", outstr);
                            else
                                printf("%s\n", outstr + 1);
                            fflush(stdout);
                        }
                    }
                }
                if (end == last_end && tableForm)
                    printf("\n");
            } else {
                if (response->errstat == SNMP_ERR_TOOBIG) {
                    if (response->errindex <= varbindsPerPacket
                        && response->errindex > 0) {
                        varbindsPerPacket = response->errindex - 1;
                    } else {
                        if (varbindsPerPacket > 30)
                            varbindsPerPacket -= 5;
                        else
                            varbindsPerPacket--;
                    }
                    if (varbindsPerPacket <= 0) {
                        exit_code = 5;
                        break;
                    }
                    end = last_end;
                    continue;
                } else if (response->errindex != 0) {
                    fprintf(stderr, "Failed object: ");
                    for (count = 1, vars = response->variables;
                         vars && count != response->errindex;
                         vars = vars->next_variable, count++);
                    if (vars)
                        fprint_objid(stderr, vars->name,
                                     vars->name_length);
                    fprintf(stderr, "\n");
                    /*
                     * Don't exit when OIDs from file are not found on agent
                     * exit_code = 1;
                     * break;
                     */
                } else {
                    fprintf(stderr, "Error in packet: %s\n",
                            snmp_errstring(response->errstat));
                    exit_code = 1;
                    break;
                }

                /*
                 * retry if the errored variable was successfully removed 
                 */
                if (!netsnmp_ds_get_boolean(NETSNMP_DS_APPLICATION_ID, 
					    NETSNMP_DS_APP_DONT_FIX_PDUS)) {
                    pdu = snmp_fix_pdu(response, SNMP_MSG_GET);
                    snmp_free_pdu(response);
                    response = NULL;
                    if (pdu != NULL)
                        goto retry;
                }
            }

        } else if (status == STAT_TIMEOUT) {
            fprintf(stderr, "Timeout: No Response from %s\n", gateway);
            response = 0;
            exit_code = 1;
            break;
        } else {                /* status == STAT_ERROR */
            snmp_sess_perror("snmpdelta", ss);
            response = 0;
            exit_code = 1;
            break;
        }

        if (response)
            snmp_free_pdu(response);
        if (end == current_name) {
            wait_for_period(period);
        }
    }
    snmp_close(ss);
    SOCK_CLEANUP;
    return (exit_code);
}
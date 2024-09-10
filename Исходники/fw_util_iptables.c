/* Iterate over the configure firewall access chains and purge expired
 * firewall rules.
*/
void
check_firewall_rules(const fko_srv_options_t * const opts)
{
    char             exp_str[12]     = {0};
    char             rule_num_str[6] = {0};
    char            *ndx, *rn_start, *rn_end, *tmp_mark;

    int             i, res, rn_offset, rule_num, is_err;
    time_t          now, rule_exp, min_exp = 0;

    struct fw_chain *ch = opts->fw_config->chain;

    time(&now);

    /* Iterate over each chain and look for active rules to delete.
    */
    for(i=0; i < NUM_FWKNOP_ACCESS_TYPES; i++)
    {
        /* If there are no active rules or we have not yet
         * reached our expected next expire time, continue.
        */
        if(ch[i].active_rules == 0 || ch[i].next_expire > now)
            continue;

        zero_cmd_buffers();

        rn_offset = 0;

        /* There should be a rule to delete.  Get the current list of
         * rules for this chain and delete the ones that are expired.
        */
        snprintf(cmd_buf, CMD_BUFSIZE-1, "%s " IPT_LIST_RULES_ARGS,
            opts->fw_config->fw_command,
            ch[i].table,
            ch[i].to_chain
        );

        res = run_extcmd(cmd_buf, cmd_out, STANDARD_CMD_OUT_BUFSIZE, 0);
        chop_newline(cmd_out);

        log_msg(LOG_DEBUG, "check_firewall_rules() CMD: '%s' (res: %d, cmd_out: %s)",
            cmd_buf, res, cmd_out);

        if(!EXTCMD_IS_SUCCESS(res))
        {
            log_msg(LOG_ERR, "Error %i from cmd:'%s': %s", res, cmd_buf, cmd_out);
            continue;
        }

        log_msg(LOG_DEBUG, "RES=%i, CMD_BUF: %s\nRULES LIST: %s", res, cmd_buf, cmd_out);

        ndx = strstr(cmd_out, EXPIRE_COMMENT_PREFIX);
        if(ndx == NULL)
        {
            /* we did not find an expected rule.
            */
            log_msg(LOG_ERR,
                "Did not find expire comment in rules list %i", i);

            if (ch[i].active_rules > 0)
                ch[i].active_rules--;

            continue;
        }

        /* walk the list and process rules as needed.
        */
        while (ndx != NULL) {
            /* Jump forward and extract the timestamp
            */
            ndx += strlen(EXPIRE_COMMENT_PREFIX);

            /* remember this spot for when we look for the next
             * rule.
            */
            tmp_mark = ndx;

            strlcpy(exp_str, ndx, sizeof(exp_str));
            rule_exp = (time_t)atoll(exp_str);

            if(rule_exp <= now)
            {
                /* Backtrack and get the rule number and delete it.
                */
                rn_start = ndx;
                while(--rn_start > cmd_out)
                {
                    if(*rn_start == '\n')
                        break;
                }

                if(*rn_start != '\n')
                {
                    /* This should not happen. But if it does, complain,
                     * decrement the active rule value, and go on.
                    */
                    log_msg(LOG_ERR,
                        "Rule parse error while finding rule line start in chain %i", i);

                    if (ch[i].active_rules > 0)
                        ch[i].active_rules--;

                    break;
                }
                rn_start++;

                rn_end = strchr(rn_start, ' ');
                if(rn_end == NULL)
                {
                    /* This should not happen. But if it does, complain,
                     * decrement the active rule value, and go on.
                    */
                    log_msg(LOG_ERR,
                        "Rule parse error while finding rule number in chain %i", i);

                    if (ch[i].active_rules > 0)
                        ch[i].active_rules--;

                    break;
                }

                strlcpy(rule_num_str, rn_start, (rn_end - rn_start)+1);

                rule_num = strtol_wrapper(rule_num_str, rn_offset, RCHK_MAX_IPT_RULE_NUM,
                        NO_EXIT_UPON_ERR, &is_err);
                if(is_err != FKO_SUCCESS)
                {
                    log_msg(LOG_ERR,
                        "Rule parse error while finding rule number in chain %i", i);

                    if (ch[i].active_rules > 0)
                        ch[i].active_rules--;

                    break;
                }

                zero_cmd_buffers();

                snprintf(cmd_buf, CMD_BUFSIZE-1, "%s " IPT_DEL_RULE_ARGS,
                    opts->fw_config->fw_command,
                    ch[i].table,
                    ch[i].to_chain,
                    rule_num - rn_offset
                );

                res = run_extcmd(cmd_buf, err_buf, CMD_BUFSIZE, 0);
                chop_newline(err_buf);

                log_msg(LOG_DEBUG, "check_firewall_rules() CMD: '%s' (res: %d, err: %s)",
                    cmd_buf, res, err_buf);

                if(EXTCMD_IS_SUCCESS(res))
                {
                    log_msg(LOG_INFO, "Removed rule %s from %s with expire time of %u",
                        rule_num_str, ch[i].to_chain, rule_exp
                    );

                    rn_offset++;

                    if (ch[i].active_rules > 0)
                        ch[i].active_rules--;
                }
                else
                    log_msg(LOG_ERR, "Error %i from cmd:'%s': %s", res, cmd_buf, err_buf);

            }
            else
            {
                /* Track the minimum future rule expire time.
                */
                if(rule_exp > now)
                    min_exp = (min_exp < rule_exp) ? min_exp : rule_exp;
            }

            /* Push our tracking index forward beyond (just processed) _exp_
             * string so we can continue to the next rule in the list.
            */
            ndx = strstr(tmp_mark, EXPIRE_COMMENT_PREFIX);
        }

        /* Set the next pending expire time accordingly. 0 if there are no
         * more rules, or whatever the next expected (min_exp) time will be.
        */
        if(ch[i].active_rules < 1)
            ch[i].next_expire = 0;
        else if(min_exp)
            ch[i].next_expire = min_exp;
    }
}
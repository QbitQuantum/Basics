fm_s32 cfg_parser(fm_s8 *buffer, CFG_HANDLER handler, fm_cust_cfg *cfg)
{
    fm_s32 ret = 0;
    fm_s8 *p = buffer;
    fm_s8 *group_start = NULL;
    fm_s8 *key_start = NULL;
    fm_s8 *value_start = NULL;

    enum fm_cfg_parser_state state = FM_CFG_STAT_NONE;

    FMR_ASSERT(p);

    for (p = buffer; *p != '\0'; p++) {
        switch (state) {
        case FM_CFG_STAT_NONE: {
            if (*p == '[') {
                /* if we get char '[' in none state, it means a new group name start */
                state = FM_CFG_STAT_GROUP;
                group_start = p + 1;
            } else if (*p == COMMENT_CHAR) {
                /* if we get char '#' in none state, it means a new comment start */
                state = FM_CFG_STAT_COMMENT;
            } else if (!isspace(*p) && (*p != '\n') && (*p != '\r')) {
                /* if we get an nonspace char in none state, it means a new key start */
                state = FM_CFG_STAT_KEY;
                key_start = p;
            }

            break;
        }
        case FM_CFG_STAT_GROUP: {
            if (*p == ']') {
                /* if we get char ']' in group state, it means a group name complete */
                *p = '\0';
                /* FIX_ME */
                /* record group name */
                state = FM_CFG_STAT_NONE;
                trim_string(&group_start);
                /* WCN_DBG(FM_NTC|MAIN, "g=%s\n", group_start); */
            }

            break;
        }
        case FM_CFG_STAT_COMMENT: {
            if (*p == '\n') {
                /* if we get char '\n' in comment state, it means new line start */
                state = FM_CFG_STAT_NONE;
                group_start = p + 1;
            }

            break;
        }
        case FM_CFG_STAT_KEY: {
            if (*p == DELIMIT_CHAR) {
                /* if we get char '=' in key state, it means a key name complete */
                *p = '\0';
                /* FIX_ME */
                /* record key name */
                state = FM_CFG_STAT_VALUE;
                value_start = p + 1;
                trim_string(&key_start);
                /* WCN_DBG(FM_NTC|MAIN, "k=%s\n", key_start); */
            }

            break;
        }
        case FM_CFG_STAT_VALUE: {
            if (*p == '\n' || *p == '\r') {
                /* if we get char '\n' or '\r' in value state, it means a value complete */
                *p = '\0';
                /* record value */
                trim_string(&value_start);
                /* WCN_DBG(FM_NTC|MAIN, "v=%s\n", value_start); */

                if (handler) {
                    ret =
                        handler(group_start, key_start, value_start,
                                cfg);
                }

                state = FM_CFG_STAT_NONE;
            }

            break;
        }
        default:
            break;
        }
    }

    return ret;
}
/* detection functions */
int rule15125eval(void *p) {

    const uint8_t *cursor_normal = 0;
    SFSnortPacket *sp = (SFSnortPacket *) p;

    const uint8_t *end_of_payload;

    dpgroupcount *dpCount;

    DEBUG_WRAP(printf("rule15125eval enter\n"));

    if((sp == NULL) || (sp->stream_session_ptr == NULL))
        return RULE_NOMATCH;

    if(sp->payload == NULL)
        return RULE_NOMATCH;

    // flow:established, to_client;
    if(checkFlow(p, rule15125options[0]->option_u.flowFlags) <= 0)
        return RULE_NOMATCH;

    DEBUG_WRAP(printf("rule15125eval flow match\n"));

    // Since "group" is in the fast pattern matcher, we want to quickly make sure
    // that either \dpgroup or \dpendgroup is in the packet so we can drop out
    // before getting into the more intense detection algorithm.

    // content:"|5C|dp", nocase;
    if(contentMatch(p, rule15125options[1]->option_u.content, &cursor_normal) > 0) {
        // content:"group", depth 8, nocase, relative;
        if(contentMatch(p, rule15125options[2]->option_u.content, &cursor_normal) <= 0)
            return RULE_NOMATCH;
    }

    // Get-store-initialize session data
    dpCount = (dpgroupcount *)getRuleData(sp, (uint32_t)rule15125.info.sigID);

    if(!dpCount) {
        dpCount = (dpgroupcount *)allocRuleData(sizeof(dpgroupcount));
        if (dpCount == NULL)
            return RULE_NOMATCH;

        if(storeRuleData(sp, dpCount, rule15125.info.sigID, &freeRuleData) < 0)
        {
            freeRuleData(dpCount);
            return RULE_NOMATCH;
        }

        dpCount->groupTally = 0;
    }

    DEBUG_WRAP(printf("rule15125eval dpCount=0x%p\n", (void*)dpCount));

    // Reset cursor to beginning of payload
    if(getBuffer(sp, CONTENT_BUF_NORMALIZED, &cursor_normal, &end_of_payload) <= 0)
        return RULE_NOMATCH;

    // Main matching loop for "|5C|d"
    while(contentMatch(p, rule15125options[5]->option_u.content, &cursor_normal) > 0) {

        if(cursor_normal + 2 >= end_of_payload)
            return RULE_NOMATCH;

        // If entering a /do statement, reset counter
        if(*cursor_normal == 'o') {

            if(!isalnum(*(cursor_normal+1))) {
                dpCount->groupTally = 0;
            }

            // Match on "pgroup" within 6 then increment count
        } else if(contentMatch(p, rule15125options[3]->option_u.content, &cursor_normal) > 0) {

            dpCount->groupTally++;

            // Match on "pendgroup" within 9 then decrement count; fire if count is ever negative
        } else if(contentMatch(p, rule15125options[4]->option_u.content, &cursor_normal) > 0) {

            dpCount->groupTally--;

            if(dpCount->groupTally < 0)
                return RULE_MATCH;

        }

        DEBUG_WRAP(printf("rule15125eval dpCount->groupTally=%d\n", dpCount->groupTally));
    }

    return RULE_NOMATCH;
}
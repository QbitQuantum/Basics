static int
ListDumpSchedule(register struct bc_dumpSchedule *adump, int alevel)
{
    register int i;
    register struct bc_dumpSchedule *child;

    /* sanity check for loops */
    if (alevel > 100) {
	printf("backup: recursing listing dump schedule\n");
	return -1;
    }

    /* move to appropriate indentation level */
    for (i = 0; i < alevel; i++)
	printf("    ");

    /* name is a pathname style name, determine trailing name and only print
     * it
     */

    printf("/%s ", tailCompPtr(adump->name));


    /* list expiration time */
    switch (adump->expType) {
    case BC_ABS_EXPDATE:
	/* absolute expiration date. Never expires if date is 0 */
	if (adump->expDate) {
            time_t t = adump->expDate;
	    printf("expires at %.24s", cTIME(&t));
	}
	break;

    case BC_REL_EXPDATE:
	{
	    struct ktime_date kt;

	    /* expiration date relative to the time that the dump is done */
	    LongTo_ktimeRelDate(adump->expDate, &kt);
	    printf(" expires in %s", RelDatetoString(&kt));
	}
	break;

    default:
	break;
    }
    printf("\n");
    for (child = adump->firstChild; child; child = child->nextSibling)
	ListDumpSchedule(child, alevel + 1);

    return 0;
}
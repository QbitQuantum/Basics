int
doconsult(struct monst *oracl)
{
    int umoney = money_cnt(invent);
    int u_pay, minor_cost = 50, major_cost = 500 + 50 * u.ulevel;
    int add_xpts;
    const char *qbuf;

    /* TODO: Do we want this? The purpose seems to be specifically to prevent
       repeating an Oracle donation. */
    action_completed();

    if (!oracl) {
        pline("There is no one here to consult.");
        return 0;
    } else if (!oracl->mpeaceful) {
        pline("%s is not in the mood for conversation (believe it or not...)", Monnam(oracl));
        return 0;
    } else if (!umoney) {
        pline("You have no money.  There's no free lunch in wireless... and in being an oracle!");
        return 0;
    }

    qbuf = msgprintf("\"Would you mind talking for a little bit?\" (%d %s)",
                     minor_cost, currency(minor_cost));
    switch (ynq(qbuf)) {
    default:
    case 'q':
        return 0;
    case 'y':
        if (umoney < minor_cost) {
            pline("You don't even have enough money for that! There's no free lunch in wireless... and in being an oracle!");
            return 0;
        }
        u_pay = minor_cost;
        break;
    case 'n':
        if (umoney <= minor_cost ||     /* don't even ask */
            (oracle_cnt == 1 || oracle_flg < 0))
            return 0;
        qbuf = msgprintf("\"Oh! You'd like to sit and talk for a _long_ while?\" (%d %s)",
                         major_cost, currency(major_cost));
        if (yn(qbuf) != 'y')
            return 0;
        u_pay = (umoney < major_cost ? umoney : major_cost);

        break;
    }

    money2mon(oracl, u_pay);
    add_xpts = 0;       /* first oracle of each type gives experience points */
    if (u_pay == minor_cost) {
        outrumor(1, BY_ORACLE);
        if (!u.uevent.minor_oracle)
            add_xpts = u_pay / (u.uevent.major_oracle ? 25 : 10);
        /* 5 pts if very 1st, or 2 pts if major already done */
        u.uevent.minor_oracle = TRUE;
    } else {
        boolean cheapskate = u_pay < major_cost;

        outoracle(cheapskate, TRUE);
        if (!cheapskate && !u.uevent.major_oracle)
            add_xpts = u_pay / (u.uevent.minor_oracle ? 25 : 10);
        /* ~100 pts if very 1st, ~40 pts if minor already done */
        u.uevent.major_oracle = TRUE;
        historic_event(FALSE, "received advice from The Oracle.");
        exercise(A_WIS, !cheapskate);
    }
    if (add_xpts) {
        more_experienced(add_xpts, u_pay / 50);
        newexplevel();
    }
    return 1;
}
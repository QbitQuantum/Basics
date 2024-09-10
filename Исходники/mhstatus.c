        /* set height of the status box */
        sz->cy = tm.tmHeight * data->nhstat_format;

        SelectObject(hdc, saveFont);
        ReleaseDC(hWnd, hdc);
    }
}
extern const char *hu_stat[];  /* defined in eat.c */
extern const char *enc_stat[]; /* define in botl.c */
void
FormatStatusString(char *text, int format)
{
    register char *nb;
    int hp, hpmax;
    int cap = near_capacity();

    Strcpy(text, plname);
    if ('a' <= text[0] && text[0] <= 'z')
        text[0] += 'A' - 'a';
    text[10] = 0;
    Sprintf(nb = eos(text), " the ");

    if (Upolyd) {
        char mbot[BUFSZ];
        int k = 0;

        Strcpy(mbot, mons[u.umonnum].mname);
        while (mbot[k] != 0) {
            if ((k == 0 || (k > 0 && mbot[k - 1] == ' ')) && 'a' <= mbot[k]
                && mbot[k] <= 'z')
                mbot[k] += 'A' - 'a';
            k++;
        }
        Sprintf(nb = eos(nb), mbot);
    } else
        Sprintf(nb = eos(nb), rank_of(u.ulevel, Role_switch, flags.female));

    if (format == NHSTAT_LINES_4)
        Sprintf(nb = eos(nb), "\r\n");

    if (ACURR(A_STR) > 18) {
        if (ACURR(A_STR) > STR18(100))
            Sprintf(nb = eos(nb), "St:%2d ", ACURR(A_STR) - 100);
        else if (ACURR(A_STR) < STR18(100))
            Sprintf(nb = eos(nb), "St:18/%02d ", ACURR(A_STR) - 18);
        else
            Sprintf(nb = eos(nb), "St:18/** ");
    } else
        Sprintf(nb = eos(nb), "St:%-1d ", ACURR(A_STR));
    Sprintf(nb = eos(nb), "Dx:%-1d Co:%-1d In:%-1d Wi:%-1d Ch:%-1d",
            ACURR(A_DEX), ACURR(A_CON), ACURR(A_INT), ACURR(A_WIS),
            ACURR(A_CHA));
    Sprintf(nb = eos(nb),
            (u.ualign.type == A_CHAOTIC)
                ? "  Chaotic"
                : (u.ualign.type == A_NEUTRAL) ? "  Neutral" : "  Lawful");
#ifdef SCORE_ON_BOTL
    if (flags.showscore)
        Sprintf(nb = eos(nb), " S:%ld", botl_score());
#endif
    if (format == NHSTAT_LINES_4 || format == NHSTAT_LINES_2)
        strcat(text, "\r\n");

    /* third line */
    hp = Upolyd ? u.mh : u.uhp;
    hpmax = Upolyd ? u.mhmax : u.uhpmax;

    if (hp < 0)
        hp = 0;
    (void) describe_level(nb = eos(nb));
    Sprintf(nb = eos(nb), "%c:%-2ld HP:%d(%d) Pw:%d(%d) AC:%-2d",
            showsyms[COIN_CLASS + SYM_OFF_O], money_cnt(invent), hp, hpmax,
            u.uen, u.uenmax, u.uac);

    if (Upolyd)
        Sprintf(nb = eos(nb), " HD:%d", mons[u.umonnum].mlevel);
    else if (flags.showexp)
        Sprintf(nb = eos(nb), " Xp:%u/%-1ld", u.ulevel, u.uexp);
    else
        Sprintf(nb = eos(nb), " Exp:%u", u.ulevel);
    if (format == NHSTAT_LINES_4)
        strcat(text, "\r\n");
    else
        strcat(text, " ");

    /* forth line */
    if (flags.time)
        Sprintf(nb = eos(nb), "T:%ld ", moves);

    if (strcmp(hu_stat[u.uhs], "        ")) {
        Strcat(text, hu_stat[u.uhs]);
        Sprintf(nb = eos(nb), " ");
    }
    if (Confusion)
        Sprintf(nb = eos(nb), "Conf");
    if (Sick) {
        if (u.usick_type & SICK_VOMITABLE)
            Sprintf(nb = eos(nb), " FoodPois");
        if (u.usick_type & SICK_NONVOMITABLE)
            Sprintf(nb = eos(nb), " Ill");
    }
    if (Blind)
        Sprintf(nb = eos(nb), " Blind");
    if (Stunned)
        Sprintf(nb = eos(nb), " Stun");
    if (Hallucination)
        Sprintf(nb = eos(nb), " Hallu");
    if (Slimed)
        Sprintf(nb = eos(nb), " Slime");
    if (cap > UNENCUMBERED)
        Sprintf(nb = eos(nb), " %s", enc_stat[cap]);
}
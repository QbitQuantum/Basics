int
read_s3hypseg_line(char *line, seg_hyp_line_t * seg_hyp_line, lm_t * lm,
                   dict_t * dict)
{
    char *p, str[128];
    conf_srch_hyp_t *hyp_word, *tail, *g, *h;
    int sum, t, i;
    s3wid_t wid;

    p = line;

    if (!get_word(&p, str)) {
        printf("failed to read sequence number in the line: %s\n", line);
        return HYPSEG_FAILURE;
    }

    strcpy(seg_hyp_line->seq, str);

    if (!get_word(&p, str) || strcmp(str, "S"))
        E_FATAL("failed to read S in the line: %s\n", line);

    get_word(&p, str);

    if (!get_word(&p, str) || strcmp(str, "T"))
        E_FATAL("failed to read T in the line: %s\n", line);

    if (!get_word(&p, str))
        E_FATAL("failed to read ascr+lscr in the line: %s\n", line);

    sum = atoi(str);

    if (!get_word(&p, str) || strcmp(str, "A"))
        E_FATAL("failed to read A in the line: %s\n", line);

    if (!get_word(&p, str))
        E_FATAL("failed to read ascr in the line: %s\n", line);

    seg_hyp_line->ascr = atoi(str);

    if (!get_word(&p, str) || strcmp(str, "L"))
        E_FATAL("failed to read L in the line: %s\n", line);

    if (!get_word(&p, str))
        E_FATAL("failed to read lscr in the line: %s\n", line);

    seg_hyp_line->lscr = atoi(str);

#if 0
    if (!get_word(&p, str) || strcmp(str, "0")) {
        E_FATAL("failed to find 0 in the line: %s\n", line);

    }
#endif

    if (seg_hyp_line->ascr + seg_hyp_line->lscr != sum) {
        E_FATAL("the sum of ascr and lscr %d is wrong (%d): %s\n",
                seg_hyp_line->ascr + seg_hyp_line->lscr, sum, line);
    }

    seg_hyp_line->wordlist = NULL;
    seg_hyp_line->wordno = 0;
    seg_hyp_line->nfr = 0;
    seg_hyp_line->cscore = WORST_CONFIDENCE_SCORE;
    tail = NULL;

    while (1) {
        if (!get_word(&p, str))
            E_FATAL("failed to read sf or nfr in the line: %s\n", line);

        t = atoi(str);

        if (!get_word(&p, str)) {
            seg_hyp_line->nfr = t;
            break;
        }

        if ((hyp_word =
             (conf_srch_hyp_t *) ckd_calloc(1,
                                            sizeof(conf_srch_hyp_t))) ==
            NULL
            || (hyp_word->sh.word =
                (char *) ckd_calloc(1024, sizeof(char))) == NULL) {
            E_FATAL("fail to allocate memory\n");
        }

        hyp_word->sh.sf = t;
        hyp_word->sh.ascr = atoi(str);
        hyp_word->next = NULL;

        if (!get_word(&p, str))
            E_FATAL("failed to read lscr in the line: %s\n", line);

        hyp_word->sh.lscr = atoi(str);

        if (!get_word(&p, str))
            E_FATAL("failed to read word in the line: %s\n", line);

        strcpy(hyp_word->sh.word, str);
        for (i = strlen(str) - 1; i >= 0; i--)
            if (str[i] == '(')
                break;
        if (i >= 0)
            str[i] = '\0';


        if (dict) {
            wid = dict_wordid(dict, str);
            if (wid == BAD_S3WID) {
                E_FATAL("String %s doesn't exists in the dictionary\n",
                        str);
            }

            hyp_word->sh.id = wid;
        }

        hyp_word->compound = 0;
        hyp_word->matchtype = 0;

        seg_hyp_line->wordno++;
        if (seg_hyp_line->wordlist == NULL)
            seg_hyp_line->wordlist = hyp_word;
        else
            tail->next = hyp_word;
        tail = hyp_word;
    }


    if (seg_hyp_line->wordlist == NULL) {
        printf("word list is NULL\n");
        return HYPSEG_FAILURE;
    }

    g = seg_hyp_line->wordlist;
    for (h = g->next; h; h = h->next) {
        g->sh.ef = h->sh.sf - 1;
        g = h;
    }
    g->sh.ef = seg_hyp_line->nfr;

    sum = 0;
    for (h = seg_hyp_line->wordlist; h; h = h->next)
        sum += h->sh.ascr;
    if (sum != seg_hyp_line->ascr) {
        E_FATAL
            ("the ascr of words is not equal to the ascr of utt: %s (sum %d != tot %d). \n",
             line, sum, seg_hyp_line->ascr);
    }

    sum = 0;
    for (h = seg_hyp_line->wordlist; h; h = h->next)
        sum += h->sh.lscr;

    if (sum != seg_hyp_line->lscr)
        E_WARN
            ("the lscr of words is not equal to the lscr of utt: %s %d %d\n",
             seg_hyp_line->seq, sum, seg_hyp_line->lscr);

    for (h = seg_hyp_line->wordlist; h; h = h->next) {
        if (h->sh.ef < h->sh.sf) {
            E_FATAL("word %s ef (%d) <= sf (%d)in the line: %s\n",
                    h->sh.word, h->sh.ef, h->sh.sf, line);
        }
    }

    return HYPSEG_SUCCESS;
}
//      How to do a correlate-style CLASSIFY on some text.
//
int crm_expr_correlate_classify(CSL_CELL *csl, ARGPARSE_BLOCK *apb,
        VHT_CELL **vht,
        CSL_CELL *tdw,
        char *txtptr, int txtstart, int txtlen)
{
    //      classify the sparse spectrum of this input window
    //      as belonging to a particular type.
    //
    //       This code should look very familiar- it's cribbed from
    //       the code for LEARN
    //
    int i, j, k;
    char ptext[MAX_PATTERN]; //  the regex pattern
    int plen;
    //  the hash file names
    char htext[MAX_PATTERN + MAX_CLASSIFIERS * MAX_FILE_NAME_LEN];
    int htext_maxlen = MAX_PATTERN + MAX_CLASSIFIERS * MAX_FILE_NAME_LEN;
    int hlen;
    //  the match statistics variable
    char stext[MAX_PATTERN + MAX_CLASSIFIERS * (MAX_FILE_NAME_LEN + 100)];
    int stext_maxlen = MAX_PATTERN + MAX_CLASSIFIERS * (MAX_FILE_NAME_LEN + 100);
    int slen;
    char svrbl[MAX_PATTERN]; //  the match statistics text buffer
    int svlen;
    int fnameoffset;
    char fname[MAX_FILE_NAME_LEN];
    int eflags;
    int cflags;

    struct stat statbuf;    //  for statting the hash file
    //regex_t regcb;

    unsigned int fcounts[MAX_CLASSIFIERS]; // total counts for feature normalize

    double cpcorr[MAX_CLASSIFIERS];         // corpus correction factors
    int64_t linear_hits[MAX_CLASSIFIERS];   // actual hits per classifier
    int64_t square_hits[MAX_CLASSIFIERS];   // square of runlenths of match
    int64_t cube_hits[MAX_CLASSIFIERS];     // cube of runlength matches
    int64_t quad_hits[MAX_CLASSIFIERS];     // quad of runlength matches
    int incr_hits[MAX_CLASSIFIERS];         // 1+2+3... hits per classifier

    int64_t total_linear_hits; // actual total linear hits for all classifiers
    int64_t total_square_hits; // actual total square hits for all classifiers
    int64_t total_cube_hits;   // actual total cube hits for all classifiers
    int64_t total_quad_hits;   // actual total cube hits for all classifiers
    int64_t total_features;    // total number of characters in the system

    hitcount_t totalhits[MAX_CLASSIFIERS];
    double tprob;       //  total probability in the "success" domain.

    int textlen;  //  text length  - rougly corresponds to
    //  information content of the text to classify

    double ptc[MAX_CLASSIFIERS]; // current running probability of this class
    double renorm = 0.0;

    char *hashes[MAX_CLASSIFIERS];
    int hashlens[MAX_CLASSIFIERS];
    char *hashname[MAX_CLASSIFIERS];
    int succhash;
    int vbar_seen;     // did we see '|' in classify's args?
    int maxhash;
    int fnstart, fnlen;
    int fn_start_here;
    int textoffset;
    int bestseen;
    int thistotal;

    if (internal_trace)
        fprintf(stderr, "executing a CLASSIFY\n");

    //          we use the main line txtptr, txtstart, and txtlen now,
    //          so we don't need to extract anything from the b1start stuff.

    //           extract the hash file names
    hlen = crm_get_pgm_arg(htext, htext_maxlen, apb->p1start, apb->p1len);
    hlen = crm_nexpandvar(htext, hlen, htext_maxlen, vht, tdw);

    //           extract the "this is a word" regex
    //
    plen = crm_get_pgm_arg(ptext, MAX_PATTERN, apb->s1start, apb->s1len);
    plen = crm_nexpandvar(ptext, plen, MAX_PATTERN, vht, tdw);

    //            extract the optional "match statistics" variable
    //
    svlen = crm_get_pgm_arg(svrbl, MAX_PATTERN, apb->p2start, apb->p2len);
    svlen = crm_nexpandvar(svrbl, svlen, MAX_PATTERN, vht, tdw);
    {
        int vstart, vlen;
        if (crm_nextword(svrbl, svlen, 0, &vstart, &vlen))
        {
            crm_memmove(svrbl, &svrbl[vstart], vlen);
            svlen = vlen;
            svrbl[vlen] = 0;
        }
        else
        {
            svlen = 0;
            svrbl[0] = 0;
        }
    }

    //     status variable's text (used for output stats)
    //
    stext[0] = 0;
    slen = 0;

    //            set our flags, if needed.  The defaults are
    //            "case"
    cflags = REG_EXTENDED;
    eflags = 0;

    if (apb->sflags & CRM_NOCASE)
    {
        if (user_trace)
            fprintf(stderr, " setting NOCASE for tokenization\n");
        cflags += REG_ICASE;
        eflags = 1;
    }


    //       Now, the loop to open the files.
    bestseen = 0;
    thistotal = 0;

    //      initialize our arrays for N .css files
    for (i = 0; i < MAX_CLASSIFIERS; i++)
    {
        fcounts[i] = 0;       // check later to prevent a divide-by-zero
                              // error on empty .css file
        cpcorr[i] = 0.0;      // corpus correction factors
        linear_hits[i] = 0;   // linear hits
        square_hits[i] = 0;   // square of the runlength
        cube_hits[i] = 0;     // cube of the runlength
        quad_hits[i] = 0;     // quad of the runlength
        incr_hits[i] = 0;     // 1+2+3... hits hits
        totalhits[i] = 0;     // absolute hit counts
        ptc[i] = 0.5;         // priori probability
    }

    //

    vbar_seen = 0;
    maxhash = 0;
    succhash = 0;
    fnameoffset = 0;

    //    now, get the file names and mmap each file
    //     get the file name (grody and non-8-bit-safe, but doesn't matter
    //     because the result is used for open() and nothing else.
    //   GROT GROT GROT  this isn't NULL-clean on filenames.  But then
    //    again, stdio.h itself isn't NULL-clean on filenames.
    if (user_trace)
        fprintf(stderr, "Classify list: -%.*s-\n", hlen, htext);
    fn_start_here = 0;
    fnlen = 1;
    while (fnlen > 0 && ((maxhash < MAX_CLASSIFIERS - 1)))
    {
        if (crm_nextword(htext,
                         hlen, fn_start_here,
                         &fnstart, &fnlen)
           && fnlen > 0)
        {
            strncpy(fname, &htext[fnstart], fnlen);
            fname[fnlen] = 0;
            //      fprintf(stderr, "fname is '%s' len %d\n", fname, fnlen);
            fn_start_here = fnstart + fnlen + 1;
            if (user_trace)
            {
                fprintf(stderr, "Classifying with file -%s- succhash=%d, maxhash=%d\n",
                        fname, succhash, maxhash);
            }
            if (fname[0] == '|' && fname[1] == 0)
            {
                if (vbar_seen)
                {
                    nonfatalerror("Only one '|' allowed in a CLASSIFY.\n",
                                  "We'll ignore it for now.");
                }
                else
                {
                    succhash = maxhash;
                }
                vbar_seen++;
            }
            else
            {
                //  be sure the file exists
                //             stat the file to get it's length
                k = stat(fname, &statbuf);
                //             quick check- does the file even exist?
                if (k != 0)
                {
                    nonfatalerror("Nonexistent Classify table named: ",
                                  fname);
                }
                else
                {
                    // [i_a] check hashes[] range BEFORE adding another one!
                    if (maxhash >= MAX_CLASSIFIERS)
                    {
                        nonfatalerror("Too many classifier files.",
                                      "Some may have been disregarded");
                    }
                    else
                    {
                        //  file exists - do the mmap
                        //
                        hashlens[maxhash] = statbuf.st_size;
                        // [i_a] hashlens[maxhash] must be fixed for the header size!
                        hashes[maxhash] = crm_mmap_file(fname,
                                                        0,
                                                        hashlens[maxhash],
                                                        PROT_READ,
                                                        MAP_SHARED,
                                                        CRM_MADV_RANDOM,
                                                        &hashlens[maxhash]);
                        if (hashes[maxhash] == MAP_FAILED)
                        {
                            nonfatalerror("Couldn't memory-map the table file",
                                          fname);
                        }
                        else
                        {
                            //
                            //     Check to see if this file is the right version
                            //
                            //     FIXME : for now, there's no version number
                            //     associated with a .correllation file
                            // int fev;
                            // if (0)
                            //(hashes[maxhash][0].hash != 1 ||
                            //  hashes[maxhash][0].key  != 0)
                            //{
                            //  fev = fatalerror ("The .css file is the wrong version!  Filename is: ",
                            //                   fname);
                            //  return (fev);
                            //}

                            //
                            //     save the name for later...
                            //
                            hashname[maxhash] = (char *)calloc((fnlen + 10), sizeof(hashname[maxhash][0]));
                            if (!hashname[maxhash])
                            {
                                untrappableerror(
                                    "Couldn't alloc hashname[maxhash]\n", "We need that part later, so we're stuck.  Sorry.");
                            }
                            else
                            {
                                strncpy(hashname[maxhash], fname, fnlen);
                                hashname[maxhash][fnlen] = 0;
                            }
                            maxhash++;
                        }
                    }
                }
            }
        }
    }

    //
    //    If there is no '|', then all files are "success" files.
    if (succhash == 0)
        succhash = maxhash;

    //    a CLASSIFY with no arguments is always a "success".
    if (maxhash == 0)
        return 0;

    if (user_trace)
    {
        fprintf(stderr, "Running with %d files for success out of %d files\n",
                succhash, maxhash);
    }

    // sanity checks...  Uncomment for super-strict CLASSIFY.
    //
    //    do we have at least 1 valid .css files?
    if (maxhash == 0)
    {
        return nonfatalerror("Couldn't open at least 1 .css file for classify().", "");
    }

#if 0
    //    do we have at least 1 valid .css file at both sides of '|'?
    if (!vbar_seen || succhash <= 0 || (maxhash <= succhash))
    {
        return nonfatalerror("Couldn't open at least 1 .css file per SUCC | FAIL category "
                             "for classify().\n", "Hope you know what are you doing.");
    }
#endif

    //
    //   now all of the files are mmapped into memory,
    //   and we can do the correlations and add up matches.
    i = 0;
    j = 0;
    k = 0;
    thistotal = 0;

    //     put in the ptr/start/len values we got from the outside caller
    textoffset = txtstart;
    textlen = txtlen;

    //
    //    We keep track of the hits in these categories
    //  linear_hits[MAX_CLASSIFIERS];  // actual hits per classifier
    //  square_hits[MAX_CLASSIFIERS];  // square of runlenths of match
    //  incr_hits[MAX_CLASSIFIERS];  // 1+2+3... hits per classifier
    //

    //   Now we do the actual correllation.
    //   for each file...
    //    slide the incoming text (mdw->filetext[textofset])
    //     across the corpus text (hashes[] from 0 to hashlens[])
    //      and count the bytes that are the same, the runlengths,
    //       etc.

    for (k = 0; k < maxhash; k++)
    {
        int it;  // it is the start index into the tested text
        int ik;  // ik is the start index into the known corpus text
        int ilm; // ilm is the "local" matches (N in a row)

        //    for each possible displacement of the known  (ik) text...
        for (ik = 0;
             ik < hashlens[k];
             ik++)
        {
            int itmax;

            ilm = 0;
            itmax = textlen;
            if (ik + itmax > hashlens[k])
                itmax = hashlens[k] - ik;
            // for each position in the test (it) text...
            for (it = 0;
                 it < itmax;
                 it++)
            {
                //   do the characters in this position match?
                if (hashes[k][ik + it] == txtptr[textoffset + it])
                {
                    // yes they matched
                    linear_hits[k]++;
                    ilm++;
                    square_hits[k] = square_hits[k] + (ilm * ilm);
                    cube_hits[k] = cube_hits[k] + (ilm * ilm * ilm);
                    quad_hits[k] = quad_hits[k] + (ilm * ilm * ilm * ilm);
                }
                else
                {
                    //   nope, they didn't match.
                    //   So, we do the end-of-runlength stuff:
                    ilm = 0;
                }
                if (0)
                    fprintf(stderr, "ik: %d  it: %d  chars %c %c lin: %lld  sqr: %lld cube: %lld quad: %lld\n",
                            ik, it,
                            hashes[k][ik + it],
                            txtptr[textoffset + it],
                            (long long int)linear_hits[k],
                            (long long int)square_hits[k],
                            (long long int)cube_hits[k],
                            (long long int)quad_hits[k]);
            }
        }
    }


    //   Now we have the total hits for each text corpus.  We can then
    //  turn that into a vague probability measure, and then renormalize
    //  that to get probabilities.
    //
    //   But first, let's reflect on what we've got here.  We our test
    //   text, and we have a corpus which is "nominally correllated",
    //   and another corpus that is nominally uncorrellated.
    //
    //   The uncorrellated text will have an average match rate of 1/256'th
    //   in the linear domain (well, for random bytes; english text will match
    //   a lot more often, due to the fact that ASCII only uses the low 7
    //   bits, most text is written in lower case, Zipf's law, etc.
    //
    //   We can calculate a predicted total on a per-character basis for all
    //   of the corpi, then use that as an average expectation.

    //    Calculate total hits
    total_linear_hits = 0;
    total_square_hits = 0;
    total_cube_hits = 0;
    total_quad_hits = 0;
    total_features = 0;
    for (k = 0; k < maxhash; k++)
    {
        total_linear_hits += linear_hits[k];
        total_square_hits += square_hits[k];
        total_cube_hits += cube_hits[k];
        total_quad_hits += quad_hits[k];
        total_features += hashlens[k];
    }


    for (k = 0; k < maxhash; k++)
    {
        if (hashlens[k] > 0
           && total_features > 0)
        {
            //     Note that we don't normalize the probabilities yet- we do
            //     that down below.
            //
            //     .00397 is not a magic number - it's the random coincidence
            //     rate for 1 chance in 256, with run-length-squared boost.
            //     .00806 is the random coincidence rate for 7-bit characters.
            //
            //ptc[k] = ((0.0+square_hits[k] - (.00397 * hashlens[k] )));
            //      ptc[k] = ((0.0+square_hits[k] - (.00806 * hashlens[k] )))
            //        / hashlens[k];

            //      ptc[k] = (0.0+square_hits[k] ) / hashlens[k];
            //      ptc[k] = (0.0+ quad_hits[k] ) / hashlens[k];
            ptc[k] = (0.0 + quad_hits[k]) / linear_hits[k];

            if (ptc[k] < 0)
                ptc[k] = 10 * DBL_MIN;
        }
        else
        {
            ptc[k] = 0.5;
        }
    }


    //    ptc[k] = (sqrt (0.0 + square_hits[k])-linear_hits[k] ) / hashlens[k] ;
    //    ptc[k] =  (0.0 + square_hits[k] - linear_hits[k] ) ;
    //    ptc[k] =  ((0.0 + square_hits[k]) / hashlens[k]) ;
    //    ptc[k] = sqrt ((0.0 + square_hits[k]) / hashlens[k]) ;
    //    ptc[k] = ((0.0 + linear_hits[k]) / hashlens[k]) ;


    //   calculate renormalizer (the Bayesian formula's denomenator)
    renorm = 0.0;

    //   now calculate the per-ptc numerators
    for (k = 0; k < maxhash; k++)
        renorm = renorm + (ptc[k]);

    //   check for a zero normalizer
    if (renorm == 0)
        renorm = 1.0;

    //  and renormalize
    for (k = 0; k < maxhash; k++)
        ptc[k] = ptc[k] / renorm;

    //   if we have underflow (any probability == 0.0 ) then
    //   bump the probability back up to 10^-308, or
    //   whatever a small multiple of the minimum double
    //   precision value is on the current platform.
    //
    for (k = 0; k < maxhash; k++)
    {
        if (ptc[k] < 10 * DBL_MIN)
            ptc[k] = 10 * DBL_MIN;
    }

    if (internal_trace)
    {
        for (k = 0; k < maxhash; k++)
        {
            fprintf(stderr,
                    " file: %d  linear: %lld  square: %lld  RMS: %6.4e  ptc[%d] = %6.4e\n",
                    k, (long long int)linear_hits[k], (long long int)square_hits[k],
                    sqrt(0.0 + square_hits[k]), k, ptc[k]);
        }
    }

    //  end of repeat-the-regex loop


    //  cleanup time!
    //  remember to let go of the fd's and mmaps
    for (k = 0; k < maxhash; k++)
    {
        crm_munmap_file(hashes[k]);
    }

    if (user_trace)
    {
        for (k = 0; k < maxhash; k++)
            fprintf(stderr, "Probability of match for file %d: %f\n", k, ptc[k]);
    }
    //
    tprob = 0.0;
    for (k = 0; k < succhash; k++)
        tprob = tprob + ptc[k];
    //
    //      Do the calculations and format some output, which we may or may
    //      not use... but we need the calculated result anyway.
    //
    if (1 /* svlen > 0 */)
    {
        char buf[1024];
        double accumulator;
        double remainder;
        double overall_pR;
        int m;
        buf[0] = 0;
        accumulator = 10 * DBL_MIN;
        for (m = 0; m < succhash; m++)
        {
            accumulator += ptc[m];
        }
        remainder = 10 * DBL_MIN;
        for (m = succhash; m < maxhash; m++)
        {
            remainder += ptc[m];
        }
        overall_pR = log10(accumulator) - log10(remainder);

        //   note also that strcat _accumulates_ in stext.
        //  There would be a possible buffer overflow except that _we_ control
        //   what gets written here.  So it's no biggie.

        if (tprob > 0.5)
        {
            sprintf(buf, "CLASSIFY succeeds; (correlate) success probability: %6.4f  pR: %6.4f\n", tprob, overall_pR);
        }
        else
        {
            sprintf(buf, "CLASSIFY fails; (correlate) success probability: %6.4f  pR: %6.4f\n", tprob, overall_pR);
        }
        if (strlen(stext) + strlen(buf) <= stext_maxlen)
            strcat(stext, buf);

        //   find best single matching file
        //
        bestseen = 0;
        for (k = 0; k < maxhash; k++)
        {
            if (ptc[k] > ptc[bestseen])
            {
                bestseen = k;
            }
        }
        remainder = 10 * DBL_MIN;
        for (m = 0; m < maxhash; m++)
        {
            if (bestseen != m)
            {
                remainder += ptc[m];
            }
        }

        //   ... and format some output of best single matching file
        //
        snprintf(buf, WIDTHOF(buf), "Best match to file #%d (%s) "
                                    "prob: %6.4f  pR: %6.4f\n",
                 bestseen,
                 hashname[bestseen],
                 ptc[bestseen],
                 (log10(ptc[bestseen]) - log10(remainder)));
        buf[WIDTHOF(buf) - 1] = 0;
        if (strlen(stext) + strlen(buf) <= stext_maxlen)
            strcat(stext, buf);
        sprintf(buf, "Total features in input file: %d\n", hashlens[bestseen]);
        if (strlen(stext) + strlen(buf) <= stext_maxlen)
            strcat(stext, buf);

        //     Now do the per-file breakdowns:
        //
        for (k = 0; k < maxhash; k++)
        {
            int m;
            remainder = 10 * DBL_MIN;
            for (m = 0; m < maxhash; m++)
            {
                if (k != m)
                {
                    remainder += ptc[m];
                }
            }
            snprintf(buf, WIDTHOF(buf),
                     "#%d (%s):"
                     " features: %d, L1: %lld L2: %lld L3: %lld, L4: %lld prob: %3.2e, pR: %6.2f\n",
                     k,
                     hashname[k],
                     hashlens[k],
                     (long long int)linear_hits[k],
                     (long long int)square_hits[k],
                     (long long int)cube_hits[k],
                     (long long int)quad_hits[k],
                     ptc[k],
                     (log10(ptc[k]) - log10(remainder)));
            buf[WIDTHOF(buf) - 1] = 0;
            // strcat (stext, buf);
            if (strlen(stext) + strlen(buf) <= stext_maxlen)
                strcat(stext, buf);
        }
        // check here if we got enough room in stext to stuff everything
        // perhaps we'd better rise a nonfatalerror, instead of just
        // whining on stderr
        if (strcmp(&(stext[strlen(stext) - strlen(buf)]), buf) != 0)
        {
            nonfatalerror("WARNING: not enough room in the buffer to create "
                          "the statistics text.  Perhaps you could try bigger "
                          "values for MAX_CLASSIFIERS or MAX_FILE_NAME_LEN?",
                          " ");
        }
        if (svlen > 0)
        {
            crm_destructive_alter_nvariable(svrbl, svlen,                    stext, (int)strlen(stext), csl->calldepth);
        }
    }

    //
    //  Free the hashnames, to avoid a memory leak.
    //
    for (i = 0; i < maxhash; i++)
        free(hashname[i]);
    if (tprob <= 0.5)
    {
        if (user_trace)
            fprintf(stderr, "CLASSIFY was a FAIL, skipping forward.\n");
        //    and do what we do for a FAIL here
        CRM_ASSERT(csl->cstmt >= 0);
        CRM_ASSERT(csl->cstmt <= csl->nstmts);
#if defined(TOLERATE_FAIL_AND_OTHER_CASCADES)
        csl->next_stmt_due_to_fail = csl->mct[csl->cstmt]->fail_index;
#else
        csl->cstmt = csl->mct[csl->cstmt]->fail_index - 1;
#endif
        if (internal_trace)
        {
            fprintf(stderr, "CLASSIFY.CORRELATE is jumping to statement line: %d/%d\n", csl->mct[csl->cstmt]->fail_index, csl->nstmts);
        }
        CRM_ASSERT(csl->cstmt >= 0);
        CRM_ASSERT(csl->cstmt <= csl->nstmts);
        csl->aliusstk[csl->mct[csl->cstmt]->nest_level] = -1;
        return 0;
    }


    //
    //   all done... if we got here, we should just continue execution
    if (user_trace)
        fprintf(stderr, "CLASSIFY was a SUCCESS, continuing execution.\n");
// regcomp_failed:
    return 0;
}
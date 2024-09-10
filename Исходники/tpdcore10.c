static void prep_test_10_data(void)
   {int i;

/* set scalars */
    qs_r = 0.0L;
    qs_w = expl(1.0);
    qs_w = 2.0L;

/* set long double array */
    for (i = 0; i < N_FLOAT; i++)
        {qa_w[i] = POWL(qs_w, (long double) (i+1));
         qa_r[i] = 0.0L;};

    return;}
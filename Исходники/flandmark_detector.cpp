FLANDMARK_Model * flandmark_init(const char* filename)
{
    int *p_int = 0, tsize = -1, tmp_tsize = -1;
    unsigned char *p_uint8 = 0;

    FILE *fin;
    if ((fopen_s(&fin,filename, "rb")) != NULL)
    {
        printf("Error opening file %s\n", filename);
        return 0;
    }

    // allocate memory for FLANDMARK_Model
    FLANDMARK_Model * tst = (FLANDMARK_Model*)malloc(sizeof(FLANDMARK_Model));

    //int fscan_ret = -1;
    if (fscanf_s(fin, " %c ", &tst->data.options.M) < 1)
    {
        return 0;
    }

    if (fscanf_s(fin, " %d %d ", &tst->data.options.bw[0], &tst->data.options.bw[1]) < 2)
    {
        return 0;
    }

    if (fscanf_s(fin, " %d %d ", &tst->data.options.bw_margin[0], &tst->data.options.bw_margin[1]) < 2)
    {
        return 0;
    }

    if (fscanf_s(fin, " %d %d ", &tst->W_ROWS, &tst->W_COLS) < 2)
    {
        return 0;
    }

    if (fscanf_s(fin, " %d %d ", &tst->data.imSize[0], &tst->data.imSize[1]) < 2)
    {
        return 0;
    }

    int M = tst->data.options.M;

    tst->data.lbp = (FLANDMARK_LBP*)malloc(M*sizeof(FLANDMARK_LBP));
    for (int idx = 0; idx < M; ++idx)
    {
        if (fscanf_s(fin, " %d %d ", &tst->data.lbp[idx].WINS_ROWS, &tst->data.lbp[idx].WINS_COLS) < 2)
        {
            return 0;
        }
    }

    for (int idx = 0; idx < 3; ++idx)
    {
        if (fscanf_s(fin, " %d %d ", &tst->data.options.PSIG_ROWS[idx], &tst->data.options.PSIG_COLS[idx]) < 2)
        {
            return 0;
        }
    }

    // load model.W -----------------------------------------------------------
    tst->W = (double*)malloc(tst->W_ROWS * sizeof(double));
    if (fread(tst->W, tst->W_ROWS * sizeof(double), 1, fin) != 1)
    {
        printf( "Error reading file %s\n", filename);
        return 0;
    }

    // load model.data.mapTable -----------------------------------------------
    p_int = (int*)malloc(M*4*sizeof(int));
    tst->data.mapTable = (int*)malloc(M*4*sizeof(int));
    if (fread(p_int, M*4*sizeof(int), 1, fin) != 1)
    {
        printf( "Error reading file %s\n", filename);
        return 0;
    }
    for (int i = 0; i < M*4; ++i)
    {
        tst->data.mapTable[i] = p_int[i];
    }
    free(p_int);

    // load model.data.lbp ---------------------------------------------------
    for (int idx = 0; idx < M; ++idx)
    {
        // lbp{idx}.winSize
        p_int = (int*)malloc(2*sizeof(int));
        if (fread(p_int, 2*sizeof(int), 1, fin) != 1)
        {
            printf( "Error reading file %s\n", filename);
            return 0;
        }
        for (int i = 0; i < 2; ++i)
        {
            tst->data.lbp[idx].winSize[i] = p_int[i];
        }
        free(p_int);

        // lbp{idx}.hop
        p_uint8 = (unsigned char*)malloc(sizeof(unsigned char));
        if (fread(p_uint8, sizeof(unsigned char), 1, fin) != 1)
        {
            printf( "Error reading file %s\n", filename);
            return 0;
        }
        tst->data.lbp[idx].hop = p_uint8[0];
        free(p_uint8);

        // lbp{idx}.wins
        tsize = tst->data.lbp[idx].WINS_ROWS*tst->data.lbp[idx].WINS_COLS;
        tst->data.lbp[idx].wins = (uint32_t*)malloc(tsize * sizeof(uint32_t));
        if (fread(tst->data.lbp[idx].wins, tsize * sizeof(uint32_t), 1, fin) != 1)
        {
            printf( "Error reading file %s\n", filename);
            return 0;
            //exit(1);
        }
    }

    // load model.options.S --------------------------------------------------
    p_int = (int*)malloc(4*M*sizeof(int));
    tst->data.options.S = (int*)malloc(4*M*sizeof(int));
    if (fread(p_int, 4*M*sizeof(int), 1, fin) != 1)
    {
        printf( "Error reading file %s\n", filename);
        return 0;
        //exit(1);
    }
    for (int i = 0; i < 4*M; ++i)
    {
        tst->data.options.S[i] = p_int[i];
    }
    free(p_int);

    // load model.options.PsiG -----------------------------------------------
    FLANDMARK_PSIG * PsiGi = NULL;
    for (int psigs_idx = 0; psigs_idx < 3; ++psigs_idx)
    {
        tsize = tst->data.options.PSIG_ROWS[psigs_idx]*tst->data.options.PSIG_COLS[psigs_idx];

        switch (psigs_idx)
        {
        case 0:
            tst->data.options.PsiGS0 = (FLANDMARK_PSIG*)malloc(tsize*sizeof(FLANDMARK_PSIG));
            PsiGi = tst->data.options.PsiGS0;
            break;
        case 1:
            tst->data.options.PsiGS1 = (FLANDMARK_PSIG*)malloc(tsize*sizeof(FLANDMARK_PSIG));
            PsiGi = tst->data.options.PsiGS1;
            break;
        case 2:
            tst->data.options.PsiGS2 = (FLANDMARK_PSIG*)malloc(tsize*sizeof(FLANDMARK_PSIG));
            PsiGi = tst->data.options.PsiGS2;
            break;
        }

        for (int idx = 0; idx < tsize; ++idx)
        {
            // disp ROWS
            p_int = (int*)malloc(sizeof(int));
            if (fread(p_int, sizeof(int), 1, fin) != 1)
            {
                printf( "Error reading file %s\n", filename);
                return 0;
                //exit(1);
            }
            PsiGi[idx].ROWS = p_int[0];
            free(p_int);
            // disp COLS
            p_int = (int*)malloc(sizeof(int));
            if (fread(p_int, sizeof(int), 1, fin) != 1)
            {
                printf( "Error reading file %s\n", filename);
                return 0;
                //exit(1);
            }
            PsiGi[idx].COLS = p_int[0];
            free(p_int);
            // disp
            tmp_tsize = PsiGi[idx].ROWS*PsiGi[idx].COLS;
            PsiGi[idx].disp = (int*)malloc(tmp_tsize*sizeof(int));
            if (fread(PsiGi[idx].disp, tmp_tsize*sizeof(int), 1, fin) != 1)
            {
                printf( "Error reading file %s\n", filename);
                return 0;
                //exit(1);
            }
        }
    }

    fclose(fin);

    tst->normalizedImageFrame = (unsigned char*)calloc(tst->data.options.bw[0]*tst->data.options.bw[1], sizeof(unsigned char));

    tst->bb = (double*)calloc(4, sizeof(double));

    tst->sf = (float*)calloc(2, sizeof(float));

    return tst;
}
/**
 * Constructor that fills a coxph_data object with phenotype and genotype
 * data.
 *
 * @param phed Reference to a phedata object with phenotype data
 * @param gend Reference to a gendata object with genotype data
 * @param snpnum The number of the SNP in the genotype data object to
 * be added to the design matrix regdata::X. When set to a number < 0
 * no SNP data is added to the design matrix (e.g. when calculating
 * the null model).
 */
coxph_data::coxph_data(const phedata &phed, const gendata &gend,
                       const int snpnum)
{
    freq        = 0;
    gcount      = 0;
    nids        = gend.nids;
    masked_data = std::vector<bool>(nids, false);

    ngpreds = gend.ngpreds;
    if (snpnum >= 0)
    {
        ncov = phed.ncov + ngpreds;
    }
    else
    {
        ncov = phed.ncov;
    }

    if (phed.noutcomes != 2)
    {
        std::cerr << "coxph_data: number of outcomes should be 2 (now: "
                  << phed.noutcomes << ")\n";
        exit(1);
    }

    X.reinit(nids, (ncov + 1)); // Note: ncov takes ngpreds into
                                // account, see above!
    stime.reinit(nids, 1);
    sstat.reinit(nids, 1);
    weights.reinit(nids, 1);
    offset.reinit(nids, 1);
    strata.reinit(nids, 1);
    order.reinit(nids, 1);

    for (int i = 0; i < nids; i++)
    {
        stime[i] = (phed.Y).get(i, 0);
        sstat[i] = static_cast<int>((phed.Y).get(i, 1));
        if (sstat[i] != 1 && sstat[i] != 0)
        {
            std::cerr << "coxph_data: status not 0/1 "
                      <<"(correct order: id, fuptime, status ...)"
                      << endl;
            exit(1);
        }
    }

    // Add a column with a constant (=1) to the X matrix (the mean)
    for (int i = 0; i < nids; i++)
    {
        X.put(1., i, 0);
    }

    // Insert the covariate data into X (note we use phed.ncov and not
    // ncov, which includes ngpreds is not computing the null model!)
    for (int j = 1; j <= phed.ncov; j++)
    {
        for (int i = 0; i < nids; i++)
        {
            X.put((phed.X).get(i, j - 1), i, j);
        }
    }

    // Insert the genotype data into X
    if (snpnum > 0)
    {
        for (int j = 0; j < ngpreds; j++)
        {
            double *snpdata = new double[nids];
            gend.get_var(snpnum * ngpreds + j, snpdata);
            for (int i = 0; i < nids; i++)
            {
                X.put(snpdata[i], i, (ncov - ngpreds + j));
            }
            delete[] snpdata;
        }
    }

    for (int i = 0; i < nids; i++)
    {
        weights[i] = 1.0;
        offset[i] = 0.0;
        strata[i] = 0;
    }

    // sort by time
    double *tmptime = new double[nids];
    int *passed_sorted = new int[nids];
    std::fill(passed_sorted, passed_sorted + nids, 0);


    for (int i = 0; i < nids; i++)
    {
        tmptime[i] = stime[i];
    }

    qsort(tmptime, nids, sizeof(double), cmpfun);

    for (int i = 0; i < nids; i++)
    {
        int passed = 0;
        for (int j = 0; j < nids; j++)
        {
            if (tmptime[j] == stime[i])
            {
                if (!passed_sorted[j])
                {
                    order[i] = j;
                    passed_sorted[j] = 1;
                    passed = 1;
                    break;
                }
            }
        }
        if (passed != 1)
        {
            std::cerr << "cannot recover element " << i << "\n";
            exit(1);
        }
    }

    stime   = reorder(stime, order);
    sstat   = reorder(sstat, order);
    weights = reorder(weights, order);
    strata  = reorder(strata, order);
    offset  = reorder(offset, order);
    X       = reorder(X, order);

    // The coxfit2() function expects data in column major order.
    X = transpose(X);

    // X.print();
    // offset.print();
    // weights.print();
    // stime.print();
    // sstat.print();

    delete[] tmptime;
    delete[] passed_sorted;
}
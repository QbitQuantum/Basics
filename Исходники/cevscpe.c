static sco_data *getScoData(scicos_block * block)
{
    sco_data *sco = (sco_data *) * (block->work);
    int i, j;

    int nclk = block->nipar - 6;

    if (sco == NULL)
    {
        /*
         * Data allocation
         */

        sco = (sco_data *) MALLOC(sizeof(sco_data));
        if (sco == NULL)
        {
            goto error_handler_sco;
        }

        sco->internal.numberOfPoints = (int *)CALLOC(nclk, sizeof(int));
        if (sco->internal.numberOfPoints == NULL)
        {
            goto error_handler_numberOfPoints;
        }
        sco->internal.maxNumberOfPoints = (int *)MALLOC(nclk * sizeof(int));
        if (sco->internal.numberOfPoints == NULL)
        {
            goto error_handler_maxNumberOfPoints;
        }
        for (i = 0; i < nclk; i++)
        {
            sco->internal.maxNumberOfPoints[i] = DEFAULT_MAX_NUMBER_OF_POINTS;
        }

        sco->internal.data = (double **)CALLOC(2 * nclk, sizeof(double *));
        if (sco->internal.data == NULL)
        {
            goto error_handler_data;
        }

        for (i = 0; i < nclk; i++)
        {
            /*
             * Alloc base pointer
             */
            sco->internal.data[2 * i + 0] = (double *)CALLOC(3 * DEFAULT_MAX_NUMBER_OF_POINTS, sizeof(double));
            if (sco->internal.data[2 * i + 0] == NULL)
            {
                goto error_handler_data_i;
            }

            /*
             * Alloc direction pointer
             */
            sco->internal.data[2 * i + 1] = (double *)CALLOC(3 * DEFAULT_MAX_NUMBER_OF_POINTS, sizeof(double));
            if (sco->internal.data[2 * i + 1] == NULL)
            {
                FREE(sco->internal.data[2 * i + 0]);
                goto error_handler_data_i;
            }
        }

        sco->scope.periodCounter = 0;
        sco->scope.cachedFigureUID = 0;
        sco->scope.cachedAxeUID = 0;
        sco->scope.cachedSegsUIDs = (int*)CALLOC(nclk, sizeof(int));
        if (sco->scope.cachedSegsUIDs == NULL)
        {
            goto error_handler_data_i;
        }

        *(block->work) = sco;
    }

    return sco;

    /*
     * Error management (out of normal flow)
     */

error_handler_data_i:
    for (j = 0; j < i; j++)
    {
        FREE(sco->internal.data[2 * j + 0]);
        FREE(sco->internal.data[2 * j + 1]);
    }
    FREE(sco->internal.data);
error_handler_data:
    FREE(sco->internal.maxNumberOfPoints);
error_handler_maxNumberOfPoints:
    FREE(sco->internal.numberOfPoints);
error_handler_numberOfPoints:
    FREE(sco);
error_handler_sco:
    // allocation error
    set_block_error(-5);
    return NULL;
}
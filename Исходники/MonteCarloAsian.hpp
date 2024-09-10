    /**
     * Destructor
     */
    ~MonteCarloAsian()
    {
        if(sigma)
        {
            free(sigma);
            sigma = NULL;
        }

        if(price) 
        {
            free(price);
            price = NULL;
        }

        if(vega) 
        {
            free(vega);
            vega = NULL;
        }

        if(refPrice) 
        {
            free(refPrice);
            refPrice = NULL;
        }

        if(refVega) 
        {
            free(refVega);
            refVega = NULL;
        }

        if(randNum)
        {
            #ifdef _WIN32
                _aligned_free(randNum);
            #else
                free(randNum);
            #endif
            randNum = NULL;
        }

        if(priceVals) 
        {
            free(priceVals);
            priceVals = NULL;
        }

        if(priceDeriv)
        {
            free(priceDeriv);
            priceDeriv = NULL;
        }

        if(devices)
        {
            free(devices);
            devices = NULL;
        }

        if(maxWorkItemSizes)
        {
            free(maxWorkItemSizes);
            maxWorkItemSizes = NULL;
        }
    }
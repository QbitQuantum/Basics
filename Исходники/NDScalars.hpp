    void operator()(ThreadParams& params,
            const std::string& name, T_Scalar value,
            const std::string& attrName = "", T_Attribute attribute = T_Attribute())
    {
        log<picLog::INPUT_OUTPUT>("HDF5: write %1%D scalars: %2%") % simDim % name;

        // Size over all processes
        Dimensions globalSize(1, 1, 1);
        // Offset for this process
        Dimensions localOffset(0, 0, 0);
        // Offset for all processes
        Dimensions globalOffset(0, 0, 0);

        for (uint32_t d = 0; d < simDim; ++d)
        {
            globalSize[d] = Environment<simDim>::get().GridController().getGpuNodes()[d];
            localOffset[d] = Environment<simDim>::get().GridController().getPosition()[d];
        }

        Dimensions localSize(1, 1, 1);

        // avoid deadlock between not finished pmacc tasks and mpi calls in adios
        __getTransactionEvent().waitForFinished();

        typename traits::PICToSplash<T_Scalar>::type splashType;
        params.dataCollector->writeDomain(params.currentStep,            /* id == time step */
                                           globalSize,                   /* total size of dataset over all processes */
                                           localOffset,                  /* write offset for this process */
                                           splashType,                   /* data type */
                                           simDim,                       /* NDims spatial dimensionality of the field */
                                           splash::Selection(localSize), /* data size of this process */
                                           name.c_str(),                 /* data set name */
                                           splash::Domain(
                                                  globalOffset,          /* offset of the global domain */
                                                  globalSize             /* size of the global domain */
                                           ),
                                           DomainCollector::GridType,
                                           &value);

        if(!attrName.empty())
        {
            /*simulation attribute for data*/
            typename traits::PICToSplash<T_Attribute>::type attType;

            log<picLog::INPUT_OUTPUT>("HDF5: write attribute %1% for scalars: %2%") % attrName % name;
            params.dataCollector->writeAttribute(params.currentStep,
                                                  attType, name.c_str(),
                                                  attrName.c_str(), &attribute);
        }
    }
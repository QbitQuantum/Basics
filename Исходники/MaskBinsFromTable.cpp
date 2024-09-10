  void MaskBinsFromTable::exec()
  {
    MatrixWorkspace_sptr inputWS = getProperty("InputWorkspace");
    DataObjects::TableWorkspace_sptr paramWS = getProperty("MaskingInformation");

    // 1. Check input table workspace and column order
    g_log.debug() << "Lines of parameters workspace = " << paramWS->rowCount() << std::endl;

    bool colname_specx = false;
    if (!paramWS)
    {
      throw std::invalid_argument("Input table workspace is not accepted.");
    }
    else
    {
      std::vector<std::string> colnames = paramWS->getColumnNames();
      // check colum name order
      if (colnames.size() < 3)
      {
        g_log.error() << "Input MaskingInformation table workspace has fewer than 3 columns.  " << colnames.size()
                      << " columns indeed" << std::endl;
        throw std::invalid_argument("MaskingInformation (TableWorkspace) has too few columns.");
      }
      if (colnames[0].compare("XMin") == 0)
      {
          // 1. Style XMin, XMax, SpectraList. Check rest
          if (colnames[1].compare("XMax") != 0 || colnames[2].compare("SpectraList") != 0)
          {
              g_log.error() << "INput MaskingInformation table workspace has wrong column order. " << std::endl;
              throw std::invalid_argument("MaskingInformation (TableWorkspace) has too few columns.");
          }
      }
      else if (colnames[0].compare("SpectraList") == 0)
      {
          // 2. Style SpectraList, XMin, XMax
          colname_specx = true;
          if (colnames[1].compare("XMin") != 0 || colnames[2].compare("XMax") != 0)
          {
              g_log.error() << "INput MaskingInformation table workspace has wrong column order. " << std::endl;
              throw std::invalid_argument("MaskingInformation (TableWorkspace) has too few columns.");
          }
      }
      else
      {
          g_log.error() << "INput MaskingInformation table workspace has wrong column order. " << std::endl;
          throw std::invalid_argument("MaskingInformation (TableWorkspace) has too few columns.");
      }
    }

    // 2. Loop over all rows
    bool firstloop = true;
    API::MatrixWorkspace_sptr outputws = this->getProperty("OutputWorkspace");

    for (size_t ib = 0; ib < paramWS->rowCount(); ++ib)
    {
      API::TableRow therow = paramWS->getRow(ib);
      double xmin, xmax;
      std::string speclist;
      if (colname_specx)
      {
          therow >> speclist >> xmin >> xmax;
      }
      else
      {
          therow >> xmin >> xmax >> speclist;
      }

      g_log.debug() << "Row " << ib << " XMin = " << xmin << "  XMax = " << xmax << " SpectraList = " << speclist << std::endl;

      API::IAlgorithm_sptr maskbins = this->createChildAlgorithm("MaskBins", 0, 0.3, true);
      maskbins->initialize();
      if (firstloop)
      {
        maskbins->setProperty("InputWorkspace", inputWS);
        firstloop = false;
      }
      else
      {
        maskbins->setProperty("InputWorkspace", outputws);
      }
      maskbins->setProperty("OutputWorkspace", outputws);
      maskbins->setPropertyValue("SpectraList", speclist);
      maskbins->setProperty("XMin", xmin);
      maskbins->setProperty("XMax", xmax);

      bool isexec = maskbins->execute();
      if (!isexec)
      {
        g_log.error() << "MaskBins() is not executed for row " << ib << std::endl;
        throw std::runtime_error("MaskBins() is not executed");
      }

      outputws = maskbins->getProperty("OutputWorkspace");
      if (!outputws)
      {
        g_log.error() << "OutputWorkspace is not retrieved for row " << ib << ". " << std::endl;
        throw std::runtime_error("OutputWorkspace is not got from MaskBins");
      }
    }
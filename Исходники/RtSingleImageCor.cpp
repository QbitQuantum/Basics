// process a single acquisition
int RtSingleImageCor::process(ACE_Message_Block *mb) {
  ACE_TRACE(("RtSingleImageCor::process"));

  RtStreamMessage *msg = (RtStreamMessage*) mb->rd_ptr();

  // get the current image to operate on
  RtMRIImage *dat = (RtMRIImage*) msg->getCurrentData();

  if (dat == NULL) {
    cout << "RtSingleImageCor::process: data passed is NULL" << endl;

    ACE_DEBUG((LM_INFO, "RtSingleImageCor:process: data passed is NULL\n"));
    return 0;
  }

  RtMaskImage *mask = getMaskFromMessage(*msg);

  numTimepoints++;

  // initialize the computation if necessary
  if (needsInit) {
    initEstimation(*dat, mask);
  }

  // allocate a new data images for the stats
  RtActivation *stat = new RtActivation(*dat);

  // setup the data id
  stat->getDataID().setFromInputData(*dat, *this);
  stat->getDataID().setDataName(NAME_ACTIVATION);
  stat->getDataID().setRoiID(mask->getDataID().getRoiID());

  stat->initToZeros();

  // residual sum of squares map
  RtActivation *res = new RtActivation(*dat);
  // setup the data id
  res->getDataID().setFromInputData(*dat, *this);
  res->getDataID().setDataName(NAME_RESIDUAL_MSE);
  res->getDataID().setRoiID(mask->getDataID().getRoiID());
  res->initToZeros();

  //// element independent setup

  /// build a design matrix row
  vnl_vector<double> Xrow = design.getRow(dat->getDataID().getTimePoint());

  bool anyOverZero = false;
  for (unsigned int i = 0; i < design.getNumColumns(); i++) {
    // check for on condition for any stimulus
    if (design.isColumnOfInterest(i)
        && Xrow[i] > std::numeric_limits<double>::epsilon()) {
      anyOverZero = true;
      break;
    }
  }


  if (DEBUG_LEVEL & MODERATE) {
    cout << " xrow " << numTimepoints << ":";
    for (unsigned int i = 0; i < Xrow.size(); i++) {
      cout << Xrow[i] << " ";
    }
    cout << endl;
  }

  // check if we should include this timepoint in variance computation
  bool includeInErr;
  if ((numTimepoints > numDataPointsForErrEst)
      || (onlyEstErrInBaseline && anyOverZero)) {
    includeInErr = false;
  }
  else {
    includeInErr = true;
    numDataPointsCount++;
  }

  //// compute t map for each element
  RtElementAccess elAc(dat, mask);
  vector<unsigned int> indices = elAc.getElementIndices();
  unsigned int curSolver = 0;
  for (vector<unsigned int>::iterator i = indices.begin(); i != indices.end();
       i++, curSolver++) {
    if (!mask->getPixel(*i)) {
      stat->setPixel(*i, numeric_limits<double>::quiet_NaN()); // assign nan
      res->setPixel(*i, numeric_limits<double>::quiet_NaN()); // assign nan
      continue;
    }

    // include this timepoint in the solver for this voxel
    double y = dat->getElement(*i);
    solvers[curSolver]->include(&y, Xrow.data_block(), 1.0);

    // get stats and residual
    double *beta = solvers[curSolver]->regress(0);

    // note that residual is always the standard L2 version, despite which
    // norm we are using for the stat scaling
    res->setPixel(*i, sqrt(solvers[curSolver]->getTotalSquaredError(0)
                           / (numTimepoints - 1)));

    // compute stat
    double err = y;
    double meanCondActivity = 0;
    for (unsigned int j = 0; j < Xrow.size(); j++) {
      if (!design.isColumnOfInterest(j)) {
        err -= beta[j] * Xrow[j];
      }
      else {
        meanCondActivity += beta[j] * Xrow[j];
      }
    }

    if (DEBUG_LEVEL & ADVANCED) {
      static double lastErr = 0;
      cerr << *i << ": err is " << err << " ?= "
           << sqrt(solvers[curSolver]->getTotalSquaredError(0)) - lastErr
           << endl;
      lastErr = sqrt(solvers[curSolver]->getTotalSquaredError(0));
    }

    // update the error in the estimate for the voxel

    // get estimation error and compute the standard deviation based on
    // the error sum and current error norm and include the error in the
    // estimate if desired
    double dev;
    switch (errorNorm) {
      case L1:
        if (includeInErr) {
          estErrSum->setPixel(*i, estErrSum->getPixel(*i) + fabs(err));
        }

        dev = estErrSum->getPixel(*i) / (numDataPointsCount - 1);
        break;

      case L2:
      default:
        if (includeInErr) {
          estErrSum->setPixel(*i, estErrSum->getPixel(*i) + err * err);
        }

        dev = sqrt(estErrSum->getPixel(*i) / (numDataPointsCount - 1));
        break;

      case LINF:
        if (includeInErr) {
          estErrSum->setPixel(*i, std::max(estErrSum->getPixel(*i), fabs(err)));
        }

        dev = estErrSum->getPixel(*i);

        break;
    }

    if (DEBUG_LEVEL & ADVANCED) {
      cerr << dev << " ?= "
           << sqrt(solvers[curSolver]->getTotalSquaredError(0)
                   / (numTimepoints - 1))
           << endl;
    }


    // compute the sds away from the mean (magic kinda happens here)
    if (includeConditionMean) {
      stat->setPixel(*i, (meanCondActivity + err) / dev);
    }
    else {
      stat->setPixel(*i, (meanCondActivity) + (err / dev));
    }

    if (DEBUG_LEVEL & ADVANCED) {
      cerr
          << numTimepoints << " "
          << *i << " "
          << y << " "
          << err + meanCondActivity << " "
          << err << " "
          << dev << " "
          << stat->getPixel(*i) << " " << endl;
    }
    if (DEBUG_LEVEL & MODERATE) {
      cerr << err << "/" << dev << "=" << stat->getPixel(*i) << endl;
    }

    if (numTimepoints > 2) {
      dumpFile
          << numTimepoints << " "
          << *i << " "
          << y << " "
          << err + meanCondActivity << " "
          << Xrow[0] << " "
          << err << " "
          << dev << " "
          << stat->getPixel(*i) << " ";
      for (unsigned int b = 0; b < design.getNumColumns(); b++) {
        dumpFile << beta[b] << " ";
      }
      dumpFile << endl;
    }

    delete beta;
  }


  if (DEBUG_LEVEL & BASIC) {
    cout << "done processing single image correlation at ";
    printNow(cout);
    cout << endl;
  }

  // set the results
  setResult(msg, stat);
  setResult(msg, res);

  return 0;
}
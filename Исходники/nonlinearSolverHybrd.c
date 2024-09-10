/*! \fn solve non-linear system with hybrd method
 *
 *  \param [in]  [data]
 *               [sysNumber] index of the corresponing non-linear system
 *
 *  \author wbraun
 */
int solveHybrd(DATA *data, int sysNumber)
{
  NONLINEAR_SYSTEM_DATA* systemData = &(data->simulationInfo.nonlinearSystemData[sysNumber]);
  DATA_HYBRD* solverData = (DATA_HYBRD*)systemData->solverData;
  /*
   * We are given the number of the non-linear system.
   * We want to look it up among all equations.
   */
  int eqSystemNumber = systemData->equationIndex;
  threadData_t *threadData = data->threadData;

  int i, j;
  integer iflag = 1;
  double xerror, xerror_scaled;
  int success = 0;
  double local_tol = 1e-12;
  double initial_factor = solverData->factor;
  int nfunc_evals = 0;
  int continuous = 1;
  int nonContinuousCase = 0;

  int giveUp = 0;
  int retries = 0;
  int retries2 = 0;
  int retries3 = 0;
  int assertCalled = 0;
  int assertRetries = 0;
  int assertMessage = 0;

  modelica_boolean* relationsPreBackup;

  struct dataAndSys dataAndSysNumber = {data, sysNumber};

  relationsPreBackup = (modelica_boolean*) malloc(data->modelData.nRelations*sizeof(modelica_boolean));

  solverData->numberOfFunctionEvaluations = 0;
  /* debug output */
  if(ACTIVE_STREAM(LOG_NLS_V))
  {
    int indexes[2] = {1,eqSystemNumber};
    infoStreamPrintWithEquationIndexes(LOG_NLS_V, 1, indexes, "start solving non-linear system >>%d<< at time %g", eqSystemNumber, data->localData[0]->timeValue);
    for(i=0; i<solverData->n; i++)
    {
      infoStreamPrint(LOG_NLS_V, 1, "%d. %s = %f", i+1, modelInfoGetEquation(&data->modelData.modelDataXml,eqSystemNumber).vars[i], systemData->nlsx[i]);
      infoStreamPrint(LOG_NLS_V, 0, "    nominal = %f\nold = %f\nextrapolated = %f",
          systemData->nominal[i], systemData->nlsxOld[i], systemData->nlsxExtrapolation[i]);
      messageClose(LOG_NLS_V);
    }
    messageClose(LOG_NLS_V);
  }

  /* set x vector */
  if(data->simulationInfo.discreteCall)
    memcpy(solverData->x, systemData->nlsx, solverData->n*(sizeof(double)));
  else
    memcpy(solverData->x, systemData->nlsxExtrapolation, solverData->n*(sizeof(double)));

  for(i=0; i<solverData->n; i++){
    solverData->xScalefactors[i] = fmax(fabs(solverData->x[i]), systemData->nominal[i]);
  }

  /* start solving loop */
  while(!giveUp && !success)
  {
    for(i=0; i<solverData->n; i++)
      solverData->xScalefactors[i] = fmax(fabs(solverData->x[i]), systemData->nominal[i]);

    /* debug output */
    if(ACTIVE_STREAM(LOG_NLS_V)) {
      printVector(solverData->xScalefactors, &(solverData->n), LOG_NLS_V, "scaling factors x vector");
      printVector(solverData->x, &(solverData->n), LOG_NLS_V, "Iteration variable values");
    }

    /* Scaling x vector */
    if(solverData->useXScaling) {
      for(i=0; i<solverData->n; i++) {
        solverData->x[i] = (1.0/solverData->xScalefactors[i]) * solverData->x[i];
      }
    }

    /* debug output */
    if(ACTIVE_STREAM(LOG_NLS_V))
    {
      printVector(solverData->x, &solverData->n, LOG_NLS_V, "Iteration variable values (scaled)");
    }

    /* set residual function continuous
     */
    if(continuous) {
      ((DATA*)data)->simulationInfo.solveContinuous = 1;
    } else {
      ((DATA*)data)->simulationInfo.solveContinuous = 0;
    }

    giveUp = 1;

    /* try */
    {
      int success = 0;
#ifndef OMC_EMCC
      MMC_TRY_INTERNAL(simulationJumpBuffer)
#endif
      hybrj_(wrapper_fvec_hybrj, &solverData->n, solverData->x,
          solverData->fvec, solverData->fjac, &solverData->ldfjac, &solverData->xtol,
          &solverData->maxfev, solverData->diag, &solverData->mode, &solverData->factor,
          &solverData->nprint, &solverData->info, &solverData->nfev, &solverData->njev, solverData->r__,
          &solverData->lr, solverData->qtf, solverData->wa1, solverData->wa2,
          solverData->wa3, solverData->wa4, (void*) &dataAndSysNumber);

      success = 1;
      if(assertCalled)
      {
        infoStreamPrint(LOG_NLS, 0, "After assertions failed, found a solution for which assertions did not fail.");
        /* re-scaling x vector */
        for(i=0; i<solverData->n; i++){
          if(solverData->useXScaling)
            systemData->nlsxOld[i] = solverData->x[i]*solverData->xScalefactors[i];
          else
            systemData->nlsxOld[i] = solverData->x[i];
        }
      }
      assertRetries = 0;
      assertCalled = 0;
      success = 1;
#ifndef OMC_EMCC
      MMC_CATCH_INTERNAL(simulationJumpBuffer)
#endif
      /* catch */
      if (!success)
      {
        if (!assertMessage)
        {
          if (ACTIVE_WARNING_STREAM(LOG_STDOUT))
          {
            if(data->simulationInfo.initial)
              warningStreamPrint(LOG_STDOUT, 1, "While solving non-linear system an assertion failed during initialization.");
            else
              warningStreamPrint(LOG_STDOUT, 1, "While solving non-linear system an assertion failed at time %g.", data->localData[0]->timeValue);
            warningStreamPrint(LOG_STDOUT, 0, "The non-linear solver tries to solve the problem that could take some time.");
            warningStreamPrint(LOG_STDOUT, 0, "It could help to provide better start-values for the iteration variables.");
            if (!ACTIVE_STREAM(LOG_NLS))
              warningStreamPrint(LOG_STDOUT, 0, "For more information simulate with -lv LOG_NLS");
            messageClose(LOG_STDOUT);
          }
          assertMessage = 1;
        }

        solverData->info = -1;
        xerror_scaled = 1;
        xerror = 1;
        assertCalled = 1;
      }
    }

    /* set residual function continuous */
    if(continuous)
    {
      ((DATA*)data)->simulationInfo.solveContinuous = 0;
    }
    else
    {
      ((DATA*)data)->simulationInfo.solveContinuous = 1;
    }

    /* re-scaling x vector */
    if(solverData->useXScaling)
      for(i=0; i<solverData->n; i++)
        solverData->x[i] = solverData->x[i]*solverData->xScalefactors[i];

    /* check for proper inputs */
    if(solverData->info == 0) {
      printErrorEqSyst(IMPROPER_INPUT, modelInfoGetEquation(&data->modelData.modelDataXml, eqSystemNumber),
          data->localData[0]->timeValue);
    }

    if(solverData->info != -1)
    {
      /* evaluate with discontinuities */
      if(data->simulationInfo.discreteCall){
        int scaling = solverData->useXScaling;
        int success = 0;
        if(scaling)
          solverData->useXScaling = 0;

        ((DATA*)data)->simulationInfo.solveContinuous = 0;

        /* try */
#ifndef OMC_EMCC
        MMC_TRY_INTERNAL(simulationJumpBuffer)
#endif
        wrapper_fvec_hybrj(&solverData->n, solverData->x, solverData->fvec, solverData->fjac, &solverData->ldfjac, &iflag, (void*) &dataAndSysNumber);
        success = 1;
#ifndef OMC_EMCC
        MMC_CATCH_INTERNAL(simulationJumpBuffer)
#endif
        /* catch */
        if (!success)
        {
          warningStreamPrint(LOG_STDOUT, 0, "Non-Linear Solver try to handle a problem with a called assert.");

          solverData->info = -1;
          xerror_scaled = 1;
          xerror = 1;
          assertCalled = 1;
        }

        if(scaling)
          solverData->useXScaling = 1;

        updateRelationsPre(data);
      }
    }

    if(solverData->info != -1)
    {
      /* scaling residual vector */
      {
        int l=0;
        for(i=0; i<solverData->n; i++){
          solverData->resScaling[i] = 1e-16;
          for(j=0; j<solverData->n; j++){
            solverData->resScaling[i] = (fabs(solverData->fjacobian[l]) > solverData->resScaling[i])
                    ? fabs(solverData->fjacobian[l]) : solverData->resScaling[i];
            l++;
          }
          solverData->fvecScaled[i] = solverData->fvec[i] * (1 / solverData->resScaling[i]);
        }
        /* debug output */
        if(ACTIVE_STREAM(LOG_NLS_V))
        {
          infoStreamPrint(LOG_NLS_V, 1, "scaling factors for residual vector");
          for(i=0; i<solverData->n; i++)
          {
            infoStreamPrint(LOG_NLS_V, 1, "scaled residual [%d] : %.20e", i, solverData->fvecScaled[i]);
            infoStreamPrint(LOG_NLS_V, 0, "scaling factor [%d] : %.20e", i, solverData->resScaling[i]);
            messageClose(LOG_NLS_V);
          }
          messageClose(LOG_NLS_V);
        }

        /* debug output */
        if(ACTIVE_STREAM(LOG_NLS_JAC))
        {
          char buffer[4096];

          infoStreamPrint(LOG_NLS_JAC, 1, "jacobian matrix [%dx%d]", (int)solverData->n, (int)solverData->n);
          for(i=0; i<solverData->n; i++)
          {
            buffer[0] = 0;
            for(j=0; j<solverData->n; j++)
              sprintf(buffer, "%s%10g ", buffer, solverData->fjacobian[i*solverData->n+j]);
            infoStreamPrint(LOG_NLS_JAC, 0, "%s", buffer);
          }
          messageClose(LOG_NLS_JAC);
        }

        /* check for error  */
        xerror_scaled = enorm_(&solverData->n, solverData->fvecScaled);
        xerror = enorm_(&solverData->n, solverData->fvec);
      }
    }

    /* reset non-contunuousCase */
    if(nonContinuousCase && xerror > local_tol && xerror_scaled > local_tol)
    {
      memcpy(data->simulationInfo.relationsPre, relationsPreBackup, sizeof(modelica_boolean)*data->modelData.nRelations);
      nonContinuousCase = 0;
    }

    if(solverData->info < 4 && xerror > local_tol && xerror_scaled > local_tol)
      solverData->info = 4;

    /* solution found */
    if(solverData->info == 1 || xerror <= local_tol || xerror_scaled <= local_tol)
    {
      int scaling;

      success = 1;
      nfunc_evals += solverData->nfev;
      if(ACTIVE_STREAM(LOG_NLS))
      {
        int indexes[2] = {1,eqSystemNumber};
        /* output solution */
        infoStreamPrintWithEquationIndexes(LOG_NLS, 1, indexes, "solution for NLS %d at t=%g", eqSystemNumber, data->localData[0]->timeValue);
        for(i=0; i<solverData->n; ++i)
        {
          infoStreamPrint(LOG_NLS, 0, "[%d] %s = %g", i+1, modelInfoGetEquation(&data->modelData.modelDataXml,eqSystemNumber).vars[i],  solverData->x[i]);
        }
        messageClose(LOG_NLS);
      }else if (ACTIVE_STREAM(LOG_NLS_V)){
        infoStreamPrint(LOG_NLS_V, 1, "system solved");
        infoStreamPrint(LOG_NLS_V, 0, "%d retries\n%d restarts", retries, retries2+retries3);
        messageClose(LOG_NLS_V);
        printStatus(data, solverData, eqSystemNumber, &nfunc_evals, &xerror, &xerror_scaled, LOG_NLS_V);
      }
      scaling = solverData->useXScaling;
      if(scaling)
        solverData->useXScaling = 0;

      /* take the solution */
      memcpy(systemData->nlsx, solverData->x, solverData->n*(sizeof(double)));

      /* try */
      {
        int success = 0;
#ifndef OMC_EMCC
        MMC_TRY_INTERNAL(simulationJumpBuffer)
#endif
        wrapper_fvec_hybrj(&solverData->n, solverData->x, solverData->fvec, solverData->fjac, &solverData->ldfjac, &iflag, (void*) &dataAndSysNumber);
        success = 1;
#ifndef OMC_EMCC
        MMC_CATCH_INTERNAL(simulationJumpBuffer)
#endif
        /* catch */
        if (!success) {
          warningStreamPrint(LOG_STDOUT, 0, "Non-Linear Solver try to handle a problem with a called assert.");

          solverData->info = 4;
          xerror_scaled = 1;
          xerror = 1;
          assertCalled = 1;
          success = 0;
          giveUp = 0;
        }
      }
      if(scaling)
        solverData->useXScaling = 1;
    }
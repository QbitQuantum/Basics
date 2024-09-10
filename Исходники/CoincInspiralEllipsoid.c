void
LALCreateTwoIFOCoincListEllipsoid(
    LALStatus                  *status,
    CoincInspiralTable        **coincOutput,
    SnglInspiralTable          *snglInput,
    InspiralAccuracyList       *accuracyParams
    )

{
  INT8                          currentTriggerNS[2];
  CoincInspiralTable           *coincHead = NULL;
  CoincInspiralTable           *thisCoinc = NULL;
  INT4                          numEvents = 0;
  INT8                          maxTimeDiff = 0;
  TriggerErrorList             *errorListHead = NULL;
  TriggerErrorList             UNUSED *thisErrorList = NULL;
  TriggerErrorList             *currentError[2];
  fContactWorkSpace            *workSpace;
  REAL8                        timeError = 0.0;


  INITSTATUS(status);
  ATTATCHSTATUSPTR( status );

  ASSERT( snglInput, status,
      LIGOMETADATAUTILSH_ENULL, LIGOMETADATAUTILSH_MSGENULL );
  ASSERT( coincOutput, status,
      LIGOMETADATAUTILSH_ENULL, LIGOMETADATAUTILSH_MSGENULL );
  ASSERT( ! *coincOutput, status,
      LIGOMETADATAUTILSH_ENNUL, LIGOMETADATAUTILSH_MSGENNUL );

  memset( currentTriggerNS, 0, 2 * sizeof(INT8) );

  /* Loop through triggers and assign each of them an error ellipsoid */
  errorListHead = XLALCreateTriggerErrorList( snglInput, accuracyParams->eMatch, &timeError );
  if ( !errorListHead )
  {
    ABORTXLAL( status );
  }

  /* Initialise the workspace for ellipsoid overlaps */
  workSpace = XLALInitFContactWorkSpace( 3, NULL, NULL, gsl_min_fminimizer_brent, 1.0e-2 );
  if (!workSpace)
  {
    XLALDestroyTriggerErrorList( errorListHead );
    ABORTXLAL( status );
  }

  /* calculate the maximum time delay
   * set it equal to 2 * worst IFO timing accuracy plus
   * light travel time for earths diameter
   * (detectors cant be further apart than this) */

  maxTimeDiff = (INT8) (1e9 * 2.0 * timeError);
  maxTimeDiff += (INT8) ( 1e9 * 2 * LAL_REARTH_SI / LAL_C_SI );

  for ( currentError[0] = errorListHead; currentError[0]->next;
      currentError[0] = currentError[0]->next)
  {

    /* calculate the time of the trigger */
    currentTriggerNS[0] = XLALGPSToINT8NS(
                 &(currentError[0]->trigger->end_time) );

    /* set next trigger for comparison */
    currentError[1] = currentError[0]->next;
    currentTriggerNS[1] = XLALGPSToINT8NS(
                 &(currentError[1]->trigger->end_time) );

    while ( (currentTriggerNS[1] - currentTriggerNS[0]) < maxTimeDiff )
    {

      INT2 match;

      /* test whether we have coincidence */
      match = XLALCompareInspiralsEllipsoid( currentError[0],
                 currentError[1], workSpace, accuracyParams );
      if ( match == XLAL_FAILURE )
      {
        /* Error in the comparison function */
        XLALDestroyTriggerErrorList( errorListHead );
        XLALFreeFContactWorkSpace( workSpace );
        ABORTXLAL( status );
      }

      /* Check whether the event was coincident */
      if ( match )
      {
#if 0
        REAL8 etp = XLALCalculateEThincaParameter( currentError[0]->trigger,  currentError[1]->trigger, accuracyParams );
#endif
        /* create a 2 IFO coinc and store */
        if ( ! coincHead  )
        {
          coincHead = thisCoinc = (CoincInspiralTable *)
            LALCalloc( 1, sizeof(CoincInspiralTable) );
        }
        else
        {
          thisCoinc = thisCoinc->next = (CoincInspiralTable *)
            LALCalloc( 1, sizeof(CoincInspiralTable) );
        }
        if ( !thisCoinc )
        {
          /* Error allocating memory */
          thisCoinc = coincHead;
          while ( thisCoinc )
          {
            coincHead = thisCoinc->next;
            LALFree( thisCoinc );
            thisCoinc = coincHead;
          }
          XLALDestroyTriggerErrorList( errorListHead );
          XLALFreeFContactWorkSpace( workSpace );
          ABORT( status, LAL_NOMEM_ERR, LAL_NOMEM_MSG );
        }

        /* Add the two triggers to the coinc */
        LALAddSnglInspiralToCoinc( status->statusPtr, &thisCoinc,
            currentError[0]->trigger );
        LALAddSnglInspiralToCoinc( status->statusPtr, &thisCoinc,
            currentError[1]->trigger );

        ++numEvents;

      }

      /* scroll on to the next sngl inspiral */

      if ( (currentError[1] = currentError[1]->next) )
      {
        currentTriggerNS[1] = XLALGPSToINT8NS( &(currentError[1]->trigger->end_time) );
      }
      else
      {
        LALInfo(status, "Second trigger has reached end of list");
        break;
      }
    }
  }

  *coincOutput = coincHead;

  /* Free all the memory allocated for the ellipsoid overlap */
  thisErrorList = errorListHead;
  XLALDestroyTriggerErrorList( errorListHead );
  XLALFreeFContactWorkSpace( workSpace );

  DETATCHSTATUSPTR (status);
  RETURN (status);
}
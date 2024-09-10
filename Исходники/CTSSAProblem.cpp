/**
 * This function synchronizes step size and number
 */
bool CTSSAProblem::sync()
{
  bool success = true;

  C_FLOAT64 Tmp = *mpDuration;
  C_FLOAT64 StepSize = *mpStepSize;
  C_FLOAT64 StepNumber = (C_FLOAT64) * mpStepNumber;

  if (mStepNumberSetLast)
    {
      StepSize = Tmp / (C_FLOAT64) * mpStepNumber;

      /* Assure that the step size is not to small for machine accuracy */
      if (fabs(StepSize) < 100.0 * std::numeric_limits< C_FLOAT64 >::epsilon() * fabs(*mpDuration))
        {
          CCopasiMessage(CCopasiMessage::WARNING,
                         MCTSSAProblem + 3, StepSize);

          StepSize = 100.0 * std::numeric_limits< C_FLOAT64 >::epsilon() * fabs(*mpDuration);
          /* Assure that the step size has the appropriate sign. */
          StepSize = (Tmp < 0.0) ? - fabs(StepSize) : fabs(StepSize);
          StepNumber = fabs(ceil(Tmp / StepSize));
        }
    }
  else
    {
      if (fabs(StepSize) < 100.0 * std::numeric_limits< C_FLOAT64 >::epsilon() * fabs(*mpDuration))
        {
          CCopasiMessage(CCopasiMessage::WARNING,
                         MCTSSAProblem + 3, StepSize);

          StepSize = 100.0 * std::numeric_limits< C_FLOAT64 >::epsilon() * fabs(*mpDuration);

          /* Assure that the step size has the appropriate sign. */
          StepSize = (Tmp < 0.0) ? - fabs(StepSize) : fabs(StepSize);
        }

      StepNumber = fabs(ceil(Tmp / StepSize));

      /* Protect against overflow */
      if ((C_FLOAT64) ULONG_MAX < StepNumber)
        {
          CCopasiMessage(CCopasiMessage::WARNING,
                         MCTSSAProblem + 2, StepNumber);

          StepNumber = (C_FLOAT64) ULONG_MAX;
          StepSize = Tmp / StepNumber;

          success = false;
        }

      /* Assure that the step size has the appropriate sign. */
      StepSize = (Tmp < 0.0) ? - fabs(StepSize) : fabs(StepSize);
    }

  *mpStepSize = StepSize;
  *mpStepNumber = (unsigned C_INT32) StepNumber;

  if (!success) throw 1;

  return success;
}
/**
 * Load a steadystate problem
 * @param "CReadConfig &" configBuffer
 */
void CSteadyStateProblem::load(CReadConfig & configBuffer,
                               CReadConfig::Mode C_UNUSED(mode))
{
  if (configBuffer.getVersion() < "4.0")
    {
      configBuffer.getVariable("RepStabilityAnalysis", "bool" ,
                               &getValue< bool >("StabilityAnalysisRequested"),
                               CReadConfig::LOOP);
      setValue("JacobianRequested", getValue< bool >("StabilityAnalysisRequested"));
    }
}
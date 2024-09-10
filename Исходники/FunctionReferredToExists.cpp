/*
 * Checks that all ids on the following Model objects are unique:
 * event assignments and assignment rules.
 */
void
FunctionReferredToExists::check_ (const Model& m, const Model&)
{
  // does not apply in l2v4 and beyond
  if (m.getLevel() == 2 && m.getVersion() < 4)
  {
    unsigned int n;

    for (n = 0; n < m.getNumFunctionDefinitions(); ++n)
    {
      mFunctions.append(m.getFunctionDefinition(n)->getId());

      checkCiElements(m.getFunctionDefinition(n));
    }
  }
}
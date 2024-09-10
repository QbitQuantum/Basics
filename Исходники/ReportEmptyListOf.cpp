/*
 * Checks that all ids on the following Model objects are unique:
 * event assignments and assignment rules.
 */
void
ReportEmptyListOf::check_ (const Model& m, const Model&)
{
  // only applies to an l3v2 model
  if (m.getLevel() != 3) return;
  else if (m.getVersion() == 1) return;

  if (isEmptyListOf(m.getListOfFunctionDefinitions()))
  {
    logEmptyList(m.getListOfFunctionDefinitions(), m);
  }

  if (isEmptyListOf(m.getListOfCompartments()))
  {
    logEmptyList(m.getListOfCompartments(), m);
  }

  if (isEmptyListOf(m.getListOfSpecies()))
  {
    logEmptyList(m.getListOfSpecies(), m);
  }

  if (isEmptyListOf(m.getListOfParameters()))
  {
    logEmptyList(m.getListOfParameters(), m);
  }

  if (isEmptyListOf(m.getListOfRules()))
  {
    logEmptyList(m.getListOfRules(), m);
  }

  if (isEmptyListOf(m.getListOfInitialAssignments()))
  {
    logEmptyList(m.getListOfInitialAssignments(), m);
  }

  if (isEmptyListOf(m.getListOfConstraints()))
  {
    logEmptyList(m.getListOfConstraints(), m);
  }

  if (isEmptyListOf(m.getListOfReactions()))
  {
    logEmptyList(m.getListOfReactions(), m);
  }

  if (isEmptyListOf(m.getListOfUnitDefinitions()))
  {
    logEmptyList(m.getListOfUnitDefinitions(), m);
  }

  if (isEmptyListOf(m.getListOfEvents()))
  {
    logEmptyList(m.getListOfEvents(), m);
  }

  unsigned int i;
  for (i = 0; i < m.getNumUnitDefinitions(); i++)
  {
    if (isEmptyListOf(m.getUnitDefinition(i)->getListOfUnits()))
    {
      logEmptyList(m.getUnitDefinition(i)->getListOfUnits(), *(m.getUnitDefinition(i)));
    }
  }

  for (i = 0; i < m.getNumEvents(); i++)
  {
    if (isEmptyListOf(m.getEvent(i)->getListOfEventAssignments()))
    {
      logEmptyList(m.getEvent(i)->getListOfEventAssignments(), *(m.getEvent(i)));
    }
  }

  for (i = 0; i < m.getNumReactions(); i++)
  {
    if (isEmptyListOf(m.getReaction(i)->getListOfReactants()))
    {
      logEmptyList(m.getReaction(i)->getListOfReactants(), *(m.getReaction(i)));
    }
    if (isEmptyListOf(m.getReaction(i)->getListOfProducts()))
    {
      logEmptyList(m.getReaction(i)->getListOfProducts(), *(m.getReaction(i)));
    }
    if (isEmptyListOf(m.getReaction(i)->getListOfModifiers()))
    {
      logEmptyList(m.getReaction(i)->getListOfModifiers(), *(m.getReaction(i)));
    }

    if (m.getReaction(i)->isSetKineticLaw())
    {
      const KineticLaw * kl = m.getReaction(i)->getKineticLaw();
      if (isEmptyListOf(kl->getListOfLocalParameters()))
      {
        logEmptyList(kl->getListOfLocalParameters(), *(m.getReaction(i)));
      }
    }
  }

}
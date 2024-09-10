/**
 * Checks that all ids on the following Model objects are unique:
 * event assignments and assignment rules.
 */
void
AssignmentCycles::check_ (const Model& m, const Model& object)
{
  // this rule ony applies in l2v2 and beyond
  if (object.getLevel() == 1 
    || (object.getLevel() == 2 && object.getVersion() == 1))
    return;

  unsigned int n;

  mIdMap.clear();

  /* create map of id mapped to id that it refers to that is
   * also the id of a Reaction, AssignmentRule or InitialAssignment
   */
  for (n = 0; n < m.getNumInitialAssignments(); ++n)
  { 
    if (m.getInitialAssignment(n)->isSetMath())
    {
      addInitialAssignmentDependencies(m, *m.getInitialAssignment(n));
    }
  }
  
  for (n = 0; n < m.getNumReactions(); ++n)
  { 
    if (m.getReaction(n)->isSetKineticLaw()){
      if (m.getReaction(n)->getKineticLaw()->isSetMath())
      {
        addReactionDependencies(m, *m.getReaction(n));
      }
    }
  }
  
  for (n = 0; n < m.getNumRules(); ++n)
  { 
    if (m.getRule(n)->isAssignment() && m.getRule(n)->isSetMath())
    {
      addRuleDependencies(m, *m.getRule(n));
    }
  }

  // check for self assignment
  checkForSelfAssignment(m);

  determineAllDependencies();
  determineCycles(m);

  checkForImplicitCompartmentReference(m);
}
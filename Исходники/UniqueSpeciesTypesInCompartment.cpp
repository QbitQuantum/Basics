/*
  * Checks that any species with boundary condition false
  * is not set by reaction and rules
  */
void
UniqueSpeciesTypesInCompartment::check_ (const Model& m, const Model& object)
{
  unsigned int n, ns;

  /* speciesType only occurs in l2v2 and higher */
  if (m.getLevel() == 1 || (m.getLevel()== 2 && m.getVersion() == 1))  return;
  
  for (n = 0; n < m.getNumCompartments(); n++)
  {
    const string & id = m.getCompartment(n)->getId();

    /* create List of species in this compartment */
    for (ns = 0; ns < m.getNumSpecies(); ns++)
    {
      if (!strcmp(m.getSpecies(ns)->getCompartment().c_str(), id.c_str()))
      {
        mSpecies.append(m.getSpecies(ns)->getId());
      }
    } 

    /* loop thru the list of Species in the compartment and check that
       no speciesTypes are same */
    for (IdList::const_iterator the_iterator = mSpecies.begin();
      the_iterator != mSpecies.end(); the_iterator++)
    {
      if (m.getSpecies(*the_iterator)->isSetSpeciesType()) 
      {
        const string & type = m.getSpecies(*the_iterator)->getSpeciesType();

        if (mSpeciesTypes.contains(type))
        {
          logConflict(*m.getSpecies(*the_iterator), *m.getCompartment(n));
        }
        else
        {
          mSpeciesTypes.append(type);
        }
      }
    }

    mSpecies.clear();
    mSpeciesTypes.clear();

  }
}
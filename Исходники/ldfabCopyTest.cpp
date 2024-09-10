int checkIrregFabCopy(const Box& a_domain)
{
  int eekflag = 0;
  int nvar = 1;
  Interval interv(0,0);
  int nghost= 0;
  IntVect ivgh= IntVect::Zero;
  Real tolerance = PolyGeom::getTolerance();
  const EBIndexSpace* const ebisPtr = Chombo_EBIS::instance();
  int numlevels = ebisPtr->numLevels();

  Box levelDomain = a_domain;
  for (int ilev = 0; ilev < numlevels-1; ilev++)
    {
      DisjointBoxLayout dblOne, dblTwo;
      int maxsizeOne = 4;
      int maxsizeTwo = 2;
      makeLayout(dblOne, levelDomain, maxsizeOne);
      makeLayout(dblTwo, levelDomain, maxsizeTwo);

      EBISLayout ebislOne, ebislTwo;
      makeEBISL(ebislOne, dblOne, levelDomain, nghost);
      makeEBISL(ebislTwo, dblTwo, levelDomain, nghost);

      LayoutData<IntVectSet> ldIVSOne(dblOne);
      LayoutData<IntVectSet> ldIVSTwo(dblTwo);
      for (DataIterator dit = dblOne.dataIterator(); dit.ok(); ++dit)
        ldIVSOne[dit()] = IntVectSet(dblOne.get(dit()));
      for (DataIterator dit = dblTwo.dataIterator(); dit.ok(); ++dit)
        ldIVSTwo[dit()] = IntVectSet(dblTwo.get(dit()));

      BaseIVFactory<Real> factOne(ebislOne, ldIVSOne);
      BaseIVFactory<Real> factTwo(ebislTwo, ldIVSTwo);

      LevelData<BaseIVFAB<Real> > dataOne(dblOne, nvar, ivgh, factOne);
      LevelData<BaseIVFAB<Real> > dataTwo(dblTwo, nvar, ivgh, factTwo);

      for (DataIterator dit = dblOne.dataIterator(); dit.ok(); ++dit)
        dataOne[dit()].setVal(1);
      for (DataIterator dit = dblTwo.dataIterator(); dit.ok(); ++dit)
        dataTwo[dit()].setVal(2);

      //copy dataone into datatwo.  then all datatwo should hold are ones
      dataOne.copyTo(interv, dataTwo, interv);
      Real rightVal = 1.0;
      for (DataIterator dit = dblTwo.dataIterator(); dit.ok(); ++dit)
        {
          const EBISBox& ebisBox = ebislTwo[dit()];
          const IntVectSet&  ivs = ldIVSTwo[dit()];
          const BaseIVFAB<Real>& fab = dataTwo[dit()];
          for (VoFIterator vofit(ivs, ebisBox.getEBGraph()); vofit.ok(); ++vofit)
            {
              Real thisVal = fab(vofit(), 0);
              if (Abs(thisVal - rightVal) > tolerance)
                {
                  eekflag = 3;
                  return eekflag;
                }
            }
        }
      levelDomain.coarsen(2);
    }
  return eekflag;
}
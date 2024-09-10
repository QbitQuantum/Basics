void adjacency(double * expr, int nSamples, int nGenes, int corType, int adjType, double power, 
               double maxPOutliers, double quick, int fallback, int cosine, 
               int replaceMissing, 
               double * adj, int * errCode, int *warn, int * nThreads, int verbose, int indent)
{
  int 	nElems = nGenes * nGenes;
  int 	nNA = 0;
  double replacementValue = 0;

  // Rprintf("Received nGenes: %d, nSamples: %d\n", nGenes, nSamples);

  // Rprintf("adjacency: adjType: %d\n", adjType);
  Rprintf("adjacency: replaceMissing: %d\n", replaceMissing);
  int err = 0;
  switch (corType)
  {
     case CorTypePearson :
        // Rprintf("Calling cor_pairwise1...");
        cor1Fast(expr, &nSamples, &nGenes, &quick, &cosine, adj, &nNA, &err, nThreads, &verbose, &indent);
        // Rprintf("..done.\n");
        if ((nNA > 0) && (!replaceMissing))
        {
          * errCode = 1;
          return;
        }
        break;
     case CorTypeBicor :
        // Rprintf("Calling bicor1...");
        bicor1Fast(expr, &nSamples, &nGenes, &maxPOutliers, &quick, &fallback, &cosine, adj, &nNA, &err,
                   warn, nThreads, &verbose, &indent);
        // Rprintf("..done.\n");
        if ((nNA > 0) && (!replaceMissing))
        {
          // Rprintf("nNA: %d\n", nNA);
          * errCode = 1;
          return;
        }
        if (err>0)
        {
          // Rprintf("bicor1 returned err: %d\n", err);
          * errCode = 3;
          return;
        }
        break;
     default : 
        * errCode = 2;
        return;
  }

  if ((*errCode==1) && replaceMissing) 
  {
    Rprintf("Replacing missing adjacency values.\n");
    *errCode = 0;
    if (adjType==AdjTypeSigned) replacementValue = -1;
    for (int i=0; i < nElems; i++)
       if (ISNAN(adj[i])) adj[i] = replacementValue;
    
  }

  // Rprintf("ADJ 1\n");
  

  switch (adjType) 
  {
    case AdjTypeUnsigned :
       for (int i=0; i < nElems; i++)
          adj[i] = pow(fabs(adj[i]), power);
       break;
    case AdjTypeUnsignedKeepSign : 
       for (int i=0; i < nElems; i++)
         adj[i] = (signbit(adj[i])? -1: 1) * pow(fabs(adj[i]), power);
       break;
    case AdjTypeSigned :
       for (int i=0; i < nElems; i++)
          adj[i] = pow((1+adj[i])/2, power);
       break;
    case AdjTypeHybrid :
       for (int i=0; i < nElems; i++)
          adj[i] = adj[i] > 0 ? pow(adj[i], power) : 0;
       break;
    default : 
       * errCode = 3;
  }
       
}
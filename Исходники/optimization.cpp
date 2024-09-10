void MaxPosterior::DE_eachIter(IM im, popTree* poptree, Chain coldCh, unsigned int nProcs, unsigned int crr_procID)
{

  Eigen::MatrixXd newPara;
  newPara.resize(1,nPara);
  for(unsigned int i=0; i<nParaVectors; i++)
    {
      unsigned int recombinationID = runiform_discrete(nPara);
      newPara.setZero();
      double newPara_each = 0.0;
      // select base vectors
      unsigned int b1=i;
      unsigned int b2=i;
      unsigned int b3=i;
      if(crr_procID == 0)
	{
	  while(b1==i)
	    b1 = runiform_discrete(nParaVectors);
	  while(b2 ==i || b2 == b1)
	    b2 = runiform_discrete(nParaVectors);
	  while(b3==i || b3== b2|| b3== b1)
	    b3 = runiform_discrete(nParaVectors);
	}
     
      for(unsigned int j=0; j<nPara; j++)
	{
	  if(crr_procID == 0)
	    {
	      newPara_each = para_atPrev(i,j);
	      if(runiform() < CR ||  j== recombinationID)
		{
		  newPara_each = para_atPrev(b1,j)+F*(para_atPrev(b2,j)-para_atPrev(b3,j)); // differential mutation
		  while(newPara_each <0 || newPara_each >priorsMax.at(j))
		    {
		      if(newPara_each <0)
			newPara_each = para_atPrev(b1,j)-runiform()*(para_atPrev(b1,j));
		      if(newPara_each > priorsMax.at(j))
			newPara_each = para_atPrev(b1,j)+runiform()*(priorsMax.at(j)-para_atPrev(b1,j));
		    }
		  
		  if(newPara_each <0 || newPara_each > priorsMax.at(j))
		    {
		      std::cout << "\n*** Error *** in map::DE_eachIter()\n";
		    }
		}
	    }
	  MPI::COMM_WORLD.Barrier();
	  MPI::COMM_WORLD.Bcast(&newPara_each, 1, MPI_DOUBLE, 0);
	  MPI::COMM_WORLD.Barrier();
	  newPara(0,j) = newPara_each;
	} //END of for(unsigned int j=0; j<nPara; j++)

      Eigen::MatrixXd paraVector(1,6);
      unsigned int nPara_popSizes =1;
      if(poptree->get_age() ==0)// single population
	{
	  for(unsigned int ii=0; ii<6; ii++)
	    {
	      if(ii==2)
		paraVector(0,ii) = newPara(0,0);
	      else
		paraVector(0,ii) = 0;
	    }
	}
      else
	{
	  //-- sampling populations --//
	  paraVector(0,0) = newPara(0,0);
	  if(im.get_samePopulationSizes() == 1)
	    paraVector(0,1) = newPara(0,0);
	  else
	    {
	      paraVector(0,1) = newPara(0,1);
	      nPara_popSizes++;
	    }
	  //-- ancestral population --//
	  if(im.get_ancPop() == 1)
	    {
	      if(im.get_samePopulationSizes() == 1)
		paraVector(0,2) = newPara(0,0);
	      else
		{
		  paraVector(0,2) = newPara(0,2);
		  nPara_popSizes++;
		}
	    }
	  else // no ancestral population
	    paraVector(0,2) = 0;
	  //-- migration rates --//
	  paraVector(0,3) = newPara(0,nPara_popSizes);
	  if(im.get_sameMigrationRates() == 1)
	    paraVector(0,4) = newPara(0,nPara_popSizes);
	  else
	    paraVector(0,4) = newPara(0,nPara_popSizes+1);
	  //-- splitting time --//
	  if(im.get_ancPop() == 1)	
	    paraVector(0,5) = newPara(0,nPara-1);
	  else // no ancestral population
	    paraVector(0,5) =im.get_splittingTimeMax();
	}

      long double logPosterior_newPara = 0;

      unsigned int lociInParallel = im.get_lociInParallel();
      if(lociInParallel ==1)
	{
	  if(coldCh.get_multiLocusSpecific_mutationRate() ==1) // variable mutation rate scalars
	    {
	      logPosterior_newPara = computeLogJointDensity_mutationScalars_MPI_overSubLoci(paraVector, im, poptree, coldCh, nProcs, crr_procID);  
	      
	    }
	  else // constant mutation rate scalars
	    {
	      logPosterior_newPara = computeLogJointDensity_MPI_overSubLoci(paraVector, im, poptree, coldCh, nProcs, crr_procID);  
	    }
	}
      else if(lociInParallel ==0)
	{
	  logPosterior_newPara = (long double) log(computeJointDensity_MPI_overSubSample(paraVector, im, poptree, coldCh, nProcs, crr_procID));
	}
      else
	{
	  std::cout << "lociInParallel should be 1 or 0, but lociInParallel = " << lociInParallel <<"\n";
	}
      
      MPI::COMM_WORLD.Barrier();

      // YC 2/27/2014
      // All the processes share the same posterior densities and parameter values.
      if(logPosterior_newPara > posterior_atPrev.at(i))
	{
	  para_atCrr.row(i) = newPara;
	  posterior_atCrr.at(i) = logPosterior_newPara;	  
	}
      else if(isinf(logPosterior_newPara) && isinf(posterior_atPrev.at(i)) )
	{	  
	  // YC 08/07/2018
	  // If the current and new posteriors are negative infinity, the new parameter values are taken.
	  
	  para_atCrr.row(i) = newPara;
	  posterior_atCrr.at(i) = logPosterior_newPara;	  
	}
      else
	{
	  para_atCrr.row(i) = para_atPrev.row(i);
	  posterior_atCrr.at(i) = posterior_atPrev.at(i);
	} 
      /*
      if(crr_procID == 0)
	{	  
	  marginals.add(newPara, posterior_newPara);
	}
      */
    }

  MPI::COMM_WORLD.Barrier();
  para_atPrev = para_atCrr;
  posterior_atPrev = posterior_atCrr;
	
  if(crr_procID == 0)
    {	  
      std::vector<long double>::const_iterator iter_max, iter_min;
      iter_max = max_element(posterior_atCrr.begin(), posterior_atCrr.end());
      iter_min = min_element(posterior_atCrr.begin(), posterior_atCrr.end());
      logPosteriorMax = *iter_max;
      logPosteriorMin = *iter_min;
      
      /*
      unsigned int found_max = 0;
      ID_max = 0;
      while(ID_max < nParaVectors && found_max==0 )
	{
	  if(*iter_max == posterior_atCrr.at(ID_max))
	    found_max =1;
	  else
	    ID_max++;
	}    
      */
      // std::cout <<"logPosteriorMax = " << logPosteriorMax <<" logPosteriorMin = " << logPosteriorMin <<"\n";
    }
  MPI::COMM_WORLD.Barrier();
  MPI::COMM_WORLD.Bcast(&logPosteriorMax, 1, MPI_LONG_DOUBLE, 0);
  MPI::COMM_WORLD.Barrier();
  MPI::COMM_WORLD.Bcast(&logPosteriorMin, 1, MPI_LONG_DOUBLE, 0);
  MPI::COMM_WORLD.Barrier();

  
  return;
}
/*!Reset function using using a PatchData object.  This function is
  called for the inner-stopping criterion directly from the
  loop over mesh function in VertexMover.  For outer criterion,
  it is called from the reset function which takes a MeshSet object.
  This function prepares the object to be used by setting the initial
  values of some of the data members.  As examples, if needed, it resets
  the cpu timer to zero, the iteration counter to zero, and the
  initial and previous objective function values to the current
  objective function value for this patch.
  The return value for this function is similar to that of terminate().
  The function returns false if the checked criteria have not been
  satisfied, and true if they have been.  reset() only checks the
  GRADIENT_INF_NORM_ABSOLUTE, GRADIENT_L2_NORM_ABSOLUTE, and the
  QUALITY_IMPROVEMENT_ABSOLUTE criteria.  Checking these criteria
  allows the QualityImprover to skip the entire optimization if
  the initial mesh satisfies the appropriate conditions.
 */
void TerminationCriterion::reset_inner(PatchData &pd, OFEvaluator& obj_eval,
                                    MsqError &err)
{
  const unsigned long totalFlag = terminationCriterionFlag | cullingMethodFlag;
  
    // clear flag for BOUNDED_VERTEX_MOVEMENT
  vertexMovementExceedsBound = 0;
  
    // Use -1 to denote that this isn't initialized yet.
    // As all valid values must be >= 0.0, a negative
    // value indicates that it is uninitialized and is
    // always less than any valid value.
  maxSquaredMovement = -1;
  
    // Clear the iteration count.
  iterationCounter = 0;
  
    //reset the inner timer if needed
  if(totalFlag & CPU_TIME){
    mTimer.reset();
  }
   
    //GRADIENT
  currentGradInfNorm = initialGradInfNorm = 0.0;
  currentGradL2NormSquared = initialGradL2NormSquared = 0.0;
  if(totalFlag & GRAD_FLAGS)
  {
    if (!obj_eval.have_objective_function()) {
      MSQ_SETERR(err)("Error termination criteria set which uses objective "
                      "functions, but no objective function is available.",
                      MsqError::INVALID_STATE);   
      return;
    } 
    int num_vertices=pd.num_free_vertices();
    mGrad.resize( num_vertices );

      //get gradient and make sure it is valid
    bool b = obj_eval.evaluate(pd, currentOFValue, mGrad, err); MSQ_ERRRTN(err);
    if (!b) {
      MSQ_SETERR(err)("Initial patch is invalid for gradient computation.", 
                      MsqError::INVALID_STATE);
      return;
    } 

      //get the gradient norms
    if (totalFlag & (GRADIENT_INF_NORM_ABSOLUTE|GRADIENT_INF_NORM_RELATIVE))
    {
      currentGradInfNorm = initialGradInfNorm = Linf(mGrad);
      MSQ_DBGOUT_P0_ONLY(debugLevel) << par_string() << "  o Initial gradient Inf norm: " << " "
                                     << RPM(initialGradInfNorm) << std::endl;
    }  
      
    if (totalFlag & (GRADIENT_L2_NORM_ABSOLUTE|GRADIENT_L2_NORM_RELATIVE))
    {
      currentGradL2NormSquared = initialGradL2NormSquared = length_squared(mGrad);
      MSQ_DBGOUT_P0_ONLY(debugLevel) << par_string() << "  o Initial gradient L2 norm: " << " "
                                     << RPM(std::sqrt(initialGradL2NormSquared)) << std::endl;
    }  

      //the OFvalue comes for free, so save it
    previousOFValue=currentOFValue;
    initialOFValue=currentOFValue;
  }
  //find the initial objective function value if needed and not already
  //computed.  If we needed the gradient, we have the OF value for free.
  // Also, if possible, get initial OF value if writing plot file.  Solvers
  // often supply the OF value for subsequent iterations so by calculating
  // the initial value we can generate OF value plots.
  else if ((totalFlag & OF_FLAGS) || 
           (plotFile.is_open() && pd.num_free_vertices() && obj_eval.have_objective_function()))
  {
      //ensure the obj_ptr is not null
    if(!obj_eval.have_objective_function()){
      MSQ_SETERR(err)("Error termination criteria set which uses objective "
                      "functions, but no objective function is available.",
                      MsqError::INVALID_STATE);
      return;
    }
    
    bool b = obj_eval.evaluate(pd, currentOFValue, err); MSQ_ERRRTN(err);
    if (!b){
      MSQ_SETERR(err)("Initial patch is invalid for evaluation.",MsqError::INVALID_STATE);
      return;
    }
      //std::cout<<"\nReseting initial of value = "<<initialOFValue;
    previousOFValue=currentOFValue;
    initialOFValue=currentOFValue;
  }
  
  if (totalFlag & (GRAD_FLAGS|OF_FLAGS))
    MSQ_DBGOUT_P0_ONLY(debugLevel) << par_string() << "  o Initial OF value: " << " " << RPM(initialOFValue) << std::endl;
  
    // Store current vertex locations now, because we'll
    // need them later to compare the current movement with.
  if (totalFlag & VERTEX_MOVEMENT_RELATIVE)
  {
    if (initialVerticesMemento)
    {
      pd.recreate_vertices_memento( initialVerticesMemento, err );
    }
    else
    {
      initialVerticesMemento = pd.create_vertices_memento( err );
    }
    MSQ_ERRRTN(err);
    maxSquaredInitialMovement = DBL_MAX;
  }
  else {
    maxSquaredInitialMovement = 0;
  }
  
  if (terminationCriterionFlag & UNTANGLED_MESH) {
    globalInvertedCount = count_inverted( pd, err );
    //if (innerOuterType==TYPE_OUTER) MSQ_DBGOUT_P0_ONLY(debugLevel) << par_string() << "  o Num Inverted: " << " " << globalInvertedCount << std::endl;
    patchInvertedCount = 0;
    MSQ_ERRRTN(err);
  }

  if (timeStepFileType) {
      // If didn't already calculate gradient abive, calculate it now.
    if (!(totalFlag & GRAD_FLAGS)) {
      mGrad.resize( pd.num_free_vertices() );
      obj_eval.evaluate(pd, currentOFValue, mGrad, err);
      err.clear();
    }
    write_timestep( pd, mGrad.empty() ? 0 : arrptr(mGrad), err);
  }
    
  if (plotFile.is_open()) {
      // two newlines so GNU plot knows that we are starting a new data set
    plotFile << std::endl << std::endl;
      // write column headings as comment in data file
    plotFile << "#Iter\tCPU\tObjFunc\tGradL2\tGradInf\tMovement\tInverted" << std::endl;
      // write initial values
    plotFile << 0 
     << '\t' << mTimer.since_birth() 
     << '\t' << initialOFValue 
     << '\t' << std::sqrt( currentGradL2NormSquared ) 
     << '\t' << currentGradInfNorm 
     << '\t' << 0.0
     << '\t' << globalInvertedCount
     << std::endl;
  }
}
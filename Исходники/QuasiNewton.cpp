void QuasiNewton::optimize_vertex_positions( PatchData& pd, MsqError& err )
{
  TerminationCriterion& term = *get_inner_termination_criterion();
  OFEvaluator& func = get_objective_function_evaluator();
  
  const double sigma = 1e-4;
  const double beta0 = 0.25;
  const double beta1 = 0.80;
  const double tol1 = 1e-8;
  const double epsilon = 1e-10;

  double norm_r; //, norm_g;
  double alpha, beta;
  double obj, objn;

  size_t i;
  
    // Initialize stuff
  const size_t nn = pd.num_free_vertices();
  double a[QNVEC], b[QNVEC], r[QNVEC];
  for (i = 0; i < QNVEC; ++i)
    r[i] = 0;
  for (i = 0; i <= QNVEC; ++i) {
    v[i].clear();
    v[i].resize( nn, Vector3D(0.0) );
    w[i].clear();
    w[i].resize( nn, Vector3D(0.0) );
  }
  d.resize( nn );
  mHess.resize( nn );  //hMesh(mesh);

  bool valid = func.update( pd, obj, v[QNVEC], mHess, err ); MSQ_ERRRTN(err);
  if (!valid) {
    MSQ_SETERR(err)("Initial objective function is not valid", MsqError::INVALID_MESH);
    return;
  }

  while (!term.terminate()) {
    pd.recreate_vertices_memento( mMemento, err ); MSQ_ERRRTN(err);
    pd.get_free_vertex_coordinates( w[QNVEC] );

    x = v[QNVEC];
    for (i = QNVEC; i--; ) {
      a[i] = r[i] * inner( &(w[i][0]), arrptr(x), nn );
      plus_eq_scaled( arrptr(x), -a[i], &v[i][0], nn );
    }
     
    solve( arrptr(d), arrptr(x) );
  
    for (i = QNVEC; i--; ) {
      b[i] = r[i] * inner( &(v[i][0]), arrptr(d), nn );
      plus_eq_scaled( arrptr(d), a[i]-b[i], &(w[i][0]), nn );
    }
    
    alpha = -inner( &(v[QNVEC][0]), arrptr(d), nn );  /* direction is negated */
    if (alpha > 0.0) {
      MSQ_SETERR(err)("No descent.", MsqError::INVALID_MESH);
      return;
    }
   
    alpha *= sigma;
    beta = 1.0;
    
    pd.move_free_vertices_constrained( arrptr(d), nn, -beta, err ); MSQ_ERRRTN(err);
    valid = func.evaluate( pd, objn, v[QNVEC], err ); 
    if (err.error_code() == err.BARRIER_VIOLATED)             
      err.clear();  // barrier violated does not represent an actual error here
    MSQ_ERRRTN(err);
    if (!valid ||
        (obj - objn < -alpha*beta - epsilon &&
         length( &(v[QNVEC][0]), nn ) >= tol1)) {
      
      if (!valid)  // function not defined at trial point
        beta *= beta0;
      else  // unacceptable iterate
        beta *= beta1;
      
      for (;;) {
        if (beta < tol1) {
          pd.set_to_vertices_memento( mMemento, err ); MSQ_ERRRTN(err);
          MSQ_SETERR(err)("Newton step not good", MsqError::INTERNAL_ERROR);
          return;
        }
      
        pd.set_free_vertices_constrained( mMemento, arrptr(d), nn, -beta, err ); MSQ_ERRRTN(err);
        valid = func.evaluate( pd, objn, err );
        if (err.error_code() == err.BARRIER_VIOLATED)             
          err.clear();  // barrier violated does not represent an actual error here
        MSQ_ERRRTN(err);
        if (!valid) // function undefined at trial point
          beta *= beta0;
        else if (obj - objn < -alpha*beta - epsilon) // unacceptlable iterate
          beta *= beta1;
        else
          break;
      }
    }
    
    for (i = 0; i < QNVEC-1; ++i) {
      r[i] = r[i+1];
      w[i].swap( w[i+1] );
      v[i].swap( v[i+1] );
    }
    w[QNVEC-1].swap( w[0] );
    v[QNVEC-1].swap( v[0] );
    
    func.update( pd, obj, v[QNVEC], mHess, err ); MSQ_ERRRTN(err);
    norm_r = length_squared( &(v[QNVEC][0]), nn );
    //norm_g = sqrt(norm_r);

    // checks stopping criterion 
    term.accumulate_patch( pd, err ); MSQ_ERRRTN(err);
    term.accumulate_inner( pd, objn, &v[QNVEC][0], err ); MSQ_ERRRTN(err);
  }
}
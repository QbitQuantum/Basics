NonlinearCGUtils::ESolveReturn
NonlinearCG<Scalar>::doSolve(
  const Ptr<Thyra::VectorBase<Scalar> > &p_inout,
  const Ptr<ScalarMag> &g_opt_out,
  const Ptr<const ScalarMag> &g_reduct_tol_in,
  const Ptr<const ScalarMag> &g_grad_tol_in,
  const Ptr<const ScalarMag> &alpha_init_in,
  const Ptr<int> &numIters_out
  )
{

  typedef ScalarTraits<Scalar> ST;
  typedef ScalarTraits<ScalarMag> SMT;
  
  using Teuchos::null;
  using Teuchos::as;
  using Teuchos::tuple;
  using Teuchos::rcpFromPtr;
  using Teuchos::optInArg;
  using Teuchos::inOutArg;
  using GlobiPack::computeValue;
  using GlobiPack::PointEval1D;
  using Thyra::VectorSpaceBase;
  using Thyra::VectorBase;
  using Thyra::MultiVectorBase;
  using Thyra::scalarProd;
  using Thyra::createMember;
  using Thyra::createMembers;
  using Thyra::get_ele;
  using Thyra::norm;
  using Thyra::V_StV;
  using Thyra::Vt_S;
  using Thyra::eval_g_DgDp;
  typedef Thyra::Ordinal Ordinal;
  typedef Thyra::ModelEvaluatorBase MEB;
  namespace NCGU = NonlinearCGUtils;
  using std::max;

  // Validate input

  g_opt_out.assert_not_null();

  // Set streams

  const RCP<Teuchos::FancyOStream> out = this->getOStream();
  linesearch_->setOStream(out);

  // Determine what step constants will be computed

  const bool compute_beta_PR =
    (
      solverType_ == NCGU::NONLINEAR_CG_PR_PLUS
      ||
      solverType_ == NCGU::NONLINEAR_CG_FR_PR
      );

  const bool compute_beta_HS = (solverType_ == NCGU::NONLINEAR_CG_HS);

  //
  // A) Set up the storage for the algorithm
  //
  
  const RCP<DefaultPolyLineSearchPointEvaluator<Scalar> >
    pointEvaluator = defaultPolyLineSearchPointEvaluator<Scalar>();

  const RCP<UnconstrainedOptMeritFunc1D<Scalar> >
    meritFunc = unconstrainedOptMeritFunc1D<Scalar>(
      model_, paramIndex_, responseIndex_ );

  const RCP<const VectorSpaceBase<Scalar> >
    p_space = model_->get_p_space(paramIndex_),
    g_space = model_->get_g_space(responseIndex_);

  // Stoarge for current iteration
  RCP<VectorBase<Scalar> >
    p_k = rcpFromPtr(p_inout),        // Current solution for p
    p_kp1 = createMember(p_space),    // Trial point for p (in line search)
    g_vec = createMember(g_space),    // Vector (size 1) form of objective g(p) 
    g_grad_k = createMember(p_space), // Gradient of g DgDp^T
    d_k = createMember(p_space),      // Search direction
    g_grad_k_diff_km1 = null;         // g_grad_k - g_grad_km1 (if needed)

  // Storage for previous iteration
  RCP<VectorBase<Scalar> >
    g_grad_km1 = null, // Will allocate if we need it!
    d_km1 = null; // Will allocate if we need it!
  ScalarMag
    alpha_km1 = SMT::zero(),
    g_km1 = SMT::zero(),
    g_grad_km1_inner_g_grad_km1 = SMT::zero(),
    g_grad_km1_inner_d_km1 = SMT::zero();
  
  if (compute_beta_PR || compute_beta_HS) {
    g_grad_km1 = createMember(p_space);
    g_grad_k_diff_km1 = createMember(p_space);
  }
  
  if (compute_beta_HS) {
    d_km1 = createMember(p_space);
  }

  //
  // B) Do the nonlinear CG iterations
  //

  *out << "\nStarting nonlinear CG iterations ...\n";

  if (and_conv_tests_) {
    *out << "\nNOTE: Using AND of convergence tests!\n";
  }
  else {
    *out << "\nNOTE: Using OR of convergence tests!\n";
  }

  const Scalar alpha_init =
    ( !is_null(alpha_init_in) ? *alpha_init_in : alpha_init_ );
  const Scalar g_reduct_tol =
    ( !is_null(g_reduct_tol_in) ? *g_reduct_tol_in : g_reduct_tol_ );
  const Scalar g_grad_tol =
    ( !is_null(g_grad_tol_in) ? *g_grad_tol_in : g_grad_tol_ );

  const Ordinal globalDim = p_space->dim();

  bool foundSolution = false;
  bool fatalLinesearchFailure = false;
  bool restart = true;
  int numConsecutiveLineSearchFailures = 0;

  int numConsecutiveIters = 0;

  for (numIters_ = 0; numIters_ < maxIters_; ++numIters_, ++numConsecutiveIters) {

    Teuchos::OSTab tab(out);

    *out << "\nNonlinear CG Iteration k = " << numIters_ << "\n";

    Teuchos::OSTab tab2(out);

    //
    // B.1) Evaluate the point (on first iteration)
    //
    
    eval_g_DgDp(
      *model_, paramIndex_, *p_k, responseIndex_,
      numIters_ == 0 ? g_vec.ptr() : null, // Only on first iteration
      MEB::Derivative<Scalar>(g_grad_k, MEB::DERIV_MV_GRADIENT_FORM) );

    const ScalarMag g_k = get_ele(*g_vec, 0);
    // Above: If numIters_ > 0, then g_vec was updated in meritFunc->eval(...).

    //
    // B.2) Check for convergence
    //

    // B.2.a) ||g_k - g_km1|| |g_k + g_mag| <= g_reduct_tol

    bool g_reduct_converged = false;

    if (numIters_ > 0) {

      const ScalarMag g_reduct = g_k - g_km1;
      
      *out << "\ng_k - g_km1 = "<<g_reduct<<"\n";
      
      const ScalarMag g_reduct_err =
        SMT::magnitude(g_reduct / SMT::magnitude(g_k + g_mag_));
      
      g_reduct_converged = (g_reduct_err <= g_reduct_tol);
      
      *out << "\nCheck convergence: |g_k - g_km1| / |g_k + g_mag| = "<<g_reduct_err
           << (g_reduct_converged ? " <= " : " > ")
           << "g_reduct_tol = "<<g_reduct_tol<<"\n";
      
    }

    // B.2.b) ||g_grad_k|| g_mag <= g_grad_tol

    const Scalar g_grad_k_inner_g_grad_k = scalarProd<Scalar>(*g_grad_k, *g_grad_k);
    const ScalarMag norm_g_grad_k = ST::magnitude(ST::squareroot(g_grad_k_inner_g_grad_k));

    *out << "\n||g_grad_k|| = "<<norm_g_grad_k << "\n";

    const ScalarMag g_grad_err = norm_g_grad_k / g_mag_;

    const bool g_grad_converged = (g_grad_err <= g_grad_tol);

    *out << "\nCheck convergence: ||g_grad_k|| / g_mag = "<<g_grad_err
         << (g_grad_converged ? " <= " : " > ")
         << "g_grad_tol = "<<g_grad_tol<<"\n";

    // B.2.c) Convergence status
    
    bool isConverged = false;
    if (and_conv_tests_) {
      isConverged = g_reduct_converged && g_grad_converged;
    }
    else {
      isConverged = g_reduct_converged || g_grad_converged;
    }

    if (isConverged) {
      if (numIters_ < minIters_) {
        *out << "\nnumIters="<<numIters_<<" < minIters="<<minIters_
             << ", continuing on!\n";
      }
      else {
        *out << "\nFound solution, existing algorithm!\n";
        foundSolution = true;
      }
    }
    else {
      *out << "\nNot converged!\n";
    }
    
    if (foundSolution) {
      break;
    }

    //
    // B.3) Compute the search direction d_k
    //

    if (numConsecutiveIters == globalDim) {

      *out << "\nThe number of consecutive iterations exceeds the"
           << " global dimension so restarting!\n";

      restart = true;

    }

    if (restart) {

      *out << "\nResetting search direction back to steppest descent!\n";

      // d_k = -g_grad_k
      V_StV( d_k.ptr(), as<Scalar>(-1.0), *g_grad_k );

      restart = false;

    }
    else {
      
      // g_grad_k - g_grad_km1
      if (!is_null(g_grad_k_diff_km1)) {
        V_VmV( g_grad_k_diff_km1.ptr(), *g_grad_k, *g_grad_km1 );
      }

      // beta_FR = inner(g_grad_k, g_grad_k) / inner(g_grad_km1, g_grad_km1)
      const Scalar beta_FR =
        g_grad_k_inner_g_grad_k / g_grad_km1_inner_g_grad_km1;
      *out << "\nbeta_FR = " << beta_FR << "\n";
      // NOTE: Computing beta_FR is free so we might as well just do it!

      // beta_PR = inner(g_grad_k, g_grad_k - g_grad_km1) /
      //    inner(g_grad_km1, g_grad_km1)
      Scalar beta_PR = ST::zero();
      if (compute_beta_PR) {
        beta_PR =
          inner(*g_grad_k, *g_grad_k_diff_km1) / g_grad_km1_inner_g_grad_km1;
        *out << "\nbeta_PR = " << beta_PR << "\n";
      }

      // beta_HS = inner(g_grad_k, g_grad_k - g_grad_km1) /
      //    inner(g_grad_k - g_grad_km1, d_km1)
      Scalar beta_HS = ST::zero();
      if (compute_beta_HS) {
        beta_HS =
          inner(*g_grad_k, *g_grad_k_diff_km1) / inner(*g_grad_k_diff_km1, *d_km1);
        *out << "\nbeta_HS = " << beta_HS << "\n";
      }
      
      Scalar beta_k = ST::zero();
      switch(solverType_) {
        case NCGU::NONLINEAR_CG_FR: {
          beta_k = beta_FR;
          break;
        }
        case NCGU::NONLINEAR_CG_PR_PLUS: {
          beta_k = max(beta_PR, ST::zero());
          break;
        }
        case NCGU::NONLINEAR_CG_FR_PR: {
          // NOTE: This does not seem to be working :-(
          if (numConsecutiveIters < 2) {
            beta_k = beta_PR;
          }
          else if (beta_PR < -beta_FR)
            beta_k = -beta_FR;
          else if (ST::magnitude(beta_PR) <= beta_FR)
            beta_k = beta_PR;
          else // beta_PR > beta_FR
            beta_k = beta_FR;
        }
        case NCGU::NONLINEAR_CG_HS: {
          beta_k = beta_HS;
          break;
        }
        default:
          TEST_FOR_EXCEPT(true);
      }
      *out << "\nbeta_k = " << beta_k << "\n";

      // d_k = beta_k * d_last + -g_grad_k
      if (!is_null(d_km1))
        V_StV( d_k.ptr(), beta_k, *d_km1 );
      else
        Vt_S( d_k.ptr(), beta_k );
      Vp_StV( d_k.ptr(), as<Scalar>(-1.0), *g_grad_k );

    }
    
    //
    // B.4) Perform the line search
    //

    // B.4.a) Compute the initial step length

    Scalar alpha_k = as<Scalar>(-1.0);

    if (numIters_ == 0) {
      alpha_k = alpha_init;
    }
    else {
      if (alpha_reinit_) {
        alpha_k = alpha_init;
      }
      else {
        alpha_k = alpha_km1;
        // ToDo: Implement better logic from Nocedal and Wright for selecting
        // this step length after first iteration!
      }
    }

    // B.4.b) Perform the linesearch (computing updated quantities in process)

    pointEvaluator->initialize(tuple<RCP<const VectorBase<Scalar> > >(p_k, d_k)());

    ScalarMag g_grad_k_inner_d_k = ST::zero();

    // Set up the merit function to only compute the value
    meritFunc->setEvaluationQuantities(pointEvaluator, p_kp1, g_vec, null);

    PointEval1D<ScalarMag> point_k(ST::zero(), g_k);
    if (linesearch_->requiresBaseDeriv()) {
      g_grad_k_inner_d_k = scalarProd(*g_grad_k, *d_k);
      point_k.Dphi = g_grad_k_inner_d_k;
    }

    ScalarMag g_kp1 = computeValue(*meritFunc, alpha_k);
    // NOTE: The above call updates p_kp1 and g_vec as well!

    PointEval1D<ScalarMag> point_kp1(alpha_k, g_kp1);

    const bool linesearchResult = linesearch_->doLineSearch(
      *meritFunc, point_k, inOutArg(point_kp1), null );

    alpha_k = point_kp1.alpha;
    g_kp1 = point_kp1.phi;

    if (linesearchResult) {
      numConsecutiveLineSearchFailures = 0;
    }
    else {
      if (numConsecutiveLineSearchFailures==0) {
        *out << "\nLine search failure, resetting the search direction!\n";
        restart = true;
      }
      if (numConsecutiveLineSearchFailures==1) {
        *out << "\nLine search failure on last iteration also, terminating algorithm!\n";
        fatalLinesearchFailure = true;
      }
      ++numConsecutiveLineSearchFailures;
    }

    if (fatalLinesearchFailure) {
      break;
    }

    //
    // B.5) Transition to the next iteration
    //
    
    alpha_km1 = alpha_k;
    g_km1 = g_k;
    g_grad_km1_inner_g_grad_km1 = g_grad_k_inner_g_grad_k;
    g_grad_km1_inner_d_km1 = g_grad_k_inner_d_k;
    std::swap(p_k, p_kp1);
    if (!is_null(g_grad_km1))
      std::swap(g_grad_km1, g_grad_k);
    if (!is_null(d_km1))
      std::swap(d_k, d_km1);
    
#ifdef TEUCHOS_DEBUG
    // Make sure we compute these correctly before they are used!
    V_S(g_grad_k.ptr(), ST::nan());
    V_S(p_kp1.ptr(), ST::nan());
#endif

  }

  //
  // C) Final clean up
  //
  
  // Get the most current value of g(p)
  *g_opt_out = get_ele(*g_vec, 0);

  // Make sure that the final value for p has been copied in!
  V_V( p_inout, *p_k );

  if (!is_null(numIters_out)) {
    *numIters_out = numIters_;
  }

  if (numIters_ == maxIters_) {
    *out << "\nMax nonlinear CG iterations exceeded!\n";
  }
  
  if (foundSolution) {
    return NonlinearCGUtils::SOLVE_SOLUTION_FOUND;
  }
  else if(fatalLinesearchFailure) {
    return NonlinearCGUtils::SOLVE_LINSEARCH_FAILURE;
  }

  // Else, the max number of iterations was exceeded
  return NonlinearCGUtils::SOLVE_MAX_ITERS_EXCEEDED;

}
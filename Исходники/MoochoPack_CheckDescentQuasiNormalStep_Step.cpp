bool CheckDescentQuasiNormalStep_Step::do_step(
  Algorithm& _algo, poss_type step_poss, IterationPack::EDoStepType type
  ,poss_type assoc_step_poss
  )
{
  using BLAS_Cpp::no_trans;
  using AbstractLinAlgPack::dot;
  using LinAlgOpPack::V_MtV;

  NLPAlgo         &algo        = rsqp_algo(_algo);
  NLPAlgoState    &s           = algo.rsqp_state();
  NLP             &nlp         = algo.nlp();
  const Range1D   equ_decomp   = s.equ_decomp();

  EJournalOutputLevel olevel = algo.algo_cntr().journal_output_level();
  std::ostream& out = algo.track().journal_out();

  // print step header.
  if( static_cast<int>(olevel) >= static_cast<int>(PRINT_ALGORITHM_STEPS) ) {
    using IterationPack::print_algorithm_step;
    print_algorithm_step( algo, step_poss, type, assoc_step_poss, out );
  }
  
  const size_type
    nb = nlp.num_bounded_x();

  // Get iteration quantities
  IterQuantityAccess<VectorMutable>
    &c_iq   = s.c(),
    &Ypy_iq = s.Ypy();
  const Vector::vec_ptr_t
    cd_k = c_iq.get_k(0).sub_view(equ_decomp);
  const Vector
    &Ypy_k = Ypy_iq.get_k(0);
  
  value_type descent_c = -1.0;
  if( s.get_iter_quant_id( Gc_name ) != AlgorithmState::DOES_NOT_EXIST ) {
    if( static_cast<int>(olevel) >= static_cast<int>(PRINT_ALGORITHM_STEPS) ) {
      out	<< "\nGc_k exists; compute descent_c = c_k(equ_decomp)'*Gc_k(:,equ_decomp)'*Ypy_k ...\n";
    }
    const MatrixOp::mat_ptr_t
      Gcd_k = s.Gc().get_k(0).sub_view(Range1D(),equ_decomp);
    VectorSpace::vec_mut_ptr_t
      t = cd_k->space().create_member();
    V_MtV( t.get(), *Gcd_k, BLAS_Cpp::trans, Ypy_k );
    if( static_cast<int>(olevel) >= static_cast<int>(PRINT_VECTORS) ) {
      out	<< "\nGc_k(:,equ_decomp)'*Ypy_k =\n" << *t;
    }
    descent_c = dot( *cd_k, *t );
  }
  else {
    if( static_cast<int>(olevel) >= static_cast<int>(PRINT_ALGORITHM_STEPS) ) {
      out	<< "\nGc_k does not exist; compute descent_c = c_k(equ_decomp)'*FDGc_k(:,equ_decomp)'*Ypy_k "
        << "using finite differences ...\n";
    }
    VectorSpace::vec_mut_ptr_t
      t = nlp.space_c()->create_member();
    calc_fd_prod().calc_deriv_product(
      s.x().get_k(0),nb?&nlp.xl():NULL,nb?&nlp.xu():NULL
      ,Ypy_k,NULL,&c_iq.get_k(0),true,&nlp
      ,NULL,t.get()
      ,static_cast<int>(olevel) >= static_cast<int>(PRINT_ALGORITHM_STEPS) ? &out : NULL
      );
    if( static_cast<int>(olevel) >= static_cast<int>(PRINT_VECTORS) ) {
      out	<< "\nFDGc_k(:,equ_decomp)'*Ypy_k =\n" << *t->sub_view(equ_decomp);
    }
    descent_c = dot( *cd_k, *t->sub_view(equ_decomp) );
  }

  if( static_cast<int>(olevel) >= static_cast<int>(PRINT_ALGORITHM_STEPS) ) {
    out	<< "\ndescent_c = " << descent_c << std::endl;
  }

  if( descent_c > 0.0 ) { // ToDo: add some allowance for > 0.0 for finite difference errors!
    if( static_cast<int>(olevel) >= static_cast<int>(PRINT_ALGORITHM_STEPS) ) {
      out	<< "\nError, descent_c > 0.0; this is not a descent direction\n"
        << "Throw TestFailed and terminate the algorithm ...\n";
    }
    TEST_FOR_EXCEPTION(
      true, TestFailed
      ,"CheckDescentQuasiNormalStep_Step::do_step(...) : Error, descent for the decomposed constraints "
      "with respect to the quasi-normal step c_k(equ_decomp)'*FDGc_k(:,equ_decomp)'*Ypy_k = "
      << descent_c << " > 0.0;  This is not a descent direction!\n" );
  }

  return true;
}
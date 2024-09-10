void MatrixSymPosDefLBFGS::secant_update(
  VectorMutable* s, VectorMutable* y, VectorMutable* Bs
  )
{
  using AbstractLinAlgPack::BFGS_sTy_suff_p_d;
  using AbstractLinAlgPack::dot;
  using LinAlgOpPack::V_MtV;
  using Teuchos::Workspace;
  Teuchos::WorkspaceStore* wss = Teuchos::get_default_workspace_store().get();

  assert_initialized();

  // Check skipping the BFGS update
  const value_type
    sTy	      = dot(*s,*y);
  std::ostringstream omsg;
  if( !BFGS_sTy_suff_p_d(*s,*y,&sTy,&omsg,"MatrixSymPosDefLBFGS::secant_update(...)" ) ) {
    throw UpdateSkippedException( omsg.str() );	
  }

  try {

  // Update counters
  if( m_bar_ == m_ ) {
    // We are at the end of the storage so remove the oldest stored update
    // and move updates to make room for the new update.  This has to be done for the
    // the matrix to behave properly
    {for( size_type k = 1; k <= m_-1; ++k ) {
      S_->col(k) = S_->col(k+1);                            // Shift S.col() to the left
      Y_->col(k) = Y_->col(k+1);                            // Shift Y.col() to the left
      STY_.col(k)(1,m_-1) = STY_.col(k+1)(2,m_);            // Move submatrix STY(2,m-1,2,m-1) up and left
      STSYTY_.col(k)(k+1,m_) = STSYTY_.col(k+1)(k+2,m_+1);  // Move triangular submatrix STS(2,m-1,2,m-1) up and left
      STSYTY_.col(k+1)(1,k) = STSYTY_.col(k+2)(2,k+1);      // Move triangular submatrix YTY(2,m-1,2,m-1) up and left
    }}
    // ToDo: Create an abstract interface, call it MultiVectorShiftVecs, to rearrange S and Y all at once.
    // This will be important for parallel performance.
  }
  else {
    m_bar_++;
  }
  // Set the update vectors
  *S_->col(m_bar_) = *s;
  *Y_->col(m_bar_) = *y;

  // /////////////////////////////////////////////////////////////////////////////////////
  // Update S'Y
  //
  // Update the row and column m_bar
  //
  //	S'Y = 
  //
  //	[	s(1)'*y(1)		...		s(1)'*y(m_bar)		...		s(1)'*y(m_bar)		]
  //	[	.						.							.					] row
  //	[	s(m_bar)'*y(1)	...		s(m_bar)'*y(m_bar)	...		s(m_bar)'*y(m_bar)	] m_bar
  //	[	.						.							.					]
  //	[	s(m_bar)'*y(1)	...		s(m_bar)'*y(m_bar)	...		s(m_bar)'*y(m_bar)	]
  //
  //								col m_bar
  //
  // Therefore we set:
  //	(S'Y)(:,m_bar) =  S'*y(m_bar)
  //	(S'Y)(m_bar,:) =  s(m_bar)'*Y

  const multi_vec_ptr_t
    S = this->S(),
    Y = this->Y();

  VectorSpace::vec_mut_ptr_t
    t = S->space_rows().create_member();  // temporary workspace

  //	(S'Y)(:,m_bar) =  S'*y(m_bar)
  V_MtV( t.get(), *S, BLAS_Cpp::trans, *y );
  STY_.col(m_bar_)(1,m_bar_) = VectorDenseEncap(*t)();

  //	(S'Y)(m_bar,:)' =  Y'*s(m_bar)
  V_MtV( t.get(), *Y, BLAS_Cpp::trans, *s );
  STY_.row(m_bar_)(1,m_bar_) = VectorDenseEncap(*t)();

  // /////////////////////////////////////////////////////////////////
  // Update S'S
  //
  //	S'S = 
  //
  //	[	s(1)'*s(1)		...		symmetric					symmetric			]
  //	[	.						.							.					] row
  //	[	s(m_bar)'*s(1)	...		s(m_bar)'*s(m_bar)	...		symmetric			] m_bar
  //	[	.						.							.					]
  //	[	s(m_bar)'*s(1)	...		s(m_bar)'*s(m_bar)	...		s(m_bar)'*s(m_bar)	]
  //
  //								col m_bar
  //
  // Here we will update the lower triangular part of S'S.  To do this we
  // only need to compute:
  //		t = S'*s(m_bar) = { s(m_bar)' * [ s(1),..,s(m_bar),..,s(m_bar) ]  }'
  // then set the appropriate rows and columns of S'S.

  Workspace<value_type>   work_ws(wss,m_bar_);
  DVectorSlice                  work(&work_ws[0],work_ws.size());

  // work = S'*s(m_bar)
  V_MtV( t.get(), *S, BLAS_Cpp::trans, *s );
  work = VectorDenseEncap(*t)();

  // Set row elements
  STSYTY_.row(m_bar_+1)(1,m_bar_) = work;
  // Set column elements
  STSYTY_.col(m_bar_)(m_bar_+1,m_bar_+1) = work(m_bar_,m_bar_);

  // /////////////////////////////////////////////////////////////////////////////////////
  // Update Y'Y
  //
  // Update the row and column m_bar
  //
  //	Y'Y = 
  //
  //	[	y(1)'*y(1)		...		y(1)'*y(m_bar)		...		y(1)'*y(m_bar)		]
  //	[	.						.							.					] row
  //	[	symmetric		...		y(m_bar)'*y(m_bar)	...		y(m_bar)'*y(m_bar)	] m_bar
  //	[	.						.							.					]
  //	[	symmetric		...		symmetric			...		y(m_bar)'*y(m_bar)	]
  //
  //								col m_bar
  //
  // Here we will update the upper triangular part of Y'Y.  To do this we
  // only need to compute:
  //		t = Y'*y(m_bar) = { y(m_bar)' * [ y(1),..,y(m_bar),..,y(m_bar) ]  }'
  // then set the appropriate rows and columns of Y'Y.

  // work = Y'*y(m_bar)
  V_MtV( t.get(), *Y, BLAS_Cpp::trans, *y );
  work = VectorDenseEncap(*t)();

  // Set row elements
  STSYTY_.col(m_bar_+1)(1,m_bar_) = work;
  // Set column elements
  STSYTY_.row(m_bar_)(m_bar_+1,m_bar_+1) = work(m_bar_,m_bar_);

  // /////////////////////////////
  // Update gamma_k

  // gamma_k = s'*y / y'*y
  if(auto_rescaling_)
    gamma_k_ = STY_(m_bar_,m_bar_) / STSYTY_(m_bar_,m_bar_+1);

  // We do not initially update Q unless we have to form a matrix-vector
  // product later.
  
  Q_updated_ = false;
  num_secant_updates_++;

  }	//	end try
  catch(...) {
    // If we throw any exception the we should make the matrix uninitialized
    // so that we do not leave this object in an inconsistant state.
    n_ = 0;
    throw;
  }

}
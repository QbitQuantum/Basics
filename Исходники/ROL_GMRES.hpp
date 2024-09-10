  void run( Vector<Real> &x, LinearOperator<Real> &A, const Vector<Real> &b,
            LinearOperator<Real> &M, int &iter, int &flag ) {

    using Teuchos::RCP;
 
    flag = 0; 

    Real zero = 0.0;
    Real one =  1.0;

    if ( !isInitialized_ ) {
      r_  = b.clone();
      w_  = b.clone();
      z_  = x.clone();

      isInitialized_ = true;
    }

    Real itol  = std::sqrt(ROL_EPSILON<Real>()); 

    // Compute initial residual
    if(useInitialGuess_) {
    
      A.apply(*r_,x,itol);
      r_->scale(-1.0);
      r_->plus(b);       // r = b-Ax
 
    }
    else {
      x.zero();
      r_->set(b);
    }

    Real temp  = 0;

    std::vector<RCP<Vector<Real > > > V;
    std::vector<RCP<Vector<Real > > > Z;

    (*res_)[0] = r_->norm();
     
    Real rtol  = std::min(absTol_,relTol_*(*res_)[0]);

    V.push_back(b.clone());
    (V[0])->set(*r_);
    (V[0])->scale(one/(*res_)[0]);    

    (*s_)(0) = (*res_)[0];

    for( iter=0; iter<maxit_; ++iter ) {

//      std::cout << (*res_)[iter] << std::endl;

      if( useInexact_ ) {
        itol = rtol/(maxit_*(*res_)[iter]); 
      }

      Z.push_back(x.clone());

      // Apply right preconditioner
      M.applyInverse(*(Z[iter]),*(V[iter]),itol);

      // Apply operator
      A.apply(*w_,*(Z[iter]),itol);

      // Evaluate coefficients and orthogonalize using Gram-Schmidt
      for( int k=0; k<=iter; ++k ) {
        (*H_)(k,iter) = w_->dot(*(V[k]));
        w_->axpy( -(*H_)(k,iter), *(V[k]) );
      } 
     
      (*H_)(iter+1,iter) = w_->norm();

      V.push_back( b.clone() );
      (V[iter+1])->set(*w_);
      (V[iter+1])->scale(one/((*H_)(iter+1,iter)));

      // Apply Givens rotations
      for( int k=0; k<=iter-1; ++k ) {
        temp            =  (*cs_)(k)*(*H_)(k,iter) + (*sn_)(k)*(*H_)(k+1,iter);
        (*H_)(k+1,iter) = -(*sn_)(k)*(*H_)(k,iter) + (*cs_)(k)*(*H_)(k+1,iter); 
        (*H_)(k,iter)   = temp;
      } 

      // Form i-th rotation matrix
      if( (*H_)(iter+1,iter) == zero ) {
        (*cs_)(iter) = one;
        (*sn_)(iter) = zero;
      }
      else if ( std::abs((*H_)(iter+1,iter)) > std::abs((*H_)(iter,iter)) ) { 
        temp = (*H_)(iter,iter) / (*H_)(iter+1,iter);
        (*sn_)(iter) = one / std::sqrt( one + temp*temp );
        (*cs_)(iter) = temp*(*sn_)(iter); 
      }
      else {
        temp = (*H_)(iter+1,iter) / (*H_)(iter,iter);
        (*cs_)(iter) = one / std::sqrt( one + temp*temp );
        (*sn_)(iter) = temp*(*cs_)(iter);  
      }
     
      // Approximate residual norm
      temp               = (*cs_)(iter)*(*s_)(iter);
      (*s_)(iter+1)      = -(*sn_)(iter)*(*s_)(iter);
      (*s_)(iter)        = temp;
      (*H_)(iter,iter)   = (*cs_)(iter)*(*H_)(iter,iter) + (*sn_)(iter)*(*H_)(iter+1,iter);
      (*H_)(iter+1,iter) = zero;
      (*res_)[iter+1]    = std::abs((*s_)(iter+1));
  
      // Update solution approximation.
      const char uplo = 'U';
      const char trans = 'N';
      const char diag = 'N';
      const char normin = 'N';
      Real scaling = zero;
      int info = 0;
      *y_ = *s_;
      lapack_.LATRS(uplo, trans, diag, normin, iter+1, H_->values(), maxit_+1, y_->values(), &scaling, cnorm_->values(), &info);

      z_->zero();

      for( int k=0; k<=iter;++k ) {
        z_->axpy((*y_)(k),*(Z[k]));
      }

      if( (*res_)[iter+1] <= rtol ) {
        // Update solution vector
        x.plus(*z_);  
        break;
      }

      if(iter == maxit_) {
        flag = 1;
      }
    } // loop over iter

  }  
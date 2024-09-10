  // Run one step of nonlinear CG.
  virtual void run( Vector<Real> &s , const Vector<Real> &g, const Vector<Real> &x, Objective<Real> &obj ) {
    // Initialize vector storage
    if ( state_->iter == 0 ) {
      if ( state_->nlcg_type != NONLINEARCG_FLETCHER_REEVES && 
           state_->nlcg_type != NONLINEARCG_FLETCHER_CONJDESC ) {
        y_ = g.clone();
      }
      if ( state_->nlcg_type == NONLINEARCG_HAGAR_ZHANG ||
           state_->nlcg_type == NONLINEARCG_OREN_LUENBERGER ) {
        yd_ = g.clone();
      }
    }

    s.set(g.dual());

    if ((state_->iter % state_->restart) != 0) {
      Real beta = 0.0;
      switch(state_->nlcg_type) {

        case NONLINEARCG_HESTENES_STIEFEL: {
          y_->set(g);
          y_->axpy(-1.0, *(state_->grad[0]));
          beta =  - g.dot(*y_) / (state_->pstep[0]->dot(y_->dual()));
          beta = std::max(beta, 0.0);
          break;
          }

        case NONLINEARCG_FLETCHER_REEVES: {
          beta = g.dot(g) / (state_->grad[0])->dot(*(state_->grad[0]));
          break;
          }

        case NONLINEARCG_DANIEL: {
          Real htol = 0.0;
          obj.hessVec( *y_, *(state_->pstep[0]), x, htol );
          beta = - g.dot(*y_) / (state_->pstep[0])->dot(y_->dual());
          beta = std::max(beta, 0.0);
          break;
          }

        case NONLINEARCG_POLAK_RIBIERE: {
          y_->set(g);
          y_->axpy(-1.0, *(state_->grad[0]));
          beta = g.dot(*y_) / (state_->grad[0])->dot(*(state_->grad[0]));
          beta = std::max(beta, 0.0);
          break;
          }

        case NONLINEARCG_FLETCHER_CONJDESC: {
          beta =  g.dot(g) / (state_->pstep[0])->dot((state_->grad[0])->dual());
          break;
          }

        case NONLINEARCG_LIU_STOREY: {
          y_->set(g);
          y_->axpy(-1.0, *(state_->grad[0]));
          beta =  g.dot(*y_) / (state_->pstep[0])->dot((state_->grad[0])->dual());
          //beta = std::max(beta, 0.0); // Is this needed?  May need research.
          break;
          }

        case NONLINEARCG_DAI_YUAN: {
          y_->set(g);
          y_->axpy(-1.0, *(state_->grad[0]));
          beta =  - g.dot(g) / (state_->pstep[0])->dot(y_->dual());
          break;
          }

        case NONLINEARCG_HAGAR_ZHANG: {
          Real eta_0 = 1e-2; 
          y_->set(g);
          y_->axpy(-1.0, *(state_->grad[0]));
          yd_->set(*y_);
          Real mult = 2.0 * ( y_->dot(*y_) / (state_->pstep[0])->dot(y_->dual()) );
          yd_->axpy(-mult, (state_->pstep[0])->dual());
          beta = - yd_->dot(g) / (state_->pstep[0])->dot(y_->dual());
          Real eta = -1.0 / ((state_->pstep[0])->norm()*std::min(eta_0,(state_->grad[0])->norm()));
          beta = std::max(beta, eta);
          break;
          }

        case NONLINEARCG_OREN_LUENBERGER: {
          Real eta_0 = 1e-2; 
          y_->set(g);
          y_->axpy(-1.0, *(state_->grad[0]));
          yd_->set(*y_);
          Real mult = ( y_->dot(*y_) / (state_->pstep[0])->dot(y_->dual()) );
          yd_->axpy(-mult, (state_->pstep[0])->dual());
          beta = - yd_->dot(g) / (state_->pstep[0])->dot(y_->dual());
          Real eta = -1.0 / ((state_->pstep[0])->norm()*std::min(eta_0,(state_->grad[0])->norm()));
          beta = std::max(beta, eta);
          break;
          }

        default:
          TEUCHOS_TEST_FOR_EXCEPTION(!(isValidNonlinearCG(state_->nlcg_type)),
                          std::invalid_argument,
                          ">>> ERROR (ROL_NonlinearCG.hpp): Invalid nonlinear CG type in the 'run' method!");  
      }

      s.axpy(beta, *(state_->pstep[0]));
    }

    // Update storage.
    if (state_->iter == 0) {
      (state_->grad[0]) = g.clone();
      (state_->pstep[0]) = s.clone();
    }
    (state_->grad[0])->set(g);
    (state_->pstep[0])->set(s);
    state_->iter++;
  }
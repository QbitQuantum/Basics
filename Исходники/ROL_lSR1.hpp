    // Update Secant Approximation
    void updateStorage( const Vector<Real> &x,  const Vector<Real> &grad,
                        const Vector<Real> &gp, const Vector<Real> &s,
                        const Real snorm,       const int iter ) {
        // Get Generic Secant State
        Teuchos::RCP<SecantState<Real> >& state = Secant<Real>::get_state();
        if ( !isInitialized_ ) {
            state->iterate = x.clone();
            isInitialized_ = true;
        }

        state->iterate->set(x);
        state->iter = iter;
        Teuchos::RCP<Vector<Real> > gradDiff = grad.clone();
        gradDiff->set(grad);
        gradDiff->axpy(-1.0,gp);

        Real sy = s.dot(gradDiff->dual());
        if (updateIterate_ || state->current == -1) {
            if (state->current < state->storage-1) {
                state->current++;                               // Increment Storage
            }
            else {
                state->iterDiff.erase(state->iterDiff.begin()); // Remove first element of s list
                state->gradDiff.erase(state->gradDiff.begin()); // Remove first element of y list
                state->product.erase(state->product.begin());   // Remove first element of rho list
            }
            state->iterDiff.push_back(s.clone());
            state->iterDiff[state->current]->set(s);          // s=x_{k+1}-x_k
            state->gradDiff.push_back(grad.clone());
            state->gradDiff[state->current]->set(*gradDiff);  // y=g_{k+1}-g_k
            state->product.push_back(sy);                     // ys=1/rho
        }
        updateIterate_ = true;
    }
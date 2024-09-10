    ErrorCode EvalSet::evaluate_reverse(EvalFcn eval, JacobianFcn jacob, InsideFcn inside_f,
                                        const double *posn, const double *verts, const int nverts, 
                                        const int ndim, const double tol, double *work, 
                                        double *params, bool *inside) {
        // TODO: should differentiate between epsilons used for
        // Newton Raphson iteration, and epsilons used for curved boundary geometry errors
        // right now, fix the tolerance used for NR
      const double error_tol_sqr = tol*tol;
      CartVect *cvparams = reinterpret_cast<CartVect*>(params);
      const CartVect *cvposn = reinterpret_cast<const CartVect*>(posn);

        // initialize to center of element
      *cvparams = CartVect(-.4);
  
      CartVect new_pos;
        // evaluate that first guess to get a new position
      ErrorCode rval = (*eval)(cvparams->array(), verts, ndim, ndim, work, new_pos.array());
      if (MB_SUCCESS != rval) return rval;
      
        // residual is diff between old and new pos; need to minimize that
      CartVect res = new_pos - *cvposn;
      Matrix3 J;

      int iters=0;
        // while |res| larger than tol
      while (res % res > error_tol_sqr) {
        if(++iters>10) {
          if (inside) {
              // if we haven't converged but we're outside, that's defined as success
            *inside = (*inside_f)(params, ndim, tol);
            if (!(*inside)) return MB_SUCCESS;
          }
          return MB_FAILURE;
        }

          // get jacobian at current params
        rval = (*jacob)(cvparams->array(), verts, nverts, ndim, work, J[0]);
        double det = J.determinant();
        assert(det > std::numeric_limits<double>::epsilon());

          // new params tries to eliminate residual
        *cvparams -= J.inverse(1.0/det) * res;

          // get the new forward-evaluated position, and its difference from the target pt
        rval = (*eval)(params, verts, ndim, ndim, work, new_pos.array());
        if (MB_SUCCESS != rval) return rval;
        res = new_pos - *cvposn;
      }

      if (inside)
        *inside = (*inside_f)(params, ndim, tol);

      return MB_SUCCESS;
    }// Map::evaluate_reverse()
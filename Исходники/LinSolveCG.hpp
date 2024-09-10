    virtual void solve(int steps = 100000, T tolerance = (T)1e-6){
      cgfassert(this->mat->getWidth() == this->b->getSize());
      cgfassert(this->mat->getWidth() == this->mat->getHeight());
      cgfassert(this->mat->getWidth() == this->x->getSize());

      this->iterations = 0;

      for(int i=0;i<this->mat->getHeight();i++){
        (*C)[i] = (T)1.0/Sqrt(Fabs((*this->mat)[i][i]));
      }

      /*r = Ax*/
      spmv(*r, *(this->mat), *(this->x));

      /*r = b - r*/;
      Vector<T>::sub(*r, *(this->b), *r);

      /*w = C * r*/
      Vector<T>::mul(*w, *C, *r);

      /*v = C * w*/
      Vector<T>::mul(*v, *C, *w);

      /*s1 = w * w*/
      Vector<T>::mul(*scratch1, *w, *w);
      T alpha;

      /*alpha = sum(s1)*/
      alpha = scratch1->sum();

      int k=0;

      while(k<steps){
        /*s1 = v * v*/
        this->iterations++;
        Vector<T>::mul(*scratch1, *v, *v);
        T residual;

        residual = scratch1->sum();
        if(Sqrt(Fabs(residual)) < (tolerance*bnorm /*+ tolerance*/)){
          warning("CG::Success in %d iterations, %10.10e, %10.10e", k, residual, Sqrt(residual));
          return;
        }

        /*u = A*v*/
        spmv(*u, *(this->mat), *v);

        /*s1 = v * u*/
        Vector<T>::mul(*scratch1, *v, *u);
        T divider;

        /*divider = sum(s1)*/
        divider = scratch1->sum();

        T t = alpha/divider;

        /*x = x + t*v*/
        /*r = r - t*u*/
        /*w = C * r*/
        Vector<T>::mfadd(*(this->x),  t, *v, *(this->x));
        Vector<T>::mfadd(*r, -t, *u, *r);
        Vector<T>::mul  (*w, *C, *r);

        /*s1 = w*w*/
        Vector<T>::mul(*scratch1, *w, *w);

        /*beta = sum(s1)*/
        T beta = scratch1->sum();
#if 1
        if(beta < (tolerance*bnorm + tolerance)){
          T rl = r->length2();
          if(Sqrt(rl)<(tolerance*bnorm + tolerance)){
            warning("CG::Success in %d iterations, %10.10e, %10.10e", k, rl,
                    Sqrt(Fabs(rl)));
            return;
          }
        }
#endif

        T s = beta/alpha;

        /*s1 = C * w*/
        Vector<T>::mul(*scratch1, *C, *w);
        /*v = s1 + s * v*/
        Vector<T>::mfadd(*v, s, *v, *scratch1);
        alpha = beta;
        k++;
      }
      message("Unsuccesfull");
      throw new SolutionNotFoundException(__LINE__, __FILE__,
                                          "Number of iterations exceeded.");

    }
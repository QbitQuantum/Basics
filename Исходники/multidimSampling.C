   double operator() (double *x, double *p) {
      // 4 parameters
      int dim = X.GetNrows();
      int k = 0;
      for (int i = 0; i<dim; ++i) { X[i] = x[i] - p[k]; k++; }
      for (int i = 0; i<dim; ++i) {
         CovMat(i,i) = p[k]*p[k];
         k++;
      }
      for (int i = 0; i<dim; ++i) {
         for (int j = i+1; j<dim; ++j) {
            // p now are the correlations N(N-1)/2
               CovMat(i,j) = p[k]*sqrt(CovMat(i,i)*CovMat(j,j));
               CovMat(j,i) = CovMat(i,j);
               k++;
         }
      }
      if (debug) {
         X.Print();
         CovMat.Print();
      }

      double det = CovMat.Determinant();
      if (det <= 0) {
         Fatal("GausND","Determinant is <= 0 det = %f",det);
         CovMat.Print();
         return 0;
      }
      double norm = std::pow( 2. * TMath::Pi(), dim/2) * sqrt(det);
      // compute the gaussians
      CovMat.Invert();
      double fval  = std::exp( - 0.5 * CovMat.Similarity(X) )/ norm;

      if (debug) {
         std::cout << "det  " << det << std::endl;
         std::cout << "norm " << norm << std::endl;
         std::cout << "fval " << fval << std::endl;
      }

      return fval;
   }
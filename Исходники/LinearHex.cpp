    ErrorCode LinearHex::integrateFcn(const double *field, const double *verts, const int nverts, const int ndim, 
                                      const int num_tuples, double *work, double *result) 
    {
      assert(field && verts && num_tuples != -1);
      double tmp_result[8];
      ErrorCode rval = MB_SUCCESS;
      for (int i = 0; i < num_tuples; i++) result[i] = 0.0;
      CartVect x;
      Matrix3 J;
      for(unsigned int j1 = 0; j1 < LinearHex::gauss_count; ++j1) {
        x[0] = LinearHex::gauss[j1][1];
        double w1 = LinearHex::gauss[j1][0];
        for(unsigned int j2 = 0; j2 < LinearHex::gauss_count; ++j2) {
          x[1] = LinearHex::gauss[j2][1];
          double w2 = LinearHex::gauss[j2][0];
          for(unsigned int j3 = 0; j3 < LinearHex::gauss_count; ++j3) {
            x[2] = LinearHex::gauss[j3][1];
            double w3 = LinearHex::gauss[j3][0];
            rval = evalFcn(x.array(),field, ndim, num_tuples, NULL, tmp_result);
            if (MB_SUCCESS != rval) return rval;
            rval = jacobianFcn(x.array(), verts, nverts, ndim, work, J[0]);
            if (MB_SUCCESS != rval) return rval;
            double tmp_det =  w1*w2*w3*J.determinant();
            for (int i = 0; i < num_tuples; i++) result[i] += tmp_result[i]*tmp_det;
          }
        }
      }

      return MB_SUCCESS;
    }// LinearHex::integrate_vector()
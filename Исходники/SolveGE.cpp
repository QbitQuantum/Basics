    void SolveGEIP(const Matrix& A, Vector &x, const Vector& b)
    { 
      // Verify that the system is well-formed
      const int size = A.Rows();
      if ((A.Cols() != size) || (b.Size() != size)) {
        throw NonconformableShapesError();
      }

      // Prepare the augmented matrix
      Matrix aug(size, size+1, NaN());
      for (int i = 0; i < size; ++i) {
        aug.Col(i) = A.Col(i);
      }
      aug.Col(size) = b;
      
      // Go to town...
      eliminate(aug, size, fabs(1e-14));
      back_substitute(aug, size);

      x = aug.Col(size);
    }
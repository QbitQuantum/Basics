    // Effects:
    // 4 things are set.
    // 1) prediction_error
    // 2) scaled_prediction_error
    // 3) forecast_precision_log_determinant
    // 4) kalman_gain
    void Marginal::high_dimensional_update(
        const Vector &observation,
        const Selector &observed,
        const SparseKalmanMatrix &transition,
        const SparseKalmanMatrix &observation_coefficient_subset) {
      Vector observed_subset = observed.select(observation);
      set_prediction_error(observed_subset
                           - observation_coefficient_subset * state_mean());

      // At this point the Kalman recursions compute the forecast precision Finv
      // and its log determinant.  However, we can get rid of the forecast
      // precision matrix, and replace it with the scaled error = Finv *
      // prediction_error.
      //
      // To evaluate the normal likelihood, we need the quadratic form:
      //   error * Finv * error == error.dot(scaled_error).
      // We also need the log determinant of Finv.
      //
      // The forecast_precision can be computed using a version of the binomial
      // inverse theorem:
      //
      //  (A + UBV).inv =
      //    A.inv - A.inv * U * (I + B * V * Ainv * U).inv * B * V * Ainv.
      //
      // When applied to F = H + Z P Z' the theorem gives
      //
      //   Finv = Hinv - Hinv * Z * (I + P Z' Hinv Z).inv * P * Z' * Hinv
      //
      // This helps because H is diagonal.  The only matrix that needs to be
      // inverted is (I + PZ'HinvZ), which is a state x state matrix.
      // 
      // We don't compute Finv directly, we compute Finv * prediction_error.

      // observation_precision refers to the precision of the observed subset.
      DiagonalMatrix observation_precision(observed.select(
          1.0 / model_->observation_variance(time_index()).diag()));

      // Set inner_matrix to I + P * Z' * Hinv * Z
      SpdMatrix ZTZ = observation_coefficient_subset.inner(
          observation_precision.diag());
      // Note: the product of two SPD matrices need not be symmetric.
      Matrix inner_matrix = state_variance() * ZTZ;
      inner_matrix.diag() += 1.0;
      LU inner_lu(inner_matrix);
      
      // inner_inv_P is inner.inv() * state_variance.  This matrix need not be
      // symmetric.
      Matrix inner_inv_P = inner_lu.solve(state_variance());
      
      Matrix HinvZ = observation_precision *
          observation_coefficient_subset.dense();
      set_scaled_prediction_error(
          observation_precision * prediction_error()
          - HinvZ * inner_inv_P * HinvZ.Tmult(prediction_error()));
      
      // The log determinant of F.inverse is the negative log of det(H + ZPZ').
      // That determinant can be computed using the "matrix determinant lemma,"
      // which says det(A + UV') = det(I + V' * A.inv * U) * det(A)
      //
      // https://en.wikipedia.org/wiki/Matrix_determinant_lemma#Generalization
      //
      // With F = H + ZPZ', and setting A = H, U = Z, V' = PZ'.
      // Then det(F) = det(I + PZ' * Hinv * Z) * det(H)
      set_forecast_precision_log_determinant(
          observation_precision.logdet() - inner_lu.logdet());

      // The Kalman gain is:  K = T * P * Z' * Finv.
      // Substituting the expression for Finv from above gives
      //
      // K = T * P * Z' *
      //   (Hinv - Hinv * Z * (I + P Z' Hinv Z).inv * P * Z' * Hinv)
      Matrix ZtHinv = HinvZ.transpose();
      set_kalman_gain(transition * state_variance() *
                      (ZtHinv - ZTZ * inner_inv_P * ZtHinv));
    }
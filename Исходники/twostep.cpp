/**
 * Compute the scale factor and bias associated with a vector observer
 * according to the equation:
 * B_k = (I_{3x3} + D)^{-1} \times (O^T A_k H_k + b + \epsilon_k)
 * where k is the sample index,
 *       B_k is the kth measurement
 *       I_{3x3} is a 3x3 identity matrix
 *       D is a 3x3 symmetric matrix of scale factors
 *       O is the orthogonal alignment matrix
 *       A_k is the attitude at the kth sample
 *       b is the bias in the global reference frame
 *       \epsilon_k is the noise at the kth sample
 *
 * After computing the scale factor and bias matrices, the optimal estimate is
 * given by
 * \tilde{B}_k = (I_{3x3} + D)B_k - b
 *
 * This implementation makes the assumption that \epsilon is a constant white,
 * gaussian noise source that is common to all k.  The misalignment matrix O
 * is not computed.
 *
 * @param bias[out] The computed bias, in the global frame
 * @param scale[out] The computed scale factor matrix, in the sensor frame.
 * @param samples[in] An array of measurement samples.
 * @param n_samples The number of samples in the array.
 * @param referenceField The magnetic field vector at this location.
 * @param noise The one-sigma squared standard deviation of the observed noise
 * in the sensor.
 */
void twostep_bias_scale(Vector3f & bias,
                        Matrix3f & scale,
                        const Vector3f samples[],
                        const size_t n_samples,
                        const Vector3f & referenceField,
                        const float noise)
{
    // Define L_k by eq 51 for k = 1 .. n_samples
    Matrix<double, Dynamic, 9> fullSamples(n_samples, 9);
    // \hbar{L} by eq 52, simplified by observing that the common noise term
    // makes this a simple average.
    Matrix<double, 1, 9> centerSample = Matrix<double, 1, 9>::Zero();
    // Define the sample differences z_k by eq 23 a)
    double sampleDeltaMag[n_samples];
    // The center value \hbar{z}
    double sampleDeltaMagCenter = 0;
    // The squared norm of the reference vector
    double refSquaredNorm = referenceField.squaredNorm();

    for (size_t i = 0; i < n_samples; ++i) {
        fullSamples.row(i) << 2 * samples[i].transpose().cast<double>(),
            -(samples[i][0] * samples[i][0]),
            -(samples[i][1] * samples[i][1]),
            -(samples[i][2] * samples[i][2]),
            -2 * (samples[i][0] * samples[i][1]),
            -2 * (samples[i][0] * samples[i][2]),
            -2 * (samples[i][1] * samples[i][2]);

        centerSample += fullSamples.row(i);

        sampleDeltaMag[i]     = samples[i].squaredNorm() - refSquaredNorm;
        sampleDeltaMagCenter += sampleDeltaMag[i];
    }
    sampleDeltaMagCenter /= n_samples;
    centerSample /= n_samples;

    // Define \tilde{L}_k for k = 0 .. n_samples
    Matrix<double, Dynamic, 9> centeredSamples(n_samples, 9);
    // Define \tilde{z}_k for k = 0 .. n_samples
    double centeredMags[n_samples];
    // Compute the term under the summation of eq 57a
    Matrix<double, 9, 1> estimateSummation = Matrix<double, 9, 1>::Zero();
    for (size_t i = 0; i < n_samples; ++i) {
        centeredSamples.row(i) = fullSamples.row(i) - centerSample;
        centeredMags[i] = sampleDeltaMag[i] - sampleDeltaMagCenter;
        estimateSummation += centeredMags[i] * centeredSamples.row(i).transpose();
    }
    estimateSummation /= noise;

    // By eq 57b
    Matrix<double, 9, 9> P_theta_theta_inv = (1.0f / noise) *
                                             centeredSamples.transpose() * centeredSamples;

#ifdef PRINTF_DEBUGGING
    SelfAdjointEigenSolver<Matrix<double, 9, 9> > eig(P_theta_theta_inv);
    std::cout << "P_theta_theta_inverse: \n" << P_theta_theta_inv << "\n\n";
    std::cout << "P_\\tt^-1 eigenvalues: " << eig.eigenvalues().transpose()
              << "\n";
    std::cout << "P_\\tt^-1 eigenvectors:\n" << eig.eigenvectors() << "\n";
#endif

    // The current value of the estimate.  Initialized to \tilde{\theta}^*
    Matrix<double, 9, 1> estimate;
    // By eq 57a
    P_theta_theta_inv.ldlt().solve(estimateSummation, &estimate);

    // estimate i+1 = estimate_i - Fisher^{-1}(at estimate_i)*gradient(theta)
    // Fisher^{-1} = \tilde{Fisher}^-1 + \hbar{Fisher}^{-1}
    size_t count = 0;
    double eta   = 10000;
    while (count++ < 200 && eta > 1e-8) {
        static bool warned = false;
        if (hasNaN(estimate)) {
            std::cout << "WARNING: found NaN at time " << count << "\n";
            warned = true;
        }
#if 0
        SelfAdjointEigenSolver<Matrix3d> eig_E(E_theta(estimate));
        Vector3d S = eig_E.eigenvalues();
        Vector3d W; W << -1 + sqrt(1 + S.coeff(0)),
            -1 + sqrt(1 + S.coeff(1)),
            -1 + sqrt(1 + S.coeff(2));
        scale = (eig_E.eigenvectors() * W.asDiagonal() *
                 eig_E.eigenvectors().transpose()).cast<float>();

        (Matrix3f::Identity() + scale).ldlt().solve(
            estimate.start<3>().cast<float>(), &bias);
        std::cout << "\n\nestimated bias: " << bias.transpose()
                  << "\nestimated scale:\n" << scale;
#endif

        Matrix<double, 1, 9> db_dtheta = dnormb_dtheta(estimate);

        Matrix<double, 9, 1> dJ_dtheta = ::dJ_dtheta(centerSample,
                                                     sampleDeltaMagCenter,
                                                     estimate,
                                                     db_dtheta,
                                                     -3 * noise,
                                                     noise / n_samples);

        // Eq 59, with reused storage on db_dtheta
        db_dtheta = centerSample - db_dtheta;
        Matrix<double, 9, 9> scale = P_theta_theta_inv +
                                     (double(n_samples) / noise) * db_dtheta.transpose() * db_dtheta;

        // eq 14b, mutatis mutandis (grumble, grumble)
        Matrix<double, 9, 1> increment;
        scale.ldlt().solve(dJ_dtheta, &increment);
        estimate -= increment;
        eta = increment.dot(scale * increment);
        std::cout << "eta: " << eta << "\n";
    }
    std::cout << "terminated at eta = " << eta
              << " after " << count << " iterations\n";

    if (!isnan(eta) && !isinf(eta)) {
        // Transform the estimated parameters from [c | E] back into [b | D].
        // See eq 63-65
        SelfAdjointEigenSolver<Matrix3d> eig_E(E_theta(estimate));
        Vector3d S = eig_E.eigenvalues();
        Vector3d W; W << -1 + sqrt(1 + S.coeff(0)),
            -1 + sqrt(1 + S.coeff(1)),
            -1 + sqrt(1 + S.coeff(2));
        scale = (eig_E.eigenvectors() * W.asDiagonal() *
                 eig_E.eigenvectors().transpose()).cast<float>();

        (Matrix3f::Identity() + scale).ldlt().solve(
            estimate.start<3>().cast<float>(), &bias);
    } else {
        // return nonsense data.  The eigensolver can fall ingo
        // an infinite loop otherwise.
        // TODO: Add error code return
        scale = Matrix3f::Ones() * std::numeric_limits<float>::quiet_NaN();
        bias  = Vector3f::Zero();
    }
}
  bool SlaterSet::initialize()
  {
    m_normalized.resize(m_overlap.cols(), m_overlap.rows());

    SelfAdjointEigenSolver<MatrixXd> s(m_overlap);
    MatrixXd p = s.eigenvectors();
    MatrixXd m = p * s.eigenvalues().cwise().inverse().cwise().sqrt().asDiagonal() * p.inverse();
    m_normalized = m * m_eigenVectors;

    if (!(m_overlap*m*m).isIdentity())
      qDebug() << "Identity test FAILED - do you need a newer version of Eigen?";
//    std::cout << m_normalized << std::endl << std::endl;
//    std::cout << s.eigenvalues() << std::endl << std::endl;
//    std::cout << m_overlap << std::endl << std::endl;
//    std::cout << s.eigenvalues().minCoeff() << ' ' << s.eigenvalues().maxCoeff() << std::endl << std::endl;

    m_factors.resize(m_zetas.size());
    m_PQNs = m_pqns;
    // Calculate the normalizations of the orbitals
    for (unsigned int i = 0; i < m_zetas.size(); ++i) {
      switch (m_slaterTypes[i]) {
        case S:
          m_factors[i] = pow(2.0 * m_zetas[i], m_pqns[i] + 0.5) *
                         sqrt(1.0 / (4.0*M_PI) / factorial(2*m_pqns[i]));
          m_PQNs[i] -= 1;
          break;
        case PX:
        case PY:
        case PZ:
          m_factors[i] = pow(2.0 * m_zetas[i], m_pqns[i] + 0.5) *
                         sqrt(3.0 / (4.0*M_PI) / factorial(2*m_pqns[i]));
          m_PQNs[i] -= 2;
          break;
        case X2:
          m_factors[i] = 0.5 * pow(2.0 * m_zetas[i], m_pqns[i] + 0.5) *
                         sqrt(15.0 / (4.0*M_PI) / factorial(2*m_pqns[i]));
          m_PQNs[i] -= 3;
          break;
        case XZ:
          m_factors[i] = pow(2.0 * m_zetas[i], m_pqns[i] + 0.5) *
                         sqrt(15.0 / (4.0*M_PI) / factorial(2*m_pqns[i]));
          m_PQNs[i] -= 3;
          break;
        case Z2:
          m_factors[i] = (0.5/sqrt(3.0)) * pow(2.0 * m_zetas[i], m_pqns[i] + 0.5) *
                         sqrt(15.0 / (4.0*M_PI) / factorial(2*m_pqns[i]));
          m_PQNs[i] -= 3;
          break;
        case YZ:
        case XY:
          m_factors[i] = pow(2.0 * m_zetas[i], m_pqns[i] + 0.5) *
                         sqrt(15.0 / (4.0*M_PI) / factorial(2*m_pqns[i]));
          m_PQNs[i] -= 3;
          break;
        default:
         qDebug() << "Orbital" << i << "not handled, type" << m_slaterTypes[i];
      }
    }
    // Convert the exponents into Angstroms
    for (unsigned int i = 0; i < m_zetas.size(); ++i)
      m_zetas[i] = m_zetas[i] / BOHR_TO_ANGSTROM;

    m_initialized = true;

    return true;
  }
void testDHomogTransInv(int ntests, bool check) {
  Isometry3d T;
  std::default_random_engine generator;
  for (int testnr = 0; testnr < ntests; testnr++) {
    Vector4d q = uniformlyRandomQuat(generator);
//    T = Quaterniond(q(0), q(1), q(2), q(3)) * Translation3d(Vector3d::Random());
    T = Quaterniond(q(0), q(1), q(2), q(3));

    const int nv = 6;
    const int nq = 7;

    auto S = Matrix<double, 6, Dynamic>::Random(6, nv).eval();
    auto qdot_to_v = MatrixXd::Random(nv, nq).eval();

    auto dT = dHomogTrans(T, S, qdot_to_v).eval();
    auto dTInv = dHomogTransInv(T, dT);
    volatile auto vol = dTInv;

    if (check) {
      auto dTInvInv = dHomogTransInv(T.inverse(), dTInv);

      if (!dT.matrix().isApprox(dTInvInv.matrix(), 1e-10)) {
        std::cout << "dTInv:\n" << dTInv << "\n\n";
        std::cout << "dT:\n" << dT << "\n\n";
        std::cout << "dTInvInv:\n" << dTInvInv << "\n\n";
        std::cout << "dTInvInv - dT:\n" << dTInvInv - dT << "\n\n";

        throw std::runtime_error("wrong");
      }
    }
  }
}
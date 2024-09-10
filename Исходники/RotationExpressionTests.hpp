  static void testJacobian(const ExpressionTester<RotationExpression> & expressionTester) {
    auto rotExp = expressionTester.getExp();
    for (int i = 0; i < 3; i++) {
      Eigen::Vector3d p;
      p.setZero();
      p(i) = 1;
      RotationExpressionNodeFunctor functor(rotExp, p);

      sm::eigen::NumericalDiff<RotationExpressionNodeFunctor> numdiff(functor, expressionTester.getEps());

      /// Discern the size of the jacobian container
      Eigen::Matrix3d C = rotExp.toRotationMatrix();
      JacobianContainer Jc(3);
      rotExp.evaluateJacobians(Jc);
      Eigen::Matrix3d Cp_cross = sm::kinematics::crossMx(C * p);
      Jc.applyChainRule(Cp_cross);

      Eigen::VectorXd dp(Jc.cols());
      dp.setZero();
      Eigen::MatrixXd Jest = numdiff.estimateJacobian(dp);

      auto JcM = Jc.asSparseMatrix();
      sm::eigen::assertNear(Jc.asSparseMatrix(), Jest, expressionTester.getTolerance(), SM_SOURCE_FILE_POS, static_cast<std::stringstream&>(std::stringstream("Testing the RotationExpression's Jacobian (column=") << i <<")").str());
      if (expressionTester.getPrintResult()) {
        std::cout << "Jest=\n" << Jest << std::endl;
        std::cout << "Jc=\n" << JcM << std::endl;
      }
    }
  }
// Transform VectorValues into valid Rot3
Values normalizeRelaxedRotations(const VectorValues& relaxedRot3) {
  gttic(InitializePose3_computeOrientationsChordal);

  Matrix ppm = Matrix::Zero(3,3); // plus plus minus
  ppm(0,0) = 1; ppm(1,1) = 1; ppm(2,2) = -1;

  Values validRot3;
  BOOST_FOREACH(const VectorValues::value_type& it, relaxedRot3) {
    Key key = it.first;
    if (key != keyAnchor) {
      const Vector& rotVector = it.second;
      Matrix3 rotMat;
      rotMat(0,0) = rotVector(0); rotMat(0,1) = rotVector(1); rotMat(0,2) = rotVector(2);
      rotMat(1,0) = rotVector(3); rotMat(1,1) = rotVector(4); rotMat(1,2) = rotVector(5);
      rotMat(2,0) = rotVector(6); rotMat(2,1) = rotVector(7); rotMat(2,2) = rotVector(8);

      Matrix U, V; Vector s;
      svd(rotMat, U, s, V);
      Matrix3 normalizedRotMat = U * V.transpose();

      //      std::cout << "rotMat \n" << rotMat << std::endl;
      //      std::cout << "U V' \n" << U * V.transpose() << std::endl;
      //      std::cout << "V \n" << V << std::endl;

      if(normalizedRotMat.determinant() < 0)
        normalizedRotMat = U * ppm * V.transpose();

      Rot3 initRot = Rot3(normalizedRotMat);
      validRot3.insert(key, initRot);
    }
  }
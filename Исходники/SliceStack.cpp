//                      left             right              back          front
// constantCoord => 0: (-0.5, _, _), 1: (0.5, _, _), 2: (_, -0.5, _), 3: (_, 0.5, _)
// also include the minimum and maximum values in the non-constant coord (mn, mx)
// and the minimum and maximum values for this coord (o_mn, o_mx)
void SliceStack::triangulateSide(int constantCoord,
                                 double fixedCoord,
                                 vector<Eigen::Vector3d> &verts,
                                 Eigen::MatrixXd &V, Eigen::MatrixXi &F) {
  // Compute the mid z-coord.
  sort(verts.begin(), verts.end(), customSortByZ);

  double mid = 0;
  for (const auto & v : verts) {
    mid += v(2);
  }
  mid /= verts.size();

  vector<Eigen::Vector3d> topV;
  vector<Eigen::Vector3d> botV;

  // Fill the botV and topV vectors
  for (int i = 0; i < verts.size(); ++i) {
    if (verts[i][2] < mid)
      botV.push_back(verts[i]);
    else
      topV.push_back(verts[i]);
  }

  // Set the z-scaling as the distance between the top and the bottom vert
  double z_spacing = verts.back()(2) - verts.front()(2);

  // If the constant coord is y, sort by x direction.
  if (constantCoord == GLOBAL::FRONT || constantCoord == GLOBAL::BACK) {
    sort(botV.begin(), botV.end(), customSortByX);
    sort(topV.rbegin(), topV.rend(), customSortByX); // backwards
  }
  // otherwise, sort by y direction.
  else {
    sort(botV.begin(), botV.end(), customSortByY);
    sort(topV.rbegin(), topV.rend(), customSortByY); // backwards
  }

  Eigen::MatrixXd inputV(verts.size() + GLOBAL::EXTRA * 2, 2);
  Eigen::MatrixXi inputE(verts.size() + GLOBAL::EXTRA * 2, 2);

  int offset = 0;

  // Add bottom points, from left to right
  for (int i = 0; i < botV.size(); ++i) {
    if (constantCoord == GLOBAL::LEFT || constantCoord == GLOBAL::RIGHT) {
      inputV.row(offset++) << botV[i][1], botV[i][2];
    } else {
      inputV.row(offset++) << botV[i][0], botV[i][2];
    }
  }

  // Add right points
  // Get the vector that extends from the top corner to the bottom corner.
  Eigen::Vector3d bot2Top = topV.front() - botV.back(); // top is sorted backwards
  for (int i = 1; i <= GLOBAL::EXTRA; ++i) {
    auto shift_by = botV.back() + bot2Top * i / (GLOBAL::EXTRA + 1);
    if (constantCoord == GLOBAL::LEFT || constantCoord == GLOBAL::RIGHT)
      inputV.row(offset++) << shift_by(1), shift_by(2);
    else
      inputV.row(offset++) << shift_by(0), shift_by(2);
  }

  // Add top points, from right to left
  for (int i = 0; i < topV.size(); ++i) {
    if (constantCoord == GLOBAL::LEFT || constantCoord == GLOBAL::RIGHT)
      inputV.row(offset++) << topV[i][1], topV[i][2];
    else
      inputV.row(offset++) << topV[i][0], topV[i][2];
  }

  // Add left points
  Eigen::Vector3d top2Bot = botV.front() - topV.back();
  for (int i = 1; i <= GLOBAL::EXTRA; ++i) {
    auto shift_by = topV.back() + top2Bot * i / (GLOBAL::EXTRA + 1);
    if (constantCoord == GLOBAL::LEFT || constantCoord == GLOBAL::RIGHT)
      inputV.row(offset++) << shift_by(1), shift_by(2);
    else
      inputV.row(offset++) << shift_by(0), shift_by(2);
  }

  // Add all the new edges.
  for (int i = 0; i < inputV.rows(); ++i) {
    inputE.row(i) << i, (i + 1) % (inputV.rows());
  }

  Eigen::MatrixXd tmpV;
  Helpers::triangulate(inputV, inputE, tmpV, F);

  // 3D-ifying the slice.
  V.resize(tmpV.rows(), 3);
  for (int i = 0; i < tmpV.rows(); ++i) {
    switch(constantCoord) {
      case GLOBAL::LEFT : V.row(i) << fixedCoord, tmpV(i, 0), tmpV(i, 1);
                          break;
      case GLOBAL::RIGHT : V.row(i) << fixedCoord, tmpV(i, 0), tmpV(i, 1);
                           break;
      case GLOBAL::FRONT : V.row(i) << tmpV(i, 0), fixedCoord, tmpV(i, 1);
                           break;
      case GLOBAL::BACK : V.row(i) << tmpV(i, 0), fixedCoord, tmpV(i, 1);
                          break;
    }
  }

  // Find the projection to map the corners back.
  Eigen::MatrixXd XT(3, 3);
  XT << V.row(0),
        V.row(botV.size() - 1),
        V.row(botV.size() + GLOBAL::EXTRA);

  Eigen::MatrixXd X = XT.transpose();

  Eigen::MatrixXd B(3, 3);
  B.col(0) << botV[0];
  B.col(1) << botV[botV.size()-1];
  B.col(2) << topV[0];

  Eigen::MatrixXd A = B * X.inverse();

  V = (A * V.transpose()).transpose();
}
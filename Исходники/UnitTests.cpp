void linearTMatrixTest(StrainLin * ene)
{
  ElementRegGrid * grid = new ElementRegGrid(1, 1, 1);
  MaterialQuad * material = new MaterialQuad(ene);
  grid->m.push_back(material);
  grid->x[1][0] += 0.1f;
  grid->x[3][1] += 0.2f;
  MatrixXf K = grid->getStiffness();

  //linear material stiffness
  ElementHex * ele = (ElementHex*)grid->e[0];
  const Quadrature & q = Quadrature::Gauss2;
  Eigen::MatrixXf Ka = Eigen::MatrixXf::Zero(3 * ele->nV(), 3 * ele->nV());
  Eigen::MatrixXf E = ene->EMatrix();
  Eigen::VectorXf U = Eigen::VectorXf::Zero(3 * ele->nV());

  for (int ii = 0; ii < ele->nV(); ii++){
    for (int jj = 0; jj < 3; jj++){
      U[3 * ii + jj] = grid->x[ii][jj] - grid->X[ii][jj];
    }
  }

  for (unsigned int ii = 0; ii < q.x.size(); ii++){
    Eigen::MatrixXf B = ele->BMatrix(q.x[ii], grid->X);
    Eigen::MatrixXf ss = E*B*U;
    //std::cout <<"sigma:\n"<< ss << "\n";

    Matrix3f F = ele->defGrad(q.x[ii], grid->X, grid->x);
    Matrix3f P = ene->getPK1(F);
    //std::cout << "P:\n";
    //P.print();

    Ka += q.w[ii] * B.transpose() * E * B;
    //std::cout << "B:\n" << B << "\n";
  }

  //std::cout << "E:\n" << E << "\n";
  //std::cout << "alt K:\n";
  //std::cout << Ka << "\n";
  float maxErr = 0;
  for (int ii = 0; ii<K.mm; ii++){
    for (int jj = 0; jj<K.nn; jj++){
      float err = (float)std::abs(Ka(ii, jj) - K(ii, jj));
      if (err>maxErr){
        maxErr = err;
      }
    }
  }

  std::cout << "max err " << maxErr << "\n";

  //assemble boundary matrix HNEB
  std::ofstream out("T.txt");

  // 2 point quadrature is accurate enough
  const Quadrature & q2d = Quadrature::Gauss2_2D;
  Eigen::MatrixXf T = Eigen::MatrixXf::Zero(3 * ele->nV(), 3 * ele->nV());
  for (int ii = 0; ii < ele->nF(); ii++){
    Eigen::MatrixXf Tf = Eigen::MatrixXf::Zero(3 * ele->nV(), 3 * ele->nV());
    Eigen::MatrixXf N = ele->NMatrix(ii);
    N.block(0, 3, 3, 3) = Eigen::MatrixXf::Zero(3, 3);
    //std::cout << "N:\n"<<N << "\n";
    for (unsigned int jj = 0; jj < q2d.x.size(); jj++){
      Vector3f quadp = ele->facePt(ii, q2d.x[jj]);
      Eigen::MatrixXf B0 = ele->BMatrix(quadp, grid->X);
      Eigen::MatrixXf B = Eigen::MatrixXf::Zero(6, 3 * ele->nV());
      //only add contributions from the face
      for (int kk = 0; kk < 4; kk++){
        int vidx = faces[ii][kk];
        B.block(0, 3 * vidx, 6, 3) = B0.block(0, 3 * vidx, 6, 3);
      }
      //B=B0;
      Eigen::MatrixXf H = ele->HMatrix(quadp);
      //std::cout << "H:\n" << H.transpose() << "\n";
      //std::cout << "B:\n" << B.transpose() << "\n";
      //std::cout << "traction:\n";
      //Tf += q2d.w[jj] * H.transpose() * N * E * B;
      Tf += q2d.w[jj] * H.transpose() * N * E * N.transpose() * H;
      //Tf += q2d.w[jj] * B.transpose() * E * B;
      Eigen::Vector3f surfF = (N * E * B * U);
      //std::cout << surfF << "\n";
      Matrix3f F = ele->defGrad(quadp, grid->X, grid->x);
      Matrix3f P = ene->getPK1(F);
      Vector3f surfF1 = P * Vector3f(facen[ii][0], facen[ii][1], facen[ii][2]);
      std::cout << surfF1[0] << " " << surfF1[1] << " " << surfF1[2] << "\n";
    }
    //out << Tf << "\n\n";
    T += Tf;
  }
  //out << T << "\n\n";
  //out << Ka << "\n";
  out.close();
}
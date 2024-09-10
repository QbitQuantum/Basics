cfgScalar MaterialQuad2D::getEnergy(Element2D* ele, ElementMesh2D * mesh)
{
  cfgScalar energy = 0;
  if (m_planeStress==false)
  {
    for(int ii = 0; ii<q->x.size();ii++){
      Matrix2S F = ele->defGrad(q->x[ii], mesh->X, mesh->x);
      energy += q->w[ii] * e[ii]->getEnergy(F);
    }
    energy *= ele->getVol(mesh->X);
  }
  else
  {
    MatrixXS K = getStiffness(ele, mesh);

    Eigen::Matrix<cfgScalar, 8, 1> u;

    for(int ii = 0; ii<ele->nV(); ii++)
    {
      int vi = ele->at(ii);
      Vector2S ui = mesh->x[vi] - mesh->X[vi];
      u(2*ii) = ui[0];
      u(2*ii+1) = ui[1];
    }
    energy = 0.5*u.transpose()*K*u;
  }
  return energy;
}
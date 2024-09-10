/* compute Jacobian */
void mmf::OptSO3ApproxGD::ComputeJacobian(const SO3f& thetaPrev, const
    SO3f& theta, Eigen::Vector3f* J, float* f) {
  Eigen::Matrix3f R = theta.matrix();
  Eigen::Matrix3f Rprev = thetaPrev.matrix();

#ifndef NDEBUG
  cout<<"qKarch"<<endl<<qKarch_<<endl;
  cout<<"xSums_"<<endl<<xSums_<<endl;
  cout<<"Ns_"<<endl<<Ns_<<endl;
#endif

  if(J) for (uint32_t k=0; k<3; ++k)
      (*J)(k) = tauR_*(Rprev.transpose()*SO3f::G(k)*R).trace();
  if(f) *f = tauR_*(Rprev.transpose()*R).trace();

  for (uint32_t j=0; j<6; ++j) { 
    if (Ns_(j) == 0) continue;
    Eigen::Vector3f m = Eigen::Vector3f::Zero();
    m(j/2) = j%2==0?-1.:1.;
    float dot = max(-1.0f,min(1.0f,qKarch_.col(j).dot(R*m)));
    float eps = acos(dot);
    if (f) *f += Ns_(j)*eps*eps;
    if (J) {
      float factor = 0.;
      if(-0.99< dot && dot < 0.99)
        factor = -(2.*Ns_(j)*eps)/(sqrt(1.f-dot*dot));
      else if(dot >= 0.99) { 
        // taylor series around 0.99 according to Mathematica
        factor = -2.*Ns_(j)*(1.0033467240646519 - 0.33601724502488395
            *(-0.99 + dot) + 0.13506297338381046* (-0.99 + dot)*(-0.99 + dot));
      }else if (dot <= -0.99) {
        factor = -2.*Ns_(j)*(21.266813135156017 - 1108.2484926534892*(0.99
              + dot) + 83235.29739487475*(0.99 + dot)*(0.99 + dot));
      }
//      std::cout << "factor " << factor << std::endl;
      for (uint32_t k=0; k<3; ++k)
        (*J)(k) += factor*qKarch_.col(j).dot(SO3f::G(k)*R*m);
    }
  }
  if (f) *f /= -Ns_.sum();
  if (J) *J /= -Ns_.sum();
}
  void compute_optimization(Real& Omega, Real& Aplus, Real& Amin)
  {
    enum {ENTR=0,OMEGA=1,APLUS=2,AMIN=3};

    Real dAmindn = 0.;
    Real dAminds = 0.;
    Real dAplusdn = 0.;
    Real dAplusds = 0.;
    Real dOmegadn = 0.;
    Real dOmegads = 0.;
    for (Uint j=0; j<inner_cell->get().sf->nb_flx_pts(); ++j)
    {
      dOmegadn   += char_flx_pt_solution[j][OMEGA] * sf_deriv_xi[j];
      dOmegads   -= char_flx_pt_solution[j][OMEGA] * sf_deriv_eta[j];
      dAmindn    += char_flx_pt_solution[j][AMIN ] * sf_deriv_xi[j];
      dAminds    -= char_flx_pt_solution[j][AMIN ] * sf_deriv_eta[j];
      dAplusdn   += char_flx_pt_solution[j][APLUS] * sf_deriv_xi[j];
      dAplusds   -= char_flx_pt_solution[j][APLUS] * sf_deriv_eta[j];
    }
    Real dOmegadt = m_u0n*dOmegadn + m_u0s*dOmegads + m_c0/2.*(dAplusds + dAminds);

    RealVector3 X;
    X << char_flx_pt_solution[cell_flx_pt][OMEGA],
         char_flx_pt_solution[cell_flx_pt][APLUS],
         char_flx_pt_solution[cell_flx_pt][AMIN];

    RealVector3 F;
    RealMatrix3 J;
    RealVector3 Xnew;

//    std::cout << "\n\n\n" << std::endl;
    Uint iter=0;
    Real error = 1.;
    while (error>1e-7 && iter<15)
    {
      Real dAmindn = 0.;
      Real dAminds = 0.;
      Real dAplusdn = 0.;
      Real dAplusds = 0.;
      Real dOmegadn = 0.;
      Real dOmegads = 0.;
      for (Uint j=0; j<inner_cell->get().sf->nb_flx_pts(); ++j)
      {
        if (j!=cell_flx_pt)
        {
          dOmegadn   += char_flx_pt_solution[j][OMEGA] * sf_deriv_xi[j];
          dOmegads   -= char_flx_pt_solution[j][OMEGA] * sf_deriv_eta[j];
          dAmindn    += char_flx_pt_solution[j][AMIN ] * sf_deriv_xi[j];
          dAminds    -= char_flx_pt_solution[j][AMIN ] * sf_deriv_eta[j];
          dAplusdn   += char_flx_pt_solution[j][APLUS] * sf_deriv_xi[j];
          dAplusds   -= char_flx_pt_solution[j][APLUS] * sf_deriv_eta[j];
        }
      }
      dOmegadn   += X[0] * sf_deriv_xi[cell_flx_pt];
      dOmegads   -= X[0] * sf_deriv_eta[cell_flx_pt];
      dAplusdn   += X[1] * sf_deriv_xi[cell_flx_pt];
      dAplusds   -= X[1] * sf_deriv_eta[cell_flx_pt];
      dAmindn    += X[2] * sf_deriv_xi[cell_flx_pt];
      dAminds    -= X[2] * sf_deriv_eta[cell_flx_pt];


      F << m_u0n*dOmegadn + m_u0s*dOmegads + m_c0/2.*dAplusds + m_c0/2.*dAminds - dOmegadt,
           dAplusdn + dOmegads,
           dAmindn - dOmegads;

      J << m_u0n*sf_deriv_xi[cell_flx_pt] + m_u0s*sf_deriv_eta[cell_flx_pt] ,  m_c0/2.*sf_deriv_eta[cell_flx_pt] , m_c0/2.*sf_deriv_eta[cell_flx_pt],
            sf_deriv_eta[cell_flx_pt]                                       ,  sf_deriv_xi[cell_flx_pt]       , 0.,
           -sf_deriv_eta[cell_flx_pt]                                       ,  0.                             , sf_deriv_xi[cell_flx_pt];

      Xnew.noalias() = X - J.inverse() * F;

      error = ((X-Xnew).array()/X.array()).abs().maxCoeff();


//      std::cout << "iter = " << iter++ << std::endl;
//      std::cout << "error= " << error << std::endl;
//      std::cout << "X    = " << X.transpose() << std::endl;
//      std::cout << "Xnew = " << Xnew.transpose() << std::endl;
//      std::cout << "F    = " << F.transpose() << std::endl;
//      std::cout << "J    = \n" << J << std::endl;



      X = Xnew;
      ++iter;
    }

    Omega = X[0];
    Aplus = X[1];
    Amin  = X[2];
  }
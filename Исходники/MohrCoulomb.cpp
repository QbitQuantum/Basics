void MohrCoulomb<DisplacementDim>::computeConstitutiveRelation(
    double const t,
    ProcessLib::SpatialPosition const& x,
    double const aperture0,
    Eigen::Ref<Eigen::VectorXd const>
        sigma0,
    Eigen::Ref<Eigen::VectorXd const>
        w_prev,
    Eigen::Ref<Eigen::VectorXd const>
        w,
    Eigen::Ref<Eigen::VectorXd const>
        sigma_prev,
    Eigen::Ref<Eigen::VectorXd>
        sigma,
    Eigen::Ref<Eigen::MatrixXd>
        Kep,
    typename FractureModelBase<DisplacementDim>::MaterialStateVariables&
        material_state_variables)
{
    material_state_variables.reset();

    MaterialPropertyValues const mat(_mp, t, x);
    Eigen::VectorXd const dw = w - w_prev;

    const int index_ns = DisplacementDim - 1;
    double const aperture = w[index_ns] + aperture0;
    double const aperture_prev = w_prev[index_ns] + aperture0;

    Eigen::MatrixXd Ke;
    {  // Elastic tangent stiffness
        Ke = Eigen::MatrixXd::Zero(DisplacementDim, DisplacementDim);
        for (int i = 0; i < index_ns; i++)
            Ke(i, i) = mat.Ks;

        Ke(index_ns, index_ns) =
            mat.Kn *
            logPenaltyDerivative(aperture0, aperture, _penalty_aperture_cutoff);
    }

    Eigen::MatrixXd Ke_prev;
    {  // Elastic tangent stiffness at w_prev
        Ke_prev = Eigen::MatrixXd::Zero(DisplacementDim, DisplacementDim);
        for (int i = 0; i < index_ns; i++)
            Ke_prev(i, i) = mat.Ks;

        Ke_prev(index_ns, index_ns) =
            mat.Kn * logPenaltyDerivative(
                         aperture0, aperture_prev, _penalty_aperture_cutoff);
    }

    // Total plastic aperture compression
    // NOTE: Initial condition sigma0 seems to be associated with an initial
    // condition of the w0 = 0. Therefore the initial state is not associated
    // with a plastic aperture change.
    Eigen::VectorXd const w_p_prev =
        w_prev - Ke_prev.fullPivLu().solve(sigma_prev - sigma0);

    {  // Exact elastic predictor
        sigma.noalias() = Ke * (w - w_p_prev);

        sigma.coeffRef(index_ns) =
            mat.Kn * w[index_ns] *
            logPenalty(aperture0, aperture, _penalty_aperture_cutoff);
    }

    sigma.noalias() += sigma0;

    double const sigma_n = sigma[index_ns];

    // correction for an opening fracture
    if (_tension_cutoff && sigma_n > 0)
    {
        Kep.setZero();
        sigma.setZero();
        material_state_variables.setTensileStress(true);
        return;
    }

    // check shear yield function (Fs)
    Eigen::VectorXd const sigma_s = sigma.head(DisplacementDim-1);
    double const mag_tau = sigma_s.norm(); // magnitude
    double const Fs = mag_tau + sigma_n * std::tan(mat.phi) - mat.c;

    material_state_variables.setShearYieldFunctionValue(Fs);
    if (Fs < .0)
    {
        Kep = Ke;
        return;
    }

    Eigen::VectorXd dFs_dS(DisplacementDim);
    dFs_dS.head(DisplacementDim-1).noalias() = sigma_s.normalized();
    dFs_dS[index_ns] = std::tan(mat.phi);

    // plastic potential function: Qs = |tau| + Sn * tan da
    Eigen::VectorXd dQs_dS = dFs_dS;
    dQs_dS[index_ns] = std::tan(mat.psi);

    // plastic multiplier
    Eigen::RowVectorXd const A = dFs_dS.transpose() * Ke / (dFs_dS.transpose() * Ke * dQs_dS);
    double const d_eta = A * dw;

    // plastic part of the dispalcement
    Eigen::VectorXd const dwp = dQs_dS * d_eta;

    // correct stress
    sigma.noalias() = sigma_prev + Ke * (dw - dwp);

    // Kep
    Kep = Ke - Ke * dQs_dS * A;
}
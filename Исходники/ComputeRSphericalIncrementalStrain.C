void
ComputeRSphericalIncrementalStrain::computeTotalStrainIncrement(RankTwoTensor & total_strain_increment)
{
    // Deformation gradient calculation in cylinderical coordinates
    RankTwoTensor A;    // Deformation gradient
    RankTwoTensor Fbar; // Old Deformation gradient

    // Step through calculating the current and old deformation gradients
    // Only diagonal components are nonzero because this is a 1D material
    // Note: x_disp is the radial displacement
    A(0,0) = (*_grad_disp[0])[_qp](0);
    Fbar(0,0) = (*_grad_disp_old[0])[_qp](0);

    // The polar and azimuthal strains are functions of radial displacement
    if (!MooseUtils::relativeFuzzyEqual(_q_point[_qp](0), 0.0))
    {
        A(1,1) = (*_disp[0])[_qp] / _q_point[_qp](0);
        Fbar(1,1) = _disp_old_0[_qp] / _q_point[_qp](0);
    }

    // The polar and azimuthal strains are equalivalent in this 1D problem
    A(2,2) = A(1,1);
    Fbar(2,2) = Fbar(1,1);

    // Gauss point deformation gradient
    _deformation_gradient[_qp] = A;
    _deformation_gradient[_qp].addIa(1.0);

    // very nearly A = gradU - gradUold, adapted to cylinderical coords
    A -= Fbar;

    total_strain_increment = 0.5 * (A + A.transpose());
}
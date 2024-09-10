void
StressDivergenceTensors::computeFiniteDeformJacobian()
{
  const RankTwoTensor I(RankTwoTensor::initIdentity);
  const RankFourTensor II_ijkl = I.mixedProductIkJl(I);

  // Bring back to unrotated config
  const RankTwoTensor unrotated_stress =
      (*_rotation_increment)[_qp].transpose() * _stress[_qp] * (*_rotation_increment)[_qp];

  // Incremental deformation gradient Fhat
  const RankTwoTensor Fhat =
      (*_deformation_gradient)[_qp] * (*_deformation_gradient_old)[_qp].inverse();
  const RankTwoTensor Fhatinv = Fhat.inverse();

  const RankTwoTensor rot_times_stress = (*_rotation_increment)[_qp] * unrotated_stress;
  const RankFourTensor dstress_drot =
      I.mixedProductIkJl(rot_times_stress) + I.mixedProductJkIl(rot_times_stress);
  const RankFourTensor rot_rank_four =
      (*_rotation_increment)[_qp].mixedProductIkJl((*_rotation_increment)[_qp]);
  const RankFourTensor drot_dUhatinv = Fhat.mixedProductIkJl(I);

  const RankTwoTensor A = I - Fhatinv;

  // Ctilde = Chat^-1 - I
  const RankTwoTensor Ctilde = A * A.transpose() - A - A.transpose();
  const RankFourTensor dCtilde_dFhatinv =
      -I.mixedProductIkJl(A) - I.mixedProductJkIl(A) + II_ijkl + I.mixedProductJkIl(I);

  // Second order approximation of Uhat - consistent with strain increment definition
  // const RankTwoTensor Uhat = I - 0.5 * Ctilde - 3.0/8.0 * Ctilde * Ctilde;

  RankFourTensor dUhatinv_dCtilde =
      0.5 * II_ijkl - 1.0 / 8.0 * (I.mixedProductIkJl(Ctilde) + Ctilde.mixedProductIkJl(I));
  RankFourTensor drot_dFhatinv = drot_dUhatinv * dUhatinv_dCtilde * dCtilde_dFhatinv;

  drot_dFhatinv -= Fhat.mixedProductIkJl((*_rotation_increment)[_qp].transpose());
  _finite_deform_Jacobian_mult[_qp] = dstress_drot * drot_dFhatinv;

  const RankFourTensor dstrain_increment_dCtilde =
      -0.5 * II_ijkl + 0.25 * (I.mixedProductIkJl(Ctilde) + Ctilde.mixedProductIkJl(I));
  _finite_deform_Jacobian_mult[_qp] +=
      rot_rank_four * _Jacobian_mult[_qp] * dstrain_increment_dCtilde * dCtilde_dFhatinv;
  _finite_deform_Jacobian_mult[_qp] += Fhat.mixedProductJkIl(_stress[_qp]);

  const RankFourTensor dFhat_dFhatinv = -Fhat.mixedProductIkJl(Fhat.transpose());
  const RankTwoTensor dJ_dFhatinv = dFhat_dFhatinv.innerProductTranspose(Fhat.ddet());

  // Component from Jacobian derivative
  _finite_deform_Jacobian_mult[_qp] += _stress[_qp].outerProduct(dJ_dFhatinv);

  // Derivative of Fhatinv w.r.t. undisplaced coordinates
  const RankTwoTensor Finv = (*_deformation_gradient)[_qp].inverse();
  const RankFourTensor dFhatinv_dGradu = -Fhatinv.mixedProductIkJl(Finv.transpose());
  _finite_deform_Jacobian_mult[_qp] = _finite_deform_Jacobian_mult[_qp] * dFhatinv_dGradu;
}
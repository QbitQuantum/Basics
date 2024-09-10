void
PlaneStrain::computeStrain( const unsigned qp,
                               const SymmTensor & total_strain_old,
                               SymmTensor & total_strain_new,
                               SymmTensor & strain_increment )
{
  strain_increment.xx() = _grad_disp_x[qp](0);
  strain_increment.yy() = _grad_disp_y[qp](1);

  if (_have_strain_zz)
    strain_increment.zz() = _strain_zz[qp];
  else if (_have_scalar_strain_zz && _scalar_strain_zz.size()>0)
    strain_increment.zz() = _scalar_strain_zz[0];
  else
    strain_increment.zz() = 0;

  strain_increment.xy() = 0.5*(_grad_disp_x[qp](1) + _grad_disp_y[qp](0));
  strain_increment.yz() = 0;
  strain_increment.zx() = 0;
  if (_large_strain)
  {
    strain_increment.xx() += 0.5*(_grad_disp_x[qp](0)*_grad_disp_x[qp](0) +
                                  _grad_disp_y[qp](0)*_grad_disp_y[qp](0));
    strain_increment.yy() += 0.5*(_grad_disp_x[qp](1)*_grad_disp_x[qp](1) +
                                  _grad_disp_y[qp](1)*_grad_disp_y[qp](1));
    strain_increment.xy() += 0.5*(_grad_disp_x[qp](0)*_grad_disp_x[qp](1) +
                                  _grad_disp_y[qp](0)*_grad_disp_y[qp](1));
  }

  if (_volumetric_locking_correction)
  {
    // volumetric locking correction
    Real volumetric_strain = 0.0;
    Real volume = 0.0;
    Real dim = 3.0;
    for (unsigned int qp_loop = 0; qp_loop < _solid_model.qrule()->n_points(); ++qp_loop)
    {
      if (_have_strain_zz)
        volumetric_strain += (_grad_disp_x[qp_loop](0) + _grad_disp_y[qp_loop](1) + _strain_zz[qp_loop]) / dim * _solid_model.JxW(qp_loop);
      else if (_have_scalar_strain_zz && _scalar_strain_zz.size() > 0)
        volumetric_strain += (_grad_disp_x[qp_loop](0) + _grad_disp_y[qp_loop](1) + _scalar_strain_zz[0]) / dim * _solid_model.JxW(qp_loop);
      else
        volumetric_strain += (_grad_disp_x[qp_loop](0) + _grad_disp_y[qp_loop](1)) / dim * _solid_model.JxW(qp_loop);

      volume += _solid_model.JxW(qp_loop);

      if (_large_strain)
      {
        volumetric_strain += 0.5 * (_grad_disp_x[qp_loop](0) * _grad_disp_x[qp_loop](0) +
                                    _grad_disp_y[qp_loop](0) * _grad_disp_y[qp_loop](0)) / dim * _solid_model.JxW(qp_loop);
        volumetric_strain += 0.5 * (_grad_disp_x[qp_loop](1) * _grad_disp_x[qp_loop](1) +
                                    _grad_disp_y[qp_loop](1) * _grad_disp_y[qp_loop](1)) / dim * _solid_model.JxW(qp_loop);
      }
    }

    volumetric_strain /= volume; // average volumetric strain

    // strain increment at _qp
    Real trace = strain_increment.trace();
    strain_increment.xx() += volumetric_strain - trace / dim;
    strain_increment.yy() += volumetric_strain - trace / dim;
    strain_increment.zz() += volumetric_strain - trace / dim;
  }

  total_strain_new = strain_increment;

  strain_increment -= total_strain_old;
}
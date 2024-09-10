void
PLC_LSH::computeLSH( const SymmTensor & strain_increment,
                     SymmTensor & plastic_strain_increment,
                     SymmTensor & stress_new )
{

  // compute deviatoric trial stress
  SymmTensor dev_trial_stress(stress_new);
  dev_trial_stress.addDiag( -stress_new.trace()/3 );

  // effective trial stress
  Real dts_squared = dev_trial_stress.doubleContraction(dev_trial_stress);
  Real effective_trial_stress = std::sqrt(1.5 * dts_squared);

  // determine if yield condition is satisfied
  Real yield_condition = effective_trial_stress - _hardening_variable_old[_qp] - _yield_stress;

  _hardening_variable[_qp] = _hardening_variable_old[_qp];
  _plastic_strain[_qp] = _plastic_strain_old[_qp];

  if (yield_condition > 0)  // then use newton iteration to determine effective plastic strain increment
  {
    unsigned int it = 0;
    Real plastic_residual = 0;
    Real norm_plas_residual = 10;
    Real first_norm_plas_residual = 10;
    Real scalar_plastic_strain_increment = 0;

    while (it < _max_its &&
          norm_plas_residual > _absolute_tolerance &&
          (norm_plas_residual/first_norm_plas_residual) > _relative_tolerance)
    {
      plastic_residual = effective_trial_stress - (3. * _shear_modulus * scalar_plastic_strain_increment) -
        _hardening_variable[_qp] - _yield_stress;
      norm_plas_residual = std::abs(plastic_residual);
      if (it == 0)
      {
        first_norm_plas_residual = norm_plas_residual;
      }

      scalar_plastic_strain_increment += plastic_residual / (3. * _shear_modulus + _hardening_constant);

      _hardening_variable[_qp] = _hardening_variable_old[_qp] + (_hardening_constant * scalar_plastic_strain_increment);

      if (_output_iteration_info == true)
      {
        _console
          << "pls_it="    << it
          << " trl_strs=" << effective_trial_stress
          << " del_p="    << scalar_plastic_strain_increment
          << " harden="   << _hardening_variable[_qp]
          << " rel_res="  << norm_plas_residual/first_norm_plas_residual
          << " rel_tol="  << _relative_tolerance
          << " abs_res="  << norm_plas_residual
          << " abs_tol="  << _absolute_tolerance
          << std::endl;
      }

      ++it;

    }

    if (it == _max_its &&
       norm_plas_residual > _absolute_tolerance &&
       (norm_plas_residual/first_norm_plas_residual) > _relative_tolerance)
    {
      mooseError("Max sub-newton iteration hit during plasticity increment solve!");
    }

    if (effective_trial_stress < 0.01)
    {
      effective_trial_stress = 0.01;
    }
    plastic_strain_increment = dev_trial_stress;
    plastic_strain_increment *= (1.5*scalar_plastic_strain_increment/effective_trial_stress);

    SymmTensor elastic_strain_increment(strain_increment);
    elastic_strain_increment -= plastic_strain_increment;

    // compute stress increment
    stress_new = *elasticityTensor() * elastic_strain_increment;

    // update stress and plastic strain
    stress_new += _stress_old;
    _plastic_strain[_qp] += plastic_strain_increment;

  } // end of if statement

}
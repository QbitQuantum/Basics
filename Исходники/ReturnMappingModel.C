void
ReturnMappingModel::computeStress( const Elem & /*current_elem*/, unsigned qp,
                                   const SymmElasticityTensor & elasticityTensor,
                                   const SymmTensor & stress_old,
                                   SymmTensor & strain_increment,
                                   SymmTensor & stress_new,
                                   SymmTensor & inelastic_strain_increment )
{

  // compute deviatoric trial stress
  SymmTensor dev_trial_stress(stress_new);
  dev_trial_stress.addDiag( -dev_trial_stress.trace()/3.0 );

  // compute effective trial stress
  Real dts_squared = dev_trial_stress.doubleContraction(dev_trial_stress);
  Real effective_trial_stress = std::sqrt(1.5 * dts_squared);

  // compute effective strain increment
  SymmTensor dev_strain_increment(strain_increment);
  dev_strain_increment.addDiag( -strain_increment.trace()/3.0);
  _effective_strain_increment = dev_strain_increment.doubleContraction(dev_strain_increment);
  _effective_strain_increment = std::sqrt(2.0/3.0 * _effective_strain_increment);

  computeStressInitialize(qp, effective_trial_stress, elasticityTensor);

  // Use Newton sub-iteration to determine inelastic strain increment

  Real scalar = 0;
  unsigned int it = 0;
  Real residual = 10;
  Real norm_residual = 10;
  Real first_norm_residual = 10;

  std::stringstream iter_output;

  while (it < _max_its &&
        norm_residual > _absolute_tolerance &&
        (norm_residual/first_norm_residual) > _relative_tolerance)
  {
    iterationInitialize( qp, scalar );

    residual = computeResidual(qp, effective_trial_stress, scalar);
    norm_residual = std::abs(residual);
    if (it == 0)
    {
      first_norm_residual = norm_residual;
      if (first_norm_residual == 0)
      {
        first_norm_residual = 1;
      }
    }

    scalar -= residual / computeDerivative(qp, effective_trial_stress, scalar);

    if (_output_iteration_info == true ||
        _output_iteration_info_on_error == true)
    {
      iter_output
        << " it="       << it
        << " trl_strs=" << effective_trial_stress
        << " scalar="   << scalar
        << " rel_res="  << norm_residual/first_norm_residual
        << " rel_tol="  << _relative_tolerance
        << " abs_res="  << norm_residual
        << " abs_tol="  << _absolute_tolerance
        << std::endl;
    }

    iterationFinalize( qp, scalar );

    ++it;
  }

  if (_output_iteration_info)
    _console << iter_output.str();


  if (it == _max_its &&
     norm_residual > _absolute_tolerance &&
     (norm_residual/first_norm_residual) > _relative_tolerance)
  {
    if (_output_iteration_info_on_error)
    {
      Moose::err << iter_output.str();
    }
    mooseError("Max sub-newton iteration hit during nonlinear constitutive model solve! (" << _name << ")");
  }

  // compute inelastic and elastic strain increments (avoid potential divide by zero - how should this be done)?
  if (effective_trial_stress < 0.01)
  {
    effective_trial_stress = 0.01;
  }

  inelastic_strain_increment = dev_trial_stress;
  inelastic_strain_increment *= (1.5*scalar/effective_trial_stress);

  strain_increment -= inelastic_strain_increment;

  // compute stress increment
  stress_new = elasticityTensor * strain_increment;

  // update stress
  stress_new += stress_old;

  computeStressFinalize(qp, inelastic_strain_increment);

}
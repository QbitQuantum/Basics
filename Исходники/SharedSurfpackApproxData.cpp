void SharedSurfpackApproxData::
vars_to_realarray(const Variables& vars, RealArray& ra)
{
  // check incoming vars for correct length (active or all views)
  if (vars.cv() + vars.div() + vars.drv() == numVars)
    merge_variable_arrays(vars.continuous_variables(),
			  vars.discrete_int_variables(),
			  vars.discrete_real_variables(), ra);
  else if (vars.acv() + vars.adiv() + vars.adrv() == numVars)
    merge_variable_arrays(vars.all_continuous_variables(),
			  vars.all_discrete_int_variables(),
			  vars.all_discrete_real_variables(), ra);
  else {
    Cerr << "Error: bad parameter set length in SharedSurfpackApproxData::"
	 << "vars_to_realarray()." << std::endl;
    abort_handler(-1);
  }
}
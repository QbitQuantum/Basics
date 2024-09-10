void Approximation::
add(const Variables& vars, bool anchor_flag, bool deep_copy)
{
  if (approxRep)
    approxRep->add(vars, anchor_flag, deep_copy);
  else { // not virtual: all derived classes use following definition
    // Approximation does not know about view mappings; therefore, take the
    // simple approach of matching up active or all counts with numVars.
    size_t num_v = sharedDataRep->numVars;
    if (vars.cv() + vars.div() + vars.drv() == num_v)
      add(vars.continuous_variables(), vars.discrete_int_variables(),
	  vars.discrete_real_variables(), anchor_flag, deep_copy);
    else if (vars.acv() + vars.adiv() + vars.adrv() == num_v)
      add(vars.all_continuous_variables(), vars.all_discrete_int_variables(),
	  vars.all_discrete_real_variables(), anchor_flag, deep_copy);
    /*
    else if (vars.cv() == num_v) {  // compactMode does not affect vars
      IntVector empty_iv; RealVector empty_rv;
      add(vars.continuous_variables(), empty_iv, empty_rv,
	  anchor_flag, deep_copy);
    }
    else if (vars.acv() == num_v) { // potential conflict with cv/div/drv
      IntVector empty_iv; RealVector empty_rv;
      add(vars.all_continuous_variables(), empty_iv, empty_rv,
	  anchor_flag, deep_copy);
    }
    */
    else {
      Cerr << "Error: variable size mismatch in Approximation::add()."
	   << std::endl;
      abort_handler(-1);
    }
  }
}
  inline var<AutodiffOrder, StrictSmoothness, ValidateIO>
    tgamma(const var<AutodiffOrder, StrictSmoothness, ValidateIO>& input) {
    
    if (ValidateIO) validate_input(input.first_val(), "tgamma");
      
    const short partials_order = 3;
    const unsigned int n_inputs = 1;
    
    create_node<unary_var_node<AutodiffOrder, partials_order>>(n_inputs);

    double val = input.first_val();
    double g = tgamma(val);
    
    try {
      push_dual_numbers<AutodiffOrder, ValidateIO>(g);
    } catch (nomad_error) {
      throw nomad_output_value_error("tgamma");
    }
      
    push_inputs(input.dual_numbers());
    
    try {
      if (AutodiffOrder >= 1) {
        double dg = digamma(val);
        push_partials<ValidateIO>(g * dg);
      
        if (AutodiffOrder >= 2) {
          double tg = trigamma(val);
          push_partials<ValidateIO>(g * (dg * dg + tg));
      
          if (AutodiffOrder >= 3)
            push_partials<ValidateIO>(g * (dg * dg * dg + 3.0 * dg * tg + quadrigamma(val)));

        }
      }
    } catch (nomad_error) {
      throw nomad_output_partial_error("tgamma");
    }
      
    return var<AutodiffOrder, StrictSmoothness, ValidateIO>(next_node_idx_ - 1);
    
  }
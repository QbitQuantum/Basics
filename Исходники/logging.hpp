//  Element functions definition ---------------------------------------------//
  inline std::string log_element::visit(format &f, 
                                        const log_param_t &log_param)
  {
    return f.accept(*this);
  }
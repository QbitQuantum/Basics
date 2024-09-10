  SEXP lnoResiduals(SEXP sp, SEXP excludeRadius){
    if(!(isNumeric(excludeRadius) && LENGTH(excludeRadius) == 1))
      Rf_error("Exclude radius must be a scalar");
    if(R_ExternalPtrTag(sp) != install("covafillPointer"))
      Rf_error("The pointer must be to a covafill object");
    covafill<double>* ptr=(covafill<double>*)R_ExternalPtrAddr(sp);

    double er = asDouble(excludeRadius);
    MatrixXd x0 = ptr->coordinates;
    vector y0 = ptr->observations;
    vector res(y0.size());

    for(int i = 0; i < x0.rows(); ++i)
      res.row(i) = ptr->operator()((vector)x0.row(i),er) - y0(i);

    return asSEXP(res);
  }
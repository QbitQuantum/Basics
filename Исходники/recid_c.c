SEXP jmoy_gradient(SEXP handle,SEXP sbeta,SEXP salpha){
  Data *data;
  SEXP sgrad;

  double *beta;
  double alpha;
  double *grad;

  int i,j;
  
  data=R_ExternalPtrAddr(handle);
  beta=REAL(sbeta);
  alpha=REAL(salpha)[0];
  PROTECT(sgrad=allocVector(REALSXP,data->nvars+1));
  grad=REAL(sgrad);
  for(i=0;i<data->nvars+1;i++)
    grad[i]=0;

  /*Uncensored observations*/
  
  for(i=0;i<data->uc_nobs;i++){
    double xbeta=0.0;
    double t=data->uc_y[i];
    double t_alpha=pow(t,alpha);
    double exp_xbeta;

    double grad_xbeta;

    for(j=0;j<data->nvars;j++)
      xbeta+=data->uc_x[i+j*data->uc_nobs]*beta[j];
    exp_xbeta=exp(xbeta);

    grad_xbeta=1.0-exp_xbeta*t_alpha;
    for (j=0;j<data->nvars;j++)
      grad[j]-=data->uc_x[i+j*data->uc_nobs]*grad_xbeta;
    
    grad[data->nvars]-=
      1.0/alpha
      +(1.0-exp_xbeta*t_alpha)*log(t);
  }

  /*Censored observations*/
  
  for(i=0;i<data->c_nobs;i++){
    double xbeta=0.0;
    double t=data->c_y[i];
    double t_alpha=pow(t,alpha);
    double exp_xbeta;

    double grad_xbeta;

    for(j=0;j<data->nvars;j++)
      xbeta+=data->c_x[i+j*data->c_nobs]*beta[j];
    exp_xbeta=exp(xbeta);

    grad_xbeta=-exp_xbeta*t_alpha;
    for (j=0;j<data->nvars;j++)
      grad[j]-=data->c_x[i+j*data->c_nobs]*grad_xbeta;
    grad[data->nvars]-=-exp_xbeta*t_alpha*log(t);
  }

  UNPROTECT(1); /*sgrad*/

  return sgrad;
}
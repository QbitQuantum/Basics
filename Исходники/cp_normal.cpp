Scalar MASA::cp_normal<Scalar>::eval_posterior(Scalar x)
{
  using std::sqrt;
  using std::exp;
  using std::pow;

  Scalar av = 0;
  Scalar post;
  Scalar sigmap;
  Scalar mp;

  for(int it = 0;it<int(vec_data.size());it++)
    {
      av +=vec_data[it];
    }
  av = av / (Scalar)vec_data.size();

  //set x_bar to average of data vector
  this->set_var("x_bar",av);
  
  sigmap = sqrt(1/((1/pow(sigma,2)) + (Scalar(vec_data.size())/pow(sigma_d,2))));
  mp     = pow(sigmap,2) * (m/pow(sigma,2) + (Scalar(vec_data.size())*x_bar/pow(sigma_d,2)));
  post   = sqrt(2*pi*pow(sigmap,2)) * exp(-(1/(2*pow(sigmap,2)))*pow((x-mp),2));

  return post;
}
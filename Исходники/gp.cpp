// Compute posterior mean at specified point.
MatrixXd GPCMGaussianProcess::posteriorMean(
    const MatrixXd* const *Xstar,           // Sample point.
    MatrixXd *var,                          // Optional variance output.
    MatrixXd *dMdXstar,                     // Change in mean with respect to Xstar.
    MatrixXd *dVdXstar                      // Change in variance with respect to Xstar.
    )
{
    // Kernalize the input.
    MatrixXd k;
    MatrixXd kGrad(X[0]->rows(),q);
    
    // If we want the mean gradient, compute gradient here.
    if (dMdXstar)
        k = kernel->covarianceGrad(X,Xstar,kGrad);
    else
        k = kernel->covariance(X,Xstar);

    // Check if we want the variance.
    if (var)
    {
        MatrixXd kd;
        MatrixXd kdGrad(Xstar[0]->rows(),q);
        
        // If we want the variance gradient, compute mean here.
        if (dVdXstar)
            kd = kernel->covarianceGrad(Xstar,kdGrad);
        else
            kd = kernel->covariance(Xstar);

        if (var->cols() > 0 && var->cols() == var->rows())
        { // If we are passed a non-empty square matrix, we want the full covariance.
            *var = kd - k.transpose()*invK*k;
        }
        else
        {
            var->resize(k.cols(),1);
            for (int i = 0; i < k.cols(); i++)
                var->block(i,0,1,1) = kd.block(i,i,1,1) - k.col(i).transpose()*invK*k.col(i);
        }

        // Check if we want the gradient of the variance.
        if (dVdXstar)
        {
            assert(var->rows() == 1); // Only supports single query points.
            *dVdXstar = kdGrad.transpose() - 2.0*kGrad.transpose()*invK*k;
        }
    }

    // Compute scaled mean gradient.
    if (dMdXstar)
    {
        *dMdXstar = (kGrad.transpose()*alpha).cwiseQuotient(scale.replicate(kGrad.cols(),1));
    }

    // Return mean.
    return (k.transpose()*alpha).cwiseQuotient(scale.replicate(k.cols(),1)) + bias.replicate(k.cols(),1);
}
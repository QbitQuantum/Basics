 bool NewtonMinimizerGradHessian::lineSearch(double& alpha, const double& wolfe1, const double& wolfe2, VectorXd& try_grad, VectorXd& direction, double& grad0_dir, double& val0, VectorXd& init_params, VectorXd& try_params, const double& precision, const double& accuracy, unsigned int max_iter, double& result)
 {
   double tryval = val0;
   double prev_val = tryval;
   double prev_alpha = tryval;
   double lo = tryval;
   double hi = tryval;
   double temp1 = tryval;
   double temp2 = tryval;
   double temp3 = tryval;
   unsigned int i = 1;
   bool bounds = true;
   
   prev_alpha = 0.;
   while(true)
   {
     try_params = direction;
     try_params *= alpha;
     try_params += init_params;
     
     bounds = function->calcValGrad(try_params, tryval, try_grad);
     for(unsigned int j=0;j<fixparameter.size();++j)
     {
       if(fixparameter[j] != 0)
       {
         try_grad[j] = 0.;
       }
     }
     if(bounds == false)
     {
       while(true)
       {
         alpha *= 0.5;
         try_params = direction;
         try_params *= alpha;
         try_params += init_params;
         
         bounds = function->calcValGrad(try_params, tryval, try_grad);
         for(unsigned int j=0;j<fixparameter.size();++j)
         {
           if(fixparameter[j] != 0)
           {
             try_grad[j] = 0.;
           }
         }
         if(bounds==true)
         {
           if(tryval < val0)
           {
             result=alpha;
             return true;
           }
         }
         if(i>max_iter){return false;}
         i++;
       }
       
       
       
       alpha = 0.5*(prev_alpha + alpha);
       i++;
       if(i > max_iter){return false;}
       continue;
     }
     
     temp1 = wolfe1*alpha;
     temp1 *= grad0_dir;
     temp1 += val0;
     if( ( tryval > temp1 ) || ( ( tryval > prev_val ) && (i>1) ))
     {
       lo = prev_alpha;
       hi = alpha;
       return zoom(wolfe1, wolfe2, lo, hi, try_grad, direction, grad0_dir, val0, prev_val, init_params, try_params, max_iter, result);
     }
     temp1 = try_grad.dot(direction);
     temp2 = -wolfe2*grad0_dir;
     temp3 = fabs(temp1);
     
     if( temp3 <= fabs(temp2) )
     {
       result = alpha;
       return bounds;
     }
     if( temp1 >= 0. )
     {
       lo = alpha;
       hi = prev_alpha;
       return zoom(wolfe1, wolfe2, lo, hi, try_grad, direction, grad0_dir, val0, tryval, init_params, try_params, max_iter, result);
     }
     prev_val = tryval;
     prev_alpha = alpha;
     alpha *= 2.;
     i++;
     if(i > max_iter){return false;}
   }
 }
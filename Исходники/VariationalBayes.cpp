void VariationalBayes::optimize(bool verbose,OPT_TYPE method,long maxIter,double ftol, double gtol){//{{{
   bool usedSteepest;
   long iteration=0,i,r;
   double boundOld,bound,squareNorm,squareNormOld=1,valBeta=0,valBetaDiv,natGrad_i,gradGamma_i,phiGradPhiSum_r;
   double *gradPhi,*natGrad,*gradGamma,*searchDir,*tmpD,*phiOld;
   gradPhi=natGrad=gradGamma=searchDir=tmpD=phiOld=NULL;
   MyTimer timer;
   // allocate stuff {{{
   //SimpleSparse *phiGradPhi=new SimpleSparse(beta);
   gradPhi = new double[T];
   // phiOld = new double[T]; will use gradPhi memory for this
   phiOld = NULL;
   natGrad = new double[T];
   if(method == OPTT_HS)
      gradGamma = new double[T];
   searchDir = new double[T];
   //searchDirOld = new double[T];
   //phiGradPhi_sum = new double[N];
   // }}}
#ifdef LOG_CONV
   ofstream logF(logFileName.c_str());
   logF.precision(15);
   logF<<"# iter bound squareNorm time(m) [M*means M*vars]"<<endl;
   if(logTimer)logTimer->setQuiet();
   #ifdef LONG_LOG
   vector<double> dirAlpha(M);
   #endif
#endif
   boundOld=getBound();
   timer.start();
   while(true){
      negGradient(gradPhi);
      // "yuck"
      //setVal(phiGradPhi,i,phi->val[i]*gradPhi[i]);
      //phiGradPhi->sumRows(phiGradPhi_sum);
      // removed need for phiGradPhi matrix:
      // removed need for phiGradPhi_sum
      /*for(r=0;r<N;r++){
         phiGradPhi_sum[r] = 0;
         for(i=phi->rowStart[r];i<phi->rowStart[r+1];i++) phiGradPhi_sum[r] += phi->val[i] * gradPhi[i];
      }*/

      // set natGrad & gradGamma
      squareNorm=0;
      valBeta = 0;
      valBetaDiv = 0;
      #pragma omp parallel for private(i,phiGradPhiSum_r,natGrad_i,gradGamma_i) reduction(+:squareNorm,valBeta,valBetaDiv)
      for(r=0;r<N;r++){
         phiGradPhiSum_r = 0;
         for(i = phi->rowStart[r]; i < phi->rowStart[r+1]; i++) 
            phiGradPhiSum_r += phi->val[i] * gradPhi[i];
         
         for(i = phi->rowStart[r]; i < phi->rowStart[r+1]; i++){
            natGrad_i = gradPhi[i] - phiGradPhiSum_r;
            gradGamma_i = natGrad_i * phi->val[i];
            squareNorm += natGrad_i * gradGamma_i;
            
            if(method==OPTT_PR){
               valBeta += (natGrad_i - natGrad[i])*gradGamma_i;
            }
            if(method==OPTT_HS){
               valBeta += (natGrad_i-natGrad[i])*gradGamma_i;
               valBetaDiv += (natGrad_i-natGrad[i])*gradGamma[i];
               gradGamma[i] = gradGamma_i;
            }
            natGrad[i] = natGrad_i;
         }
      }
      
      if((method==OPTT_STEEPEST) || (iteration % (N*M)==0)){
         valBeta=0;
      }else if(method==OPTT_PR ){
         // already computed:
         // valBeta=0;
         // for(i=0;i<T;i++)valBeta+= (natGrad[i]-natGradOld[i])*gradGamma[i];
         valBeta /= squareNormOld;
      }else if(method==OPTT_FR ){
         valBeta = squareNorm / squareNormOld;
      }else if(method==OPTT_HS ){
         // already computed:
         //valBeta=div=0;
         //for(i=0;i<T;i++){
         //   valBeta += (natGrad[i]-natGradOld[i])*gradGamma[i];
         //   div += (natGrad[i]-natGradOld[i])*gradGammaOld[i];
         //}
         if(valBetaDiv!=0)valBeta /= valBetaDiv;
         else valBeta = 0;
      }

      if(valBeta>0){
         usedSteepest = false;
         //for(i=0;i<T;i++)searchDir[i]= -natGrad[i] + valBeta*searchDirOld[i];
         // removed need for searchDirOld:
         #pragma omp parallel for
         for(i=0;i<T;i++)
            searchDir[i]= -natGrad[i] + valBeta*searchDir[i];
      }else{
         usedSteepest = true;
         #pragma omp parallel for
         for(i=0;i<T;i++)
            searchDir[i]= -natGrad[i];
      }

      //try conjugate step
      SWAPD(gradPhi,phiOld);
      memcpy(phiOld,phi_sm->val,T*sizeof(double)); // memcpy(phiOld,pack(),T*sizeof(double));
      unpack(phiOld,searchDir);
      bound = getBound();
      iteration++;
      // make sure there is an increase in L, else revert to steepest
      if((bound<boundOld) && (valBeta>0)){
         usedSteepest = true;
         #pragma omp parallel for
         for(i=0;i<T;i++)
            searchDir[i]= -natGrad[i];
         unpack(phiOld,searchDir);
         bound = getBound();
         // this should not be increased: iteration++;
      }
      if(bound<boundOld) { // If bound decreased even after using steepest, step back and quit.
         unpack(phiOld);
      }
      SWAPD(gradPhi,phiOld);
      if(verbose){
         #ifdef SHOW_FIXED
            messageF("iter(%c): %5.ld  bound: %.3lf grad: %.7lf  beta: %.7lf  fixed: %ld\n",(usedSteepest?'s':'o'),iteration,bound,squareNorm,valBeta,phi->countAboveDelta(0.999));
         #else
            messageF("iter(%c)[%5.lds]: %5.ld  bound: %.3lf grad: %.7lf  beta: %.7lf\n",(usedSteepest?'s':'o'),(long)timer.getTime(),iteration,bound,squareNorm,valBeta);
         #endif
      }else if(!quiet){
         messageF("\riter(%c): %5.ld  bound: %.3lf grad: %.7lf  beta: %.7lf      ",(usedSteepest?'s':'o'),iteration,bound,squareNorm,valBeta);
      }
#ifdef LOG_CONV
   if((iteration%100==0) ||
      ((iteration<500) && (iteration%50==0)) ||
      ((iteration<150) && (iteration%10==0)) ||
      ((iteration<50) && (iteration%5==0))){
      logF<<iteration<<" "<<bound<<" "<<squareNorm;
      if(logTimer)logF<<" "<<logTimer->current(0,'m');
      #ifdef LONG_LOG
      double alphaSum = 0, alphaVarNorm;
      // True 'alpha' - Dirichlet parameter is alpha+phiHat.
      for(i=1;i<M;i++){
         dirAlpha[i] = alpha[i] + phiHat[i];
         alphaSum += dirAlpha[i];
      }
      for(i=1;i<M;i++)logF<< " " << dirAlpha[i] / alphaSum;
      alphaVarNorm = alphaSum*alphaSum*(alphaSum+1);
      for(i=1;i<M;i++)logF<<" "<<dirAlpha[i]*(alphaSum-dirAlpha[i])/alphaVarNorm;
      #endif
      logF<<endl;
   }
#endif

      // convergence check {{{
      if(bound<boundOld){
         message("\nEnd: bound decrease\n");
         break;
      }
      if(abs(bound-boundOld)<=ftol){
         message("\nEnd: converged (ftol)\n");
         break;
      }
      if(squareNorm<=gtol){
         message("\nEnd: converged (gtol)\n");
         break;
      }
      if(iteration>=maxIter){
         message("\nEnd: maxIter exceeded\n");
         break;
      }
      // }}}
      // store essentials {{{
      squareNormOld=squareNorm;
      boundOld=bound;
      // }}}
      R_INTERUPT;
   }
   if(quiet){
      messageF("iter(%c): %5.ld  bound: %.3lf grad: %.7lf  beta: %.7lf\n",(usedSteepest?'s':'o'),iteration,bound,squareNorm,valBeta);
   }
#ifdef LOG_CONV
   logF<<iteration<<" "<<bound<<" "<<squareNorm;
   if(logTimer)logF<<" "<<logTimer->current(0,'m');
   #ifdef LONG_LOG
   double alphaSum = 0, alphaVarNorm;
   // True 'alpha' - Dirichlet parameter is alpha+phiHat.
   for(i=1;i<M;i++){
      dirAlpha[i] = alpha[i] + phiHat[i];
      alphaSum += dirAlpha[i];
   }
   for(i=1;i<M;i++)logF<< " " << dirAlpha[i] / alphaSum;
   alphaVarNorm = alphaSum*alphaSum*(alphaSum+1);
   for(i=1;i<M;i++)logF<<" "<<dirAlpha[i]*(alphaSum-dirAlpha[i])/alphaVarNorm;
   #endif
   logF<<endl;
   if(logTimer)logTimer->setVerbose();
   logF.close();
#endif
   // free memory {{{
   //delete phiGradPhi;
   delete[] gradPhi;
   delete[] natGrad;
   if(method == OPTT_HS)
      delete[] gradGamma;
   delete[] searchDir;
   //delete[] searchDirOld;
   //delete[] phiGradPhi_sum;
   // }}}
}//}}}
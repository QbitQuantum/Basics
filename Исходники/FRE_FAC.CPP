double MatterFreeE::TemperatureFind(double En,double Den,double Low,double Up,
                                    double Start,double Err,int NumIt)
{
   Current=this;
   E=En;D=Den;
   double T0=Start;
   int err;
#ifdef FZERO_TEMPERATURE_ITERATION
      if (4<(err=Fzero(DeltaFree,Low,Up,T0,Err,Err,100)) )
        {cout<<" Bad ZeroFzeroFreeE in MatterFreeE::TemperatureFind Not Zero\nfound T "
             <<T0<<" Mis "<<DeltaFree(T0)<<" err "<<err<<"\n";T0=Zero_Temp;}
#else
#ifdef FZERO_LOGTEMPERATURE_ITERATION
//                   ln(50)=3.91 ln(1e6)=13.8  ln(100)=4.6
    T0=log(Start);Low=log(Low);Up=log(Up);Err=0.1*Err;
    if (4<(err=Fzero(DeltaFreeLog,Low,Up,T0,Err,Err,100)) ) {
        cout<<" Bad ZeroFzeroFreeE in MatterFreeE::Temperature Not Zero\nfound T "
            <<exp(T0)<<" Mis "<<DeltaFreeLog(T0)<<" err "<<err<<"\n";
        T0 = MinimTmin;
    } else 
        T0=exp(T0);
#else
  MinFind1DClass *min1d=new MinFind1DClass(1,NULL);
  double MinError=Err,FoundEMis;
  int Cont=1,MaxIt=7,NumT=MaxIt,it;
  VecCl TmpPar(1),TmpStp(1);TmpPar[1]=L_T;TmpStp[1]=500;
  T0=Start;
#ifdef MULTIDIM_TEMPERATURE_ITERATION
  Derive2DStd *D2=new Derive2DStd(new DeriveStaticFunc(DeltaFree));
  MinFindNDimClass MinNd(D2,min1d,1e-10,1e-8,MinError);
  for (it=1;((it<=NumT)&&(Cont));it++) Cont=MinNd.Execute(TmpPar,TmpStp,1,FoundEMis);
  if (it>MaxIt)
      if (4<(err=Fzero(DeltaFree,Low,Up,T0,Err,Err,100)) )
        {cout<<" Bad ZeroFzeroFreeE in MatterFreeE::TemperatureFind Not Zero\nfound T "
             <<T0<<" Mis "<<DeltaFree(T0)<<" err "<<err<<"\n";T0=Zero_Temp;}
      else T0=TmpPar[1];
#else
  T0=log(Start);Low=log(Low);Up=log(Up);Err=0.1*Err;
  TmpPar[1]=log(TmpPar[1]);TmpStp[1]=log(TmpStp[1]);
  Derive2DStd *D2=new Derive2DStd(new DeriveStaticFunc(DeltaFreeLog));
  MinFindNDimClass MinNd(D2,min1d,1e-10,1e-8,MinError);
  for (it=1;((it<=NumT)&&(Cont));it++) Cont=MinNd.Execute(TmpPar,TmpStp,1,FoundEMis);
  if (it>MaxIt)
    if (4<(err=Fzero(DeltaFreeLog,Low,Up,T0,Err,Err,100)) )
     {cout<<" Bad ZeroFzeroFreeE in MatterFreeE::Temperature Not Zero\nfound T "
          <<exp(T0)<<" Mis "<<DeltaFreeLog(T0)<<" err "<<err<<"\n";T0=Zero_Temp;}
    else T0=exp(T0);
  else T0=exp(TmpPar[1]);

#endif
#endif
#endif
//#ifdef FZERO_TEMPERATURE_ITERATION
////   if (!ZeroNewtonIt(DeltaFree,T0,StndErr*0.1,100,1e6,Zero_Temp,0.8*T0,0.01))
////int Fzero(X_func f,double From,double To,double &Guess,double ErrorAbs,double ErrorRel,
////                  int MaxIter)
//    if (4<(err=Fzero(DeltaFree,50,1e6,T0,StndErr*0.1,StndErr*0.1,100)) )
//     {cout<<" Bad ZeroFzeroFreeE in MatterFreeE::Temperature Not Zero\nfound T "
//          <<T0<<" Mis "<<DeltaFree(T0)<<" err "<<err<<"\n";T0=Zero_Temp;}
////if (err!=0) cout<<" Mis E "<<DeltaFree(T0)<<" T "<<T0<<" err "<<err<<"\n";

  return T0;
}
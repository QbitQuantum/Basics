//typedef double* FOOL;
int MAPGetDir(double *Param,double *MaxStep,MatrCl &DirMat,double ErrorMatr) 
  {
//cout<<"   MAPGetDir  Begin  \n";
   int Dimen=Param[0],DimExp=(*MAPVar).ExperPoint[0],Ret=1;
   if ((Dimen>0) && (DimExp>0))
     {
      int k,k1;
      int Iter;
      VecCl TmpGr(DimExp),CurGr(DimExp);
      VecCl HiGrad(Dimen);
      MatrCl WMat1(Dimen),WMat2(Dimen);
      double TmpHi,CurHi=True_Hi(Param); 
//cout<<" Coreleft MAPDir "<<coreleft()<<"\n";
      double *TmpPar=new double[Dimen+1];
      double *NormDiag=new double[Dimen+1];
      VecCl *GrDat=new VecCl[Dimen+1];
      for (k=1;k<=Dimen;k++) GrDat[k].SetDim(DimExp);

      True_Gr(Param,CurGr.Ptr);
// begining of calculation of d(hi)/dx[k] in HiGrad[k]
//cout<<" Coreleft 90     "<<coreleft()<<"\n";
      for (k=1;k<=Dimen;k++)
        {
if (fabs(MaxStep[k])<MathZer) cout<<" MAPGetDir MaxStep k "<<MaxStep[k]<<"  "<<k<<"\n";
         movmem(Param,TmpPar,sizeof(double)*(Dimen+1));
         TmpPar[k]+=DERIVESTP*MaxStep[k];
         True_Gr(TmpPar,TmpGr.Ptr);
         for (k1=1;k1<=DimExp;k1++) 
           GrDat[k][k1]=(TmpGr[k1]-CurGr[k1])/(DERIVESTP*MaxStep[k]);
         TmpHi=True_Hi(TmpPar);
         HiGrad[k]=(CurHi-TmpHi)/(DERIVESTP*MaxStep[k]);
        }
//cout<<" Hi Grad "<<HiGrad<<"Cur_Hi "<<CurHi<<"\nMax Step ";
//      for (k=1;k<=Dimen;k++) cout<<MaxStep[k]<<"  ";cout<<"\n";
//ChRead();
//
//     end of calculation of d(hi)/dx[k] in HiGrad[k]}
//
//{ begining of calculation d(integral(dx[i]))/dx[k]=hmat[i,k]
//                                       D'[k]=correl[k]               }
      for (k=1;k<=Dimen;k++)
        {
         for (k1=k;k1<=Dimen;k1++) 
            WMat1(k,k1)=Correl_Func(DimExp,GrDat[k].Ptr,GrDat[k1].Ptr);
         if (WMat1(k,k)<MathZer) 
           {cout<<" Function does not depend from parameter "<<k<<". Exiting\n";
            Ret=0;goto exi;
           }
         double d=sqrt(WMat1(k,k));
if (d<MathZer) cout<<" MAPGetDir sqrt(WMat1(k,k)) k "<<d<<"  "<<k<<"\n";
         NormDiag[k]=1/d;//sqrt(WMat1(k,k));
        }
//cout<<" dxi/dxk \n"<<WMat1;
      for ( k=1;k<=Dimen;k++)
       { 
        for (k1=k;k1<=Dimen;k1++)
          {
           WMat1(k,k1)=WMat1(k,k1)*NormDiag[k]*NormDiag[k1];
           WMat1(k1,k)=WMat1(k,k1);
          }
       } 
//cout<<" dxi/dxk normalized\n"<<WMat1;
//  fwritem(nomparam,addr(hmat),1,1);k0:=ermes('first converted',-1);
//{ end      of calculation d(integral(dx[i]))/dx[k]=hmat[i,k]
//                                       D'[k,k]=correl[k]               }
//cout<<" Coreleft 129    "<<coreleft()<<"\n";

//      if ((Err=Jacobi(WMat1,1000,ErrorMatr,TmpPar,WMat1,Iter))!=0) 
//        {cout<<" Cannot Calculate Jacobi. Error ="<<Err<<" \n";exit(1);}
      if (!ReduceLQ(WMat1,WMat1,TmpPar,ErrorMatr)) 
        {cout<<" Cannot Calculate ReduceLQ. \n";Ret=0;goto exi;}
//cout<<" Coreleft 132=129"<<coreleft()<<"\n";
//cout<<" Eigen Vectors\n"<<WMat1<<" Eigen Val \n";ChRead();
//for ( k=1;k<=Dimen;k++) cout<<TmpPar[k]<<"   ";cout<<"\n";
      
//      Transpon(WMat1);  //Because ReduceLQ we have not to transpon
      WMat2=WMat1;
//cout<<" Coreleft 137    "<<coreleft()<<"\n";
//cout<<"Inverse ";
      Inverse(WMat1);
//cout<<" O Key \n";
//cout<<" Coreleft 139=137"<<coreleft()<<"\n";
      for ( k=1;k<=Dimen;k++)
       { 
        for ( k1=1;k1<=Dimen;k1++)
          {
         double d=sqrt(fabs(TmpPar[k1]));
if (d<MathZer) cout<<" MAPGetDir sqrt(fabs(TmpPar[k1])) k1 "<<d<<"  "<<k1<<"\n";
           WMat2(k,k1)=WMat2(k,k1)/d;//sqrt(fabs(TmpPar[k1]));
          } 
       } 
      WMat1=WMat2*WMat1;
//cout<< " Result Matr After Mull\n"<<WMat1;
      for ( k=1;k<=Dimen;k++)
       { 
        for ( k1=1;k1<=Dimen;k1++)
           WMat1(k,k1)=WMat1(k,k1)*NormDiag[k];
       } 
//cout<<" MaxStep: ";
      for ( k=1;k<=Dimen;k++)
       { 
        double s=0;
        for (int k1=1;k1<=Dimen;k1++)  s+=HiGrad[k1]*WMat1(k1,k);
        MaxStep[k]=s;
//cout<<MaxStep[k]<<"  ";
       } 
//cout<<"\n";
//ChRead();
//cout<<" Coreleft 158=90    "<<coreleft()<<"\n";
      DirMat=WMat1;
//cout<<" Coreleft 160 "<<coreleft()<<"\n";
//cout<< " Dir  Matr \n"<<DirMat;
//cout<<"MaxStep ";for (k=1;k<=Dimen;k++) cout<<MaxStep[k]<<"  ";cout<<"\n";
  exi:
    delete TmpPar;
    delete NormDiag;
    for ( k=0;k<=Dimen;k++)  {delete GrDat[k].Ptr;GrDat[k].Ptr=NULL;}
    delete GrDat;
//cout<< "End  MAPGetDir\n";
//cout<<" Coreleft MAPDir "<<coreleft()<<"\n";
   }
  return Ret;
 };
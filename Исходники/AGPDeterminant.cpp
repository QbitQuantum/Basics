  void
  AGPDeterminant::evaluateLogAndStore(ParticleSet& P) {

    //GeminalBasis->evaluate(P);
    GeminalBasis->evaluateForWalkerMove(P);//@@

    /* evaluate \f$ psi_{up}(iat)= \sum_{j} C_{ij} \phi_j^{u}({\bf r}_{iat})  \f$
     * \f$ psi_{down}(iat-Nup) =  \sum_{j} C_{ij} \phi_j^{d}({\bf r}_{iat})\f$
     */
    MatrixOperators::product(GeminalBasis->Y, Lambda, phiT);

    for(int u=0; u<Nup; u++) //paired block
    {
      for(int d=0, jat=Nup; d<Ndown; d++,jat++) 
      {
        //psiM(d,u) = BLAS::dot(BasisSize,phiT[u],GeminalBasis->y(jat));
        psiM(d,u) = BLAS::dot(BasisSize,phiT[u],GeminalBasis->Y[jat]);//@@
      }
      //unpaired block Ndown x unpaired
      for(int d=Ndown,unpaired=0; d<Nup; d++,unpaired++) 
      {
        //psiM(d,u) = BLAS::dot(BasisSize,LambdaUP[unpaired],GeminalBasis->y(u));
        psiM(d,u) = BLAS::dot(BasisSize,LambdaUP[unpaired],GeminalBasis->Y[u]);//@@
      }
    }

    CurrentDet = Invert(psiM.data(),Nup,Nup,WorkSpace.data(),Pivot.data());

    for(int iat=0; iat<Nup; iat++) {
      for(int d=0,jat=Nup; d<Ndown; d++,jat++) 
      {
        //dpsiU(iat,d)=dot(phiT[jat],GeminalBasis->dy(iat),BasisSize);
        //d2psiU(iat,d)=dot(phiT[jat],GeminalBasis->d2y(iat),BasisSize);
        dpsiU(iat,d)=dot(phiT[jat],GeminalBasis->dY[iat],BasisSize);//@@
        d2psiU(iat,d)=dot(phiT[jat],GeminalBasis->d2Y[iat],BasisSize);//@@
      }
      for(int d=Ndown,unpaired=0; d<Nup; d++,unpaired++) 
      {
        //dpsiU(iat,d)=dot(LambdaUP[unpaired],GeminalBasis->dy(iat),BasisSize);
        //d2psiU(iat,d)=dot(LambdaUP[unpaired],GeminalBasis->d2y(iat),BasisSize);
        dpsiU(iat,d)=dot(LambdaUP[unpaired],GeminalBasis->dY[iat],BasisSize);//@@
        d2psiU(iat,d)=dot(LambdaUP[unpaired],GeminalBasis->d2Y[iat],BasisSize);//@@
      }
      GradType rv=dot(psiM[iat],dpsiU[iat],Nup);
      ValueType lap=dot(psiM[iat],d2psiU[iat],Nup);
      myG[iat]=rv;
      myL[iat]=lap-dot(rv,rv);
    }

    for(int jat=Nup,d=0; jat<NumPtcls; jat++,d++) 
    {
      GradType rv;
      ValueType lap=0;
      for(int u=0; u<Nup; u++) 
      {
        ValueType dfac=psiM(u,d);
        //rv += dfac*(dpsiD(d,u)=dot(phiT[u],GeminalBasis->dy(jat),BasisSize));
        //lap += dfac*(d2psiD(d,u)=dot(phiT[u],GeminalBasis->d2y(jat),BasisSize));
        rv += dfac*(dpsiD(d,u)=dot(phiT[u],GeminalBasis->dY[jat],BasisSize));//@@
        lap += dfac*(d2psiD(d,u)=dot(phiT[u],GeminalBasis->d2Y[jat],BasisSize));//@@
      }
      myG[jat]=rv;
      myL[jat]=lap-dot(rv,rv);
    }

    dY = GeminalBasis->dY;
    d2Y = GeminalBasis->d2Y;
  }
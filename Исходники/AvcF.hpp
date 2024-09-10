  //! RHS: x->z  (x'=z).
  inline void operator()(double t,double x[],double z[]) const
  {
    // references to clarify (?) the code:
    const double& nConIntraK =x[0];
    const double& nConIntraNa =x[1];
    const double& nConIntraCa =x[2];
    const double& nConIntraCl =x[3];
    const double& nConIntraglu =x[4];
    const double& aConIntraK =x[5];
    const double& aConIntraNa =x[6];
    const double& aConIntraCa =x[7];
    const double& aConIntraCl =x[8];
    const double& aConIntraglu =x[9];
    const double& ConExtraK =x[10];
    const double& ConExtraNa =x[11];
    const double& ConExtraCa =x[12];
    const double& ConExtraCl =x[13];
    const double& ConExtraglu =x[14];
    const double& nVm =x[15];
    const double& aVm =x[16];
    const double& nPropVol =x[17];
    const double& aPropVol =x[18];
    //------------Compute------------------
    double depol=fdepol(t,x[20]);
    // calcul des potentiels d'équilibre par la loi de Nernst 
  
    double  nEK = (RTF)*log(ConExtraK/nConIntraK);
    //double nECa = ((RT)/(2*F))*log(ConExtraCa/nConIntraCa); 
    double nENa = (RTF)*log(ConExtraNa/nConIntraNa); 
    double nEglu = (-RTF)*log(ConExtraglu/nConIntraglu);
    double nECl = (-RTF)*log(ConExtraCl/nConIntraCl);

    double aEK = (RTF)*log(ConExtraK/aConIntraK);
    //double aECa = ((RT)/(2*F))*log(ConExtraCa/aConIntraCa); 
    double aENa = (RTF)*log(ConExtraNa/aConIntraNa); 
    double aEglu = (-RTF)*log(ConExtraglu/aConIntraglu); 
    double aECl = (-RTF)*log(ConExtraCl/aConIntraCl); 


    //courant du canal potassique KDR
	
    double  nmeqKDR = (0.0047*(nVm - 8)/(1 - exp(-(nVm - 8)/12))) / 
      (0.0047*( nVm - 8)/(1 - exp(-(nVm - 8)/12.0)) + exp(-(nVm + 127)/30.0)); 
    double nheqKDR = 1/(1 + exp((nVm + 25)/4.0)); 
    double nIKDR = 1.e-3 * ngKDR * nmeqKDR*nmeqKDR * nheqKDR *(nVm - nEK); 
         
    double ameqKDR = (0.0047*(aVm - 8)/(1 - exp(-(aVm - 8)/12))) /
      (0.0047*( aVm - 8)/(1 - exp(-(aVm - 8)/12)) + exp(-(aVm + 127)/30)); 
    double aheqKDR = 1/(1 + exp((aVm + 25)/4)); 
    double aIKDR = 1.e-3 * agKDR * ameqKDR* ameqKDR * aheqKDR *(aVm - aEK); 
    //courant du canal potassique BK  
	
    double nmeqBK = 250*nConIntraCa*exp(nVm/24)/(250*nConIntraCa*exp(nVm/24) +
  						 0.1*exp(-nVm/24)); 
    double nIBK = 1.e-3 * ngBK * nmeqBK *(nVm - nEK); 
          
    double ameqBK = 250*aConIntraCa*exp(aVm/24)/(250*aConIntraCa*exp(aVm/24) +
  						 0.1*exp(-aVm/24)); 
    double aIBK = 1.e-3 * agBK * ameqBK * (aVm - aEK);  

    //courant du canal potassiques Kir  
	
    double ameqKir = 1/(2+exp(1.62*(FRT)*(aVm-aEK))); 
    double aIKir =  1.e-3  * agKir * ameqKir * (ConExtraK/(ConExtraK+13))*
      (aVm - aEK);                 

    //courant du canal calcique CaHVA
          
    double nCurlyPhi= FRT*nVm; 
    double nA1 = (nConIntraCa*exp(2*nCurlyPhi)-ConExtraCa) / 
      (exp(2*nCurlyPhi) - 1); 
              
    double  namCaHVA = 8.5/(1 + exp(-(nVm - 8)/12.5)); 
    double  nbmCaHVA = 35/(1 + exp((nVm + 74)/14.5)); 
    double  nmeqCaHVA = namCaHVA/(namCaHVA  + nbmCaHVA) ; 
    double  nahCaHVA =  0.0015/(1 + exp((nVm + 29)/8)); 
    double  nbhCaHVA = 0.0055/(1 + exp(-(nVm + 23)/8)); 
    double  nheqCaHVA = nahCaHVA/(nahCaHVA  + nbhCaHVA) ; 
    double  nICaHVA = 10 * F * npHVA * ngCaHVA * 4 * nCurlyPhi * 
      nmeqCaHVA * nheqCaHVA * nA1 ; 
    //nICaHVA*=bCaHVA;
                   
    double  aCurlyPhi= FRT*aVm; 
    double  aA1 = (aConIntraCa*exp(2*aCurlyPhi)-ConExtraCa) / 
      (exp(2*aCurlyPhi) - 1); 
    
    double  aamCaHVA = 8.5/(1 + exp(-(aVm - 8)/12.5)); 
    double  abmCaHVA = 35/(1 + exp((aVm + 74)/14.5)); 
    double  ameqCaHVA = aamCaHVA/(aamCaHVA  + abmCaHVA) ; 
    double  aahCaHVA =  0.0015/(1 + exp((aVm + 29)/8)); 
    double  abhCaHVA = 0.0055/(1 + exp(-(aVm + 23)/8)); 
    double  aheqCaHVA = aahCaHVA/(aahCaHVA  + abhCaHVA) ; 
    double  aICaHVA = 10 * F * apHVA * agCaHVA * 4 * aCurlyPhi *
      ameqCaHVA * aheqCaHVA * aA1 ; 
    //aICaHVA*=bCaHVA;

  //courant du canal sodique NaP
    double  namNaP =200/(1 + exp(-(nVm - 18)/16)); 
    double  nbmNaP = 25/(1 + exp((nVm + 58)/8)); 
    double  nmeqNaP = namNaP/(namNaP  + nbmNaP) ; 
    double  nINaP = (1.e-3 * ngNaP * nmeqNaP * (nVm - nENa));// *bNap;
          
    double aamNaP =200/(1 + exp(-(aVm - 18)/16)); 
    double abmNaP = 25/(1 + exp((aVm + 58)/8)); 
    double ameqNaP = aamNaP/(aamNaP  + abmNaP) ; 
    double aINaP = (1.e-3 * agNaP * ameqNaP * (aVm - aENa));//*bNap;

    //courants dus au récepteur NMDA et AMPA
	
    double nConGLU=ConExtraglu;
          
    double nA2 = 72*nConGLU/(72*nConGLU + 6.6) ; 
    double nB2 = 1/(1 + 0.028*exp(-0.062*nVm)) ;
          
    double  nCK = ((nConIntraK/ConExtraK)*exp(nCurlyPhi)- 1)/
      (exp(nCurlyPhi)- 1);
    double ngKNMDA = ((nPK*F*F)/(RT))*ConExtraK ; 
    double nIKNMDA = 1.e-3 * ngKNMDA * nA2 * nB2 * nCK * nVm; 
              
    double nCNa = ((nConIntraNa/ConExtraNa)*exp(nCurlyPhi)- 1)/
      (exp(nCurlyPhi)- 1);
    double ngNaNMDA = ((nPK*F*F)/(RT))*ConExtraNa; 
    double nINaNMDA = 1.e-3 * ngNaNMDA * nA2 * nB2 * nCNa * nVm; 
          
    double nCCa = ((nConIntraCa/ConExtraCa)*exp(2*nCurlyPhi)- 1)/
      (exp(2*nCurlyPhi)- 1);
    double ngCaNMDA = ((4*6*nPK*F*F)/(RT))*ConExtraCa; 
    double nICaNMDA = 1.e-3 * ngCaNMDA * nA2 * nB2 * nCCa * nVm; 
    //nIKNMDA*=bNMDA;
    //nINaNMDA*=bNMDA;
    //nICaNMDA*=bNMDA;
     
    double aConGLU=ConExtraglu;
          
    double aA2 = 1100*aConGLU/(1100*aConGLU + 190) ; 
    double aCK = ((aConIntraK/ConExtraK)*exp(aCurlyPhi)- 1)/
      (exp(aCurlyPhi)- 1);

    double agKAMPA = ((aPK*F*F)/(RT))*ConExtraK ; 
    double aIKAMPA = 1.e-3 * agKAMPA * aA2 * aCK * aVm; 
              
    double aCNa = ((aConIntraNa/ConExtraNa)*exp(aCurlyPhi)- 1)/
      (exp(aCurlyPhi)- 1);
    double agNaAMPA = ((aPK*F*F)/(RT))*ConExtraNa; 
    double aINaAMPA = 1.e-3 * agNaAMPA * aA2 * aCNa * aVm; 
    //aIKAMPA*=bAMPA;
    //aINaAMPA*= bAMPA;
    //courants de la pompe Na+/K+  
          
    double nCapitalPhi = FRT*(nVm + 176.5); 
    double nA3 = pow(ConExtraK/(ConExtraK + 3.7),2) ; 
    double nB3 = pow(nConIntraNa/(nConIntraNa + 0.6),3) ; 
    double nC3 = (0.052*sinh(nCapitalPhi))/(0.026*exp(nCapitalPhi) + 
  					  22.5*exp(-nCapitalPhi)); 
    double nIKpompeKNa = -0.01 * nrNaK * depol * nA3 * nB3 * nC3 ; 
          
    //double nINapompeKNa = (3/2)*(-10)^(-2) * nrNaK * depol * nA3 * nB3 * nC3; 
    double nINapompeKNa = (1.5)*0.01 * nrNaK * depol * nA3 * nB3 * nC3;

    double aCapitalPhi = FRT*(aVm + 176.5); 
    double aA3 = pow(ConExtraK/(ConExtraK + 3.7),2) ; 
    double aB3 = pow(aConIntraNa/(aConIntraNa + 0.6),3) ; 
    double aC3 = (0.052*sinh(aCapitalPhi))/(0.026*exp(aCapitalPhi) +
  					    22.5*exp(-aCapitalPhi)); 
    double aIKpompeKNa = -0.01 * arNaK * depol * aA3 * aB3 * aC3 ; 
  
    double aINapompeKNa = (1.5)*0.01  * arNaK * depol * aA3 * aB3 * aC3; 

    //courant de la pompe Ca2+
          
    double nICapompe = depol*ngCapompe*0.01*nConIntraCa/(nConIntraCa+0.0002);
    double aICapompe = depol*agCapompe*0.01*aConIntraCa/(aConIntraCa+0.0002);

    //courant de la pompe Cl-
           
    double nIClpompe=-0.01 * depol *ngClpompe * nConIntraCl/(nConIntraCl+25);
    double aIClpompe=-0.01 * depol *agClpompe * aConIntraCl/(aConIntraCl+25);  


    //courants de l'antiport Na+/Ca2+   
          
    double aa=F/(2*RT);
 
    double nA4 = pow(nConIntraNa,3)*ConExtraCa*exp(aa*nVm)
      - pow(ConExtraNa,3)*nConIntraCa*exp(-aa*nVm); 
    double nB4 = 1 + 0.0001*(pow(ConExtraNa,3)*nConIntraCa 
  			     + pow(nConIntraNa,3)*ConExtraCa); 

    double nICaantiport = -0.01*(nrNaCa/20736.0) * nA4/nB4; 
                
    double nINaantiport = (1.5)* 0.01*(nrNaCa/20736.0) * nA4/nB4; 
          
    double aA4 = pow(aConIntraNa,3)*ConExtraCa*exp(aa*aVm)
      - pow(ConExtraNa,3)*aConIntraCa*exp(-aa*aVm); 
    double aB4 = 1 + 0.0001*(pow(ConExtraNa,3)*aConIntraCa 
  			     + pow(aConIntraNa,3)*ConExtraCa);         
    double aICaantiport = -0.01*  (arNaCa/20736.0) * aA4/aB4; 
                
    double aINaantiport = (1.5)* 0.01*(arNaCa/20736.0) * aA4/aB4;   

    //nICaantiport*=bNaCa;  nINaantiport*=bNaCa;
    //aICaantiport*=bNaCa;  aINaantiport*=bNaCa;
    //courants du transporteur du glutamate
          
    double nEtransp = (RT/F)*log(
  				 pow(ConExtraNa/nConIntraNa,3)*
  				 (nConIntraK/ConExtraK)*
  				 (ConExtraglu/nConIntraglu)
  				 );
 
    //double nIglu = -0.001 * ngtransp * (nVm - nEtransp);
          
    double nINatransporteur = 3*0.001 * ngtransp * (nVm - nEtransp); 
    double nIKtransporteur = -0.001 * ngtransp * (nVm - nEtransp); 
    double nIglutransporteur = -0.001 * ngtransp * (nVm - nEtransp);   
          
          
    double aEtransp = (RT/F)*log(
  				 pow(ConExtraNa/aConIntraNa,3)*
  				 (aConIntraK/ConExtraK)*
  				 (ConExtraglu/aConIntraglu)
  				 );


    //double aIglu = -0.001 * agtransp * (aVm - aEtransp);
          
    double aINatransporteur = 3*0.001 * agtransp * (aVm - aEtransp); 
    double aIKtransporteur = -0.001 * agtransp * (aVm - aEtransp); 
    double aIglutransporteur = -0.001 * agtransp * (aVm - aEtransp); 
 
    // nINatransporteur*=bGLU; nIKtransporteur*=bGLU;
    // nIglutransporteur*=bGLU;aINatransporteur*=bGLU;
    // aIKtransporteur*=bGLU; aIglutransporteur*=bGLU;   
    // courants du transporteur Na/K/Cl
          
    double aEinvNaKCl = -2*aECl + aEK + aENa;

    double aINacotransp = -0.001*arNaKCl * aEinvNaKCl;
         
    double aIKcotransp = -0.001*arNaKCl * aEinvNaKCl;
    
    double aIClcotransp = 2*0.001*arNaKCl * aEinvNaKCl;

    // aINacotransp*=bNaKCl;
    // aIKcotransp*=bNaKCl;
    // aIClcotransp*=bNaKCl;
    //courants de glutamate
          
    double nIgludiff = 0.001 * ngglu * (nVm - nEglu); 
    double aIgludiff = 0.001 * agglu * (aVm - aEglu); 
          
    //courant du canal Cl-
          
    double  nEinvKCl = nECl - nEK;
    double  nIClglob = -0.001 * ngClglob *  nEinvKCl;
    double  nIKglob = 0.001 * ngClglob *  nEinvKCl;
    double aEinvKCl = aECl - aEK;
    double aIClglob = -0.001 * agClglob *  aEinvKCl;
    double aIKglob = 0.001 * agClglob *  aEinvKCl;

    //courants stretch pour le Cl

    double nIstre = - ngstre * 
      (nPropVol0 + 50 * (nPropVol - nPropVol0))/nPropVol0;
          
    double aIstre = - agstre * 
      (aPropVol0 + 50 * (aPropVol - aPropVol0))/aPropVol0;
                   
    // courants Cl
          
    double nICl = 0.001 * ngCl*(nVm-nECl);
    double aICl = 0.001 * agCl*(aVm-aECl); 
           
    //somme des courants

  
    double  nSommeCourantsK = nIKDR + nIBK + nIKNMDA + nIKpompeKNa +
      nIKtransporteur + nIKglob; 
                  
    double  nSommeCourantsCa  = nICaHVA + nICaNMDA + nICaantiport + nICapompe; 
                  
    double nSommeCourantsNa   = nINaP + nINaNMDA + nINapompeKNa + 
      nINaantiport + nINatransporteur ; 
         
    double  nSommeCourantsglu  = nIglutransporteur + nIgludiff ; 
         
    double  nSommeCourantsCl = nICl + nIClglob + nIClpompe + nIstre; 
                 
    // double  nSommeCourantsCat  = nSommeCourantsNa + nSommeCourantsK +
    //   nSommeCourantsCa ;
        
    // double  ncourants  = nSommeCourantsCat + nSommeCourantsCl +
    //   nSommeCourantsglu ;
        
         
    double aSommeCourantsK = aIKDR + aIKir + aIBK + aIKAMPA + aIKpompeKNa +
      aIKtransporteur + aIKcotransp + aIKglob; 
                  
    double aSommeCourantsCa  = aICaHVA + aICaantiport +
      aICapompe; 
                  
    double  aSommeCourantsNa   = aINaP + aINaAMPA + aINapompeKNa +
      aINaantiport + aINatransporteur + aINacotransp ; 
         
    double  aSommeCourantsglu   = aIglutransporteur + aIgludiff ; 
         
    double  aSommeCourantsCl = aICl + aIClglob + aIClpompe + aIClcotransp +
    aIstre;
               
    // double  aSommeCourantsCat  = aSommeCourantsNa + aSommeCourantsK +
    //   aSommeCourantsCa ;
    
  
    // double acourants  = aSommeCourantsCat + aSommeCourantsCl +
    //   aSommeCourantsglu ;
         
    //------ F:------------------------------------------
    double snfv=1000*n1*nsurf/(F*v);

    z[0]=-snfv*nSommeCourantsK;
    z[1]=-snfv*nSommeCourantsNa;
    z[2]=-snfv*nSommeCourantsCa/2.0;
    z[3]= snfv*nSommeCourantsCl;
    z[4]= snfv*nSommeCourantsglu;

    const double safv=1000*n2*asurf/(F*v);
    z[5]=-safv*aSommeCourantsK;
    z[6]=-safv*aSommeCourantsNa;
    z[7]=-safv*aSommeCourantsCa/2.0;
    z[8]= safv*aSommeCourantsCl;
    z[9]=safv*aSommeCourantsglu;

    z[10]=snfv*nSommeCourantsK+safv*aSommeCourantsK;
    z[11]=snfv*nSommeCourantsNa+safv*aSommeCourantsNa;
    z[12]=snfv*nSommeCourantsCa/2.0+safv*aSommeCourantsCa/2.0;
    z[13]=-snfv*nSommeCourantsCl-safv*aSommeCourantsCl;
    z[14]=-snfv*nSommeCourantsglu-safv*aSommeCourantsglu;

    //---Vmn et Vma:

    z[15]=-1000.0*(nsurf/ncap)*(nSommeCourantsNa+nSommeCourantsK+
  				nSommeCourantsCa+
  				nSommeCourantsCl+nSommeCourantsglu);

    z[16]= -1000.0*(asurf/acap)*(aSommeCourantsNa+
  				 aSommeCourantsK+aSommeCourantsCa+
  				 aSommeCourantsCl+aSommeCourantsglu);

  //
    double Cn=nConIntraK+nConIntraNa+nConIntraCa+nConIntraCl+nConIntraglu;
    double Ca=aConIntraK+aConIntraNa+aConIntraCa+aConIntraCl+aConIntraglu;
    double Ce=ConExtraK+ConExtraNa+ConExtraCa+ConExtraCl+ConExtraglu;


    //---fn:
  
    z[17]=alpha_n*(Cn+nnP0/(v*nPropVol)-Ce);
		
		
    //---fa:
    z[18]=alpha_a*(Ca+anP0/(v*aPropVol)-Ce);


    //---transformation pour utiliser les variables "primales":
    for(int i=0;i<5;i++)
      z[i]=(z[i]-x[i]*z[17])/nPropVol;
    for(int i=5;i<10;i++)
      z[i]=(z[i]-x[i]*z[18])/aPropVol;
    for(int i=10;i<15;i++)
      z[i]=(z[i]+x[i]*(z[17]+z[18]))/(1.0-aPropVol-nPropVol);

    //---recuperation:
    recup(x,z[19],z[20]);
  }
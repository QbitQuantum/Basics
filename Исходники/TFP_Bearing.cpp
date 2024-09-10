int
TFP_Bearing::kt3Drma(double *v, double *vp, double *Fr, double A, double *P, double *vpi) {

  Vector vF (v, 8); 
  Vector vpF (vp, 8); 
  Vector FrF (Fr, 8); 
  Vector PF (P,4);  

  /*
  opserr << "v: " << vF;
  opserr << "vp: " << vpF;
  opserr << "Fr: " << FrF;
  opserr << "A: " << A << endln;
  opserr << "P: " << PF;
  */

  static double Ri[8];
  static double R[8];
  static double N[4];

  static Matrix kcont(8,8);
  static Matrix krot(8,8);

  int cont = 0;

  kthat.Zero(); 
  kt.Zero(); 
  ks.Zero(); 
  Af.Zero(); 
  kcont.Zero(); 
  krot.Zero();
			
  for (int i=0; i<4; i++)
    N[i] = A;
  
  for (int i=0; i<4; i++) {
    int z=4+i;
    Ri[i]=sqrt((r[i]-h[i])*(r[i]-h[i]) - v[z]*v[z]);
    Ri[z]=sqrt((r[i]-h[i])*(r[i]-h[i]) - v[i]*v[i]);
    d[i] = r[i] - sqrt(r[i]*r[i]) - sqrt(v[i]*v[i]+v[z]*v[z]);
    N[i] = A + sqrt((P[0]-P[2])*(P[0]-P[2]) + (P[1]-P[3])*(P[1]-P[3])) * 
      sqrt(v[i]*v[i]+v[z]*v[z])/r[i];
    R[i] = Ri[i];
    R[z] = Ri[z];
  }
  
  double dh =0;
  for (int i=0; i<4; i++) {
    dh += d[i];
  }
  
  //  R[0] = (Ri[0]*Ri[2])/(Ri[2]+fabs(v[2])*Ri[0]);
  //  R[1]=(Ri[1]*Ri[3])/(Ri[3]+fabs(v[3])*Ri[1]);
  //  R[4]=(Ri[4]*Ri[6])/(Ri[6]+fabs(v[4])*Ri[6]);
  //  R[5]=(Ri[5]*Ri[7])/(Ri[7]+fabs(v[5])*Ri[7]);

  double PNorm = 0.0;
  for (int i=0; i<4; i++) {
    PNorm += P[i]*P[i];
  }
  PNorm = sqrt(PNorm);
  
  N[0]=A+PNorm*(sqrt(v[0]*v[0]+v[4]*v[4])/r[0]+sqrt(v[2]*v[2]+v[6]*v[6])/r[2]);
  N[1]=A+PNorm*(sqrt(v[1]*v[1]+v[5]*v[5])/r[1]+sqrt(v[3]*v[3]+v[7]*v[7])/r[3]);

  for (int i=0; i<4; i++) {
    int z=4+i;
    //    double vyield=0.01;
    double qYield=mu[i]*N[i];
    double k0=qYield/vyield;
    
    //get trial shear forces of hysteretic component
    double qTrialx = k0*(v[i] -vs[i]- vp[i]);
    double qTrialy = k0*(v[z] -vs[z]- vp[z]);

    // compute yield criterion of hysteretic component
    double qTrialNorm = sqrt(qTrialx*qTrialx+qTrialy*qTrialy);
    double Y = qTrialNorm - qYield;
 
    // elastic step -> no updates for pastic displacements required
    if (Y <= 0 ) {
      // set tangent stiffnesses
      ks(i,i) = k0 + N[i]/R[i];
      ks(z,z) = k0 + N[i]/R[z];
      vpi[i] = vp[i];
      vpi[z] = vp[z];

    // plastic step -> return mapping
    } else {    
      // compute consistency parameters
      double dGamma = Y/k0;
      // update plastic displacements
      vpi[i] = vp[i] + dGamma*qTrialx/qTrialNorm;
      vpi[z] = vp[z] + dGamma*qTrialy/qTrialNorm;
      //  set tangent stiffnesses
      double qTrialNorm3 = qTrialNorm*qTrialNorm*qTrialNorm;
      ks(i,i) =  qYield*k0*qTrialy*qTrialy/qTrialNorm3 + N[i]/R[i];
      ks(i,z) = -qYield*k0*qTrialx*qTrialy/qTrialNorm3;
      ks(z,i) = -qYield*k0*qTrialx*qTrialy/qTrialNorm3;
      ks(z,z) =  qYield*k0*qTrialx*qTrialx/qTrialNorm3 + N[i]/R[z];
    }

    //opserr << "ks: " << ks;

    // restrainer contact stiffness
    double vt=sqrt(v[i]*v[i]+v[z]*v[z]); //local displacment of surface
    double rt=(dOut[i]-dIn[i])/2.0;  //restrainer distance
    double del=0.1;

    if (vt>rt) {
      cont=1;
      double krim=k0*2;
      // set restrainer stiffnesses
      double vi2 = v[i]*v[i];
      double vz2 = v[z]*v[z];
      kcont(i,i) =  krim*v[i]*v[i]/(vi2+vz2);
      kcont(i,z) =  krim*v[z]*v[i]/(vi2+vz2);
      kcont(z,i) =  krim*v[z]*v[i]/(vi2+vz2);
      kcont(z,z) =  krim*v[z]*v[z]/(vi2+vz2);
       
      //force rotation matrix
      double F=sqrt(Fr[i]*Fr[i]+Fr[z]*Fr[z]);
      krot(i,i) =  F* ((v[i]+del)/sqrt((v[i]+del)*(v[i]+del)+vz2) - (v[i]-del)/sqrt((v[i]-del)*(v[i]-del)+vz2));
      krot(i,z) =  F* (v[i]/sqrt(vi2+(v[z]+del)*(v[z]+del)) - v[i]/sqrt(vi2+(v[z]-del)*(v[z]-del)));
      krot(z,i) =  F* (v[z]/sqrt((v[i]+del)*(v[i]+del)+vz2) - v[z]/sqrt((v[i]-del)*(v[i]-del)+vz2));
      krot(z,z) =  F* ((v[z]+del)/sqrt(vi2+(v[z]+del)*v[z]+del) - (v[z]-del)/sqrt(vi2+(v[z]-del)*v[z]-del));
    }
  }

    
  double del = 0.1;

  for (int i=0; i<8; i++)
    for (int j=0; j<8; j++)
      ksrest(i,j)=kcont(i,j)+krot(i,j)/(del * 2.0);

  //  opserr << "ksrest: " << ksrest;

  Af.Zero();
  Af(0,4) = Ri[0];
  Af(1,5) = Ri[1];
  Af(2,0) = Ri[2]/(Ri[2]+Ri[3]); 
  Af(2,2) = -Ri[2]/(Ri[2]+Ri[3]);
  Af(2,4) = -Ri[2]*(Ri[0]+Ri[3])/(Ri[2]+Ri[3]);
  Af(2,5) = Ri[2]*(-Ri[1]+Ri[3])/(Ri[2]+Ri[3]);
  Af(3,0) = Ri[3]/(Ri[2]+Ri[3]);
  Af(3,2) = -Ri[3]/(Ri[2]+Ri[3]);
  Af(3,4) = Ri[3]*(-Ri[0]+Ri[2])/(Ri[2]+Ri[3]);
  Af(3,5) = Ri[3]*(-Ri[2]-Ri[1])/(Ri[2]+Ri[3]);
  Af(4,6) = Ri[4];
  Af(5,7) = Ri[5];
  Af(6,1) = Ri[6]/(Ri[6]+Ri[7]);
  Af(6,3) = -Ri[6]/(Ri[6]+Ri[7]);
  Af(6,6) = -Ri[6]*(Ri[4]+Ri[7])/(Ri[6]+Ri[7]);
  Af(6,7) = Ri[6]*(-Ri[5]+Ri[7])/(Ri[6]+Ri[7]);
  Af(7,1) = Ri[7]/(Ri[6]+Ri[7]);
  Af(7,3) = -Ri[7]/(Ri[6]+Ri[7]);
  Af(7,6) = Ri[7]*(-Ri[4]+Ri[6])/(Ri[6]+Ri[7]);
  Af(7,7) = Ri[7]*(-Ri[6]-Ri[5])/(Ri[6]+Ri[7]);


  //  opserr << "Af: " << Af;
  //  opserr << "ks: " << ks;
  //  opserr << "ksrest: " << ksrest;

  static Matrix KsPlusKsrest(8,8);


  KsPlusKsrest = ks;
  KsPlusKsrest += ksrest;
  KsPlusKsrest(0,2) = KsPlusKsrest(0,2) + N[0]/R[2];
  KsPlusKsrest(1,3) = KsPlusKsrest(1,3) + N[1]/R[5];
  KsPlusKsrest(4,6) = KsPlusKsrest(4,6) + N[4]/R[6];
  KsPlusKsrest(5,7) = KsPlusKsrest(5,7) + N[5]/R[7];
    
  kt.addMatrixTripleProduct(0.0, Af, KsPlusKsrest,1.0);

  //  opserr << "kt:" << kt;

  static Matrix Kee(4,4);

  for (int i=0; i<4; i++) {
    for (int j=0; j<4; j++) {
      kthat(i,j) = kt(i,j);
      Kee(i,j) = kt(i+4, j+4);
      kei(i,j) = kt(i+4, j);
    }
  }

  Kee.Invert(kee);
  kthat.addMatrixTripleProduct(1.0, kei, kee, -1.0);

  //  opserr << "kthat: " << kthat;

  return cont;
}
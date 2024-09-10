void computeEdgeSE3Gradient(Isometry3d& E,
                        Matrix6d& Ji, 
                        Matrix6d& Jj,
                        const Isometry3d& Z, 
                        const Isometry3d& Xi,
                        const Isometry3d& Xj,
                        const Isometry3d& Pi, 
                        const Isometry3d& Pj
                        ){
  // compute the error at the linearization point
  const Isometry3d A=Z.inverse()*Pi.inverse();
  const Isometry3d B=Xi.inverse()*Xj;
  const Isometry3d C=Pj;
 
  const Isometry3d AB=A*B;  
  const Isometry3d BC=B*C;
  E=AB*C;

  const Matrix3d Re=E.rotation();
  const Matrix3d Ra=A.rotation();
  const Matrix3d Rb=B.rotation();
  const Matrix3d Rc=C.rotation();
  const Vector3d tc=C.translation();
  //const Vector3d tab=AB.translation();
  const Matrix3d Rab=AB.rotation();
  const Vector3d tbc=BC.translation();  
  const Matrix3d Rbc=BC.rotation();

  Matrix<double, 3 , 9 >  dq_dR;
  compute_dq_dR (dq_dR, 
     Re(0,0),Re(1,0),Re(2,0),
     Re(0,1),Re(1,1),Re(2,1),
     Re(0,2),Re(1,2),Re(2,2));

  Ji.setZero();
  Jj.setZero();
  
  // dte/dti
  Ji.block<3,3>(0,0)=-Ra;

  // dte/dtj
  Jj.block<3,3>(0,0)=Ra*Rb;

  // dte/dqi
  {
    Matrix3d S;
    skewT(S,tbc);
    Ji.block<3,3>(0,3)=Ra*S;
  }

  // dte/dqj
  {
    Matrix3d S;
    skew(S,tc);
    Jj.block<3,3>(0,3)=Rab*S;
  }

  // dre/dqi
  {
    double buf[27];
    Map<Matrix<double, 9,3> > M(buf);
    Matrix3d Sxt,Syt,Szt;
    skewT(Sxt,Syt,Szt,Rbc);
    Map<Matrix3d> Mx(buf);    Mx = Ra*Sxt;
    Map<Matrix3d> My(buf+9);  My = Ra*Syt;
    Map<Matrix3d> Mz(buf+18); Mz = Ra*Szt;
    Ji.block<3,3>(3,3) = dq_dR * M;
  }

  // dre/dqj
  {
    double buf[27];
    Map<Matrix<double, 9,3> > M(buf);
    Matrix3d Sx,Sy,Sz;
    skew(Sx,Sy,Sz,Rc);
    Map<Matrix3d> Mx(buf);    Mx = Rab*Sx;
    Map<Matrix3d> My(buf+9);  My = Rab*Sy;
    Map<Matrix3d> Mz(buf+18); Mz = Rab*Sz;
    Jj.block<3,3>(3,3) = dq_dR * M;
  }

}
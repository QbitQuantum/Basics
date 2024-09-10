void localizerGVG::propagate(double Vm, double Wm, double dt) {  
  Matrix3d Fr;
  Fr<<1, 0, -Vm*dt*sin(oldYaw),
      0, 1,  Vm*dt*cos(oldYaw),
      0, 0,  1;
  MatrixXd Gr(3,2);
  Gr<< -dt*cos(oldYaw), 0, 
       -dt*sin(oldYaw), 0,
        0,             -dt;
    
  P.block(0,0,3,3)=Fr*P.block(0,0,3,3)*Fr.transpose()+Gr*Qr*Gr.transpose();
  CF=Fr*CF;
  normalizeCovariance();
}
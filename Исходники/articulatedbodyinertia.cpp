 ArticulatedBodyInertia operator*(const Frame& T,const ArticulatedBodyInertia& I){
     Frame X=T.Inverse();
     //mb=ma
     //hb=R*(h-m*r)
     //Ib = R(Ia+r x h x + (h-m*r) x r x)R'
     Map<Matrix3d> E(X.M.data);
     Matrix3d rcross;
     rcross << 0,-X.p[2],X.p[1],
         X.p[2],0,-X.p[0],
         -X.p[1],X.p[0],0;
     
     Matrix3d HrM=I.H-rcross*I.M;
     return ArticulatedBodyInertia(E*I.M*E.transpose(),E*HrM*E.transpose(),E*(I.I-rcross*I.H.transpose()+HrM*rcross)*E.transpose());
 }
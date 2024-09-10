 RigidBodyInertia operator*(const Frame& T,const RigidBodyInertia& I){
     Frame X=T.Inverse();
     //mb=ma
     //hb=R*(h-m*r)
     //Ib = R(Ia+r x h x + (h-m*r) x r x)R'
     Vector hmr = (I.h-I.m*X.p);
     Vector3d r_eig = Map<Vector3d>(X.p.data);
     Vector3d h_eig = Map<Vector3d>(I.h.data);
     Vector3d hmr_eig = Map<Vector3d>(hmr.data);
     Matrix3d rcrosshcross = h_eig *r_eig.transpose()-r_eig.dot(h_eig)*Matrix3d::Identity();
     Matrix3d hmrcrossrcross = r_eig*hmr_eig.transpose()-hmr_eig.dot(r_eig)*Matrix3d::Identity();
     Matrix3d R = Map<Matrix3d>(X.M.data);
     RotationalInertia Ib;
     Map<Matrix3d>(Ib.data) = R*((Map<Matrix3d>(I.I.data)+rcrosshcross+hmrcrossrcross)*R.transpose());
     
     return RigidBodyInertia(I.m,T.M*hmr,Ib,mhi);
 }
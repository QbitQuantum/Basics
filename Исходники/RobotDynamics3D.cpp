void RobotDynamics3D::GetKineticEnergyMatrixDeriv(int z,Matrix& dB) const
{
  if(JP.n != q.n || JP.m != q.n || JO.n != q.n || JO.m != q.n) 
    FatalError("RobotDynamics3D::GetKineticEnergyMatrixDeriv: Dynamics not updated");

  //O(n) descendants
  vector<bool> descendants;
  GetDescendants(z,descendants);
  for(size_t i=0;i<descendants.size();i++)
    if(descendants[i]) Assert(IsAncestor(i,z));

  dB.resize(q.n,q.n,Zero);
  //no need for an initializer, we don't use these things if they don't
  Array2D<Vector3> dJP(q.n,q.n);
  Array2D<Vector3> dJO(q.n,q.n);
  //dJp(k,j) = ddpk/djdz
  //dJo(k,j) = ddok/djdz
  //for dJP(k,j) to be nonzero, z,j must be ancestor of k
  for(int k=0;k<q.n;k++) {
    if(!descendants[k]) continue;
    for(int j=k;j!=-1;j=parents[j]) { //j<k  z<k ???
      //GetJacobianDeriv_Fast(links[k].com,k,j,z,dJO(k,j),dJP(k,j));
      if(!GetJacobianDeriv(links[k].com,k,j,z,dJO(k,j),dJP(k,j))) {
	FatalError("Error, an invalid jacobian derivative in dB setup");
	dJO(k,j).setZero();
	dJP(k,j).setZero();
      }
      if(z > j) Assert(dJO(k,j).isZero());
    }
  }
  //for an entry k to be added to i,j,
  //z, i, and j must be ancestors of k
  Matrix3 inertiaWorld;
  //sum up d/dz(Jk^t*Mk*Jk) over all links k
  for(int k=0;k<q.n;k++) {
    if(!descendants[k]) continue;
    links[k].GetWorldInertia(inertiaWorld);
    Matrix3 temp;
    if(links[z].type == RobotLink3D::Revolute) {
      Matrix3 wcross;
      wcross.setCrossProduct(links[z].T_World.R*links[z].w);
      temp.sub(wcross*inertiaWorld,inertiaWorld*wcross);
    }
    else temp.setZero();
    
    for(int i=k;i!=-1;i=parents[i]) {
      const Vector3& JPi=JP(k,i);
      const Vector3& dJPi=dJP(k,i);
      const Vector3& JOi=JO(k,i);
      const Vector3& dJOi=dJO(k,i);
      for(int j=k;j!=-1;j=parents[j]) {
	const Vector3& JPj=JP(k,j);
	const Vector3& dJPj=dJP(k,j);
	const Vector3& JOj=JO(k,j);
	const Vector3& dJOj=dJO(k,j);
	
	Real val=Zero;
	val+=links[k].mass*(dot(JPi,dJPj)+dot(dJPi,JPj));
	//derivative of angular momentum
	val+=(dot(dJOi,inertiaWorld*JOj)+dot(JOi,inertiaWorld*dJOj));
	//coriolis forces
	//val+=([w]*inertiaWorld-inertiaWorld*[w])*JOi*JOj
	val+=dot(JOi,temp*JOj);
	dB(i,j) += val;
      }
    }
  }
  
  /*
    for(int i=0;i<q.n;i++) {
    for(int j=0;j<q.n;j++) {
    Real ke_dz=GetKineticEnergyDeriv(i,j,z);
    if(!FuzzyEquals(ke_dz,dB(i,j),(Real)1e-7)) {
    cout<<"Error in kinetic energy deriv "<<i<<" "<<j<<" : "<<ke_dz<<" vs "<<dB(i,j)<<endl;
    cout<<"Difference "<<ke_dz-dB(i,j)<<endl;
    Assert(ke_dz == dB(i,j));
    }
    }
    }
  */
}
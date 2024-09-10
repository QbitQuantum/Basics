void RobotKinematics3D::GetJacobianDeriv_Fast(const Vector3& pm, int m, int i, int j, Vector3&ddtheta,Vector3& ddp) const
{
  Assert(i <= m);
  Assert(j <= m);
  bool swapped = false;
  if(i < j) {  //order so j < i, 
    Swap(i,j);
    swapped = true;
  }
  //Get i's Jacobian then transform to j, and modify
  Frame3D JPmi,JPjj;
  Matrix3 R0_j;
  links[i].GetJacobian(q[i],links[m].T_World,JPmi);
  links[j].GetJacobian(q[j],links[j].T_World,JPjj);
  R0_j.setTranspose(links[j].T_World.R);
  
  Matrix3 RA1B = JPjj.R*R0_j;
  ddp = RA1B*(JPmi*pm);
  if(swapped) ddtheta.setZero();
  else ddtheta=RA1B*links[i].T_World.R*links[i].w;
}
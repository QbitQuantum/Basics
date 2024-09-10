void CollisionConstraint::Jacobian_i(const Vector& x,int i,Vector& Ji_active)
{
  //approximate jacobian -- assumes the cp doesn't change
  //D = cp(q)-cpmesh
  //d/dq |D| = d/dq sqrt(D.D) = 1/|D|*D^t*dD/dq = 1/|D|*D^t*Jcp

	Assert( Ji_active.n == (int)this->activeDofs.Size());
	Vector Ji; Ji.resize( robot.links.size());

	Vector3 cpi,cpmesh,dir;
	Vector3 dv;
	Real dirNorm;

	Ji.setZero();
	if( query[i].query && query[i].ClosestPoints(cpi,cpmesh,dir)) {
		dirNorm = dir.norm();
		if(dirNorm >= Epsilon)
			dir /= dirNorm;
		//jacobian Ji is Jpi*dir/|dir|
		for(int j = i; j != -1; j = robot.parents[j]) {
			robot.GetPositionJacobian(cpi,i,j,dv);
			if(dirNorm < Epsilon)
				Ji(j) = dot(dv,dv);
			else
				Ji(j) = dot(dir,dv);
		}
	}
//	cout << "Ji ********************* :" << endl;
//	cout << Ji << endl;
//	cout << "direction:" << dir << endl;
	/*
	Config q; readConfig("q_inCollision.txt", q);
	Config q_pushout = q + Ji;
	logConfig("q_pushout.txt", q_pushout);
	*/
//	getchar();
	for( int i = 0; i < this->activeDofs.Size(); i++)
	{
//		cout << "mapping " << i << ":" << this->activeDofs.mapping[i] << endl;
		Ji_active[i] = Ji[ this->activeDofs.mapping[i]];
	}
//	exit(-1);

//	Assert(Ji.n == (int)robot.links.size());
//
//	Vector3 cpi,cpmesh,dir;
//	Vector3 dv;
//	Real dirNorm;
//
//	Ji.setZero();
//	if( query[i].query && query[i].ClosestPoints(cpi,cpmesh,dir)) {
//		dirNorm = dir.norm();
//		if(dirNorm >= Epsilon)
//			dir /= dirNorm;
//		//jacobian Ji is Jpi*dir/|dir|
//		for(int j = i; j != -1; j = robot.parents[j]) {
//			robot.GetPositionJacobian(cpi,i,j,dv);
//			if(dirNorm < Epsilon)
//				Ji(j) = dot(dv,dv);
//			else
//				Ji(j) = dot(dir,dv);
//		}
//	}
}
//用了彭老师书上介绍的求交方法，但是transform之后就有问题
bool Triangle::intersect(const Ray &r, Hit &h, float tmin)
{
	Matrix A;
	A.SetToIdentity();
	A.Set(0,0,a.x()-b.x());
	A.Set(1,0,a.x()-c.x());
	A.Set(2,0,r.getDirection().x());

	A.Set(0,1,a.y()-b.y());
	A.Set(1,1,a.y()-c.y());
	A.Set(2,1,r.getDirection().y());

	A.Set(0,2,a.z()-b.z());
	A.Set(1,2,a.z()-c.z());
	A.Set(2,2,r.getDirection().z());

	Vec4f vr(a.x()-r.getOrigin().x(),a.y()-r.getOrigin().y(),a.z()-r.getOrigin().z(),1);

	if(fabs(r.getDirection().Dot3(normal))>0.0f)
	{
		A.Inverse();
		A.Transform(vr);
		if((vr.x()+vr.y())<=1 && vr.x()>=0 && vr.y()>=0 && vr.z()>tmin && vr.z()<h.getT())
		{
			h.set(vr.z(),material,normal,r);
			return 1;
		}
	}
	return 0;
	//为什么当使用transform之后，这里的求交函数就不能用了？  用没有加速的程序检测了一下，也无法求交，应该是这里的求交写错掉了
	//Vec3f origin = r.getOrigin();
	//Vec3f direct = r.getDirection();
	//float isParallel = normal.Dot3(direct);
	//Vec3f tempbeta0;
	//Vec3f tempbeta1;
	//Vec3f tempbeta2;
	//float beta0;
	//float beta1;
	//float beta2;
	//if(fabs(isParallel)>0.0f)
	//{
	//	float dist = -(normal.Dot3(origin)+d)/isParallel;
	//	Vec3f q = origin + direct*dist;
	//	Vec3f::Cross3(tempbeta0,(c-b),(q-b));
	//	Vec3f::Cross3(tempbeta1,(a-c),(q-c));
	//	Vec3f::Cross3(tempbeta2,(b-a),(q-a));
	//	if(i0 == 0)
	//	{
	//		beta0 = tempbeta0.x()/normal.x();	
	//		beta1 = tempbeta1.x()/normal.x();
	//		beta2 = tempbeta2.x()/normal.x();
	//	}
	//	else if(i0 == 1)
	//	{
	//		beta0 = tempbeta0.y()/normal.y();
	//		beta1 = tempbeta1.y()/normal.y();
	//		beta2 = tempbeta2.y()/normal.y();
	//	}
	//	else
	//	{
	//		beta0 = tempbeta0.z()/normal.z();
	//		beta1 = tempbeta1.z()/normal.z();
	//		beta2 = tempbeta2.z()/normal.z();
	//	}
	//	if(beta0>=0 && beta0<=1 && beta1>=0 && beta1<=1 && beta2>=0 && beta2<=1)
	//	{
	//		if(dist > tmin && dist < h.getT())
	//		{
	//			h.set(dist,material,normal,r);
	//			return true;	
	//		}
	//	}
	//}
	//return false;
}
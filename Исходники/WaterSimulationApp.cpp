void WaterSimulationApp::addForce(float dt )
{

	float length= randomForce.length();
	Vec3f pos1=randomForceX+randomForce;
	Vec3f x = Vec3f::zero();
	if(length<1e-6)return;
	int num =(int)(length/fluidsys->cellDim.x+1);
	for(int i=0;i<num;i++){
		x=randomForceX.lerp((float)i/length,pos1);
		fluidsys->addSource(x,dt,fluidsys->u0,randomForce.x);
		fluidsys->addSource(x,dt,fluidsys->v0,randomForce.y);
		fluidsys->addSource(x,dt,fluidsys->w0,randomForce.z);
	}
	randomForce.zero();
}
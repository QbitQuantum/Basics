bool PyramidObject::checkCulling( void )
{
	Vect center = this->pyramidModel->cullC;
	center *= this->LocalToWorld;
	float radius = this->pyramidModel->cullR;
	
	///////////////////////////////////////////////////////////////////GET NON UNIFORM SCALE OF RADIUS///////////////////////////////////////////////////////////////////
	float scale_x = (this->LocalToWorld.m0 * this->LocalToWorld.m0) + (this->LocalToWorld.m1 * this->LocalToWorld.m1) + (this->LocalToWorld.m2 * this->LocalToWorld.m2);
	scale_x = sqrt(scale_x);
	float scale_y = (this->LocalToWorld.m4 * this->LocalToWorld.m4) + (this->LocalToWorld.m5 * this->LocalToWorld.m5) + (this->LocalToWorld.m6 * this->LocalToWorld.m6);
	scale_y = sqrt(scale_y);
	float scale_z = (this->LocalToWorld.m8 * this->LocalToWorld.m8) + (this->LocalToWorld.m9 * this->LocalToWorld.m9) + (this->LocalToWorld.m10 * this->LocalToWorld.m10);
	scale_z = sqrt(scale_z);

	if (scale_x > scale_y && scale_x > scale_z)
		radius *= scale_x;
	else if (scale_y > scale_x && scale_y > scale_z)
		radius *= scale_y;
	else 
		radius *= scale_z;

	////////////////////////////////////////////////////////////////CACLCULATE POINTS ON SPHERE////////////////////////////////////////////////////////////////////////////
	Vect pX = center + (Vect(1.0, 0.0, 0.0) * this->pyramidModel->cullR);
	Vect pY = center + (Vect(0.0, 1.0, 0.0) * this->pyramidModel->cullR);
	Vect pZ = center + (Vect(0.0, 0.0, 1.0) * this->pyramidModel->cullR);

	pX *= this->LocalToWorld;
	pY *= this->LocalToWorld;
	pZ *= this->LocalToWorld;

	Vect FTR;
	Vect NBL;
	
	pCamera->getNearBottomLeft(NBL);
	pCamera->getFarTopRight(FTR);


	///////////////////////////////////////////////////////////////CHECK IF IN FRUSTRUM/////////////////////////////////////////////////////////////////////////////////////
	Vect Normal;
	float Result;
	
	Vect Distance = (center - NBL);

	pCamera->getBottomNorm(Normal);
	Result = Distance.dot(Normal);
	
	if (Result > radius)
		return true;

	pCamera->getLeftNorm(Normal);
	Result = Distance.dot(Normal);
	
	if (Result > radius)
		return true;
	
	pCamera->getFrontNorm(Normal);
	Result = Distance.dot(Normal);
	
	if (Result > radius)
		return true;

	
	Distance = (center - FTR);
	
	pCamera->getBackNorm(Normal);
	Result = Distance.dot(Normal);
	
	if (Result > radius)
		return true;

	pCamera->getRightNorm(Normal);
	Result = Distance.dot(Normal);
	
	if (Result > radius)
		return true;

	pCamera->getTopNorm(Normal);
	Result = Distance.dot(Normal);
	
	if (Result > radius)
		return true;

	return false;
}
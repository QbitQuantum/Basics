/////////////////////////////////////
// Name:	
// Purpose:	
// Output:	
// Return:	
/////////////////////////////////////
PUBLIC void CameraYawPitchRoll(hCAMERA cam, angle yaw, angle pitch, angle roll)
{
	cam->aYaw+=yaw; cam->aPitch+=pitch; cam->aRoll+=roll;

	float cosY,cosP,cosR, sinY,sinP,sinR;

	cosY = COS(cam->aYaw);   sinY = SIN(cam->aYaw);
	cosP = COS(cam->aPitch); sinP = SIN(cam->aPitch);
	cosR = COS(cam->aRoll);  sinR = SIN(cam->aRoll);

	//set up dir(fwd vect)
	float *dir = (float*)cam->vDir;

	dir[eX] = sinY*cosP;
	dir[eY] = sinP;
	dir[eZ] = cosP*-cosY;

	//set up look-at
	cam->vTarget = cam->vDir+cam->vEye;
}
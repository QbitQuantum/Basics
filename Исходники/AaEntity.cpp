void AaEntity::roll(float roll) 
{ 
	dirtyWM=true; 
	*quaternion = XMQuaternionMultiply(*quaternion,XMQuaternionRotationRollPitchYaw(0,0,roll));
}
// Multiplying a quaternion q with a vector v applies the q-rotation to v
vec3 tgQuaternion::operator* (vec3 v){
	v.normalize();
 
	tgQuaternion vecQuat, resQuat;
	vecQuat.x = v.x;
	vecQuat.y = v.y;
	vecQuat.z = v.z;
	vecQuat.w = 0.0f;
 
	resQuat = vecQuat * getConjugate();
	resQuat = *this * resQuat;
 
	return (vec3(resQuat.x, resQuat.y, resQuat.z));
}
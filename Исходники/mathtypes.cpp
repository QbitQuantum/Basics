void btQuaternion_to_Quaternion(JNIEnv * const &jenv, jobject &target, const btQuaternion & source)
{
	quaternion_ensurefields(jenv, target);
	jenv->SetFloatField(target, quaternion_x, source.getX());
	jenv->SetFloatField(target, quaternion_y, source.getY());
	jenv->SetFloatField(target, quaternion_z, source.getZ());
	jenv->SetFloatField(target, quaternion_w, source.getW());
}
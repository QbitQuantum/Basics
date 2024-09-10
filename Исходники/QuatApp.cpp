void QuatApp::SlerpArray( Quat *result, const Quat *source, const Quat *target, const float slerpFactor, const int numQuats )
{
	for (int i = 0; i < numQuats; i++)
	{
		Slerp(result[i], source[i], target[i], slerpFactor);
	}
}
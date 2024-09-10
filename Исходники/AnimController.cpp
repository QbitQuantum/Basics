Quat AnimController::Interpolate(const Quat& first, const Quat& second, float lambda) const
{
    Quat result;

    // note: ensure minimal angle interpolation
	float dot = first.Dot(second); 

	if(dot >= 0.0f)
	{
		result.x = first.x*(1.0f-lambda)+second.x*lambda;
		result.y = first.y*(1.0f-lambda)+second.y*lambda;
		result.z = first.z*(1.0f-lambda)+second.z*lambda;
		result.w = first.w*(1.0f-lambda)+second.w*lambda;
	}
	else
	{
		result.x = first.x*(1.0f-lambda)-second.x*lambda;
		result.y = first.y*(1.0f-lambda)-second.y*lambda;
		result.z = first.z*(1.0f-lambda)-second.z*lambda;
		result.w = first.w*(1.0f-lambda)-second.w*lambda;
	}

	result.Normalize();

	return result;
}
void LightInfo::GetPointLightOnPoint(const SSEVector& _cameraSpacePoint, const SSEVector& _point, const SSEVector& _normal, int _lightIndex, const SSEVector& _diffuse, const SSEVector& _specular, SSEVector& _out) {
	// Get the direction and distance from the light source.
	SSEVector diff(GetPointLights()[_lightIndex].GetPosition().x, GetPointLights()[_lightIndex].GetPosition().y, GetPointLights()[_lightIndex].GetPosition().z, 0);
	diff -= _point;
	SSEVector lightDirection = diff;

	// Get the distance
	float distance = diff.Length();

	// The direction 
	diff.Normalize();

	// The attenuation
	float attenuation = GetPointLights()[_lightIndex].GetAttenuation(distance);

	// Diffuse lighting
	// Get the light intensity
	SSEVector intensity(GetPointLights()[_lightIndex].GetIntensity().x, GetPointLights()[_lightIndex].GetIntensity().y, GetPointLights()[_lightIndex].GetIntensity().z, 0);

	// Calculate the light
	SSEVector color = intensity;
	color *= diff.Dot(_normal);
	color *= attenuation;
	color *= _diffuse;

	// Clamp the color.
	color.Clamp();

	// Specular
	// We get the half angle between the camera and the direction to the camera.
	SSEVector halfAngle = lightDirection;
	halfAngle += _cameraSpacePoint;
	halfAngle.Normalize();

	SSEVector specular = _specular;
	specular *= powf(halfAngle.Dot(_normal), 10);
	specular *= attenuation;
	specular *= intensity;
	
	// Clamp specular
	specular.Clamp();

	// Add to the color
	_out += color;
	_out += specular;
}
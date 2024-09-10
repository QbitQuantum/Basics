void PointLight::shade( Ray3D& ray ) {
	// TODO: implement this function to fill in values for ray.col 
	// using phong shading.  Make sure your vectors are normalized, and
	// clamp colour values to 1.0.
	//
	// It is assumed at this point that the intersection information in ray 
	// is available.  So be sure that traverseScene() is called on the ray 
	// before this function.  
	Intersection intersectionPoint = ray.intersection;
	Vector3D normal = intersectionPoint.normal; // ~n
	normal.normalize();
	Vector3D reflectedDir = -ray.dir; //~c
	Vector3D lightSourceDir = _pos - intersectionPoint.point; //~s
	lightSourceDir.normalize();
	//Perfect Mirror Specular Reflection
	Vector3D pMSpecRefl = (2*lightSourceDir.dot(normal))*normal - lightSourceDir; //~m
	pMSpecRefl.normalize();

	// From the lecture notes

	//NOTE: Because of the definition of the operator *, the order of multiplier and multiplicand
	//is not the same as the formula from our lecture notes.
	Colour ambLight = (ray.intersection.mat->ambient) * _col_ambient;

	Colour diffLight;
	if (lightSourceDir.dot(normal) < 0)
	{
		diffLight = 0 * (ray.intersection.mat->diffuse) * _col_diffuse;
	}
	else
	{
		diffLight = lightSourceDir.dot(normal) * (ray.intersection.mat->diffuse) * _col_diffuse;
	}

	Colour specLight;
	if (reflectedDir.dot(pMSpecRefl) < 0)
	{
		specLight = 0 * (ray.intersection.mat->specular) * _col_specular;
	}
	else
	{
		specLight = pow((reflectedDir.dot(pMSpecRefl)), (ray.intersection.mat->specular_exp)) * (ray.intersection.mat->specular) * _col_specular;
	}


//	//ray.col=(intersectionPoint.mat->diffuse); //sig1.ppm, sig2.ppm
//	//ray.col = diffLight + ambLight; // diffuse1.ppm diffuse2.ppm
//	ray.col = diffLight + ambLight + specLight; //phong1.ppm, phong2.ppm


	/*if (ray.intersection.t_value > 0.01 && ray.intersection.t_value < 0.99){
		// in shadow
		ray.col = ray.shadowCoef * (diffLight + specLight +ambLight);

	} else {
		//ray.col = (ray.intersection.mat->diffuse); // sig.ppm: diffuse
		//ray.col = dL + aL; // diffuse.ppm: diffuse + ambient
		ray.col = ray.col + ray.shadowCoef * (diffLight + specLight +ambLight); // phong.ppm: diffuse + specular + ambient

	}*/
	diffLight.clamp();
	specLight.clamp();
	ambLight.clamp();
	if (ray.inShadow){
		ray.col = ray.col + ambLight;
	}else{
		ray.col = ray.col + (diffLight + specLight +ambLight);
	}

}
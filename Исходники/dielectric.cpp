// Light that bounces multiple times before reaching the eye
Rgb Dielectric::indirectRadiance(Intersection *intersection, Ray ray, Scene *scene, int depth)
{
	/*
	 *	IDEA: Set index of refraction to be the same as the airs. In this event, should go straight through
	 *		  and the towardsViewer and refracted vector should differ in sign value (ie, they will be pointing 
	 *		  in opposite directions, but parallel)
	 */


	//TODO: Might as well store the surface normal with the intersection
	Vector3 towardsViewer = -ray.getDirection().normalized();
	Vector3 normal = intersection->getSurface()->computeSurfaceNormal(intersection->getIntersectionPoint()).normalized();

	Ray reflectedRay(intersection->getIntersectionPoint(),
					 -towardsViewer.reflect(normal),
					 ray.getRefractiveIndex(),
					 ray.getMaxDepth());

	// Add refracted ray
	bool isReflected = false;
	Vector3 refractedDirection = towardsViewer.refract(normal, ray.getRefractiveIndex(), refractiveIndex, isReflected);

	Ray refractedRay(intersection->getIntersectionPoint(),
					 refractedDirection,
					 refractiveIndex,
					 ray.getMaxDepth());

	// Compute fresnel
	double fresnel = computeFresnel(towardsViewer, normal, ray.getRefractiveIndex(),  refractiveIndex);

	Rgb radiance;
	if (fresnel >= 1.0 || isReflected == true)
	{
		radiance = scene->trace(reflectedRay, EPSILON, depth + 1).getPixelColor();
	}
	else
	{
		Rgb refractedColor = scene->trace(refractedRay, EPSILON, depth + 1).getPixelColor();
		Rgb reflectedColor = scene->trace(reflectedRay, EPSILON, depth + 1).getPixelColor();

		radiance.u.a[0] = (1.0 - fresnel) * refractedColor.u.a[0] + (fresnel) * reflectedColor.u.a[0];
		radiance.u.a[1] = (1.0 - fresnel) * refractedColor.u.a[1] + (fresnel) * reflectedColor.u.a[1];
		radiance.u.a[2] = (1.0 - fresnel) * refractedColor.u.a[2] + (fresnel) * reflectedColor.u.a[2];
	}
	return kAbsorption * radiance;
}
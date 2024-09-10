const ColorRGB Scene3D::traceRay(const Ray& ray, int depth) const
{

	float closest_t_value = NO_INTERSECT;
	const SceneObject* closest_object = findClosest(ray, closest_t_value);

	if (closest_object == 0)
		return ColorRGB(0,0,0);

	ColorRGB retColor(0,0,0);


	for (int i = 0; i < lights.size(); i++)
	{
		Vector3D normL = ((*lights[i]).get_position()-ray.getPointAt(closest_t_value)).normalize();
		Vector3D normN = (*closest_object).surface_normal(ray.getPointAt(closest_t_value));

		retColor += (*lights[i]).get_color()*(*closest_object).get_color()*std::max((normL*normN),float(0));
		
		if (depth < 6 && (*closest_object).get_reflectivity() > 0)
		{
				Ray reflected_ray = ray.reflect(ray.getPointAt(closest_t_value), (*closest_object).surface_normal(ray.getPointAt(closest_t_value)));
				ColorRGB reflection_color = traceRay(reflected_ray, depth+1);
				retColor+= (*closest_object).get_reflectivity()*reflection_color;
		}
		
	}	


	return retColor;
}
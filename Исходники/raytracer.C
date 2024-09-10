t_double3			color_diffused(t_scene *scene, t_surface *surface, t_vector ray)
{
	t_double3		color_hit;
	t_light			*light;
	int				light_nb;
	double			dot_light;
	t_surface		*light_intersect;
	t_double3		reflected;

	color_hit = (t_double3){0, 0, 0};
	light = scene->light;
	light_nb = 0;
	while (light)
	{
		light_intersect = is_in_light(surface, scene, light, &dot_light);
		if (light_intersect->object == NULL || light_intersect->distance > 0)
		{
			color_hit = v_plus_v(color_hit, color_mix(scale_v(light->color,
				dot_light), surface->object->gloss,
				// scale_v(surface->object->color, dot_light)));
				scale_v(surface->color, dot_light)));
			reflected = reflect(scale_v(normalize(v_minus_v(light->pos, surface->point)), -1), surface->normal);
			color_hit = v_plus_v(color_hit, scale_v(light->color, pow(max_double(0, -dot_product(reflected, ray.dir) * surface->object->gloss), 2)));
		}
		free(light_intersect);
		light_nb++;
		light = light->next;
	}
	if (light_nb > 1)
		color_hit = scale_v(color_hit, (1.0 / (double)light_nb));
	return (color_hit);
}
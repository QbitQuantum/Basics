Color MirrorMaterial::shade(const Intersection &intersection, const Scene &scene) const
{
    VectorD vec_incident = -intersection.incident_ray.direction;
    if(intersection.incident_ray.recursion_depth >= scene.options().max_recursion)
    {
        return Color(0.0, 0.0, 0.0);
    }

    VectorD n = intersection.normal;
    // Reflection vector
    VectorD vec_r = 2 * n.dot(vec_incident) * n - vec_incident;
    vec_r.normalize();
    // Reflection ray
    Ray ray_r(intersection.hit_point, vec_r);
    ray_r.recursion_depth = intersection.incident_ray.recursion_depth + 1;
    // Trace reflection ray
    Color reflected_color;
    Intersection reflection_hit = scene.trace(ray_r);
    if(reflection_hit.exists)
    {
        reflected_color = reflection_hit.hit_object->material()->shade(reflection_hit, scene);
    }
    else
    {
        reflected_color = scene.background();
    }

    return reflected_color;
}
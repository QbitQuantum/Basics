colorf DefaultShader::Run(const ShaderArgs &args)
{
//  std::cout << "DefaultShader Run" << std::endl;

    colorf color = args.scene->GetAmbientLight();
    std::vector<SimpleLight *> lightList = args.scene->GetLightList();

    for (std::vector<SimpleLight *>::const_iterator i = lightList.begin(); i != lightList.end(); i++) {
        const SimpleLight *l = *i;

        // cast a ray at each light, see if we're in a shadow
        Ray ray;
        ray.origin = args.pos + args.normal * 0.001f;
        ray.dir = l->GetPos() - ray.origin;
        ray.dir.Normalize();
        ray.light = true;

//      std::cout << "casting ray back to light" << std::endl;
        if (!args.scene->DoesIntersect(ray, (ray.origin - l->GetPos()).Length())) {
            Vector3d suntosurface = l->GetPos() - args.pos;
            suntosurface.Normalize();

//          std::cout << "does not intersect" << std::endl;

            float light = Dot(suntosurface, args.normal);

            // calculate falloff

            color += (l->GetColor() * light) * m_DiffuseColor;
        }
    }

//  std::cout << "color " << color << std::endl;
    // see how much of it is a pure reflection
    if (m_Shinyness > 0.0f) {
        Ray ray;
        ray.origin = args.pos;

        // calculate the reflection ray
        float d = Dot(args.ray->dir, args.normal);

        Vector3d reflect(
            args.ray->dir.getx() - 2.0 * d * args.normal.getx(),
            args.ray->dir.gety() - 2.0 * d * args.normal.gety(),
            args.ray->dir.getz() - 2.0 * d * args.normal.getz());

        ray.dir = reflect;

        color *= (1.0f - m_Shinyness);

        // recursively trace to see
        colorf reflectcolor;
        if (args.tracer->Cast(reflectcolor, ray)) {
            color += reflectcolor * m_Shinyness;
        }
    }

//  std::cout << "default shader color " << color << std::endl;
    return color;
}
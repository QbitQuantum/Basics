Point3D RayScene::GetColor(Ray3D ray,int rDepth,Point3D cLimit)
{
    Point3D color;
    RayIntersectionInfo info;
    Ray3D reflection;
    Ray3D refraction;
    Ray3D reflectedRay;
    Point3D reflect, reflColor, refractColor;
    int shad;
    int numCrossed = 0;

    double dist;
    dist = group -> intersect(ray, info, -1);
    if (dist == -1)
        return background;

    color = ambient*info.material -> ambient + info.material -> emissive;

    if (ray.direction.dot(info.normal) < 0)
    {
        for (int j = 0; j < this->lightNum; j++)
        {
            shad = this->lights[j]->isInShadow(info, this->group, numCrossed);
            Point3D ts = lights[j]->transparency(info, group, cLimit);

            color += this->lights[j]->getDiffuse(ray.position, info) * ts;
            color += this->lights[j]->getSpecular(ray.position, info) * ts;
        }

        reflect = Reflect(ray.direction, info.normal);

        // Reflected ray
        reflectedRay = Ray3D(info.iCoordinate, reflect);
        reflectedRay.position = reflectedRay(0.0001);

        if (rDepth > 0 && (info.material->specular[0] > cLimit[0]) && (info.material->specular[1] > cLimit[1]) && (info.material->specular[2] > cLimit[2])) 
        {
            reflColor = GetColor(reflectedRay, rDepth - 1, (cLimit / info.material->specular));

            if (reflColor.p[0] == background.p[0] && reflColor.p[1] == background.p[1] && reflColor.p[2] == background.p[2])
                reflColor = Point3D();

            // reflected color added
            reflColor *= info.material -> specular;
            color += reflColor;
        }
    }

    // refraction
    if (this -> Refract(ray.direction, info.normal, info.material->refind, refraction.direction))
    {
        refraction.position = info.iCoordinate;
        refraction.position = refraction(0.0001);
        refractColor = this -> GetColor(refraction, rDepth - 1, cLimit);

        if (refractColor.p[0] == background.p[0] && refractColor.p[1] == background.p[1] && refractColor.p[2] == background.p[2])
            refractColor = Point3D();

        refractColor *= info.material -> transparent;
        color += refractColor;
    }

    for (int i = 0; i < 3; i++)
    {
        if (color.p[i] > 1)
            color.p[i] = 1;
    }

    for (int i = 0; i < 3; i++)
    {
        if (color.p[i] < 0)
            color.p[i] = 0;
    }

    return color;
}
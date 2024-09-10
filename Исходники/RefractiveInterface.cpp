Vector3
RefractiveInterface::shade(const Ray& ray, const HitInfo& hit, const Scene& scene, const bool& isFront) const
{
    Ray rayLight;
    HitInfo hitLight;
    Vector3 L = Vector3(0.0f, 0.0f, 0.0f);

    const Vector3 viewDir = -ray.d; // d is a unit vector

    const PointLights *plightlist = scene.pointLights();
    // loop over all of the POINT lights
    PointLights::const_iterator plightIter;
    for (plightIter = plightlist->begin(); plightIter != plightlist->end(); plightIter++)
    {
        PointLight* pLight = *plightIter;
        Vector3 l = pLight->position() - hit.P;
        rayLight.o = hit.P;
        rayLight.d = l.normalized();
        Vector3 brdf = BRDF(rayLight.d, hit.N, -ray.d, isFront);
        if (brdf == 0) continue;
        if (scene.trace(hitLight, rayLight, 0.0001, l.length())) continue;

        // the inverse-squared falloff
        float falloff = l.length2();

        float nDotL = fabs(dot(hit.N, l));
        Vector3 result = pLight->color();

        L += nDotL / falloff * pLight->wattage() *brdf * result;
    }

    const AreaLights *alightlist = scene.areaLights();
    // loop over all of the lights
    AreaLights::const_iterator alightIter;
    for (alightIter = alightlist->begin(); alightIter != alightlist->end(); alightIter++)
    {
        AreaLight* aLight = *alightIter;
        vec3pdf vp = aLight->randPt();
        Vector3 l = vp.v - hit.P; // shoot a shadow ray to a random point on the area light
        rayLight.o = hit.P;
        rayLight.d = l.normalized();

        Vector3 brdf = BRDF(rayLight.d, hit.N, -ray.d, isFront);
        if (brdf == 0) continue;
        // if the shadow ray hits the "backside of the light" continue to the next area light
        if (!aLight->intersect(hitLight, rayLight)){
            continue;
        }
        // if the shadow ray is occluded by another (hence the "skip") object continue the next light
        if (scene.trace(hitLight, rayLight, aLight, 0.0001, l.length())){
            continue;
        }

        // the inverse-squared falloff
        float falloff = l.length2();

        float nDotL = fabs(dot(hit.N, l));
        Vector3 result = aLight->color();

        L += std::max(0.0f, dot(hitLight.N, -l))* 0.0f, nDotL / falloff*
            aLight->wattage() / aLight->area() *brdf * result / (vp.p);
    }

    // add the ambient component
    L += m_ka;

    return L;
}
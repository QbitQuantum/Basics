//alg for calculating shading. Calls diffuseShade and SpecularShade
Color RT_lights(Figure* obj, const Ray& ray, const Vec& thePoint, const Vec& normal)
{
    Color c = Color();
    for (list<Light*>::iterator iterator = lightList.begin(), end = lightList.end(); iterator != end; ++iterator) {
        Light* theLight = *iterator;

        pair<double, Figure*> inter = nearestIntersection(Ray(Vec(thePoint), theLight->getPos()), MIN_T / SHAD_RES, 1.0, EPSILON, false);
        if (inter.first <= 0) {
            Vec* toLight = thePoint.normalize(theLight->getPos());
            double dotProduct = toLight->dot(normal);
            Vec* subt = (thePoint.sub(theLight->getPos()));
            double dist = abs(subt->getMag());
            Color dif = diffuseShade(obj, theLight, max(dotProduct, 0.0), dist);
            Vec* Q = normal.scale(normal.dot(*toLight));
            Vec* S = Q->sub(*toLight);
            Vec* S2 = S->scale(2.0);
            Vec* R = toLight->add(*S2);
            Vec* norm = ray.getNorm();
            Vec* scaledNorm = norm->scale(-1.0);
            dotProduct = max(0.0, R->dot(*scaledNorm));
            Color spec = specularShade(obj, normal, theLight, *toLight, pow(dotProduct, obj->getShininess()), ray, dist);
            c = c.add(dif.add(spec));
            delete(toLight);
            delete(Q);
            delete(S);
            delete(R);
            delete(S2);
            delete(subt);
            delete(norm);
            delete(scaledNorm);
        }
    }
    return c;
}
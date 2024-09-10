Vector3
PencilShader::shade(const Ray& ray, const HitInfo& hit, const Scene& scene) const
{

    int m = 0;
    int totalRays = 0;
    float step = (float)RAD_H/SAMPLES;
    std::vector<Vector3> normals;
    std::vector<HitInfo> hits;

    for(float r = step; r <= RAD_H; r+=step){
        float theta_step = (2.0*M_PI)/(pow(2, r+2));
        for(float theta = 0; theta <= 2.0*M_PI; theta += theta_step){
            totalRays++;
            float x = r*cos(theta);
            float y = r*sin(theta);
            Ray stencilRay;
            Vector3 dir = Vector3(ray.d);
            dir.x += x;
            dir.y += y;
            stencilRay.o = ray.o;
            stencilRay.d = dir;

            HitInfo h;
            if(scene.trace(h, stencilRay)){

                if(h.objId != hit.objId){
                    m++;
                } else{
                    normals.push_back(Vector3(h.N));
                    hits.push_back(h);

                }
            } else m++;
        }
    }

    //Hit other geometry, outline edge
    if(m > 0){
        return Vector3(0.0f);
    }

    float gradient = 0.0;
    //Check for creases or silhouettes
    for(int i = 0; i <= normals.size(); i++){
        gradient += (dot(normals[i], hit.N))/normals.size();
        if(gradient < 0.01)
            return Vector3(0.0f);
    }

    Vector3 L = Vector3(0.0f, 0.0f, 0.0f);
    const Lights *lightlist = scene.lights();
    Ray shadow;
    shadow.o = hit.P - ray.o;

    Lights::const_iterator lightIter;
    for (lightIter = lightlist->begin(); lightIter != lightlist->end(); lightIter++)
    {
        PointLight* pLight = *lightIter;

        Vector3 l = pLight->position() - hit.P;

        // the inverse-squared falloff
        float falloff = l.length2();

        // normalize the light direction
        l /= sqrt(falloff);

        // get the diffuse component
        shadow.d = l;
        float nDotL = dot(hit.N, l);
        //Map into color location
        L += getTextureColor(nDotL, hit);
    }
    return L;
}
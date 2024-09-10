Vector3
EdgeShading::shade(const Ray& ray, const HitInfo& hit, const Scene& scene) const
{
    Vector3 hitPoint = hit.P - ray.o;

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
        float weight = 1 - (fabs(m-(0.5*totalRays))/(0.5*totalRays));
        return CellShading::shade(ray, hit, scene)*weight;
    }

    float gradient = 0.0;
    //Check for creases or silhouettes
    for(int i = 0; i <= normals.size(); i++){
        gradient += (dot(normals[i], hit.N))/normals.size();
    }

    return CellShading::shade(ray, hit, scene);
}
Vector3 PhotonTracer::refractDirection(Vector3& dir, Vector3& normal, float IOR)
{
    Vector3 result;

    bool TIR = false;
    float n = 1.0f;
    float nt = IOR;

    float incidentDot = Vector3::DotProduct(dir, normal);

    //entering the object
    if(incidentDot < 0){
        //refraction index
        float compN = n / nt;

        //compute the refracted direction
        double c1, cs2;
        c1 = -incidentDot;
        cs2 = 1.0f - compN * compN * (1.0f - c1 * c1);
        result = compN * dir + (compN * c1 - sqrt(cs2)) *  normal;
        result.normalize();
    }
    //exiting the glass
    else{
        //refraction index
        float compN = nt / n;

        double c1, cs2;
        c1 = incidentDot;
        cs2 = 1.0f - compN * compN * (1.0f - c1 * c1);

        if(cs2 < 0.0f)
            TIR = true;

        if(!TIR){
            //compute the refracted direction
            result = compN * dir - (compN * c1 - sqrt(cs2)) *  normal;
            result.normalize();
        }
    }

    if(TIR){
        Vector3 negativeNormal = -normal;
        return reflectDirection(dir, negativeNormal);
    }

    float cos1, cos2;
    if(incidentDot < 0){
        cos1 = -incidentDot;
        cos2 = -Vector3::DotProduct(normal, result);
    }
    else{
        cos1 = incidentDot;
        cos2 = Vector3::DotProduct(normal, result);
    }

    float parallel = (nt * cos1 - n * cos2) / (nt * cos1 + n * cos2);
    float perp = (n * cos1 - nt * cos2) / (n * cos1 + nt * cos2);

    float reflectComp = 0.5f * (parallel * parallel + perp * perp);

    float randomVal = (float)(rand() % 1025) / 1024.0f;
    if(randomVal <= reflectComp){
        if(incidentDot < 0.0f)
            return reflectDirection(dir, normal);
        else{
            Vector3 negativeNormal = -normal;
            return reflectDirection(dir, negativeNormal);
        }
    }
    else
        return result;
}
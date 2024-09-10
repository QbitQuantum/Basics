STImage *FieldMorph(STImage *image,
                    const std::vector<Feature> &sourceFeatures,
                    const std::vector<Feature> &targetFeatures,
                    float t, float a, float b, float p)
{
    int width = image->GetWidth();
    int height = image->GetHeight();
    STImage *result = new STImage(width, height, STColor4ub(255,255,255,255));
    
    std::vector<Feature> interpolatedFeatures = interpolateFeatures(sourceFeatures, targetFeatures, t);
    
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            STVector2 dispSum = STVector2(0, 0);
            float weightsum = 0;
            STPoint2 X = STPoint2(x, y);
            
            int numFeatures = sourceFeatures.size();
            for (int i = 0; i < numFeatures; i++) {
                STPoint2 Pp = sourceFeatures[i].P;
                STPoint2 Qp = sourceFeatures[i].Q;
                STPoint2 P = interpolatedFeatures[i].P;
                STPoint2 Q = interpolatedFeatures[i].Q;
                
                float u = calculateU(X, P, Q);
                float v = calculateV(X, P, Q);
                STPoint2 Xp = calculateXp(Pp, Qp, u, v);
                
                STVector2 displacement = STVector2(Xp) - STVector2(X);
                float dist = calculateDistance(X, P, Q, u, v);
                float weight = calculateWeight(Q, P, a, b, p, dist);
                dispSum += displacement * weight;
                weightsum += weight;
            }
            STPoint2 Xprime = X + dispSum/weightsum;
            
            result->SetPixel(x, y, interpolatedColor(Xprime, image));
        }
    }
    
    return result;
}
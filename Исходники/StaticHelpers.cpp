bool StaticHelpers::angleIsCloserToB(float a, float val, float b)
{
    Vec2 vectA = degreesToVec2(a);
    Vec2 vectV = degreesToVec2(val);
    Vec2 vectB = degreesToVec2(b);
    float diffA = acosf(vectV.dot(vectA)/(vectV.length() * vectA.length())) * 180 / M_PI;
    float diffB = acosf(vectV.dot(vectB)/(vectV.length() * vectB.length())) * 180 / M_PI;
    return diffA > diffB;
}
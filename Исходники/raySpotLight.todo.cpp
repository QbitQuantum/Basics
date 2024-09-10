/*
iff (D.dot(L) < cos(cutOffAngle))
	IL = (D.dot(L))^(alpha) / (kc + kl*d + kq*d*d)
else
	IL = 0

IS = KS * (V.dot(R))^n * IL
*/
Point3D RaySpotLight::getSpecular(Point3D cameraPosition,RayIntersectionInfo& iInfo) {
    Point3D L = location - iInfo.iCoordinate;
    double d = L.length();
    L = L.unit();
    Point3D D = -direction.unit();
    double alpha = dropOffRate;
    double DdotL = D.dot(L);

    if (DdotL <= cos(cutOffAngle) || DdotL < 0)
        return Point3D();

    double IL = pow(DdotL, alpha) / (constAtten + linearAtten * d + quadAtten * d * d);
    double n = iInfo.material->specularFallOff;
    Point3D N = iInfo.normal.unit();
    Point3D V = (iInfo.iCoordinate - cameraPosition).unit();
    Point3D R = (-L + N * 2 * N.dot(L)).unit();
    Point3D KS = iInfo.material->specular * color;
    Point3D IS = KS * pow(V.dot(R), n) * IL;
    IS.clamp(0, 1); //Coefficients of the returned value should all be in the range [0,1].
    return IS;
}
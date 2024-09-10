/*! Calculates \a matWorldToLight and \a matEyeToLight for a spot light
    \a spotL and inverse viewing matrix \a matEyeToWorld.
*/
void ShaderShadowMapEngine::calcSpotLightMatrices(
    Matrixr   &matWorldToLight,
    Matrixr   &matEyeToLight,
    const SpotLight *spotL,
    const Matrixr   &matEyeToWorld)
{
    if(spotL->getBeacon() != NULL)
        spotL->getBeacon()->getToWorld(matWorldToLight);

    Matrixr matLightPos;
    matLightPos.setTranslate(spotL->getPosition());

    Matrixr    matLightDir;
    Quaternion rotLightDir(Vec3r(0.f, 0.f, 1.f), -spotL->getDirection());
    matLightDir.setRotate(rotLightDir);

    matWorldToLight.mult  (matLightPos);
    matWorldToLight.mult  (matLightDir);
    matWorldToLight.invert(           );

    matEyeToLight = matWorldToLight;
    matEyeToLight.mult(matEyeToWorld);
}
Color<real> BlinnPhongShader<real>::GetDiffuseAndSpecular( const Light<real>& light )
{
    Color<real> finalColor( 0, 0, 0, 1 );

    ////////////////////////////////////////////
    //////////////////IFT 3355//////////////////
    ////////////////////////////////////////////
    //Ici, vous calculerez les composantes
    //diffuse et spéculaire en vous servant des
    //propriétés du matériau.
    ////////////////////////////////////////////
    //////////////////IFT 3355//////////////////
    ////////////////////////////////////////////

    Vector3<real> lightPos = light.GetGlobalPosition();
    Vector3<real> lightDir = (lightPos - mIntersection.GetPosition()).Normalized();
    real r2 = (mIntersection.GetPosition() - lightPos).SquaredLength();
    Vector3<real> intersectionShifted = mIntersection.GetPosition() + EPS*mIntersection.GetNormal();

    // Shadow+Diffuse
    bool lightVisible = mRayTracer.IsLightVisible(intersectionShifted, &light);
    if (!lightVisible)
        return finalColor;

    switch (light.GetLightType()) {
    case Light<real>::TypeDirectional:
    case Light<real>::TypeSpot:
    case Light<real>::TypePoint:
        finalColor += mMaterial.GetDiffuse() *
            std::max<real>(0, lightDir * mIntersection.GetNormal()) *
            GetMaterialSurfaceColor();
        break;
    }

    // Specular
    const Camera<real> *cam = mScene.GetActiveCamera();
    Vector3<real> camDir = cam->GetFrontDirection();
    Vector3<real> H = lightDir + camDir;
    H.Normalize();
    Vector3<real> N = mIntersection.GetNormal();
    real n = mMaterial.GetShininess();
    real cs = (n+2)/2;
    Color<real> ks = mMaterial.GetSpecular();
    Color<real> m = mMaterial.GetMetallic();

    finalColor += cs * ks *
        (m*GetMaterialSurfaceColor() + (Color<real>(1, 1, 1, 1) - m)) *
        pow(N * H, n);

    return finalColor * light.GetIntensity() / (r2 * PI);
}
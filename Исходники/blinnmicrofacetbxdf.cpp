glm::vec3 BlinnMicrofacetBxDF::SampleAndEvaluateScatteredEnergy(const glm::vec3 &wo, glm::vec3 &wi_ret, float rand1, float rand2, float &pdf_ret) const{

    float cos_theta( powf( rand1, 1.f / ( exponent + 1.f ) ) );
    float sin_theta( sqrtf( fmaxf( 0.f, 1.f - cos_theta * cos_theta ) ) );

    float phi( rand2 * TWO_PI );
    float cos_phi( cosf( phi ) );
    float sin_phi( sinf( phi ) );

    glm::vec3 wh( sin_theta * cos_phi, sin_theta * sin_phi, cos_theta );

    float woDwh( glm::dot( wo, wh ) );

    if( woDwh < 0.f ) wh = -wh;

    wi_ret = -wo + 2.f * woDwh * wh;
    pdf_ret = PDF( wo, wi_ret );

    return EvaluateScatteredEnergy( wo, wi_ret );
}
ALWAYS_INLINE void FELighting::setPixel(LightingData& data, LightSource::PaintingData& paintingData,
    int lightX, int lightY, float factorX, int normalX, float factorY, int normalY)
{
    m_lightSource->updatePaintingData(paintingData, lightX, lightY, static_cast<float>(data.pixels->get(data.offset + 3)) * data.surfaceScale);

    data.normalVector.setX(factorX * static_cast<float>(normalX) * data.surfaceScale);
    data.normalVector.setY(factorY * static_cast<float>(normalY) * data.surfaceScale);
    data.normalVector.setZ(1.0f);
    data.normalVector.normalize();

    if (m_lightingType == FELighting::DiffuseLighting)
        data.lightStrength = m_diffuseConstant * (data.normalVector * paintingData.lightVector);
    else {
        FloatPoint3D halfwayVector = paintingData.lightVector;
        halfwayVector.setZ(halfwayVector.z() + 1.0f);
        halfwayVector.normalize();
        if (m_specularExponent == 1.0f)
            data.lightStrength = m_specularConstant * (data.normalVector * halfwayVector);
        else
            data.lightStrength = m_specularConstant * powf(data.normalVector * halfwayVector, m_specularExponent);
    }

    if (data.lightStrength > 1.0f)
        data.lightStrength = 1.0f;
    if (data.lightStrength < 0.0f)
        data.lightStrength = 0.0f;

    data.pixels->set(data.offset, static_cast<unsigned char>(data.lightStrength * paintingData.colorVector.x()));
    data.pixels->set(data.offset + 1, static_cast<unsigned char>(data.lightStrength * paintingData.colorVector.y()));
    data.pixels->set(data.offset + 2, static_cast<unsigned char>(data.lightStrength * paintingData.colorVector.z()));
}
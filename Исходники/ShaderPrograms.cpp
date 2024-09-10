bool PhongShadowProgram::renderLight(int index, const SgLight* light, const Affine3& T, const Affine3& viewMatrix, bool shadowCasting)
{
    LightInfo& info = lightInfos[index];

    if(const SgDirectionalLight* dirLight = dynamic_cast<const SgDirectionalLight*>(light)){
        Vector3 d = viewMatrix.linear() * T.linear() * -dirLight->direction();
        Vector4f pos(d.x(), d.y(), d.z(), 0.0f);
        glUniform4fv(info.positionLocation, 1, pos.data());

    } else if(const SgPointLight* pointLight = dynamic_cast<const SgPointLight*>(light)){
        Vector3 p(viewMatrix * T.translation());
        Vector4f pos(p.x(), p.y(), p.z(), 1.0f);
        glUniform4fv(info.positionLocation, 1, pos.data());
        glUniform1f(info.constantAttenuationLocation, pointLight->constantAttenuation());
        glUniform1f(info.linearAttenuationLocation, pointLight->linearAttenuation());
        glUniform1f(info.quadraticAttenuationLocation, pointLight->quadraticAttenuation());
        
        if(const SgSpotLight* spotLight = dynamic_cast<const SgSpotLight*>(pointLight)){
            Vector3 d = viewMatrix.linear() * T.linear() * spotLight->direction();
            Vector3f direction(d.cast<float>());
            glUniform3fv(info.directionLocation, 1, direction.data());
            glUniform1f(info.cutoffAngleLocation, spotLight->cutOffAngle());
            glUniform1f(info.beamWidthLocation, spotLight->beamWidth());
            glUniform1f(info.cutoffExponentLocation, spotLight->cutOffExponent());
        }
    } else {
        return false;
    }
        
    Vector3f intensity(light->intensity() * light->color());
    glUniform3fv(info.intensityLocation, 1, intensity.data());
    Vector3f ambientIntensity(light->ambientIntensity() * light->color());
    glUniform3fv(info.ambientIntensityLocation, 1, ambientIntensity.data());

    if(shadowCasting){
        if(currentShadowIndex < numShadows_){
            ShadowInfo& shadow = shadowInfos[currentShadowIndex];
            glUniform1i(shadow.shadowMapLocation, currentShadowIndex + 1);
            glUniform1i(shadow.lightIndexLocation, index);
            ++currentShadowIndex;
        }
    }

    return true;
}
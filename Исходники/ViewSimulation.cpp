void ViewSimulation::render(gl::Texture texture) {
    shader->bind();
    shader->uniform("texture", 0);
    shader->uniform("maxRaidus", GlobalSettings::getInstance().maxRadius);
    shader->uniform("gravity", GlobalSettings::getInstance().gravity);
    shader->uniform("yFloor", GlobalSettings::getInstance().floor);
    shader->uniform("yCeiling", GlobalSettings::getInstance().ceiling);
    
//    shader->uniform("zoneRadius", GlobalSettings::getInstance().zoneRadius);
    shader->uniform("zoneRadius", GlobalSettings::getInstance().noiseZoneRadius->getValue());
    
//    shader->uniform("lowThreshold", GlobalSettings::getInstance().lowThreshold);
//    shader->uniform("highThreshold", GlobalSettings::getInstance().highThreshold);

    shader->uniform("lowThreshold", GlobalSettings::getInstance().noiseLowThreshold->getValue());
    shader->uniform("highThreshold", GlobalSettings::getInstance().noiseHighThreshold->getValue());

//    shader->uniform("repelStrength", GlobalSettings::getInstance().repelStrength);
//    shader->uniform("attractStrength", GlobalSettings::getInstance().attractStrength);
//    shader->uniform("orientStrength", GlobalSettings::getInstance().orientStrength);
    
    shader->uniform("repelStrength", GlobalSettings::getInstance().noiseRepelStrength->getValue());
    shader->uniform("attractStrength", GlobalSettings::getInstance().noiseAttractStrength->getValue());
    shader->uniform("orientStrength", GlobalSettings::getInstance().noiseOrientStrength->getValue());
    
    shader->uniform("yVelDecrease", GlobalSettings::getInstance().yVelDecrease);
//    shader->uniform("flashingRadius", GlobalSettings::getInstance().flashingRadius);
    shader->uniform("flashingRadius", GlobalSettings::getInstance().noiseFlashingRadius->getValue());
    shader->uniform("catchingSpeed", GlobalSettings::getInstance().catchingSpeed);
    shader->uniform("flashingSpeed", GlobalSettings::getInstance().flashingSpeed);
    shader->uniform("maxThetaDiff", GlobalSettings::getInstance().maxThetaDiff);
    shader->uniform("speedMutiplier", GlobalSettings::getInstance().speedMutiplier);

    texture.bind();
    gl::draw(mesh);
    texture.unbind();
    shader->unbind();
}
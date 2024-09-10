void GfxLight::update (const Vector3 &cam_pos)
{
    if (dead) THROW_DEAD(className);
    light->setPosition(to_ogre(getWorldTransform().pos));
    light->setDirection(to_ogre(getWorldTransform().removeTranslation()*Vector3(0,1,0)));
    corona->pos = getWorldTransform() * coronaLocalPos;
    Vector3 col = enabled ? fade * coronaColour : Vector3(0,0,0);
    corona->dimensions = Vector3(coronaSize, coronaSize, coronaSize);

    Vector3 light_dir_ws = (cam_pos - getWorldTransform().pos).normalisedCopy();
    Vector3 light_aim_ws_ = getWorldTransform().removeTranslation() * Vector3(0,1,0);

    float angle = light_aim_ws_.dot(light_dir_ws);
    float inner = gritcos(coronaInnerAngle);
    float outer = gritcos(coronaOuterAngle);
    if (outer != inner) {
            float occlusion = std::min(std::max((angle-inner)/(outer-inner), 0.0f), 1.0f);
            col *= (1-occlusion);
    }
    corona->diffuse = Vector3(0, 0, 0);
    corona->emissive = col;
}
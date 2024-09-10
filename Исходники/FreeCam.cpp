void FreeCam::update(gdl::Input& input, const gdl::Clock& clock)
{
    float delta;

    delta = static_cast<float>(clock.getElapsed());

    glm::ivec2 motion = input.getMouseDelta();
    _theta += (_sensivity * static_cast<float>(motion.x));
    _phi -= (_sensivity * static_cast<float>(motion.y));
    vectorsFromAngles();

    moveCam(input, delta);
}
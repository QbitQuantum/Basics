void PlanetElement::setAtmoUniforms(ShaderProgram * program) {
  updateWaveLength(program);

  QVector3D lightPosition = SceneData::Instance().getLight("sunlight")->position;
  QVector3D lightDirection = lightPosition - planet->position;
  lightDirection.normalize();

  float rayleigh = 0.0025f; // Rayleigh scattering constant
  float rayleigh4Pi = rayleigh * 4.0f * M_PI;
  float mie = 0.0010f; // Mie scattering constant
  float mie4Pi = mie * 4.0f * M_PI;
  float sun = 20.0f; // Sun brightness constant
  float g = -0.990f; // The Mie phase asymmetry factor

  //    float mieScaleDepth = 0.1f;

  program->use();
  program->setUniform("lightPosition", lightDirection);

  program->setUniform("rayleighSun", rayleigh * sun);
  program->setUniform("mieSun", mie * sun);
  program->setUniform("rayleigh4Pi", rayleigh4Pi);
  program->setUniform("mie4Pi", mie4Pi);

  program->setUniform("g", g);
  program->setUniform("g2", g * g);
  program->setUniform("useRayleigh", planet->useRayleigh);
  program->setUniform("useMie", planet->useMie);
  program->setUniform("attenuation", planet->useAttenuation);
}
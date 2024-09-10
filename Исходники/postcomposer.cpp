void PostComposer::passBloom() {
  // Pass 1 : downsample
  writeHalfBuffer->resizeViewport();
  writeHalfBuffer->bind();

  glClear(GL_COLOR_BUFFER_BIT);

  shaderBloom1->bind();
  readBuffer->bindAndTransmitTextures(shaderBloom1);

  quad->draw(shaderBloom1->attribute("position"));

  writeHalfBuffer->unbind();

  swapHalfBuffers();

  // Pass 1.b : blur
  passBlurLinear(true);

  // Pass 2 : compose + upsample
  writeBuffer->resizeViewport();
  writeBuffer->bind();

  glClear(GL_COLOR_BUFFER_BIT);

  shaderBloom2->bind();
  Texture *base = readBuffer->getTexture("texScene");
  base->bind();
  shaderBloom2->transmitUniform("texScene", base);
  Texture *bloom = readHalfBuffer->getTexture("texScene");
  bloom->bind();
  shaderBloom2->transmitUniform("texBloom", bloom);

  quad->draw(shaderBloom2->attribute("position"));

  writeBuffer->unbind();

  swapBuffers();
}
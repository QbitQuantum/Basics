void SixFringeCapture::_calculateDepthMap( Texture& unwrappedPhase )
{
  m_imageProcessor.bindDrawBuffer(m_depthMapAttachPoint);
  m_depthCalculator.uniform("scalingFactor", m_scalingFactor);
  m_depthCalculator.bind();
  unwrappedPhase.bind(GL_TEXTURE0);
  m_referencePhase.bind(GL_TEXTURE1);
  m_imageProcessor.process();
}
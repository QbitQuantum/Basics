/* virtual */
void
av::sound::openal::OpenALSoundRenderer::setListenerPosition(const ::osg::Matrix& position)
{
  ::osg::Vec3f translation;
  ::osg::Quat rotation;
  ::osg::Vec3f scale;
  ::osg::Quat scaleOrientation;

  position.decompose(translation, rotation, scale, scaleOrientation);

  ::alListenerfv(AL_POSITION, translation.ptr());
  ::osg::Matrix rotationMat;
  rotation.get(rotationMat);

  ::osg::Vec3f atAndUpVec[2];

  atAndUpVec[0] = rotationMat * ::osg::Vec3f(0.0f, 0.0f, -1.0f);
  atAndUpVec[1] = rotationMat * ::osg::Vec3f(0.0f, 1.0f, 0.0f);

  ::alListenerfv(AL_ORIENTATION, atAndUpVec[0].ptr());

  mPosition = position;
}
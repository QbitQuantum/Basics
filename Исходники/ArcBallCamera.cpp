void ArcBallCamera::updatePosition()
{
  //LOG_INFO << "m_inclination = " << m_inclination << " / m_azimuth = " << m_azimuth;
  //LOG_INFO << "BEFORE - m_position = " << m_position.x << " " << m_position.y << " " << m_position.z;

  Vec3D viewDir = m_position - m_lookAt;

  viewDir.x = sinf(m_inclination * PI / 180.) * sinf(m_azimuth * PI / 180.);
  viewDir.y = cosf(m_inclination * PI / 180.);
  viewDir.z = sinf(m_inclination * PI / 180.) * cosf(m_azimuth * PI / 180.);

  viewDir.normalize();
  m_position = viewDir * m_distance + m_lookAt;

  //LOG_INFO << "AFTER - m_position = " << m_position.x << " " << m_position.y << " " << m_position.z;
}
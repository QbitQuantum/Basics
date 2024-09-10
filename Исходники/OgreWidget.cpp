void  OgreWidget::mouseMoveEvent(QMouseEvent * e)
{
  if (m_oldPos != InvalidMousePoint)
    {
      Ogre::Real deltaX = e->pos().x() - m_oldPos.x();
      Ogre::Real deltaY = e->pos().y() - m_oldPos.y();

      if (m_mouseButtonsPressed.testFlag(Qt::MiddleButton))
        {
          if(e->modifiers().testFlag(Qt::ControlModifier))
            m_camera->zoom(-deltaY);
          else if (e->modifiers().testFlag(Qt::ShiftModifier))
            m_camera->rotate(deltaX, -deltaY);
          else
            m_camera->shift(-deltaX, -deltaY);
        }
      else if (m_mouseButtonsPressed.testFlag(Qt::LeftButton) && !m_selectionManager.isEmpty())
        {
          if (m_constraintedX && e->modifiers().testFlag(Qt::ShiftModifier))
            m_selectionManager.pitch(Ogre::Degree(deltaX));
          else if (m_constraintedY && e->modifiers().testFlag(Qt::ShiftModifier))
            m_selectionManager.yaw(Ogre::Degree(deltaX));
          else if (m_constraintedZ && e->modifiers().testFlag(Qt::ShiftModifier))
            m_selectionManager.roll(Ogre::Degree(deltaX));
          else
            {
              Ogre::Plane plane;

              if (m_constraintedX)
                plane.redefine(Ogre::Vector3(1, 0, 0), m_selectionManager.getPosition());
              else if (m_constraintedY)
                plane.redefine(Ogre::Vector3(0, 1, 0), m_selectionManager.getPosition());
              else if (m_constraintedZ)
                plane.redefine(Ogre::Vector3(0, 0, 1), m_selectionManager.getPosition());

              Ogre::Ray                   oldRay = m_camera->getCamera()->getCameraToViewportRay(e->pos().x() / (float)width(), e->pos().y() / (float)height());
              Ogre::Ray                   ray = m_camera->getCamera()->getCameraToViewportRay(m_oldPos.x() / (float)width(), m_oldPos.y() / (float)height());
              std::pair<bool, Ogre::Real> oldResult = oldRay.intersects(plane);
              std::pair<bool, Ogre::Real> result = ray.intersects(plane);

              if (result.first && oldResult.first)
                {
                  Ogre::Vector3 point;

                  point = oldRay.getPoint(oldResult.second) - ray.getPoint(result.second);
                  m_selectionManager.translate(point.x, point.y, point.z);
                }
            }
          emit itemMoved();
        }
      m_oldPos = e->pos();

      update();
      e->accept();
    }
  else
    {
      e->ignore();
    }
}
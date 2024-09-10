void
ClipGrabber::mouseMoveEvent(QMouseEvent* const event,
			    Camera* const camera)
{
  if (!m_pressed)
    return;
  
  QPoint delta = event->pos() - m_prevPos;

  Vec voxelScaling = Global::voxelScaling();

  Vec tang = m_tang;
  Vec xaxis = m_xaxis;
  Vec yaxis = m_yaxis;
  tang = Matrix::rotateVec(m_xform, tang);
  xaxis = Matrix::rotateVec(m_xform, xaxis);
  yaxis = Matrix::rotateVec(m_xform, yaxis);

  if (event->buttons() != Qt::LeftButton)
    {
      tang = VECDIVIDE(tang, voxelScaling);
      xaxis = VECDIVIDE(xaxis, voxelScaling);
      yaxis = VECDIVIDE(yaxis, voxelScaling);

      Vec trans(delta.x(), -delta.y(), 0.0f);
      
      // Scale to fit the screen mouse displacement
      trans *= 2.0 * tan(camera->fieldOfView()/2.0) *
	             fabs((camera->frame()->coordinatesOf(Vec(0,0,0))).z) /
	             camera->screenHeight();

      // Transform to world coordinate system.
      trans = camera->frame()->orientation().rotate(trans);

      Vec voxelScaling = Global::voxelScaling();
      trans = VECDIVIDE(trans, voxelScaling);

      if (event->modifiers() & Qt::ControlModifier ||
	  event->modifiers() & Qt::MetaModifier)
	{
	  if (moveAxis() < MoveY0)
	    {
	      float vx = trans*m_xaxis;
	      if (moveAxis() == MoveX0)
		setScale1(scale1() + 0.05*vx);
	      else
		setScale1(scale1() - 0.05*vx);
	    }
	  else if (moveAxis() < MoveZ)
	    {
	      float vy = trans*m_yaxis;
	      if (moveAxis() == MoveY0)
		setScale2(scale2() + 0.05*vy);
	      else
		setScale2(scale2() - 0.05*vy);
	    }
	}
      else
	{
	  if (moveAxis() < MoveY0)
	    {
	      float vx = trans*xaxis;
	      trans = vx*xaxis;
	    }
	  else if (moveAxis() < MoveZ)
	    {
	      float vy = trans*yaxis;
	      trans = vy*yaxis;
	    }
	  else if (moveAxis() == MoveZ)
	    {
	      float vz = trans*tang;
	      trans = vz*tang;
	    }
	  
	  translate(trans);
	}
    }
  else
    {
      Vec axis;
      if (moveAxis() < MoveY0) axis = xaxis;
      else if (moveAxis() < MoveZ) axis = yaxis;
      else if (moveAxis() == MoveZ) axis = tang;

      Vec voxelScaling = Global::voxelScaling();
      Vec pos = VECPRODUCT(position(), voxelScaling);
      pos = Matrix::xformVec(m_xform, pos);

      float r = size();
      Vec trans(delta.x(), -delta.y(), 0.0f);

      Vec p0 = camera->projectedCoordinatesOf(pos); p0 = Vec(p0.x, p0.y, 0);
      Vec c0 = pos + r*axis;
      c0 = camera->projectedCoordinatesOf(c0); c0 = Vec(c0.x, c0.y, 0);
      Vec perp = c0-p0;
      perp = Vec(-perp.y, perp.x, 0);
      perp.normalize();

      float angle = perp * trans;
      rotate(axis, angle);
    }

  m_prevPos = event->pos();
}
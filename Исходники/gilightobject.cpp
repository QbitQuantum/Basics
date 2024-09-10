void
GiLightObject::computeTangents()
{
  m_xaxis.clear();
  m_yaxis.clear();
  m_tgP.clear();

  int nkf = m_points.count();
  if (nkf < 2)
    {
      m_xaxis << Vec(1,0,0);
      m_yaxis << Vec(0,1,0);
      m_tgP << Vec(0,0,1);
      return;
    }

  Vec pxaxis = Vec(1,0,0);
  Vec ptang = Vec(0,0,1);

  for(int kf=0; kf<nkf; kf++)
    {
      Vec prevP, nextP;

      if (kf == 0)
	{	  
	  prevP = m_points[kf];
	}
      else
	prevP = m_points[kf-1];

      if (kf == nkf-1)
	{
	  nextP = m_points[kf];
	}
      else
	nextP = m_points[kf+1];
      
      Vec tgP = 0.5*(nextP - prevP);
      m_tgP.append(tgP);

      //-------------------
      tgP.normalize();
      Vec xaxis, yaxis;
      Vec axis;
      float angle;      
      StaticFunctions::getRotationBetweenVectors(ptang, tgP, axis, angle);
      if (qAbs(angle) > 0.0 && qAbs(angle) < 3.1415)
	{
	  Quaternion q(axis, angle);	  
	  xaxis = q.rotate(pxaxis);
	}
      else
	xaxis = pxaxis;

      yaxis = tgP^xaxis;

      m_xaxis.append(xaxis);
      m_yaxis.append(yaxis);

      pxaxis = xaxis;
      ptang = tgP;
      //-------------------
    } 
}
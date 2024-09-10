QGradientStops
SplineInformation::interpolateGradientStops(QGradientStops stops1,
					    QGradientStops stops2,
					    float frc)
{
  QVector<float> pos; 

  for(int i=0; i<stops1.size(); i++)
    pos.append(stops1[i].first);

  for(int i=0; i<stops2.size(); i++)
    {
      float pos2 = stops2[i].first;
      bool flag = true;
      for(int j=0; j<stops1.size(); j++)
	{
	  if (fabs(pos[j] - pos2) < 0.0001)
	    {
	      flag = false;
	      break;
	    }
	}
      if (flag)
	pos.append(pos2);
    }

  qSort(pos.begin(), pos.end());

  QGradientStops gradStops1 = StaticFunctions::resampleGradientStops(stops1);
  QGradientStops gradStops2 = StaticFunctions::resampleGradientStops(stops2);

  QGradientStops gradStops;
  int gsize = gradStops1.size()-1;
  for(int i=0; i<pos.size(); i++)
    {
      int idx = pos[i]*gsize;
      QColor color1 = gradStops1[idx].second;
      QColor color2 = gradStops2[idx].second;

      // linear interpolation of colors
      float rb,gb,bb,ab, re,ge,be,ae;
      rb = color1.red();
      gb = color1.green();
      bb = color1.blue();
      ab = color1.alpha();
      re = color2.red();
      ge = color2.green();
      be = color2.blue();
      ae = color2.alpha();
      
      float r,g,b,a;
      r = rb + frc*(re-rb);
      g = gb + frc*(ge-gb);
      b = bb + frc*(be-bb);
      a = ab + frc*(ae-ab);


      QColor color = QColor(r,g,b,a);
      gradStops << QGradientStop(pos[i], color);
    }

  return gradStops;
}
bool calculateWheelSpeed(Position a, Position b)
{
	double edelta = principleValue(a.getTheta() - a.deltaAngle(b));
	double etheta = principleValue(b.getTheta() - a.deltaAngle(b));
  
	double edistance = a.distance(b);
  if(edistance<tolerate_distance && fabs(etheta)<tolerate_angle && fabs(edelta)<tolerate_angle)
    return true;
  //Serial.println(edelta);
 // Serial.println(etheta);
  //Serial.println(edistance);
	double k1 = 1;
	double k2 = 10;
	double lambda = 2;
	double beta = 0.4;
	double Vmax = 90;// mm/s
	double wheelRadius = 34; //mm
	double wheelGap = 340; //mm
	if(edistance==0)
    edistance = 0.0001;
	double K = - (k2*(edelta - atan(-k1*etheta)) + (1+k1/(1+pow(k1*etheta,2)))*sin(edelta))/edistance;
	
	double v = Vmax/(1+beta*pow(fabs(K),lambda));
	double omega = K*v;
 /* double sat = 1;
  if(omega>=sat)
    omega = sat;
  if(omega<=-sat)
    omega = -sat;*/
	
  TOMEGA[0] =(2*v - wheelGap*omega)/(2*wheelRadius);//wL in radian
  TOMEGA[1] =(2*v + wheelGap*omega)/(2*wheelRadius);//wR in radian 

  
  
    return false;	
}
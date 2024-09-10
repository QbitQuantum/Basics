/* fast intersection function between ray/cylinder */
int intersect_cylinder(const Cylinder& cylinder, const TVector& position, 
			     const TVector& direction, double& lamda, 
			     TVector& pNormal, TVector& newposition) {

  TVector RC;
  double d;
  double t,s;
  TVector n,O;
  double ln;
  double in,out;

  TVector::subtract(position,cylinder._Position,RC);
  TVector::cross(direction,cylinder._Axis,n);
  
  ln = n.mag();
  if ( (ln<ZERO)&&(ln>-ZERO) ) 
    return 0;
  
  n.unit();
  
  d = fabs( RC.dot(n) );

  if (d <= cylinder._Radius) {
    TVector::cross(RC,cylinder._Axis,O);
    t = - O.dot(n)/ln;
    TVector::cross(n,cylinder._Axis,O);
    O.unit();
    s = fabs( sqrt(cylinder._Radius * cylinder._Radius - d*d) / 
	      direction.dot(O) );
    
    in = t-s;
    out = t+s;
    if (in<-ZERO) {
      if (out<-ZERO) return 0;
      else lamda = out;
    }
    else
      if (out<-ZERO) {
	lamda = in;
      }
      else
	if (in<out) lamda = in;
	else lamda=out;
    
    newposition = position+direction*lamda;
    TVector HB = newposition-cylinder._Position;
    pNormal = HB - cylinder._Axis*(HB.dot(cylinder._Axis));
    pNormal.unit();
    
    return 1;
  }
  
  return 0;
}
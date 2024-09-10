bool TransformWidget::Hover(int x,int y,Camera::Viewport& viewport,double& distance)
{
  Real globalScale = 1.0;
  if(scaleToScreen) {
    float sx,sy,sz;
    viewport.project(T.t,sx,sy,sz);
    globalScale = sz/viewport.scale;
  }
  distance = Inf;
  int oldHoverItem = hoverItem;
  hoverItem = -1;
  Ray3D r;
  viewport.getClickSource(x,y,r.source);
  viewport.getClickVector(x,y,r.direction);
  //check origin
  if(enableTranslation && enableOriginTranslation) {
    Sphere3D s;
    s.center = T.t;
    s.radius = originRadius*globalScale;
    Real tmin,tmax;
    if(s.intersects(r,&tmin,&tmax)) {
      distance = tmin;
      hoverItem = 0;
    }
  }
  //check translation axes
  for(int i=0;i<3;i++) {
    if(!enableTranslation) break;
    if(!enableTranslationAxes[i]) continue;
    Line3D axisLine;
    axisLine.source = T.t;
    axisLine.direction = Vector3(T.R.col(i));
    Real t,u;
    axisLine.closestPoint(r,t,u);
    t = Clamp(t,0.0,axisLength*globalScale);
    u = Clamp(u,0.0,Inf);
    Vector3 paxis,pray;
    axisLine.eval(t,paxis);
    r.eval(u,pray);
    if(paxis.distanceSquared(pray) <= Sqr(axisRadius*globalScale)) {
      if(u < distance) {
	distance = u;
	hoverItem = 1+i;
      }
    }
  }
  if(enableRotation) {
    //check rotation rings
    Circle3D c;
    c.center = T.t;
    for(int i=0;i<3;i++) {
      if(!enableRotationAxes[i]) continue;
      c.axis = Vector3(T.R.col(i));
      c.radius = ringOuterRadius*globalScale;
      Real t;
      if(c.intersects(r,&t) && t >= 0) {
	c.radius = ringInnerRadius*globalScale;
	if(!c.intersects(r,NULL)) {
	  if(t < distance) {
	    distance = t;
	    hoverItem = i+4;
	  }
	}
      }
    }
  }
  if(enableRotation && enableOuterRingRotation) {
    //check outer ring
    Circle3D c;
    c.center = T.t;
    viewport.getViewVector(c.axis);
    c.radius = (ringOuterRadius+arrowHeight)*globalScale;
    Real t;
    if(c.intersects(r,&t) && t >= 0) {
      c.radius = (ringInnerRadius+arrowHeight)*globalScale;
      if(!c.intersects(r,NULL)) {
	if(t < distance) {
	  distance = t;
	  hoverItem = 7;
	}
      }
    }
    clickAxis = c.axis;
  }
  if(hoverItem != oldHoverItem) Refresh();
  r.eval(distance,hoverPos);
  return hoverItem != -1;
}
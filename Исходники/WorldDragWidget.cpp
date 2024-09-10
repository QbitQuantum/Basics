bool WorldDragWidget::Hover(int x,int y,Camera::Viewport& viewport,double& distance)
{
  if(!active) return false;
  Ray3D r;
  viewport.getClickSource(x,y,r.source);
  viewport.getClickVector(x,y,r.direction);
  hoverID = -1;
  distance = Inf;
  if(robotsActive) {
    int body;
    Vector3 localpt;
    Robot* rob = world->RayCastRobot(r,body,localpt);
    if(rob) {
      hoverPt = localpt;
      int index = -1;
      for(size_t i=0;i<world->robots.size();i++)
	if(rob == (Robot*)world->robots[i]) { index=(int)i; break; }
      hoverID = world->RobotLinkID(index,body);
      const Geometry::AnyCollisionGeometry3D* geom = world->GetGeometry(hoverID);
      Vector3 worldpt = geom->GetTransform()*localpt;
      distance = worldpt.distance(r.source);
      dragPt = worldpt;
    }
  }
  if(objectsActive) {
    Vector3 localpt;
    RigidObject* obj = world->RayCastObject(r,localpt);
    if(obj) {
      Vector3 worldpt = obj->T*localpt;
      Real d=worldpt.distance(r.source);
      if(d < distance) {
	distance = d;
	hoverPt = localpt;
	int index = -1;
	for(size_t i=0;i<world->rigidObjects.size();i++)
	  if(obj == (RigidObject*)world->rigidObjects[i]) { index=(int)i; break; }
	hoverID = world->RigidObjectID(index);
	dragPt = worldpt;
      }
    }
  }
  hoverDistance = distance;
  if(hoverID >= 0)  {
    return true;
  }
  return false;
}
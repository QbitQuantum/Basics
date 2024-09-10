  HyperGraphElementAction* EdgeSE2Landmark_malcolmDrawAction::operator()(HyperGraph::HyperGraphElement* element, 
               HyperGraphElementAction::Parameters* params_){
// 	  std::cout << "DRAW up :D" << std::endl;exit(0);
    if (typeid(*element).name()!=_typeName){
		std::cout << "Wrong name :(" <<std::endl;;
      return 0;
	}
	
// 	refreshPropertyPtrs(params_);
//     if (! _previousParams)
//       return this;
//     
//     if (_show && !_show->value())
//       return this;
// 
// 	EdgeSE2Prior* e =  static_cast<EdgeSE2Prior*>(element);
//     VertexSE2* fromEdge = static_cast<VertexSE2*>(e->vertex(0));
//     VertexSE2* toEdge   = static_cast<VertexSE2*>(e->vertex(1));
// //     EdgeSE2PointXY* e =  static_cast<EdgeSE2PointXY*>(element);
// //     VertexSE2* fromEdge = static_cast<VertexSE2*>(e->vertex(0));
// //     VertexPointXY* toEdge   = static_cast<VertexPointXY*>(e->vertex(1));
//     if (! fromEdge)
//       return this;
//     Vector3D p3d=e->measurement().toVector();
// 	Vector2D p;
// 	p << p3d(0), p3d(1);
//     glPushAttrib(GL_ENABLE_BIT|GL_LIGHTING|GL_COLOR);
//     glDisable(GL_LIGHTING);
//     if (!toEdge){
//       p=fromEdge->estimate()/*.toVector()*/*p;
//       glColor3f(LANDMARK_EDGE_GHOST_COLOR);
//       glPushAttrib(GL_POINT_SIZE);
//       glPointSize(3);
//       glBegin(GL_POINTS);
//       glVertex3f((float)p.x(),(float)p.y(),0.f);
//       glEnd();
//       glPopAttrib();
//     } else {
//       p=toEdge->estimate().toVector();
//       glColor3f(LANDMARK_EDGE_COLOR);
//     }
//     glBegin(GL_LINES);
//     glVertex3f((float)fromEdge->estimate().translation().x(),(float)fromEdge->estimate().translation().y(),0.f);
//     glVertex3f((float)p.x(),(float)p.y(),0.f);
//     glEnd();
//     glPopAttrib();
//     return this;

    refreshPropertyPtrs(params_);
    if (! _previousParams)
      return this;
    
    if (_show && !_show->value())
      return this;

    EdgeSE2Landmark_malcolm* e =  static_cast<EdgeSE2Landmark_malcolm*>(element);
    VertexSE2* from = static_cast<VertexSE2*>(e->vertex(0));
    VertexSE2* to   = static_cast<VertexSE2*>(e->vertex(1));
    if (! from && ! to)
      return this;
    SE2 fromTransform;
    SE2 toTransform;
    glPushAttrib(GL_ENABLE_BIT | GL_LIGHTING | GL_COLOR);
    glDisable(GL_LIGHTING);
    if (! from) {
      glColor3f(POSE_EDGE_LANDMARK_MALCOLM_GHOST_COLOR);
      toTransform = to->estimate();
      fromTransform = to->estimate()*e->measurement().inverse();
      // DRAW THE FROM EDGE AS AN ARROW
      glPushMatrix();
      glTranslatef((float)fromTransform.translation().x(), (float)fromTransform.translation().y(),0.f);
      glRotatef((float)RAD2DEG(fromTransform.rotation().angle()),0.f,0.f,1.f);
      opengl::drawArrow2D((float)_triangleX->value(), (float)_triangleY->value(), (float)_triangleX->value()*.3f);
      glPopMatrix();
    } else if (! to){
      glColor3f(POSE_EDGE_LANDMARK_MALCOLM_GHOST_COLOR);
      fromTransform = from->estimate();
      toTransform = from->estimate()*e->measurement();
      // DRAW THE TO EDGE AS AN ARROW
      glPushMatrix();
      glTranslatef(toTransform.translation().x(),toTransform.translation().y(),0.f);
      glRotatef((float)RAD2DEG(toTransform.rotation().angle()),0.f,0.f,1.f);
      opengl::drawArrow2D((float)_triangleX->value(), (float)_triangleY->value(), (float)_triangleX->value()*.3f);
      glPopMatrix();
    } else {
      glColor3f(POSE_EDGE_LANDMARK_MALCOLM_COLOR);
      fromTransform = from->estimate();
      toTransform = to->estimate();
    }
    glBegin(GL_LINES);
    glVertex3f((float)fromTransform.translation().x(),(float)fromTransform.translation().y(),0.f);
    glVertex3f((float)toTransform.translation().x(),(float)toTransform.translation().y(),0.f);
    glEnd();
    glPopAttrib();
    return this;
  }
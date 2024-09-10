void UtilGL::drawArrow(const Vector3 &a,const Vector3 &u,double radius,const string &s1,const string &s2,double arrowRatio) {
  Vector3 to;
  to.set(a+u*(1.0-arrowRatio));

  glPushMatrix();

  glPushMatrix();
  glTranslatef(a.x(),a.y(),a.z());
  if (!s1.empty()) {
    draw(s1,Vector3(0,0,0));
  }
  glPopMatrix();


  glPushMatrix();
  Quaternion q;
  q.set(Vector3(0,0,1),u);
  double angle;Vector3 axe;
  q.copyToAngleAxis(&angle,&axe);
  glTranslatef(a.x(),a.y(),a.z());
  glRotatef(angle,axe.x(),axe.y(),axe.z());
  glScalef(radius,radius,(to-a).length());
  drawCylinder();
  glPopMatrix();

  if (u.length()>0.0001) {
  glPushMatrix();
  glTranslatef((a+u).x(),(a+u).y(),(a+u).z());

  glPushMatrix();
  if (!s2.empty()) {
    draw(s2,Vector3(0.2*arrowRatio*u.length(),0.03,0));
  }
  glPopMatrix();

  glPopMatrix();

  glPushMatrix();
  glTranslatef(to.x(),to.y(),to.z());
  Matrix4 m;
  m.setRotation(Vector3(0,0,1),u);
  glMultMatrixf(m.fv());



  drawCone(radius*(2.0-arrowRatio),u.length()*arrowRatio);




  glPopMatrix();
  }

  glPopMatrix();

}